model PotVumetro "5-LED VU meter driven by a potentiometer — FMI 2.0 ME compatible"
  // ============================================================================
  // PotVumetro.mo
  // 5-LED VU meter controlled by a potentiometer signal.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Takes a normalized potentiometer reading (0.0 to 1.0) and activates
  //   up to 5 LEDs in a bar-graph fashion. Each LED lights when the input
  //   crosses its threshold. No continuous states, no dynamic memory,
  //   no file I/O — fully self-contained FMU.
  //
  // Interface:
  //   Inputs  : pot         (Real  [0,1]) — potentiometer signal
  //   Outputs : led1..led5  (Boolean)    — LED activation signals
  //
  // Thresholds:
  //   led1 >= 0.20  (green)
  //   led2 >= 0.40  (green)
  //   led3 >= 0.60  (yellow)
  //   led4 >= 0.80  (orange)
  //   led5 >= 1.00  (red)
  // ============================================================================
  // ── Input ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput pot(min = 0.0, max = 1.0) "Normalized potentiometer signal in range [0.0, 1.0]" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.BooleanOutput led1 "LED 1 (green)  — ON when pot >= 0.20" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{100, 60}, {120, 80}}), iconTransformation(extent = {{100, 60}, {120, 80}})));
  Modelica.Blocks.Interfaces.BooleanOutput led2 "LED 2 (green)  — ON when pot >= 0.40" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{100, 30}, {120, 50}}), iconTransformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput led3 "LED 3 (yellow) — ON when pot >= 0.60" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{100, 0}, {120, 20}}), iconTransformation(extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.BooleanOutput led4 "LED 4 (orange) — ON when pot >= 0.80" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{100, -30}, {120, -10}}), iconTransformation(extent = {{100, -30}, {120, -10}})));
  Modelica.Blocks.Interfaces.BooleanOutput led5 "LED 5 (red)    — ON when pot >= 1.00 (full scale)" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{100, -60}, {120, -40}}), iconTransformation(extent = {{100, -60}, {120, -40}})));
equation
// Each LED activates when the potentiometer signal reaches its threshold.
// Using >= so the LED turns ON exactly at the threshold value.
  led1 = pot >= 0.2;
  led2 = pot >= 0.4;
  led3 = pot >= 0.6;
  led4 = pot >= 0.8;
  led5 = pot >= 1.0;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {// Outer frame
    Rectangle(extent = {{-100, 100}, {100, -100}}, lineColor = {0, 0, 0}, fillColor = {245, 245, 245}, fillPattern = FillPattern.Solid), // Title
    Text(extent = {{-90, 95}, {90, 70}}, lineColor = {0, 0, 128}, textString = "PotVumetro"), // Potentiometer body
    Rectangle(extent = {{-80, 10}, {-40, -10}}, lineColor = {0, 0, 0}, fillColor = {180, 180, 180}, fillPattern = FillPattern.Solid), // Potentiometer wiper
    Line(points = {{-60, 10}, {-60, 30}}, color = {0, 0, 0}), // Potentiometer label
    Text(extent = {{-90, -20}, {-30, -40}}, lineColor = {0, 0, 0}, textString = "pot"), // LED 1 — green
    Ellipse(extent = {{60, 75}, {80, 55}}, lineColor = {0, 0, 0}, fillColor = {0, 200, 0}, fillPattern = FillPattern.Solid), Text(extent = {{82, 74}, {98, 56}}, lineColor = {0, 150, 0}, textString = "1"), // LED 2 — green
    Ellipse(extent = {{60, 45}, {80, 25}}, lineColor = {0, 0, 0}, fillColor = {0, 200, 0}, fillPattern = FillPattern.Solid), Text(extent = {{82, 44}, {98, 26}}, lineColor = {0, 150, 0}, textString = "2"), // LED 3 — yellow
    Ellipse(extent = {{60, 15}, {80, -5}}, lineColor = {0, 0, 0}, fillColor = {220, 220, 0}, fillPattern = FillPattern.Solid), Text(extent = {{82, 14}, {98, -4}}, lineColor = {180, 180, 0}, textString = "3"), // LED 4 — orange
    Ellipse(extent = {{60, -15}, {80, -35}}, lineColor = {0, 0, 0}, fillColor = {255, 140, 0}, fillPattern = FillPattern.Solid), Text(extent = {{82, -16}, {98, -34}}, lineColor = {200, 100, 0}, textString = "4"), // LED 5 — red
    Ellipse(extent = {{60, -45}, {80, -65}}, lineColor = {0, 0, 0}, fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid), Text(extent = {{82, -46}, {98, -64}}, lineColor = {180, 0, 0}, textString = "5"), // Wiring lines from potentiometer to LEDs
    Line(points = {{-40, 0}, {60, 65}}, color = {0, 0, 200}), Line(points = {{-40, 0}, {60, 35}}, color = {0, 0, 200}), Line(points = {{-40, 0}, {60, 5}}, color = {0, 0, 200}), Line(points = {{-40, 0}, {60, -25}}, color = {0, 0, 200}), Line(points = {{-40, 0}, {60, -55}}, color = {0, 0, 200})}),
    Documentation(info = "<html>
      <h3>PotVumetro</h3>
      <p>5-LED VU meter model driven by a single normalized potentiometer input.</p>
      <p>Each LED activates when the input crosses its fixed threshold.
         The model is purely algebraic (zero continuous states) and is fully
         compliant with FMI 2.0 Model Exchange and fmi-c-embedded.</p>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Output</th><th>Color</th><th>Threshold</th></tr>
        <tr><td>led1</td><td>Green</td><td>pot &ge; 0.20</td></tr>
        <tr><td>led2</td><td>Green</td><td>pot &ge; 0.40</td></tr>
        <tr><td>led3</td><td>Yellow</td><td>pot &ge; 0.60</td></tr>
        <tr><td>led4</td><td>Orange</td><td>pot &ge; 0.80</td></tr>
        <tr><td>led5</td><td>Red</td><td>pot &ge; 1.00</td></tr>
      </table>
    </html>"));
end PotVumetro;
