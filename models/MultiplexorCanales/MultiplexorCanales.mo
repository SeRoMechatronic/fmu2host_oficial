model MultiplexorCanales "4-to-1 analog multiplexer with Integer channel select — FMI 2.0 ME"
  // ============================================================================
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.IntegerInput canal_seleccion "Channel selector. Valid values: 0, 1, 2, 3" annotation(
    Placement(transformation(extent = {{-120, 50}, {-100, 70}}), iconTransformation(origin = {0, -8}, extent = {{-120, 50}, {-100, 70}})));
  Modelica.Blocks.Interfaces.RealInput canal_0 "Channel 0 analog input" annotation(
    Placement(transformation(extent = {{-120, 10}, {-100, 30}})));
  Modelica.Blocks.Interfaces.RealInput canal_1 "Channel 1 analog input" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}})));
  Modelica.Blocks.Interfaces.RealInput canal_2 "Channel 2 analog input" annotation(
    Placement(transformation(extent = {{-120, -30}, {-100, -10}})));
  Modelica.Blocks.Interfaces.RealInput canal_3 "Channel 3 analog input" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput salida "Selected channel output. 0.0 if channel selector is invalid" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.IntegerOutput canal_activo "Active channel number [0,3]. -1 if selector is invalid" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput canal_valido "ON when canal_seleccion is in range [0, 3]" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
equation
// Route the selected channel to output. Default to 0.0 for invalid select.
  salida = if canal_seleccion == 0 then canal_0 elseif canal_seleccion == 1 then canal_1
   elseif canal_seleccion == 2 then canal_2
   elseif canal_seleccion == 3 then canal_3 else 0.0;
// Report active channel as integer; -1 signals invalid selection
  canal_activo = if canal_seleccion >= 0 and canal_seleccion <= 3 then canal_seleccion else -1;
// Validity flag
  canal_valido = canal_seleccion >= 0 and canal_seleccion <= 3;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {245, 250, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 60, 120}, extent = {{-90, 95}, {90, 72}}, textString = "MultiplexorCanales"), Polygon(lineColor = {0, 60, 120}, fillColor = {200, 220, 255}, fillPattern = FillPattern.Solid, points = {{-20, 70}, {-20, -50}, {20, -30}, {20, 50}, {-20, 70}}), Text(textColor = {0, 60, 120}, extent = {{-18, 20}, {18, -10}}, textString = "MUX"), Line(origin = {0, -60}, points = {{-100, 60}, {-20, 60}}, color = {0, 80, 180}), Line(points = {{-100, 20}, {-20, 20}}, color = {0, 80, 180}), Line(points = {{-100, -20}, {-20, -20}}, color = {0, 80, 180}), Line(points = {{-100, -40}, {-20, -40}}, color = {0, 80, 180}), Text(origin = {-10, -16},textColor = {0, 60, 150}, extent = {{-98, 68}, {-52, 78}}, textString = "SEL"), Text(origin = {14, -18},textColor = {0, 60, 150}, extent = {{-98, 28}, {-52, 38}}, textString = "CH0"), Text(origin = {14, 2}, textColor = {0, 60, 150}, extent = {{-98, -12}, {-52, -2}}, textString = "CH1"), Text(origin = {14, 2}, textColor = {0, 60, 150}, extent = {{-98, -32}, {-52, -22}}, textString = "CH2"), Line(origin = {0, -8}, points = {{-100, 60}, {-20, 60}}, color = {60, 0, 120}), Line(points = {{20, 39}, {100, 40}}, color = {0, 80, 200}), Rectangle(origin = {0, 14}, lineColor = {0, 0, 150}, fillColor = {210, 215, 255}, fillPattern = FillPattern.Solid, extent = {{40, -2}, {85, -28}}), Text(origin = {0, 14}, textColor = {0, 0, 150}, extent = {{42, -4}, {83, -26}}, textString = "CH#"), Line(origin = {0, 10}, points = {{85, -11}, {100, -10}}, color = {0, 0, 150}), Ellipse(origin = {28, 10}, fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{40, -40}, {60, -60}}), Text(origin = {-4, -10}, textColor = {0, 160, 60}, extent = {{62, -42}, {100, -58}}, textString = "VAL"), Text(origin = {14, -38}, textColor = {0, 60, 150}, extent = {{-98, -12}, {-52, -2}}, textString = "CH3")}),
    Documentation(info = "<html>
      <h3>MultiplexorCanales — 4-to-1 Analog Multiplexer</h3>
      <p>Routes one of four Real inputs to the output using an Integer selector.
         Invalid selection produces 0.0 output and activates the fault flag.</p>
    </html>"),
  Diagram(graphics));
end MultiplexorCanales;
