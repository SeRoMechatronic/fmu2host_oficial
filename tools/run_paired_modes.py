#!/usr/bin/env python3
"""Run every configured scenario through both generated FMI execution modes.

The historical suite contains model-specific oracles that were designed for a
particular mode and, for some scenarios, a particular ME integrator.  This
script deliberately keeps those oracles unchanged and reports their outcomes
separately for ME and CS.  It is therefore a diagnostic paired-mode study, not
a claim that the two numerical methods must produce pointwise-identical traces.
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import os
import platform
import sys
from datetime import datetime, timezone
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
ROOT = TOOLS_DIR.parent
sys.path.insert(0, str(TOOLS_DIR))

from full_test_runner import evaluate_check, locate_exe, run_sim
from oracle_scope import MODE_INDEPENDENT, classify_check
from run_all_tests import discover_configs


def load_config(path: Path) -> dict:
    spec = importlib.util.spec_from_file_location(f"paired_{path.stem}", path)
    module = importlib.util.module_from_spec(spec)
    assert spec and spec.loader
    spec.loader.exec_module(module)
    return module.CONFIG


def applicable_checks(test: dict, mode: str, solver: str | None) -> list[tuple[int, dict]]:
    selected = []
    for index, check in enumerate(test.get("checks", [])):
        if check.get("mode") not in (None, mode):
            continue
        if check.get("solver") not in (None, solver):
            continue
        selected.append((index, check))
    return selected


def evaluate(model: str, test: dict, mode: str, executable: Path | None) -> dict:
    solver = test.get("solver", "rk4") if mode == "me" else None
    checks = applicable_checks(test, mode, solver)
    scoped = [
        (index, check, *classify_check(model, test, check))
        for index, check in checks
    ]
    mi_defined = sum(scope == MODE_INDEPENDENT for _, _, scope, _ in scoped)
    if executable is None:
        return {
            "execution": "missing",
            "error": "generated executable not found",
            "checks_pass": 0,
            "checks_fail": len(checks),
            "oracle_pass": False,
            "mode_independent_checks_defined": mi_defined,
            "mode_independent_checks_evaluated": 0,
            "mode_independent_checks_pass": 0,
            "mode_independent_checks_fail": 0,
            "mode_independent_checks_not_evaluated": mi_defined,
            "mode_independent_oracle_pass": False if mi_defined else None,
            "check_outcomes": [],
        }

    rows, error = run_sim(
        executable,
        test.get("t_end", 1.0),
        test.get("h", 0.01),
        solver,
        test.get("inputs", {}),
        test.get("schedule", {}),
    )
    if rows is None:
        return {
            "execution": "error",
            "error": error,
            "checks_pass": 0,
            "checks_fail": len(checks),
            "oracle_pass": False,
            "mode_independent_checks_defined": mi_defined,
            "mode_independent_checks_evaluated": 0,
            "mode_independent_checks_pass": 0,
            "mode_independent_checks_fail": 0,
            "mode_independent_checks_not_evaluated": mi_defined,
            "mode_independent_oracle_pass": False if mi_defined else None,
            "check_outcomes": [],
        }

    outcomes = []
    check_outcomes = []
    for index, check, scope, rationale in scoped:
        ok, detail = evaluate_check(check, rows)
        outcomes.append((ok, detail))
        check_outcomes.append(
            {
                "index": index,
                "type": check.get("type", "at_t"),
                "column": check.get("col", ""),
                "scope": scope,
                "scope_rationale": rationale,
                "passed": ok,
                "detail": detail,
            }
        )
    passed = sum(1 for ok, _ in outcomes if ok)
    failed = sum(1 for ok, _ in outcomes if not ok)
    mi_outcomes = [item for item in check_outcomes if item["scope"] == MODE_INDEPENDENT]
    mi_passed = sum(item["passed"] for item in mi_outcomes)
    mi_failed = len(mi_outcomes) - mi_passed
    return {
        "execution": "ok",
        "rows": len(rows),
        "checks_pass": passed,
        "checks_fail": failed,
        "oracle_pass": failed == 0 and (passed > 0 or not checks),
        "failed_check_details": [detail for ok, detail in outcomes if not ok],
        "mode_independent_checks_defined": mi_defined,
        "mode_independent_checks_evaluated": len(mi_outcomes),
        "mode_independent_checks_pass": mi_passed,
        "mode_independent_checks_fail": mi_failed,
        "mode_independent_checks_not_evaluated": 0,
        "mode_independent_oracle_pass": mi_failed == 0 if mi_outcomes else None,
        "check_outcomes": check_outcomes,
    }


def totals(records: list[dict], mode: str) -> dict:
    values = [record[mode] for record in records]
    return {
        "scenarios": len(values),
        "execution_ok": sum(value["execution"] == "ok" for value in values),
        "execution_error": sum(value["execution"] == "error" for value in values),
        "missing": sum(value["execution"] == "missing" for value in values),
        "oracle_pass": sum(value["oracle_pass"] for value in values),
        "checks_pass": sum(value["checks_pass"] for value in values),
        "checks_fail": sum(value["checks_fail"] for value in values),
        "mode_independent_checks_defined": sum(
            value["mode_independent_checks_defined"] for value in values
        ),
        "mode_independent_checks_evaluated": sum(
            value["mode_independent_checks_evaluated"] for value in values
        ),
        "mode_independent_checks_pass": sum(
            value["mode_independent_checks_pass"] for value in values
        ),
        "mode_independent_checks_fail": sum(
            value["mode_independent_checks_fail"] for value in values
        ),
        "mode_independent_checks_not_evaluated": sum(
            value["mode_independent_checks_not_evaluated"] for value in values
        ),
        "mode_independent_oracle_eligible": sum(
            value["mode_independent_oracle_pass"] is not None for value in values
        ),
        "mode_independent_oracle_pass": sum(
            value["mode_independent_oracle_pass"] is True for value in values
        ),
    }


def write_outputs(records: list[dict], build_dir: Path, out_dir: Path) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)
    summary = {
        "schema_version": 2,
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "platform": platform.platform(),
        "python": platform.python_version(),
        "build_configuration": "Release executables from an external CMake build tree",
        "interpretation": (
            "The same scenario definitions and retained oracles are applied "
            "to ME and CS. A frozen retrospective scope classification reports "
            "mode-independent checks separately from solver-specific diagnostics."
        ),
        "me": totals(records, "me"),
        "cs": totals(records, "cs"),
        "paired": {
            "both_execute": sum(
                record["me"]["execution"] == "ok"
                and record["cs"]["execution"] == "ok"
                for record in records
            ),
            "both_oracle_pass": sum(
                record["me"]["oracle_pass"] and record["cs"]["oracle_pass"]
                for record in records
            ),
            "same_oracle_outcome": sum(
                record["me"]["oracle_pass"] == record["cs"]["oracle_pass"]
                for record in records
            ),
            "both_mode_independent_oracle_pass": sum(
                record["me"]["mode_independent_oracle_pass"] is True
                and record["cs"]["mode_independent_oracle_pass"] is True
                for record in records
            ),
        },
        "records": records,
    }
    (out_dir / "paired_modes.json").write_text(
        json.dumps(summary, indent=2, ensure_ascii=False), encoding="utf-8"
    )

    with (out_dir / "paired_modes.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            [
                "model",
                "scenario",
                "configured_mode",
                "solver",
                "me_execution",
                "me_oracle_pass",
                "me_checks_pass",
                "me_checks_fail",
                "cs_execution",
                "cs_oracle_pass",
                "cs_checks_pass",
                "cs_checks_fail",
                "me_mode_independent_pass",
                "me_mode_independent_fail",
                "me_mode_independent_not_evaluated",
                "cs_mode_independent_pass",
                "cs_mode_independent_fail",
                "cs_mode_independent_not_evaluated",
            ]
        )
        for record in records:
            writer.writerow(
                [
                    record["model"],
                    record["scenario"],
                    record["configured_mode"],
                    record["solver"],
                    record["me"]["execution"],
                    record["me"]["oracle_pass"],
                    record["me"]["checks_pass"],
                    record["me"]["checks_fail"],
                    record["cs"]["execution"],
                    record["cs"]["oracle_pass"],
                    record["cs"]["checks_pass"],
                    record["cs"]["checks_fail"],
                    record["me"]["mode_independent_checks_pass"],
                    record["me"]["mode_independent_checks_fail"],
                    record["me"]["mode_independent_checks_not_evaluated"],
                    record["cs"]["mode_independent_checks_pass"],
                    record["cs"]["mode_independent_checks_fail"],
                    record["cs"]["mode_independent_checks_not_evaluated"],
                ]
            )

    me = summary["me"]
    cs = summary["cs"]
    paired = summary["paired"]
    error_rows = [
        record
        for record in records
        if record["me"]["execution"] != "ok" or record["cs"]["execution"] != "ok"
    ]
    lines = [
        "# Paired Model Exchange / Co-Simulation diagnostic",
        "",
        "> This study applies the same retained scenarios to both modes. A frozen, "
        "outcome-independent rule classifies checks by their documented purpose. "
        "Solver-discrimination checks remain in the full diagnostic but are excluded "
        "from the mode-independent comparison.",
        "",
        "| Mode | Scenarios | Executed | Execution errors | Oracle-pass scenarios | Passed checks | Failed checks |",
        "|---|---:|---:|---:|---:|---:|---:|",
        f"| ME | {me['scenarios']} | {me['execution_ok']} | {me['execution_error']} | {me['oracle_pass']} | {me['checks_pass']} | {me['checks_fail']} |",
        f"| CS | {cs['scenarios']} | {cs['execution_ok']} | {cs['execution_error']} | {cs['oracle_pass']} | {cs['checks_pass']} | {cs['checks_fail']} |",
        "",
        "## Mode-independent semantic checks",
        "",
        "| Mode | Defined | Evaluated | Passed | Failed | Not evaluated after execution error | Eligible scenarios | Oracle-pass scenarios |",
        "|---|---:|---:|---:|---:|---:|---:|---:|",
        f"| ME | {me['mode_independent_checks_defined']} | {me['mode_independent_checks_evaluated']} | {me['mode_independent_checks_pass']} | {me['mode_independent_checks_fail']} | {me['mode_independent_checks_not_evaluated']} | {me['mode_independent_oracle_eligible']} | {me['mode_independent_oracle_pass']} |",
        f"| CS | {cs['mode_independent_checks_defined']} | {cs['mode_independent_checks_evaluated']} | {cs['mode_independent_checks_pass']} | {cs['mode_independent_checks_fail']} | {cs['mode_independent_checks_not_evaluated']} | {cs['mode_independent_oracle_eligible']} | {cs['mode_independent_oracle_pass']} |",
        "",
        "The denominator is the number of checks defined before execution. Checks in a "
        "scenario that does not execute are reported as not evaluated, not converted into "
        "failed semantic assertions.",
        "",
        f"Both modes executed successfully for **{paired['both_execute']}/{len(records)}** scenarios. "
        f"Both satisfied the retained oracle for **{paired['both_oracle_pass']}/{len(records)}** scenarios; "
        f"their pass/fail classification agreed for **{paired['same_oracle_outcome']}/{len(records)}** scenarios.",
        "",
        "## Execution errors",
        "",
    ]
    if error_rows:
        for record in error_rows:
            for mode in ("me", "cs"):
                value = record[mode]
                if value["execution"] != "ok":
                    lines.append(
                        f"- `{record['scenario']}` ({record['model']}, {mode.upper()}): "
                        f"{value.get('error', value['execution'])}"
                    )
    else:
        lines.append("No execution errors were observed.")
    lines += [
        "",
        "## Interpretation boundary",
        "",
        "The retained suite mixes analytical, invariant, event, boundary, and "
        "solver-discrimination checks. The scope rule is implemented in "
        "`tools/oracle_scope.py`; it excludes entire scenarios whose documented purpose "
        "is an Euler/RK4 discriminator, energy-drift measurement, or ME step-size "
        "comparison. The machine-readable JSON stores the scope, rationale, and result "
        "for every evaluated check.",
        "",
    ]
    (out_dir / "README.md").write_text("\n".join(lines), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--build-dir",
        type=Path,
        default=os.environ.get("FMU2HOST_BUILD_DIR"),
        help="CMake build tree containing generated Release executables",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT / "results" / "paired_modes",
    )
    args = parser.parse_args()
    if args.build_dir is None:
        parser.error("set --build-dir or FMU2HOST_BUILD_DIR")
    build_dir = args.build_dir.expanduser().resolve()
    os.environ["FMU2HOST_BUILD_DIR"] = str(build_dir)

    records = []
    configs = discover_configs(ROOT / "examples")
    for index, config_path in enumerate(configs, 1):
        config = load_config(config_path)
        model = config["model_name"]
        exe_me = config.get("exe_me") or locate_exe(model, "me", config_path)
        exe_cs = config.get("exe_cs") or locate_exe(model, "cs", config_path)
        print(f"[{index:02d}/{len(configs)}] {model}", flush=True)
        for test in config["tests"]:
            record = {
                "model": model,
                "scenario": test["id"],
                "title": test["title"],
                "configured_mode": test.get("mode", "me"),
                "solver": test.get("solver", "rk4"),
                "me": evaluate(model, test, "me", exe_me),
                "cs": evaluate(model, test, "cs", exe_cs),
            }
            records.append(record)

    write_outputs(records, build_dir, args.output.resolve())
    me = totals(records, "me")
    cs = totals(records, "cs")
    print(
        f"ME: {me['execution_ok']}/{me['scenarios']} executed; "
        f"CS: {cs['execution_ok']}/{cs['scenarios']} executed"
    )
    return 0 if me["execution_error"] == 0 and cs["execution_error"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
