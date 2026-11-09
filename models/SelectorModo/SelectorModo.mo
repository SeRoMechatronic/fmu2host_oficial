model SelectorModo "Integer mode selector — actuator routing + status code — FMI 2.0 ME"
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Integer MODO_MANUAL = 0 "Integer code for manual operation mode";
  parameter Integer MODO_AUTO = 1 "Integer code for automatic operation mode";
  parameter Integer MODO_EMERGENCIA = 2 "Integer code for emergency stop mode";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.IntegerInput modo_operacion "Operation mode selector. Valid values: 0=Manual, 1=Auto, 2=Emergency" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput consigna_manual "Manual setpoint [0,1]. Used only when modo_operacion = MODO_MANUAL" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput salida_actuador "Actuator drive signal [0,1]. Forced to 0.0 in Emergency or unknown mode" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}}), iconTransformation(origin = {0, -4}, extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.IntegerOutput codigo_estado "Numeric status code: 1=Manual, 10=Auto, 99=Emergency, -1=Invalid" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}}), iconTransformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput fallo_modo "ON when modo_operacion is outside the valid range [0, 2]" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}}), iconTransformation(origin = {0, -22}, extent = {{100, -50}, {120, -30}})));
equation
// Route actuator output based on active mode.
// Unknown modes default to 0.0 (safe state — actuator off).
  salida_actuador = if modo_operacion == MODO_MANUAL then min(1.0, max(0.0, consigna_manual)) elseif modo_operacion == MODO_AUTO then 0.5
   elseif modo_operacion == MODO_EMERGENCIA then 0.0 else 0.0;
// Status code mapping for external monitoring or display
  codigo_estado = if modo_operacion == MODO_EMERGENCIA then 99 elseif modo_operacion == MODO_AUTO then 10
   elseif modo_operacion == MODO_MANUAL then 1 else -1;
// Fault: mode value outside defined range
  fallo_modo = modo_operacion < MODO_MANUAL or modo_operacion > MODO_EMERGENCIA;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {248, 245, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {60, 0, 120}, extent = {{-90, 95}, {90, 72}}, textString = "SelectorModo"), Ellipse(lineColor = {60, 0, 120}, fillColor = {230, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-70, 60}, {-20, 10}}), Line(points = {{-45, 35}, {-35, 50}}, color = {60, 0, 120}, thickness = 2), Text(textColor = {60, 0, 120}, extent = {{-72, 8}, {-18, -4}}, textString = "M A E"), Rectangle(lineColor = {0, 80, 0}, fillColor = {200, 240, 200}, fillPattern = FillPattern.Solid, extent = {{20, 50}, {55, 20}}), Text(textColor = {0, 80, 0}, extent = {{22, 48}, {53, 22}}, textString = "ACT"), Rectangle(lineColor = {0, 0, 150}, fillColor = {200, 210, 255}, fillPattern = FillPattern.Solid, extent = {{20, -10}, {55, -40}}), Text(textColor = {0, 0, 150}, extent = {{22, -12}, {53, -38}}, textString = "STS"), Ellipse(origin = {12, 0},fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -52}, {82, -72}}), Text(origin = {-8, -16},textColor = {180, 0, 0}, extent = {{84, -54}, {100, -70}}, textString = "ERR"), Line(points = {{-20, 35}, {20, 35}}, color = {60, 0, 120}), Line(points = {{55, 35}, {100, 35}}, color = {0, 80, 0}), Line(points = {{55, -25}, {100, 0}}, color = {0, 0, 150}), Line(points = {{55, -25}, {76, -58}}, color = {200, 0, 0}), Text(origin = {-224, 66}, textColor = {0, 0, 127}, extent = {{268, -54}, {319, -70}}, textString = "StateCode")}),
    Documentation(info = "<html>
      <h3>SelectorModo — Operation Mode Selector</h3>
      <p>Algebraic mode router. Integer input selects between Manual (0),
         Automatic (1) and Emergency (2) operation modes.</p>
    </html>"));
end SelectorModo;
