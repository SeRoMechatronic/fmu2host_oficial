# fmu2host

`fmu2host` transforms an OpenModelica FMI 2.0 source-code FMU into an
inspectable, model-specific C/CMake host. It generates independent Model
Exchange (ME) and Co-Simulation (CS) adapters when the FMU declares those
modes, a typed interface derived from `modelDescription.xml`, deterministic
simulation entry points, and a preserved scenario layer for experiments.

This repository is the software and data reproducibility package for the
accompanying journal article. It contains the generator, 30 source FMUs,
generated hosts, 28 behavioral test batteries, and machine-readable results.
The manuscript and all files under `paper/` are deliberately excluded from the
public repository.

## Evidence at a glance

- 30/30 source FMUs regenerate successfully.
- Standards preflight accepts 28 archives; `ArraysVectores` and
  `StringInputOutput` are retained only as explicit invalid-input diagnostics.
- 30 ME and 30 CS Release executables compile on Windows/MSVC.
- The retained ME regression suite executes 279/279 scenarios; 242 satisfy all
  of their original oracles (669/762 checks).
- In the corrected paired-mode diagnostic, CS completes 267/279 scenarios. The
  remaining 12 execution failures are `fmi2DoStep` failures for the
  periodic-event sequencer.
- The frozen purpose-based subset contains 749 mode-independent checks. ME
  passes 656/749; CS passes 607/721 evaluated checks, with 28 not evaluated
  after execution errors.
- A three-path `ExtremeValues` experiment identifies the former access
  violations as output-before-step ordering and verifies the generated-host
  correction on all ten scenarios.
- FMPy 0.3.29 triangulation records independent importer/lifecycle results for
  the six anomalous FMUs.
- All raw summaries, hashes, and per-model metrics are under `results/`.

These counts characterize the tested artifacts; they are not FMI-conformance
scores or estimates of reliability for arbitrary FMUs.

## Repository layout

| Path | Purpose |
|---|---|
| `tools/` | XML parser, host generator, regeneration and evidence scripts |
| `include/`, `src/` | Host abstraction and fixed-step ME solvers |
| `models/` | Source-bearing OpenModelica FMI 2.0 FMUs and extracted sources |
| `examples/*/host/` | Generated adapters plus preserved `scenario.c` files |
| `tests/` | Parser contract tests |
| `results/` | Retained suite, paired-mode study, FMPy triangulation, hashes, and metrics |
| `SUBMISSION_CHECKLIST.md` | Author, archival, and editorial actions before submission |

## Prerequisites

- Python 3.10 or later
- CMake 3.15 or later
- A C11 compiler supported by the OpenModelica-generated sources
- Optional: Matplotlib for diagnostic plots
- Optional: FMPy 0.3.29 for the independent triangulation experiment

The full evidence currently included was produced on Windows 11 with Visual
Studio 2022. Generated paths are resolved relative to the repository through
`FMU2HOST_ROOT`; a build directory is intentionally not committed.

OpenModelica embeds the exporting workstation's absolute paths in generated C,
JSON, and DLL strings. For the public artifact, `tools/sanitize_export_paths.py`
applies a documented, length-preserving replacement of that path prefix in the
FMU archives and expanded copies. It does not alter FMI identifiers, equations,
value references, or scenarios. The committed manifest hashes the sanitized
release artifacts.

## Reproduce the build

From the repository root:

```powershell
python tools\preflight_fmi_contracts.py
python tools\regen_all.py
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
python -m unittest discover -s tests -v
```

The generator always refreshes derived adapters, entry points, API headers,
and CMake files. Existing `scenario.c` files are preserved because they are
user-owned experiment definitions.

## Reproduce the experiments

Point the runners to the configured build tree:

```powershell
$env:FMU2HOST_BUILD_DIR = (Resolve-Path build)
python tools\run_all_tests.py
python tools\run_paired_modes.py
python tools\run_fmpy_triangulation.py
python tools\run_extremevalues_isolation.py
python tools\export_oracle_catalog.py
python tools\collect_evidence.py --timing-repetitions 10
```

`run_all_tests.py` returns a non-zero status when any retained oracle fails;
this is expected for the retained five partial-failure models. The paired-mode
runner also returns non-zero if an execution fails. Consult the generated
reports rather than treating either status as a build failure.

The principal evidence files are:

- `results/HISTORICAL_SUITE.md`
- `results/suite_summary.md` (generated legacy detail)
- `results/paired_modes/README.md`
- `results/paired_modes/paired_modes.json`
- `results/fmpy_triangulation/triangulation.json`
- `results/extremevalues_isolation/isolation.json`
- `results/preflight/preflight.json`
- `results/oracles/oracle_catalog.csv`
- `results/oracles/excluded_solver_specific.csv`
- `results/evidence/artifact_manifest.json`
- `results/evidence/model_metrics.csv`
- `results/evidence/generation_timings.csv`

## Supported semantics and boundaries

The generator targets FMI 2.0 source FMUs containing OpenModelica-compatible C
sources. ME supports fixed-step Euler and RK4, step-boundary state-event
detection, discrete-state iteration, `nextEventTime` step clamping, and
termination requests. Inputs are piecewise constant over each ME macro-step.
CS delegates advancement and event handling to `fmi2DoStep` in the exported
FMU.

The project does not claim arbitrary-FMU support, FMI 3.0 support, adaptive ME
integration, sub-step root localization, asynchronous CS, or bare-metal
deployment. FMI scalar `Real`, `Integer`, `Boolean`, and `String` variables are
supported; unsupported scalar kinds are rejected explicitly. Structured FMI
2.0 interfaces remain dependent on the exporter metadata.

The legacy artifact name `CSPuro_SinME` is retained for traceability, but its
`modelDescription.xml` declares both ME and CS. It must not be interpreted as
a CS-only benchmark.

## Reproducibility definition

Here, reproducibility means that the same source FMU and generator version can
regenerate the model-dependent host structure and rerun the preserved scenario
and regression configuration. It does not mean bit-identical compiler output
across operating systems or toolchains. The manifest records SHA-256 hashes so
that a published release can be tied to the exact evaluated artifacts.

## Citation and release

The evaluated public snapshot is identified by the Git tag `article-v1.1`.
The SHA-256 manifest binds that tag to the evaluated FMUs and generator. The
manuscript is maintained separately and is not part of the tag.

## License

See [LICENSE](LICENSE). Third-party code embedded in exported FMUs remains
subject to its original notices and licenses.
