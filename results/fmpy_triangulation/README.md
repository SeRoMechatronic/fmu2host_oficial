# FMPy triangulation of the six anomalous FMUs

FMPy version: `0.3.29`.

FMPy provides an independent XML importer, FMI lifecycle and simulation driver. The FMU implementation binary remains shared, so this is triangulation of importing and orchestration rather than a second model implementation.

| Mode | Scenarios attempted | Executed | Execution errors | Checks evaluated | Passed | Failed |
|---|---:|---:|---:|---:|---:|---:|
| ME (fixed-step Euler driver) | 52 | 51 | 1 | 161 | 101 | 60 |
| CS | 52 | 39 | 13 | 133 | 96 | 37 |

## Importer findings

- `ArraysVectores` was rejected before instantiation: Variable "alguno_true" (line 507) has an illegal combination of causality="output" and variability="fixed".

Unsupported requested inputs are preserved per scenario in the JSON/CSV. They expose cases where the battery requests a variable whose FMI causality is `local`.
