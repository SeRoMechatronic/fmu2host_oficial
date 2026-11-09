"""Frozen scope classification for the retained behavioral checks.

The classification is retrospective: the original batteries predate this
analysis.  It is based on each scenario's documented purpose, not on whether a
check passed.  A complete scenario is conservatively excluded when it was
designed to discriminate Euler from RK4, quantify solver drift, or compare ME
step sizes.  All other checks express model/interface behavior and are treated
as mode-independent.  Explicit ``oracle_scope`` fields can override the table
for future batteries.
"""

from __future__ import annotations


MODE_INDEPENDENT = "mode_independent"
SOLVER_SPECIFIC = "solver_specific"
VALID_SCOPES = {MODE_INDEPENDENT, SOLVER_SPECIFIC}


SOLVER_SPECIFIC_SCENARIOS = {
    ("CrecimientoPoblacional", "TC-CP-003"): "Euler overshoot discriminator",
    ("CuerposAcoplados", "TC-CA-002"): "RK4 energy-drift tolerance",
    ("CuerposAcoplados", "TC-CA-003"): "Euler energy-drift discriminator",
    ("OsciladorArmonico", "TC-OA-005"): "RK4 energy-drift tolerance",
    ("OsciladorArmonico", "TC-OA-006"): "Euler energy-drift discriminator",
    ("OsciladorArmonico", "TC-OA-009"): "RK4 step-size comparison",
    ("PenduloNoLineal", "TC-PN-004"): "RK4 energy-drift tolerance",
    ("PenduloNoLineal", "TC-PN-005"): "Euler energy-drift discriminator",
    ("PenduloNoLineal", "TC-PN-010"): "RK4-versus-Euler energy comparison",
    ("SistemaLorenz", "TC-LZ-004"): "Euler divergence discriminator",
    ("SistemaLorenz", "TC-LZ-009"): "large-step Euler divergence discriminator",
}


def classify_check(model: str, test: dict, check: dict) -> tuple[str, str]:
    """Return ``(scope, rationale)`` without consulting observed outcomes."""
    explicit = check.get("oracle_scope", test.get("oracle_scope"))
    if explicit is not None:
        if explicit not in VALID_SCOPES:
            raise ValueError(f"unknown oracle_scope {explicit!r}")
        return explicit, "explicit battery annotation"

    key = (model, test["id"])
    if key in SOLVER_SPECIFIC_SCENARIOS:
        return SOLVER_SPECIFIC, SOLVER_SPECIFIC_SCENARIOS[key]
    return MODE_INDEPENDENT, "model/interface behavioral requirement"
