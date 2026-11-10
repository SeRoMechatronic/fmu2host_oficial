# ExtremeValues causal-isolation experiment

| Path | Scenarios | Executed | Errors | Checks passed/evaluated |
|---|---:|---:|---:|---:|
| exporter-provided binary + FMPy | 10 | 10 | 0 | 42/42 |
| FMPy source-compiled binary + FMPy | 10 | 10 | 0 | 42/42 |
| fmu2host source-compiled static executable | 10 | 10 | 0 | 42/42 |

The corrected source-compiled host completes all ten scenarios, matching both FMPy paths.  The former access violations were caused by sampling outputs after changing the input but before fmi2DoStep; advancing the FMU before reading outputs resolves the stale discrete-relation state and the crash.

Targeted tracing localized the former negative-input failure to the first Boolean output read, inside the exporter-generated square-root guard, before the first fmi2DoStep. Reordering the CS loop to set inputs, complete fmi2DoStep, and then sample outputs removes the failure in the same executable and scenarios.

Reproduce with:

```powershell
python tools/run_extremevalues_isolation.py
```
