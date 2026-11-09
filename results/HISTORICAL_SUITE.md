# Historical Model Exchange suite

The retained behavioral suite contains 28 model-specific batteries, 279
scenarios, and 762 assertions. It was rerun against the regenerated Release
executables on Windows/MSVC.

| Unit | Total | Passed | Not passed |
|---|---:|---:|---:|
| Models satisfying every oracle | 28 | 23 | 5 |
| Scenarios | 279 | 242 | 37 |
| Checks | 762 | 669 | 93 |

All 279 ME executions completed. The five models with at least one retained
oracle discrepancy were:

| Artifact identifier | Scenario outcome | Check outcome | Observed boundary |
|---|---:|---:|---|
| `ArraysVectores` | 2/10 | 6/39 | Expected array elements are declared local, not FMI inputs. |
| `BooleanLogica` | 4/10 | 23/37 | Edge-dependent state does not follow the scheduled input transitions. |
| `ContadorEventos` | 2/10 | 15/31 | Edge-dependent counter updates are absent. |
| `EtapaSecuenciador` | 1/12 | 9/28 | Periodic-event behavior does not satisfy the retained oracle. |
| `MatrizEstado` | 6/10 | 16/27 | The retained exported source folds the expected input term to zero. |

These outcomes are not an FMI-conformance score. The checks are heterogeneous
and non-independent, and the suite was designed iteratively by the authors.
The raw per-scenario traces, plots, and reports remain under
`examples/*/host/test/results/`. The generated legacy summary is
`suite_summary.md`; the independent paired-mode study is under
`paired_modes/`.
