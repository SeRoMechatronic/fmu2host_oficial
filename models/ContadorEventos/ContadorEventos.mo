model ContadorEventos "Event counter 0-99 with BCD outputs and overflow flag — FMI 2.0 ME"
  // ============================================================================
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.BooleanInput evento "Event signal. Counter increments on each rising edge (false→true)" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}}), iconTransformation(origin = {0, -14}, extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.BooleanInput reset "Reset signal. Rising edge clears the counter to 0. Overrides evento" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}}), iconTransformation(origin = {0, 38}, extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.IntegerOutput cuenta "Current counter value [0, 99]" annotation(
    Placement(transformation(extent = {{100, 50}, {120, 70}}), iconTransformation(origin = {0, -24}, extent = {{100, 50}, {120, 70}})));
  Modelica.Blocks.Interfaces.IntegerOutput decenas "Tens digit of counter value [0, 9]. For 7-segment display digit 1" annotation(
    Placement(transformation(extent = {{100, 10}, {120, 30}}), iconTransformation(origin = {0, -6}, extent = {{100, 10}, {120, 30}})));
  Modelica.Blocks.Interfaces.IntegerOutput unidades "Units digit of counter value [0, 9]. For 7-segment display digit 0" annotation(
    Placement(transformation(extent = {{100, -30}, {120, -10}}), iconTransformation(origin = {0, 12}, extent = {{100, -30}, {120, -10}})));
  Modelica.Blocks.Interfaces.BooleanOutput desbordamiento "ON when counter has reached its maximum value of 99" annotation(
    Placement(transformation(extent = {{100, -70}, {120, -50}})));
  // ── Internal state ────────────────────────────────────────────────────────
  discrete Integer contador(start = 0, fixed = true);

  //Integer contador(start = 0) "Internal counter state. Updated only on discrete events";
equation
// Event handling with priority: reset > event increment.
// pre(contador) uses the value from just before the current event.
// Saturation: counter holds at 99 instead of wrapping around.
 when {edge(evento), reset} then
  contador = if reset then 0
             else if pre(contador) >= 99 then 99
             else pre(contador) + 1;
  end when;
// Outputs — algebraic functions of the discrete counter state
  cuenta = contador;
  decenas = div(contador, 10);
  unidades = mod(contador, 10);
  desbordamiento = contador >= 99;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {0, 2},fillColor = {245, 255, 245}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 80, 0}, extent = {{-90, 95}, {90, 72}}, textString = "ContadorEventos"), Rectangle(origin = {1, -21},fillColor = {20, 20, 20}, fillPattern = FillPattern.Solid, extent = {{-21, 62}, {21, 6}}), Text(origin = {1, -7},textColor = {0, 255, 0}, extent = {{-17, 35}, {17, 5}}, textString = "8 8", fontSize = 48), Line(origin = {0, -14},points = {{-100, 40}, {-75, 40}, {-75, 55}, {-55, 55}, {-55, 40}, {-20, 40}}, color = {0, 120, 0}, thickness = 1.5), Text(origin = {0, -14},textColor = {0, 120, 0}, extent = {{-98, 60}, {-52, 70}}, textString = "EVT"), Line(origin = {0, 34},points = {{-100, -35}, {-20, -35}}, color = {180, 0, 0}, thickness = 1.5), Polygon(origin = {2, 34},lineColor = {180, 0, 0}, fillColor = {180, 0, 0}, fillPattern = FillPattern.Solid, points = {{-30, -30}, {-30, -40}, {-22, -35}, {-30, -30}}), Text(origin = {4, 22},textColor = {180, 0, 0}, extent = {{-98, -22}, {-52, -12}}, textString = "RST"), Ellipse(origin = {0, 12},fillColor = {255, 140, 0}, fillPattern = FillPattern.Solid, extent = {{30, -62}, {50, -82}}), Text(origin = {-52, 14},textColor = {200, 100, 0}, extent = {{52, -64}, {80, -80}}, textString = "OVF"), Line(origin = {0, -24},points = {{22, 60}, {100, 60}}, color = {0, 120, 0}), Line(origin = {0, -6},points = {{20, 20}, {100, 20}}, color = {0, 0, 180}), Line(origin = {0, 12},points = {{20, -20}, {100, -20}}, color = {0, 0, 180}), Line(origin = {0, 12},points = {{50, -72}, {100, -72}}, color = {200, 100, 0})}),
    Documentation(info = "<html>
      <h3>ContadorEventos — Discrete Event Counter</h3>
      <p>Counts rising edges on the evento input. Saturates at 99. Reset has
         priority. BCD decomposition outputs drive two 7-segment displays.</p>
    </html>"));
end ContadorEventos;
