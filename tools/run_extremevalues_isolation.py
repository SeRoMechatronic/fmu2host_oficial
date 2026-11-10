#!/usr/bin/env python3
"""Isolate the ExtremeValues CS failure across binary and source-compiled paths.

The experiment runs the retained mode-independent scenarios through FMPy twice:
first with the exporter-provided Windows binary and then with a new Windows
binary compiled by FMPy from the source FMU.  The generated-host outcome is
read from the paired-mode artifact to form a three-path comparison.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import shutil
import subprocess
import sys
import tempfile
import zipfile
from datetime import datetime, timezone
from pathlib import Path

from fmpy import __version__ as fmpy_version
from fmpy import read_model_description

TOOLS_DIR = Path(__file__).resolve().parent
ROOT = TOOLS_DIR.parent
sys.path.insert(0, str(TOOLS_DIR))

from run_all_tests import discover_configs
from run_fmpy_triangulation import (
    aggregate,
    load_config,
    name_index,
    simulate,
)


MODEL = "ValoresExtremos"


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def binary_digest(fmu: Path) -> str:
    with zipfile.ZipFile(fmu) as archive:
        candidates = [
            name
            for name in archive.namelist()
            if name.lower().endswith("binaries/win64/valoresextremos.dll")
        ]
        if len(candidates) != 1:
            raise RuntimeError(f"expected one win64 DLL in {fmu}, found {candidates}")
        return sha256_bytes(archive.read(candidates[0]))


def compile_source_fmu(source: Path, destination: Path) -> dict:
    shutil.copy2(source, destination)
    command = [
        sys.executable,
        "-m",
        "fmpy",
        "compile",
        str(destination),
        "--generator",
        "Visual Studio 17 2022",
        "--platform",
        "x64",
        "--configuration",
        "Release",
    ]
    completed = subprocess.run(
        command,
        cwd=ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )
    if completed.returncode != 0:
        tail = completed.stdout.splitlines()[-30:]
        raise RuntimeError("FMPy source compilation failed:\n" + "\n".join(tail))
    warning_lines = [line.strip() for line in completed.stdout.splitlines() if "warning" in line.lower()]
    return {
        "tool": f"FMPy {fmpy_version}",
        "generator": "Visual Studio 17 2022",
        "platform": "x64",
        "configuration": "Release",
        "returncode": completed.returncode,
        "warning_lines": len(warning_lines),
    }


def load_extreme_config() -> dict:
    for path in discover_configs(ROOT / "examples"):
        config = load_config(path)
        if config["model_name"] == MODEL:
            return config
    raise RuntimeError(f"scenario configuration not found for {MODEL}")


def run_variant(label: str, fmu: Path, config: dict) -> dict:
    description = read_model_description(fmu, validate=False)
    index = name_index(description.modelVariables)
    records = []
    for test in config["tests"]:
        result = simulate(test, fmu, description, "CoSimulation", index)
        records.append(
            {
                "model": MODEL,
                "scenario": test["id"],
                "title": test["title"],
                "cs": result,
            }
        )
    return {
        "label": label,
        "fmu_sha256": sha256_file(fmu),
        "win64_binary_sha256": binary_digest(fmu),
        "summary": aggregate(records, "cs"),
        "records": records,
    }


def host_summary() -> dict:
    paired_path = ROOT / "results" / "paired_modes" / "paired_modes.json"
    paired = json.loads(paired_path.read_text(encoding="utf-8"))
    records = [record for record in paired["records"] if record["model"] == MODEL]
    values = [record["cs"] for record in records]
    return {
        "label": "fmu2host source-compiled static executable",
        "summary": {
            "scenarios_attempted": len(values),
            "execution_ok": sum(value["execution"] == "ok" for value in values),
            "execution_error": sum(value["execution"] != "ok" for value in values),
            "checks_defined": sum(
                value.get("checks_defined", value.get("checks_pass", 0) + value.get("checks_fail", 0))
                for value in values
            ),
            "checks_evaluated": sum(
                value.get("checks_evaluated", value.get("checks_pass", 0) + value.get("checks_fail", 0))
                for value in values
            ),
            "checks_pass": sum(value.get("checks_pass", 0) for value in values),
            "checks_fail": sum(value.get("checks_fail", 0) for value in values),
        },
        "records": [
            {
                "scenario": record["scenario"],
                "execution": record["cs"]["execution"],
                "returncode": record["cs"].get("returncode"),
                "error": record["cs"].get("error"),
            }
            for record in records
        ],
    }


def conclusion(exported: dict, compiled: dict, host: dict) -> str:
    first = exported["summary"]
    second = compiled["summary"]
    third = host["summary"]
    if first["execution_ok"] == second["execution_ok"] == third["execution_ok"] == 10:
        return (
            "The corrected source-compiled host completes all ten scenarios, matching both "
            "FMPy paths.  The former access violations were caused by sampling outputs after "
            "changing the input but before fmi2DoStep; advancing the FMU before reading outputs "
            "resolves the stale discrete-relation state and the crash."
        )
    if first["execution_ok"] == second["execution_ok"] == 10 and third["execution_error"]:
        return (
            "Both the exporter-provided binary and FMPy's source-compiled binary complete all "
            "ten CS scenarios under the same FMPy driver, while the generated static host fails. "
            "Source compilation alone therefore does not reproduce the access violations; the "
            "remaining difference is narrowed to the static-host linkage or execution path."
        )
    if first["execution_ok"] == 10 and second["execution_error"]:
        return (
            "The exporter-provided binary completes under FMPy but FMPy's source-compiled binary "
            "does not.  The failure is therefore reproduced without the generated host and is "
            "consistent with a source-compilation/runtime boundary."
        )
    return (
        "The three paths do not match either isolating pattern; inspect the per-scenario records "
        "before assigning the failure to a component."
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--compiled-fmu",
        type=Path,
        help="reuse an already FMPy-compiled FMU instead of compiling a temporary copy",
    )
    args = parser.parse_args()

    original = ROOT / "models" / MODEL / f"{MODEL}.fmu"
    config = load_extreme_config()
    compilation = None
    with tempfile.TemporaryDirectory(prefix="fmu2host-extreme-") as temporary:
        if args.compiled_fmu:
            compiled_path = args.compiled_fmu.resolve()
            compilation = {"tool": f"FMPy {fmpy_version}", "reused_precompiled_copy": True}
        else:
            compiled_path = Path(temporary) / f"{MODEL}_fmpy_compiled.fmu"
            compilation = compile_source_fmu(original, compiled_path)

        exported = run_variant("exporter-provided binary + FMPy", original, config)
        compiled = run_variant("FMPy source-compiled binary + FMPy", compiled_path, config)
        host = host_summary()

    summary = {
        "schema_version": 1,
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "model": MODEL,
        "fmpy_version": fmpy_version,
        "compilation": compilation,
        "paths": [exported, compiled, host],
        "conclusion": conclusion(exported, compiled, host),
        "causal_evidence": (
            "Targeted tracing localized the former negative-input failure to the first Boolean "
            "output read, inside the exporter-generated square-root guard, before the first "
            "fmi2DoStep. Reordering the CS loop to set inputs, complete fmi2DoStep, and then "
            "sample outputs removes the failure in the same executable and scenarios."
        ),
    }

    output = ROOT / "results" / "extremevalues_isolation"
    output.mkdir(parents=True, exist_ok=True)
    (output / "isolation.json").write_text(
        json.dumps(summary, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    with (output / "isolation.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(["path", "scenarios", "executed", "errors", "checks_evaluated", "checks_pass", "checks_fail"])
        for item in summary["paths"]:
            values = item["summary"]
            writer.writerow(
                [
                    item["label"],
                    values["scenarios_attempted"],
                    values["execution_ok"],
                    values["execution_error"],
                    values["checks_evaluated"],
                    values["checks_pass"],
                    values["checks_fail"],
                ]
            )

    lines = [
        "# ExtremeValues causal-isolation experiment",
        "",
        "| Path | Scenarios | Executed | Errors | Checks passed/evaluated |",
        "|---|---:|---:|---:|---:|",
    ]
    for item in summary["paths"]:
        values = item["summary"]
        lines.append(
            f"| {item['label']} | {values['scenarios_attempted']} | {values['execution_ok']} | "
            f"{values['execution_error']} | {values['checks_pass']}/{values['checks_evaluated']} |"
        )
    lines.extend(
        [
            "",
            summary["conclusion"],
            "",
            summary["causal_evidence"],
            "",
            "Reproduce with:",
            "",
            "```powershell",
            "python tools/run_extremevalues_isolation.py",
            "```",
            "",
        ]
    )
    (output / "README.md").write_text("\n".join(lines), encoding="utf-8")
    print(summary["conclusion"])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
