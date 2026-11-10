# Oracle catalog

The retained suite defines **762** checks: **696** belong to the primary preflight-valid population and **66** to the negative diagnostics. The frozen scope rule classifies **749** as mode-independent and **13** as solver-specific diagnostics.

`oracle_catalog.csv` records every check, its parameters, execution settings, scope, and the scenario author's documented rationale. `excluded_solver_specific.csv` is the complete audit list excluded from the mode-independent comparison.

The `oracle_basis` field is deliberately conservative: it distinguishes documented reference values, invariants, and solver-discrimination diagnostics without claiming an independent formal derivation where none was recorded.
