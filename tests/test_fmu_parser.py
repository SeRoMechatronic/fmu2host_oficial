from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from fmu_parser import parse_fmu


def document(*, version="2.0", scalar="Real", me="MEPrefix", cs="CSPrefix") -> str:
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<fmiModelDescription fmiVersion="{version}" modelName="DifferentPrefixes"
 guid="{{test-guid}}" numberOfEventIndicators="0">
  <ModelExchange modelIdentifier="{me}"/>
  <CoSimulation modelIdentifier="{cs}"/>
  <ModelVariables>
    <ScalarVariable name="u" valueReference="1" causality="input">
      <{scalar} start="0"/>
    </ScalarVariable>
  </ModelVariables>
  <ModelStructure/>
</fmiModelDescription>
"""


class ParserContractTests(unittest.TestCase):
    def parse(self, xml: str):
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "modelDescription.xml"
            path.write_text(xml, encoding="utf-8")
            return parse_fmu(temporary)

    def test_rejects_non_fmi_2(self):
        with self.assertRaisesRegex(ValueError, "supports FMI 2.0 only"):
            self.parse(document(version="3.0"))

    def test_preserves_distinct_mode_identifiers(self):
        info = self.parse(document(me="ModelExchangeSymbols", cs="CoSimulationSymbols"))
        self.assertEqual(info.identifier_for("me"), "ModelExchangeSymbols")
        self.assertEqual(info.identifier_for("cs"), "CoSimulationSymbols")
        self.assertEqual(info.model_identifier, "ModelExchangeSymbols")

    def test_rejects_unsupported_scalar_types(self):
        with self.assertRaisesRegex(ValueError, "Unsupported FMI scalar type"):
            self.parse(document(scalar="Enumeration"))

    def test_known_legacy_named_model_declares_both_modes(self):
        info = parse_fmu(str(ROOT / "models" / "CS_Puro" / "CSPuro_SinME"))
        self.assertTrue(info.has_me)
        self.assertTrue(info.has_cs)


if __name__ == "__main__":
    unittest.main()
