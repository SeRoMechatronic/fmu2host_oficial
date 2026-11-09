model CodigoErrorDiagnostico "Priority-coded diagnostics for 3 analog channels — FMI 2.0 ME"
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real umbral_temperatura = 0.85 "Over-temperature threshold (normalized). Above this → error code 101";
  parameter Real umbral_tension = 0.1 "Under-voltage threshold (normalized). Below this → error code 202";
  parameter Real umbral_vibracion = 0.75 "Over-vibration threshold (normalized). Above this → error code 303";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput temperatura "Normalized temperature [0,1]" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, 50}, {-100, 70}}), iconTransformation(extent = {{-120, 50}, {-100, 70}})));
  Modelica.Blocks.Interfaces.RealInput tension "Normalized supply voltage [0,1]" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, 10}, {-100, 30}}), iconTransformation(extent = {{-120, 10}, {-100, 30}})));
  Modelica.Blocks.Interfaces.RealInput vibracion "Normalized vibration level [0,1]" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{-120, -30}, {-100, -10}}), iconTransformation(extent = {{-120, -30}, {-100, -10}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.IntegerOutput codigo_error "Error code: 0=OK, 101=Over-temp, 202=Under-volt, 303=Over-vibration" annotation(
    Placement(transformation(origin = {0, 20}, extent = {{100, 30}, {120, 50}}), iconTransformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.IntegerOutput nivel_prioridad "Priority level: 0=None, 1=Low, 2=Medium, 3=High" annotation(
    Placement(transformation(origin = {0, 20}, extent = {{100, -10}, {120, 10}}), iconTransformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput parada_emergencia "ON when nivel_prioridad >= 3 — immediate shutdown required" annotation(
    Placement(transformation(origin = {0, 20}, extent = {{100, -50}, {120, -30}}), iconTransformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.RealOutput factor_reduccion "Power derating factor: 1.0=full, 0.75=25% cut, 0.5=50% cut, 0.0=stop" annotation(
    Placement(transformation(origin = {0, 20}, extent = {{100, -90}, {120, -70}}), iconTransformation(extent = {{100, -90}, {120, -70}})));
equation
// Cascaded priority: temperature fault overrides voltage, which overrides
// vibration. Only the highest-priority active fault is reported.
  codigo_error = if temperatura > umbral_temperatura then 101 elseif tension < umbral_tension then 202
   elseif vibracion > umbral_vibracion then 303 else 0;
// Map error code to numeric priority level
  nivel_prioridad = if codigo_error == 101 then 3 elseif codigo_error == 202 then 2
   elseif codigo_error == 303 then 1 else 0;
// Emergency stop at highest priority
  parada_emergencia = nivel_prioridad >= 3;
// Graduated derating based on priority level
  factor_reduccion = if nivel_prioridad == 0 then 1.0 elseif nivel_prioridad == 1 then 0.75
   elseif nivel_prioridad == 2 then 0.5 else 0.0;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {255, 248, 245}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {120, 0, 0}, extent = {{-90, 95}, {90, 72}}, textString = "CodErrorDiag"), Rectangle(lineColor = {120, 0, 0}, fillColor = {255, 225, 220}, fillPattern = FillPattern.Solid, extent = {{-40, 60}, {30, 10}}), Text(textColor = {120, 0, 0}, extent = {{-38, 58}, {28, 40}}, textString = "DIAG"), Text(textColor = {80, 0, 0}, extent = {{-38, 40}, {28, 12}}, textString = "101
202
303"), Line(points = {{-100, 60}, {-40, 40}}, color = {180, 0, 0}), Text(origin = {-12, -30},textColor = {180, 0, 0}, extent = {{-98, 72}, {-52, 82}}, textString = "TEMP"), Line(points = {{-100, 20}, {-40, 30}}, color = {0, 0, 180}), Text(origin = {-8, -22},textColor = {0, 0, 180}, extent = {{-98, 30}, {-52, 42}}, textString = "VOLT"), Line(points = {{-100, -20}, {-40, 20}}, color = {0, 100, 0}), Text(origin = {-10, -14},textColor = {0, 100, 0}, extent = {{-98, -10}, {-52, 0}}, textString = "VIB"), Rectangle(origin = {0, -4}, lineColor = {0, 0, 100}, fillColor = {210, 215, 255}, fillPattern = FillPattern.Solid, extent = {{40, 55}, {85, 35}}), Text(origin = {0, -4}, textColor = {0, 0, 150}, extent = {{42, 53}, {83, 37}}, textString = "ERR"), Rectangle(origin = {0, -14}, lineColor = {100, 60, 0}, fillColor = {255, 235, 200}, fillPattern = FillPattern.Solid, extent = {{40, 25}, {85, 5}}), Text(origin = {0, -14}, textColor = {120, 60, 0}, extent = {{42, 23}, {83, 7}}, textString = "PRI"), Ellipse(origin = {14, -20}, fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{40, -10}, {60, -30}}), Text(origin = {-46, -20}, textColor = {180, 0, 0}, extent = {{62, -12}, {100, -28}}, textString = "STOP"), Line(origin = {0, -4}, points = {{85, 45}, {100, 45}}, color = {0, 0, 150}), Line(origin = {0, -14}, points = {{85, 15}, {100, 15}}, color = {120, 60, 0}), Line(points = {{74, -40}, {100, -40}}, color = {180, 0, 0}), Line(points = {{0, 10}, {0, -80}}, color = {0, 160, 60}), Line(origin = {-68, -20},points = {{68, -60}, {168, -60}}, color = {0, 160, 60})}),
    Documentation(info = "<html>
      <h3>CodigoErrorDiagnostico — Priority Fault Diagnostics</h3>
      <p>Monitors 3 channels with priority-coded output. Temperature has highest
         priority, vibration lowest. Provides graduated power derating.</p>
    </html>"),
  Diagram(graphics));
end CodigoErrorDiagnostico;
