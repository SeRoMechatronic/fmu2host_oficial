model TiposMixtos "Mixed-type FMU — Real, Integer, Boolean inputs and outputs with String parameters"
  // ============================================================================
  // TiposMixtos.mo
  // FMU with all four FMI 2.0 base types: Real, Integer, Boolean, String.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model exercises every FMI 2.0 variable type in a single FMU.
  //   A codegen tool must generate fmi2Set*/fmi2Get* call sites for all
  //   four types: Real, Integer, Boolean, and String (as parameters).
  //
  //   The computation is deliberately simple so that test results are
  //   trivially verifiable by hand: no differential equations, no states.
  //
  // Interface:
  //   Inputs  : r_in  (Real)    — real input value
  //             i_in  (Integer) — integer input value
  //             b_in  (Boolean) — boolean input flag
  //   Params  : etiqueta (String) — sensor label (String param, read at init)
  //             unidad   (String) — engineering unit  (String param)
  //   Outputs : r_out (Real)    — r_in * 2.0
  //             i_out (Integer) — i_in + 1
  //             b_out (Boolean) — NOT b_in
  //             r_abs (Real)    — |r_in|
  // ============================================================================
  // ── String parameters ───────────────────────────────────────────────────────
  parameter String etiqueta = "sensor_principal" "Human-readable label for this sensor channel — exercises String parameter path";
  parameter String unidad = "m/s" "Engineering unit of the real input — exercises second String parameter";
  // ── Inputs ──────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput r_in "Real input — any value; output will be r_in * 2.0" annotation(
    Placement(transformation(extent = {{-120, 50}, {-100, 70}}), iconTransformation(origin = {0, -20}, extent = {{-120, 50}, {-100, 70}})));
  Modelica.Blocks.Interfaces.IntegerInput i_in "Integer input — output will be i_in + 1" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}}), iconTransformation(origin = {0, -20}, extent = {{-120, -10}, {-100, 10}})));
  Modelica.Blocks.Interfaces.BooleanInput b_in "Boolean input — output will be NOT b_in" annotation(
    Placement(transformation(extent = {{-120, -70}, {-100, -50}}), iconTransformation(origin = {0, -20}, extent = {{-120, -70}, {-100, -50}})));
  // ── Outputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput r_out "r_in multiplied by 2.0" annotation(
    Placement(transformation(extent = {{100, 50}, {120, 70}}), iconTransformation(origin = {0, -20}, extent = {{100, 50}, {120, 70}})));
  Modelica.Blocks.Interfaces.IntegerOutput i_out "i_in incremented by 1" annotation(
    Placement(transformation(extent = {{100, 10}, {120, 30}}), iconTransformation(origin = {0, -20}, extent = {{100, 10}, {120, 30}})));
  Modelica.Blocks.Interfaces.BooleanOutput b_out "Logical negation of b_in" annotation(
    Placement(transformation(extent = {{100, -30}, {120, -10}}), iconTransformation(origin = {0, -20}, extent = {{100, -30}, {120, -10}})));
  Modelica.Blocks.Interfaces.RealOutput r_abs "Absolute value of r_in — always >= 0" annotation(
    Placement(transformation(extent = {{100, -70}, {120, -50}}), iconTransformation(origin = {0, -20}, extent = {{100, -70}, {120, -50}})));
equation
// All purely algebraic — no states, no integration
  r_out = r_in*2.0;
  i_out = i_in + 1;
  b_out = not b_in;
  r_abs = abs(r_in);
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle( fillColor = {248, 248, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 6},textColor = {0, 0, 128}, extent = {{-90, 95}, {90, 72}}, textString = "TiposMixtos"), Text(origin = {0, 6},textColor = {100, 100, 100}, extent = {{-90, 70}, {90, 55}}, textString = "Real · Integer · Boolean · String"), Rectangle(origin = {0, -20},lineColor = {0, 0, 200}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-95, 72}, {-40, 52}}), Text(origin = {0, -20},textColor = {0, 0, 200}, extent = {{-93, 70}, {-42, 54}}, textString = "Real  r_in"), Rectangle(origin = {0, -20},lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{-95, 12}, {-40, -8}}), Text(origin = {0, -20},textColor = {0, 150, 0}, extent = {{-93, 10}, {-42, -6}}, textString = "Int   i_in"), Rectangle(origin = {0, -20},lineColor = {200, 100, 0}, fillColor = {255, 235, 200}, fillPattern = FillPattern.Solid, extent = {{-95, -48}, {-40, -68}}), Text(origin = {0, -20},textColor = {200, 100, 0}, extent = {{-93, -50}, {-42, -66}}, textString = "Bool  b_in"), Rectangle(origin = {0, -20},lineColor = {80, 80, 80}, fillColor = {230, 230, 230}, fillPattern = FillPattern.Solid, extent = {{-15, 40}, {15, -40}}), Text(origin = {0, -20},textColor = {60, 60, 60}, extent = {{-13, 35}, {13, -35}}, textString = "×2
+1
NOT
abs"), Line(origin = {0, -20},points = {{-40, 62}, {-15, 20}}, color = {0, 0, 200}), Line(origin = {0, -20},points = {{-40, 2}, {-15, 0}}, color = {0, 150, 0}), Line(origin = {0, -20},points = {{-40, -58}, {-15, -20}}, color = {200, 100, 0}), Rectangle(origin = {0, -20},lineColor = {0, 0, 200}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{40, 72}, {95, 52}}), Text(origin = {0, -20},textColor = {0, 0, 200}, extent = {{42, 70}, {93, 54}}, textString = "r_out"), Rectangle(origin = {0, -20},lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{40, 32}, {95, 12}}), Text(origin = {0, -20},textColor = {0, 150, 0}, extent = {{42, 30}, {93, 14}}, textString = "i_out"), Rectangle(origin = {0, -20},lineColor = {200, 100, 0}, fillColor = {255, 235, 200}, fillPattern = FillPattern.Solid, extent = {{40, -8}, {95, -28}}), Text(origin = {0, -20},textColor = {200, 100, 0}, extent = {{42, -10}, {93, -26}}, textString = "b_out"), Rectangle(origin = {0, -20},lineColor = {150, 0, 150}, fillColor = {240, 210, 255}, fillPattern = FillPattern.Solid, extent = {{40, -48}, {95, -68}}), Text(origin = {0, -20},textColor = {150, 0, 150}, extent = {{42, -50}, {93, -66}}, textString = "r_abs"), Line(origin = {0, -20},points = {{15, 20}, {40, 62}}, color = {0, 0, 200}), Line(origin = {0, -20},points = {{15, 5}, {40, 22}}, color = {0, 150, 0}), Line(origin = {0, -20},points = {{15, -10}, {40, -18}}, color = {200, 100, 0}), Line(origin = {0, -20},points = {{15, -25}, {40, -58}}, color = {150, 0, 150})}),
    Documentation(info = "<html>
      <h3>TiposMixtos — All Four FMI 2.0 Base Types</h3>
      <p>This model exercises every variable type defined in the FMI 2.0 standard
         in a single FMU: <b>Real</b>, <b>Integer</b>, <b>Boolean</b>, and
         <b>String</b> (as parameters).</p>
      <p>The model is purely algebraic (zero states, no integration) so that
         every output can be verified by hand inspection.</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Direction</th><th>Formula</th></tr>
        <tr><td>r_in</td><td>Real</td><td>Input</td><td>—</td></tr>
        <tr><td>i_in</td><td>Integer</td><td>Input</td><td>—</td></tr>
        <tr><td>b_in</td><td>Boolean</td><td>Input</td><td>—</td></tr>
        <tr><td>etiqueta</td><td>String</td><td>Parameter</td><td>read at init</td></tr>
        <tr><td>unidad</td><td>String</td><td>Parameter</td><td>read at init</td></tr>
        <tr><td>r_out</td><td>Real</td><td>Output</td><td>r_in × 2</td></tr>
        <tr><td>i_out</td><td>Integer</td><td>Output</td><td>i_in + 1</td></tr>
        <tr><td>b_out</td><td>Boolean</td><td>Output</td><td>NOT b_in</td></tr>
        <tr><td>r_abs</td><td>Real</td><td>Output</td><td>|r_in|</td></tr>
      </table>
    </html>"));
end TiposMixtos;
