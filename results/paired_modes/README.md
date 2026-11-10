# Paired Model Exchange / Co-Simulation study

> Primary results include only behavioral models whose source archive passed standards preflight. The two rejected archives remain in a separate negative-diagnostic population. The same retained scenarios are applied to both modes. A frozen, outcome-independent rule classifies checks by their documented purpose. Solver-discrimination checks remain in the full diagnostic but are excluded from the mode-independent comparison.

## Primary preflight-valid behavioral population (26 models)

| Mode | Scenarios | Executed | Execution errors | Oracle-pass scenarios | Passed checks | Failed checks |
|---|---:|---:|---:|---:|---:|---:|
| ME | 259 | 259 | 0 | 230 | 636 | 60 |
| CS | 259 | 247 | 12 | 202 | 586 | 110 |

## Mode-independent semantic checks

| Mode | Defined | Evaluated | Passed | Failed | Not evaluated after execution error | Eligible scenarios | Oracle-pass scenarios |
|---|---:|---:|---:|---:|---:|---:|---:|
| ME | 683 | 683 | 623 | 60 | 0 | 248 | 219 |
| CS | 683 | 655 | 578 | 77 | 28 | 248 | 196 |

The denominator is the number of checks defined before execution. Checks in a scenario that does not execute are reported as not evaluated, not converted into failed semantic assertions.

Both modes executed successfully for **247/259** scenarios. Both satisfied the retained oracle for **202/259** scenarios; their pass/fail classification agreed for **231/259** scenarios.

## Negative diagnostics and full retained suite

The rejected archives are: **ArraysVectores, StringInputOutput**. Together they contribute 20 scenarios. The full retained diagnostic contains 28 models and 279 scenarios; ME executes 279/279 and CS executes 267/279. These combined values are retained for audit continuity, not used as the primary conforming result.

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
