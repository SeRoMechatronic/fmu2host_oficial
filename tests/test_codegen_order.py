import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from fmu_codegen_host import generate_main_cs
from fmu_parser import FMUInfo, Variable


class CoSimulationOrderingTests(unittest.TestCase):
    def test_step_completes_before_outputs_are_sampled(self):
        info = FMUInfo(
            model_name="OrderingProbe",
            model_identifier="OrderingProbe",
            guid="{probe}",
            description="",
            generation_tool="test",
            has_cs=True,
            has_me=True,
            n_states=0,
            n_event_indicators=0,
            me_identifier="OrderingProbe",
            cs_identifier="OrderingProbe",
            variables=[
                Variable("u", 1, "input", "continuous", "Real"),
                Variable("guard", 2, "output", "discrete", "Boolean"),
            ],
        )

        source = generate_main_cs(info)
        set_position = source.index("set_real")
        step_position = source.index("do_step")
        time_position = source.index("t += step", step_position)
        get_position = source.index("get_boolean")
        callback_position = source.index("on_outputs", get_position)

        self.assertLess(set_position, step_position)
        self.assertLess(step_position, time_position)
        self.assertLess(time_position, get_position)
        self.assertLess(get_position, callback_position)


if __name__ == "__main__":
    unittest.main()
