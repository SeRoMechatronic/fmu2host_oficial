# Changelog

## Article release candidate

- Added independent ME and CS symbol-prefix handling.
- Added strict FMI 2.0 and scalar-type validation.
- Regenerated typed scenario support for both execution modes.
- Corrected final-step handling so simulations stop at the requested horizon.
- Added ME termination-request and `nextEventTime` handling.
- Preserved user-owned scenarios during bulk regeneration.
- Made unknown regression-check types fail explicitly.
- Added a 279-scenario paired ME/CS diagnostic study.
- Added SHA-256 artifact manifests and per-model engineering metrics.
- Added parser contract tests and public reproducibility documentation.

The original development history remains in the parent research workspace; it
is not part of this clean public release package.
