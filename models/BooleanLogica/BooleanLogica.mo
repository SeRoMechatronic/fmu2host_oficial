model BooleanLogica "Combinational and sequential Boolean logic — latch, edge counter, XOR, threshold"
  // ============================================================================
  // BooleanLogica.mo
  // Mixed combinational and sequential Boolean logic with a real threshold input.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model combines:
  //     - Pure combinational logic: AND, OR, XOR of Boolean inputs
  //     - Sequential (clocked) logic: D-latch and rising-edge counter
  //     - Mixed Real+Boolean: Boolean output derived from a Real threshold
  //
  //   It exercises fmi2SetBoolean (inputs a, b, clk) and fmi2SetReal (umbral),
  //   and fmi2GetBoolean (y_and, y_or, y_xor, y_latch) and fmi2GetInteger
  //   (cuenta_flancos) in the same step loop — testing that mixed-type
  //   output reading works correctly.
  //
  //   The D-latch captures the value of input 'a' on every rising edge of 'clk'.
  //   The edge counter counts the total number of rising edges seen on 'clk'.
  //
  // Interface:
  //   Inputs  : a             (Boolean) — first logic input
  //             b             (Boolean) — second logic input
  //             clk           (Boolean) — clock signal (rising edge triggers latch)
  //             umbral        (Real)    — threshold for Boolean output above_threshold
  //   Outputs : y_and         (Boolean) — a AND b
  //             y_or          (Boolean) — a OR b
  //             y_xor         (Boolean) — a XOR b  (exclusive OR)
  //             y_latch       (Boolean) — D-latch: value of a at last rising edge of clk
  //             cuenta_flancos(Integer) — total rising edges counted on clk
  //             above_threshold(Boolean)— TRUE when umbral > 0.5
  // ============================================================================
  // ── Inputs ──────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.BooleanInput a "First Boolean logic input" annotation(
    Placement(transformation(extent = {{-120, 60}, {-100, 80}})));
  Modelica.Blocks.Interfaces.BooleanInput b "Second Boolean logic input" annotation(
    Placement(transformation(extent = {{-120, 20}, {-100, 40}})));
  Modelica.Blocks.Interfaces.BooleanInput clk "Clock input — rising edge (FALSE→TRUE) triggers latch capture and edge count" annotation(
    Placement(transformation(extent = {{-120, -20}, {-100, 0}})));
  Modelica.Blocks.Interfaces.RealInput umbral "Real threshold input — above_threshold output is TRUE when umbral > 0.5" annotation(
    Placement(transformation(extent = {{-120, -60}, {-100, -40}})));
  // ── Outputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.BooleanOutput y_and "Combinational: a AND b — TRUE only when both inputs are TRUE" annotation(
    Placement(transformation(extent = {{100, 70}, {120, 90}})));
  Modelica.Blocks.Interfaces.BooleanOutput y_or "Combinational: a OR b — TRUE when at least one input is TRUE" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput y_xor "Combinational: a XOR b — TRUE when inputs differ" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput y_latch "Sequential: D-latch output — holds value of 'a' captured at last rising edge of clk" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.IntegerOutput cuenta_flancos "Sequential: total count of rising edges detected on 'clk' since start" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  Modelica.Blocks.Interfaces.BooleanOutput above_threshold "Mixed Real+Boolean: TRUE when umbral > 0.5" annotation(
    Placement(transformation(origin = {110, -110}, extent = {{-10, -10}, {10, 10}}), iconTransformation(origin = {110, -110}, extent = {{-10, -10}, {10, 10}})));
  // ── Discrete state variables ─────────────────────────────────────────────────
  discrete Boolean latch(start = false, fixed = true) "Latch state: holds the Boolean value of 'a' captured at last clk rising edge";
  discrete Integer flancos(start = 0, fixed = true) "Edge counter: incremented on every rising edge of clk";
equation
// ── Combinational logic (purely algebraic) ───────────────────────────────────
  y_and = a and b;
  y_or = a or b;
  y_xor = (a or b) and not (a and b);
// XOR: true when a ≠ b
// ── Output aliases ────────────────────────────────────────────────────────────
  y_latch = latch;
  cuenta_flancos = flancos;
  above_threshold = umbral > 0.5;
// ── Sequential logic: triggered on rising edge of clk ────────────────────────
  when edge(clk) then
    latch = a;
// D-latch: capture a at clock edge
    flancos = pre(flancos) + 1;
// increment edge counter
  end when;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {0, 5}, fillColor = {245, 245, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 135}, {100, -135}}), Text(origin = {0, 44}, textColor = {0, 0, 150}, extent = {{-90, 95}, {90, 76}}, textString = "BooleanLogica"), Text(origin = {0, 44}, textColor = {100, 100, 100}, extent = {{-90, 74}, {90, 60}}, textString = "AND · OR · XOR · latch · counter"), Rectangle(lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{-95, 78}, {-45, 62}}), Text(textColor = {0, 150, 0}, extent = {{-93, 76}, {-47, 64}}, textString = "a (Bool)"), Rectangle(lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{-95, 38}, {-45, 22}}), Text(textColor = {0, 150, 0}, extent = {{-93, 36}, {-47, 24}}, textString = "b (Bool)"), Rectangle(lineColor = {180, 100, 0}, fillColor = {255, 235, 200}, fillPattern = FillPattern.Solid, extent = {{-95, -2}, {-45, -18}}), Text(textColor = {180, 100, 0}, extent = {{-93, -4}, {-47, -16}}, textString = "clk ↑"), Rectangle(lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-95, -42}, {-45, -58}}), Text(textColor = {0, 0, 180}, extent = {{-93, -44}, {-47, -56}}, textString = "umbral"), Ellipse(origin = {18, 34}, lineColor = {0, 100, 0}, fillColor = {230, 255, 230}, fillPattern = FillPattern.Solid, lineThickness = 1, extent = {{-25, 55}, {-5, 35}}), Text(origin = {18, 34}, textColor = {0, 100, 0}, extent = {{-23, 53}, {-7, 37}}, textString = "AND"), Ellipse(origin = {18, 24}, lineColor = {170, 85, 0}, fillColor = {230, 255, 230}, fillPattern = FillPattern.Solid, lineThickness = 1, extent = {{-25, 25}, {-5, 5}}), Text(origin = {14, 28}, textColor = {0, 100, 0}, extent = {{-17, 17}, {-5, 5}}, textString = "OR"), Ellipse(origin = {20, 12}, lineColor = {255, 170, 0}, fillColor = {230, 255, 230}, fillPattern = FillPattern.Solid, lineThickness = 1, extent = {{-25, -5}, {-5, -25}}), Text(origin = {20, 12}, textColor = {0, 100, 0}, extent = {{-23, -7}, {-7, -23}}, textString = "XOR"), Rectangle(origin = {-12, 6}, lineColor = {180, 100, 0}, fillColor = {255, 240, 210}, fillPattern = FillPattern.Solid, extent = {{-5, -35}, {25, -65}}), Text(origin = {-12, 6}, textColor = {150, 80, 0}, extent = {{-3, -38}, {23, -50}}, textString = "D-FF"), Text(origin = {-12, 6}, textColor = {150, 80, 0}, extent = {{-3, -52}, {23, -62}}, textString = "clk↑"), Text(origin = {14, 8}, textColor = {0, 0, 150}, extent = {{35, 88}, {95, 74}}, textString = "y_and"), Text(origin = {18, 8}, textColor = {0, 0, 150}, extent = {{35, 48}, {95, 34}}, textString = "y_or"), Text(origin = {16, 6}, textColor = {0, 0, 150}, extent = {{35, 8}, {95, -6}}, textString = "y_xor"), Text(origin = {6, 8}, textColor = {180, 100, 0}, extent = {{35, -32}, {95, -46}}, textString = "y_latch"), Text(origin = {14, 0}, textColor = {180, 0, 0}, extent = {{35, -72}, {95, -86}}, textString = "flancos"), Line(origin = {0, 2},points = {{-45, 68}, {-7, 77}}, color = {0, 150, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled}), Line(points = {{-45, 30}, {-7, 75}}, color = {0, 150, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled}), Line(points = {{-45, 70}, {-7, 41}}, color = {170, 85, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled}), Line(points = {{-45, 30}, {-7, 37}}, color = {170, 85, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled}), Line(points = {{13, 79}, {99, 80}}, color = {0, 0, 150}), Line(points = {{13, 39}, {99, 40}}, color = {0, 0, 150}), Line(points = {{15, -3}, {99, -2}}, color = {0, 0, 150}), Line(origin = {0, -2}, points = {{13, -40}, {99, -38}}, color = {180, 100, 0}), Text(origin = {-16, -20}, textColor = {255, 85, 127}, extent = {{41, -82}, {111, -98}}, textString = "above_threshold"), Line(origin = {0, 2}, points = {{-45, 68}, {-3, 1}}, color = {255, 170, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled}), Line(points = {{-45, 30}, {-5, -5}}, color = {255, 170, 0}, thickness = 1, arrow = {Arrow.None, Arrow.Filled})}),
    Documentation(info = "<html>
      <h3>BooleanLogica — Combinational and Sequential Logic</h3>
      <p>This model mixes purely combinational Boolean logic (AND, OR, XOR)
         with sequential logic (D-latch triggered by rising edge of clk)
         and a mixed Real→Boolean conversion (above_threshold).</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Description</th></tr>
        <tr><td>a, b</td><td>Boolean Input</td><td>Logic inputs</td></tr>
        <tr><td>clk</td><td>Boolean Input</td><td>Clock (rising edge)</td></tr>
        <tr><td>umbral</td><td>Real Input</td><td>Threshold value</td></tr>
        <tr><td>y_and</td><td>Boolean Output</td><td>a AND b</td></tr>
        <tr><td>y_or</td><td>Boolean Output</td><td>a OR b</td></tr>
        <tr><td>y_xor</td><td>Boolean Output</td><td>a XOR b</td></tr>
        <tr><td>y_latch</td><td>Boolean Output</td><td>D-latch (a at last clk↑)</td></tr>
        <tr><td>cuenta_flancos</td><td>Integer Output</td><td>Rising edge count</td></tr>
        <tr><td>above_threshold</td><td>Boolean Output</td><td>umbral &gt; 0.5</td></tr>
      </table>
    </html>"),
  Diagram(graphics));
end BooleanLogica;
