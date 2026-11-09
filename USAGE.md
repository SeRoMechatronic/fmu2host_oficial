# Usage guide

## Generate one host

```powershell
python tools\fmu_codegen_host.py models\MyModel\MyModel.fmu examples\mymodel\host
```

For each mode declared by the FMU, the command creates a static adapter linked
to the source-FMU C implementation. It also creates a typed API, a generated
entry point, CMake targets, and (only if absent) `scenario.c`.

Generated files may be refreshed at any time. Edit only `scenario.c` to define:

- `get_config()`: stop time, communication/integration step, and ME solver;
- `get_inputs()`: time-dependent scalar stimuli;
- `on_outputs()`: optional application-side output handling.

## Generate every bundled host

```powershell
python tools\regen_all.py
```

The command preserves every existing scenario definition.

## Configure and build

Visual Studio 2022:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

Single-configuration generators:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Targets follow `<modelIdentifier>_host_me` and
`<modelIdentifier>_host_cs`. A generated executable accepts:

```text
ME: executable [t_end] [h] [euler|rk4] [name=value] [name@time=value]
CS: executable [t_end] [h]             [name=value] [name@time=value]
```

Example:

```powershell
.\build\examples\osciladorarmonico\host\Release\osciladorarmonico_host_me.exe 10 0.01 rk4
```

Both modes emit CSV to standard output. Diagnostics go to standard error.

## Validation commands

```powershell
$env:FMU2HOST_BUILD_DIR = (Resolve-Path build)
python -m unittest discover -s tests -v
python tools\run_all_tests.py
python tools\run_paired_modes.py
python tools\collect_evidence.py
```

The historical suite intentionally retains non-passing oracles. The paired
study is diagnostic: it applies historical ME-oriented oracles to CS as well,
but does not assume that the internal CS solver must reproduce Euler- or
RK4-specific behavior.

## Add a new FMU

1. Add the `.fmu` under `models/`.
2. Generate its host into `examples/<name>/host`.
3. Edit the preserved `scenario.c`.
4. Reconfigure CMake so the new `add_subdirectory` is discovered.
5. Add a `test_*_full.py` battery if the model belongs in the behavioral suite.
6. Rebuild and rerun the evidence scripts.

## Common failures

- **Unsupported FMI version/type:** the parser rejects anything outside FMI
  2.0 and scalar Real/Integer/Boolean/String.
- **Missing executable:** ensure `FMU2HOST_BUILD_DIR` points to the configured
  build tree, not the repository root.
- **Unresolved symbols:** the mode-specific `modelIdentifier` in XML must match
  the exported C symbols; ME and CS prefixes are handled independently.
- **CS `fmi2DoStep` error:** this is reported as an execution failure and must be
  diagnosed in the exported FMU/runtime; it is not silently ignored.
- **Historical oracle failure:** inspect the model report and exporter metadata
  before assigning causality to the host.
