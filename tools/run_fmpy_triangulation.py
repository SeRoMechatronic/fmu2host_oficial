#!/usr/bin/env python3
"""Triangulate the six anomalous FMUs with the independent FMPy importer.

The behavioral scenarios are reused unchanged.  FMPy supplies the importer,
FMI lifecycle and numerical driver; the FMU binary itself is necessarily the
same exported implementation used by the generated hosts.
"""

from __future__ import annotations

import csv
import importlib.util
import json
import re
import sys
import traceback
from datetime import datetime, timezone
from pathlib import Path

import numpy as np
from fmpy import __version__ as fmpy_version
from fmpy import read_model_description, simulate_fmu

TOOLS_DIR = Path(__file__).resolve().parent
ROOT = TOOLS_DIR.parent
sys.path.insert(0, str(TOOLS_DIR))

from full_test_runner import evaluate_check
from oracle_scope import MODE_INDEPENDENT, classify_check
from run_all_tests import discover_configs


TARGETS = {
    "ArraysVectores",
    "BooleanLogica",
    "ContadorEventos",
    "EtapaSecuenciador",
    "MatrizEstado",
    "ValoresExtremos",
}


def load_config(path: Path) -> dict:
    spec = importlib.util.spec_from_file_location(f"fmpy_{path.stem}", path)
    module = importlib.util.module_from_spec(spec)
    assert spec and spec.loader
    spec.loader.exec_module(module)
    return module.CONFIG


def canonical(name: str) -> str:
    return re.sub(r"[^a-z0-9]", "", name.lower())


def _traceback_tail() -> list[str]:
    """Return a short traceback without publishing the local user profile path."""
    text = traceback.format_exc()
    home = str(Path.home())
    text = text.replace(home, "<user-home>")
    text = text.replace(home.replace("\\", "/"), "<user-home>")
    return text.splitlines()[-5:]


def name_index(variables) -> dict[str, str]:
    """Map host-safe and FMI spellings to an unambiguous FMI variable name."""
    groups: dict[str, list[str]] = {}
    for variable in variables:
        groups.setdefault(canonical(variable.name), []).append(variable.name)
    result = {variable.name: variable.name for variable in variables}
    for key, names in groups.items():
        if len(names) == 1:
            result[key] = names[0]
    return result


def resolve(index: dict[str, str], name: str) -> str | None:
    return index.get(name) or index.get(canonical(name))


def numpy_dtype(fmi_type: str):
    return {
        "Boolean": np.bool_,
        "Integer": np.int32,
        "Enumeration": np.int32,
        "String": object,
    }.get(fmi_type, np.float64)


def make_input(test: dict, variables, index: dict[str, str]):
    by_name = {variable.name: variable for variable in variables}
    requested = set(test.get("inputs", {})) | set(test.get("schedule", {}))
    supported: dict[str, str] = {}
    unsupported: list[dict] = []
    for host_name in sorted(requested):
        actual = resolve(index, host_name)
        if actual is None:
            unsupported.append({"requested": host_name, "reason": "not declared"})
        elif by_name[actual].causality != "input":
            unsupported.append(
                {
                    "requested": host_name,
                    "fmi_name": actual,
                    "causality": by_name[actual].causality,
                    "reason": "not FMI-settable input metadata",
                }
            )
        else:
            supported[host_name] = actual

    if not supported:
        return None, unsupported

    times = {0.0, float(test.get("t_end", 1.0))}
    for host_name, entries in test.get("schedule", {}).items():
        if host_name in supported:
            times.update(float(t) for t, _ in entries)
    times = sorted(times)
    dtype = [("time", np.float64)]
    for actual in dict.fromkeys(supported.values()):
        dtype.append((actual, numpy_dtype(by_name[actual].type)))
    trajectory = np.zeros(len(times), dtype=dtype)
    trajectory["time"] = times

    for host_name, actual in supported.items():
        initial = test.get("inputs", {}).get(host_name, 0)
        schedule = sorted(test.get("schedule", {}).get(host_name, []))
        values = []
        for time in times:
            value = initial
            for change_time, change_value in schedule:
                if float(change_time) <= time:
                    value = change_value
                else:
                    break
            values.append(value)
        trajectory[actual] = values
    return trajectory, unsupported


def simulate(test: dict, fmu_path: Path, description, mode: str, index: dict[str, str]):
    applicable = []
    for check_number, check in enumerate(test.get("checks", [])):
        if check.get("mode") not in (None, mode.lower()):
            continue
        solver = test.get("solver", "rk4") if mode == "ModelExchange" else None
        if check.get("solver") not in (None, solver):
            continue
        scope, rationale = classify_check(description.modelName, test, check)
        if scope == MODE_INDEPENDENT:
            applicable.append((check_number, check, rationale))

    outputs: list[str] = []
    unresolved_outputs: list[str] = []
    output_map: dict[str, str] = {}
    for _, check, _ in applicable:
        host_name = check.get("col", "")
        actual = resolve(index, host_name)
        if actual is None:
            unresolved_outputs.append(host_name)
        else:
            output_map[host_name] = actual
            if actual not in outputs:
                outputs.append(actual)

    input_data, unsupported_inputs = make_input(test, description.modelVariables, index)
    try:
        kwargs = {
            "filename": fmu_path,
            "validate": False,
            "start_time": 0.0,
            "stop_time": float(test.get("t_end", 1.0)),
            "output_interval": float(test.get("h", 0.01)),
            "relative_tolerance": 1e-6,
            "fmi_type": mode,
            "input": input_data,
            "output": outputs,
            "record_events": True,
            "model_description": description,
        }
        if mode == "ModelExchange":
            # A fixed-step driver avoids retry storms when an anomalous FMU
            # rejects an otherwise legal setter call.  It also makes each FMI
            # call sequence directly auditable.
            kwargs["solver"] = "Euler"
            kwargs["step_size"] = float(test.get("h", 0.01))
        else:
            kwargs["step_size"] = float(test.get("h", 0.01))
        result = simulate_fmu(**kwargs)
        rows = []
        for sample in result:
            row = {"t": float(sample["time"])}
            for host_name, actual in output_map.items():
                value = sample[actual]
                row[host_name] = float(value) if not isinstance(value, str) else value
            rows.append(row)
    except Exception as exc:
        return {
            "execution": "error",
            "error_type": type(exc).__name__,
            "error": str(exc),
            "traceback_tail": _traceback_tail(),
            "unsupported_inputs": unsupported_inputs,
            "unresolved_outputs": sorted(set(unresolved_outputs)),
            "checks_defined": len(applicable),
            "checks_evaluated": 0,
            "checks_pass": 0,
            "checks_fail": 0,
        }

    outcomes = []
    for check_number, check, rationale in applicable:
        if check.get("col", "") in unresolved_outputs:
            outcomes.append(
                {
                    "index": check_number,
                    "passed": False,
                    "detail": "FMI variable name could not be resolved",
                    "scope_rationale": rationale,
                }
            )
            continue
        passed, detail = evaluate_check(check, rows)
        outcomes.append(
            {
                "index": check_number,
                "type": check.get("type", "at_t"),
                "column": check.get("col", ""),
                "passed": bool(passed),
                "detail": detail,
                "scope_rationale": rationale,
            }
        )
    return {
        "execution": "ok",
        "samples": len(rows),
        "unsupported_inputs": unsupported_inputs,
        "unresolved_outputs": sorted(set(unresolved_outputs)),
        "checks_defined": len(applicable),
        "checks_evaluated": len(outcomes),
        "checks_pass": sum(item["passed"] for item in outcomes),
        "checks_fail": sum(not item["passed"] for item in outcomes),
        "oracle_pass": all(item["passed"] for item in outcomes) if outcomes else None,
        "check_outcomes": outcomes,
    }


def aggregate(records: list[dict], mode: str) -> dict:
    values = [record[mode] for record in records if mode in record]
    return {
        "scenarios_attempted": len(values),
        "execution_ok": sum(value["execution"] == "ok" for value in values),
        "execution_error": sum(value["execution"] == "error" for value in values),
        "checks_defined": sum(value.get("checks_defined", 0) for value in values),
        "checks_evaluated": sum(value.get("checks_evaluated", 0) for value in values),
        "checks_pass": sum(value.get("checks_pass", 0) for value in values),
        "checks_fail": sum(value.get("checks_fail", 0) for value in values),
        "oracle_pass_scenarios": sum(value.get("oracle_pass") is True for value in values),
    }


def main() -> int:
    configs = {
        load_config(path)["model_name"]: (path, load_config(path))
        for path in discover_configs(ROOT / "examples")
        if load_config(path)["model_name"] in TARGETS
    }
    records = []
    importer = []
    for model in sorted(TARGETS):
        path, config = configs[model]
        fmu_path = next((ROOT / "models").rglob(f"{model}.fmu"))
        print(f"{model}:", flush=True)
        try:
            description = read_model_description(fmu_path, validate=False)
        except Exception as exc:
            importer.append(
                {
                    "model": model,
                    "status": "rejected",
                    "error_type": type(exc).__name__,
                    "error": str(exc),
                }
            )
            print(f"  importer rejected metadata: {exc}", flush=True)
            continue
        importer.append({"model": model, "status": "accepted"})
        index = name_index(description.modelVariables)
        for test in config["tests"]:
            record = {"model": model, "scenario": test["id"], "title": test["title"]}
            if description.modelExchange:
                record["me"] = simulate(test, fmu_path, description, "ModelExchange", index)
            if description.coSimulation:
                record["cs"] = simulate(test, fmu_path, description, "CoSimulation", index)
            records.append(record)
        print(f"  {len(config['tests'])} scenarios attempted", flush=True)

    summary = {
        "schema_version": 1,
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "fmpy_version": fmpy_version,
        "scope": sorted(TARGETS),
        "independence_boundary": (
            "FMPy supplies an independent importer, lifecycle implementation, and "
            "simulation driver; the exported FMU implementation is shared."
        ),
        "importer": importer,
        "me": aggregate(records, "me"),
        "cs": aggregate(records, "cs"),
        "records": records,
    }
    out = ROOT / "results" / "fmpy_triangulation"
    out.mkdir(parents=True, exist_ok=True)
    (out / "triangulation.json").write_text(
        json.dumps(summary, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    with (out / "triangulation.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            ["model", "scenario", "mode", "execution", "checks_defined", "checks_pass", "checks_fail", "unsupported_inputs"]
        )
        for record in records:
            for mode in ("me", "cs"):
                if mode not in record:
                    continue
                value = record[mode]
                writer.writerow(
                    [record["model"], record["scenario"], mode, value["execution"], value.get("checks_defined", 0), value.get("checks_pass", 0), value.get("checks_fail", 0), json.dumps(value.get("unsupported_inputs", []), ensure_ascii=False)]
                )

    rejected = [item for item in importer if item["status"] == "rejected"]
    me, cs = summary["me"], summary["cs"]
    lines = [
        "# FMPy triangulation of the six anomalous FMUs",
        "",
        f"FMPy version: `{fmpy_version}`.",
        "",
        "FMPy provides an independent XML importer, FMI lifecycle and simulation driver. "
        "The FMU implementation binary remains shared, so this is triangulation of importing "
        "and orchestration rather than a second model implementation.",
        "",
        "| Mode | Scenarios attempted | Executed | Execution errors | Checks evaluated | Passed | Failed |",
        "|---|---:|---:|---:|---:|---:|---:|",
        f"| ME (fixed-step Euler driver) | {me['scenarios_attempted']} | {me['execution_ok']} | {me['execution_error']} | {me['checks_evaluated']} | {me['checks_pass']} | {me['checks_fail']} |",
        f"| CS | {cs['scenarios_attempted']} | {cs['execution_ok']} | {cs['execution_error']} | {cs['checks_evaluated']} | {cs['checks_pass']} | {cs['checks_fail']} |",
        "",
        "## Importer findings",
        "",
    ]
    if rejected:
        for item in rejected:
            lines.append(f"- `{item['model']}` was rejected before instantiation: {item['error']}")
    else:
        lines.append("All six model descriptions were accepted.")
    lines.extend(
        [
            "",
            "Unsupported requested inputs are preserved per scenario in the JSON/CSV. "
            "They expose cases where the battery requests a variable whose FMI causality is `local`.",
            "",
        ]
    )
    (out / "README.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"ME {me}; CS {cs}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
