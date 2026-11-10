# Paired Model Exchange / Co-Simulation diagnostic

> This study applies the same retained scenarios to both modes. A frozen, outcome-independent rule classifies checks by their documented purpose. Solver-discrimination checks remain in the full diagnostic but are excluded from the mode-independent comparison.

| Mode | Scenarios | Executed | Execution errors | Oracle-pass scenarios | Passed checks | Failed checks |
|---|---:|---:|---:|---:|---:|---:|
| ME | 279 | 279 | 0 | 242 | 669 | 93 |
| CS | 279 | 267 | 12 | 213 | 615 | 147 |

## Mode-independent semantic checks

| Mode | Defined | Evaluated | Passed | Failed | Not evaluated after execution error | Eligible scenarios | Oracle-pass scenarios |
|---|---:|---:|---:|---:|---:|---:|---:|
| ME | 749 | 749 | 656 | 93 | 0 | 268 | 231 |
| CS | 749 | 721 | 607 | 114 | 28 | 268 | 207 |

The denominator is the number of checks defined before execution. Checks in a scenario that does not execute are reported as not evaluated, not converted into failed semantic assertions.

Both modes executed successfully for **267/279** scenarios. Both satisfied the retained oracle for **213/279** scenarios; their pass/fail classification agreed for **250/279** scenarios.

## Execution errors

- `TC-ES-001` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-002` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-003` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-004` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-005` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-006` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-007` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-008` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-009` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-010` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-011` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed
- `TC-ES-012` (EtapaSecuenciador, CS): EXIT 1: Error: fmi2DoStep failed

## Interpretation boundary

The retained suite mixes analytical, invariant, event, boundary, and solver-discrimination checks. The scope rule is implemented in `tools/oracle_scope.py`; it excludes entire scenarios whose documented purpose is an Euler/RK4 discriminator, energy-drift measurement, or ME step-size comparison. The machine-readable JSON stores the scope, rationale, and result for every evaluated check.
