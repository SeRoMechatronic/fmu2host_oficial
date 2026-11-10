#!/usr/bin/env python3
"""Export the complete retained oracle catalog and scope exclusions to CSV."""

from __future__ import annotations

import csv
import json
import sys
from pathlib import Path


TOOLS = Path(__file__).resolve().parent
ROOT = TOOLS.parent
sys.path.insert(0, str(TOOLS))

from oracle_scope import MODE_INDEPENDENT, classify_check
from run_all_tests import discover_configs
from run_paired_modes import load_config


FIELDS = [
    "model", "scenario", "title", "check_index", "check_type", "column",
    "configured_mode", "configured_solver", "t_end", "step_size", "inputs_json",
    "schedule_json", "oracle_parameters_json", "scope", "scope_rationale",
    "oracle_basis", "documented_rationale",
]


def basis(check: dict, scope: str) -> str:
    if scope != MODE_INDEPENDENT:
        return "solver-discrimination diagnostic"
    if check.get("type") in {"always", "eventually", "no_nan_inf", "monotonic", "bounded"}:
        return "documented behavioral invariant"
    return "documented scenario reference value"


def main() -> int:
    rows = []
    for config_path in discover_configs(ROOT / "examples"):
        config = load_config(config_path)
        model = config["model_name"]
        for test in config["tests"]:
            for index, check in enumerate(test.get("checks", [])):
                scope, rationale = classify_check(model, test, check)
                parameters = {key: value for key, value in check.items() if key not in {"col", "type", "mode", "solver"}}
                rows.append(
                    {
                        "model": model,
                        "scenario": test["id"],
                        "title": test["title"],
                        "check_index": index,
                        "check_type": check.get("type", "at_t"),
                        "column": check.get("col", ""),
                        "configured_mode": check.get("mode", test.get("mode", "me")),
                        "configured_solver": check.get("solver", test.get("solver", "rk4")),
                        "t_end": test.get("t_end", 1.0),
                        "step_size": test.get("h", 0.01),
                        "inputs_json": json.dumps(test.get("inputs", {}), ensure_ascii=False, sort_keys=True),
                        "schedule_json": json.dumps(test.get("schedule", {}), ensure_ascii=False, sort_keys=True),
                        "oracle_parameters_json": json.dumps(parameters, ensure_ascii=False, sort_keys=True),
                        "scope": scope,
                        "scope_rationale": rationale,
                        "oracle_basis": basis(check, scope),
                        "documented_rationale": test.get("interpretation", test.get("description", "")),
                    }
                )

    output = ROOT / "results" / "oracles"
    output.mkdir(parents=True, exist_ok=True)
    with (output / "oracle_catalog.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS)
        writer.writeheader()
        writer.writerows(rows)

    excluded = [row for row in rows if row["scope"] != MODE_INDEPENDENT]
    with (output / "excluded_solver_specific.csv").open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS)
        writer.writeheader()
        writer.writerows(excluded)

    lines = [
        "# Oracle catalog",
        "",
        f"The retained suite defines **{len(rows)}** checks. The frozen scope rule classifies "
        f"**{len(rows) - len(excluded)}** as mode-independent and **{len(excluded)}** as "
        "solver-specific diagnostics.",
        "",
        "`oracle_catalog.csv` records every check, its parameters, execution settings, scope, "
        "and the scenario author's documented rationale. `excluded_solver_specific.csv` is the "
        "complete audit list excluded from the mode-independent comparison.",
        "",
        "The `oracle_basis` field is deliberately conservative: it distinguishes documented "
        "reference values, invariants, and solver-discrimination diagnostics without claiming "
        "an independent formal derivation where none was recorded.",
        "",
    ]
    (output / "README.md").write_text("\n".join(lines), encoding="utf-8")
    print(f"oracle catalog: {len(rows)} checks; {len(excluded)} solver-specific exclusions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
