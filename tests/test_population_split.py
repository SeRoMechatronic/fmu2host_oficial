import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class PopulationSplitTests(unittest.TestCase):
    def test_primary_and_negative_diagnostic_populations_are_disjoint_and_additive(self):
        paired = json.loads(
            (ROOT / "results" / "paired_modes" / "paired_modes.json").read_text(encoding="utf-8")
        )
        populations = paired["populations"]
        primary = populations["primary_preflight_valid_behavioral"]
        negative = populations["negative_diagnostic"]
        full = populations["full_retained_diagnostic"]

        self.assertEqual(26, primary["models"])
        self.assertEqual(2, negative["models"])
        self.assertEqual(["ArraysVectores", "StringInputOutput"], negative["models_included"])
        self.assertEqual(full["models"], primary["models"] + negative["models"])
        self.assertEqual(full["scenarios"], primary["scenarios"] + negative["scenarios"])
        for mode in ("me", "cs"):
            for field in (
                "scenarios", "execution_ok", "execution_error", "oracle_pass",
                "checks_pass", "checks_fail", "mode_independent_checks_defined",
                "mode_independent_checks_evaluated", "mode_independent_checks_pass",
                "mode_independent_checks_fail", "mode_independent_checks_not_evaluated",
            ):
                self.assertEqual(
                    full[mode][field],
                    primary[mode][field] + negative[mode][field],
                    f"{mode}.{field}",
                )


if __name__ == "__main__":
    unittest.main()
