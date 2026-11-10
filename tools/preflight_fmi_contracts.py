#!/usr/bin/env python3
"""Validate every source FMU before code generation and publish the decisions."""

from __future__ import annotations

import csv
import hashlib
import json
from datetime import datetime, timezone
from pathlib import Path

from fmpy import __version__ as fmpy_version
from fmpy.validation import validate_fmu


ROOT = Path(__file__).resolve().parent.parent


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            value.update(block)
    return value.hexdigest()


def main() -> int:
    records = []
    for fmu in sorted((ROOT / "models").rglob("*.fmu")):
        problems = validate_fmu(str(fmu))
        records.append(
            {
                "model": fmu.stem,
                "fmu": fmu.relative_to(ROOT).as_posix(),
                "sha256": digest(fmu),
                "decision": "accept" if not problems else "reject",
                "problem_count": len(problems),
                "problems": problems,
            }
        )

    accepted = sum(record["decision"] == "accept" for record in records)
    rejected = len(records) - accepted
    report = {
        "schema_version": 1,
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "validator": f"FMPy {fmpy_version}",
        "policy": (
            "FMUs with no reported FMI contract violation are accepted into the conformance "
            "population. Rejected archives may be retained only as explicit negative diagnostics."
        ),
        "archives": len(records),
        "accepted": accepted,
        "rejected": rejected,
        "records": records,
    }

    output = ROOT / "results" / "preflight"
    output.mkdir(parents=True, exist_ok=True)
    (output / "preflight.json").write_text(
        json.dumps(report, indent=2, ensure_ascii=False), encoding="utf-8"
    )
    with (output / "preflight.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(["model", "fmu", "sha256", "decision", "problem_count", "problem"])
        for record in records:
            if record["problems"]:
                for problem in record["problems"]:
                    writer.writerow(
                        [record["model"], record["fmu"], record["sha256"], "reject", record["problem_count"], problem]
                    )
            else:
                writer.writerow([record["model"], record["fmu"], record["sha256"], "accept", 0, ""])

    lines = [
        "# FMI contract preflight",
        "",
        f"FMPy {fmpy_version} validation accepts **{accepted}/{len(records)}** source FMUs and rejects **{rejected}**.",
        "Rejected archives are excluded from the conformance population and retained only as negative diagnostics.",
        "",
        "| Model | Decision | Problems |",
        "|---|---|---:|",
    ]
    for record in records:
        lines.append(f"| {record['model']} | {record['decision']} | {record['problem_count']} |")
    lines.extend(["", "Full validator messages and archive hashes are in `preflight.csv` and `preflight.json`.", ""])
    (output / "README.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"preflight: {accepted} accepted, {rejected} rejected")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
