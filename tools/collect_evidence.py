#!/usr/bin/env python3
"""Collect reproducible artifact, coverage, and engineering-cost evidence."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import platform
import shutil
import statistics
import subprocess
import sys
import tempfile
import time
import zipfile
from collections import Counter
from datetime import datetime, timezone
from pathlib import Path
from xml.etree import ElementTree as ET

ROOT = Path(__file__).resolve().parent.parent


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def normalized(value: str) -> str:
    return "".join(character.lower() for character in value if character.isalnum())


def xml_from_fmu(path: Path) -> ET.Element:
    with zipfile.ZipFile(path) as archive:
        return ET.fromstring(archive.read("modelDescription.xml"))


def executable_for(build_dir: Path, identifier: str, mode: str) -> Path | None:
    expected = normalized(identifier) + "host" + mode
    for candidate in build_dir.rglob(f"*_host_{mode}.exe"):
        if normalized(candidate.stem) == expected:
            return candidate
    return None


def quantiles(values: list[float]) -> dict:
    ordered = sorted(values)
    if not ordered:
        return {}
    quartiles = statistics.quantiles(ordered, n=4, method="inclusive") if len(ordered) > 1 else [ordered[0]] * 3
    return {
        "min": ordered[0],
        "q1": quartiles[0],
        "median": statistics.median(ordered),
        "q3": quartiles[2],
        "max": ordered[-1],
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--build-dir",
        type=Path,
        default=os.environ.get("FMU2HOST_BUILD_DIR"),
        help="configured CMake build tree",
    )
    parser.add_argument("--skip-generation-timing", action="store_true")
    args = parser.parse_args()
    if args.build_dir is None:
        parser.error("set --build-dir or FMU2HOST_BUILD_DIR")
    build_dir = args.build_dir.resolve()
    if not build_dir.is_dir():
        parser.error(f"build directory not found: {build_dir}")

    tested_names = set()
    for config in (ROOT / "examples").rglob("test_*_full.py"):
        tested_names.add(normalized(config.parent.parent.parent.name))

    records = []
    generator = ROOT / "tools" / "fmu_codegen_host.py"
    for index, fmu in enumerate(sorted((ROOT / "models").rglob("*.fmu")), 1):
        root = xml_from_fmu(fmu)
        me = root.find("ModelExchange")
        cs = root.find("CoSimulation")
        identifier = (me if me is not None else cs).get("modelIdentifier")
        model_name = root.get("modelName", fmu.stem)
        variables = root.findall(".//ScalarVariable")
        types = Counter()
        causalities = Counter()
        variabilities = Counter()
        for variable in variables:
            scalar_type = next((child.tag for child in variable if child.tag in {"Real", "Integer", "Boolean", "String", "Enumeration"}), "Unknown")
            types[scalar_type] += 1
            causalities[variable.get("causality", "local")] += 1
            variabilities[variable.get("variability", "continuous")] += 1
        derivatives = root.find("./ModelStructure/Derivatives")
        generation_seconds = None
        generated_bytes = None
        generated_files = None
        if not args.skip_generation_timing:
            with tempfile.TemporaryDirectory(prefix="fmu2host_evidence_") as temporary:
                temporary_path = Path(temporary)
                copied_fmu = temporary_path / fmu.name
                output = temporary_path / "host"
                shutil.copy2(fmu, copied_fmu)
                started = time.perf_counter()
                process = subprocess.run(
                    [sys.executable, str(generator), str(copied_fmu), str(output)],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.PIPE,
                    text=True,
                    encoding="utf-8",
                    errors="replace",
                )
                generation_seconds = time.perf_counter() - started
                if process.returncode != 0:
                    raise RuntimeError(f"generation failed for {fmu}: {process.stderr[-500:]}")
                generated = [path for path in output.rglob("*") if path.is_file()]
                generated_bytes = sum(path.stat().st_size for path in generated)
                generated_files = len(generated)

        me_exe = executable_for(build_dir, identifier, "me") if me is not None else None
        cs_exe = executable_for(build_dir, identifier, "cs") if cs is not None else None
        source_files = list((fmu.with_suffix("") / "sources").rglob("*"))
        source_files = [path for path in source_files if path.is_file()]
        record = {
            "model": model_name,
            "fmu": fmu.relative_to(ROOT).as_posix(),
            "sha256": sha256(fmu),
            "fmu_bytes": fmu.stat().st_size,
            "generation_tool": root.get("generationTool", ""),
            "has_me": me is not None,
            "has_cs": cs is not None,
            "states": len(list(derivatives)) if derivatives is not None else 0,
            "event_indicators": int(root.get("numberOfEventIndicators", "0")),
            "variables": len(variables),
            "types": dict(types),
            "causalities": dict(causalities),
            "variabilities": dict(variabilities),
            "source_files": len(source_files),
            "source_bytes": sum(path.stat().st_size for path in source_files),
            "generation_seconds": generation_seconds,
            "generated_files": generated_files,
            "generated_bytes": generated_bytes,
            "me_executable_bytes": me_exe.stat().st_size if me_exe else None,
            "cs_executable_bytes": cs_exe.stat().st_size if cs_exe else None,
            "behavioral_suite": normalized(fmu.parent.name) in tested_names or normalized(model_name) in tested_names,
        }
        records.append(record)
        print(f"[{index:02d}] {model_name}", flush=True)

    generation_values = [record["generation_seconds"] for record in records if record["generation_seconds"] is not None]
    executable_values = [
        size
        for record in records
        for size in (record["me_executable_bytes"], record["cs_executable_bytes"])
        if size is not None
    ]
    manifest = {
        "schema_version": 1,
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "platform": platform.platform(),
        "python": platform.python_version(),
        "generator_sha256": sha256(generator),
        "build_configuration": "Release executables from an external CMake build tree",
        "models": len(records),
        "behaviorally_evaluated_models": sum(record["behavioral_suite"] for record in records),
        "me_executables": sum(record["me_executable_bytes"] is not None for record in records),
        "cs_executables": sum(record["cs_executable_bytes"] is not None for record in records),
        "generation_seconds": quantiles(generation_values),
        "executable_bytes": quantiles(executable_values),
        "records": records,
    }
    output = ROOT / "results" / "evidence"
    output.mkdir(parents=True, exist_ok=True)
    (output / "artifact_manifest.json").write_text(
        json.dumps(manifest, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    with (output / "model_metrics.csv").open("w", newline="", encoding="utf-8") as handle:
        fields = [
            "model", "fmu", "sha256", "behavioral_suite", "has_me", "has_cs",
            "states", "event_indicators", "variables", "source_files", "source_bytes",
            "generation_seconds", "generated_files", "generated_bytes",
            "me_executable_bytes", "cs_executable_bytes",
        ]
        writer = csv.DictWriter(handle, fields, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(records)

    gen = manifest["generation_seconds"]
    exe = manifest["executable_bytes"]
    lines = [
        "# Artifact and engineering evidence",
        "",
        f"- Source FMUs: **{manifest['models']}**",
        f"- Models in the behavioral suite: **{manifest['behaviorally_evaluated_models']}**",
        f"- Built executables: **{manifest['me_executables']} ME + {manifest['cs_executables']} CS**",
    ]
    if gen:
        lines.append(
            f"- Generation including archive extraction: median **{gen['median']:.3f} s** "
            f"(IQR {gen['q1']:.3f}--{gen['q3']:.3f} s; range {gen['min']:.3f}--{gen['max']:.3f} s)"
        )
    if exe:
        lines.append(
            f"- Release executable size: median **{exe['median']/1048576:.2f} MiB** "
            f"(IQR {exe['q1']/1048576:.2f}--{exe['q3']/1048576:.2f} MiB; "
            f"range {exe['min']/1048576:.2f}--{exe['max']/1048576:.2f} MiB)"
        )
    lines += [
        "",
        "Hashes, per-model feature counts, source sizes, generated sizes, and executable sizes are in "
        "`artifact_manifest.json` and `model_metrics.csv`.",
        "",
    ]
    (output / "README.md").write_text("\n".join(lines), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
