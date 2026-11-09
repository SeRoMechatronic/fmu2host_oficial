import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from oracle_scope import MODE_INDEPENDENT, SOLVER_SPECIFIC, classify_check


class OracleScopeTests(unittest.TestCase):
    def test_solver_discriminator_is_excluded(self):
        scope, rationale = classify_check(
            "OsciladorArmonico", {"id": "TC-OA-006"}, {"type": "bounded"}
        )
        self.assertEqual(SOLVER_SPECIFIC, scope)
        self.assertIn("Euler", rationale)

    def test_behavioral_check_is_mode_independent(self):
        scope, _ = classify_check(
            "BooleanLogica", {"id": "TC-BL-001"}, {"type": "final_value"}
        )
        self.assertEqual(MODE_INDEPENDENT, scope)

    def test_explicit_scope_overrides_scenario_table(self):
        scope, _ = classify_check(
            "OsciladorArmonico",
            {"id": "TC-OA-006"},
            {"type": "bounded", "oracle_scope": MODE_INDEPENDENT},
        )
        self.assertEqual(MODE_INDEPENDENT, scope)


if __name__ == "__main__":
    unittest.main()
