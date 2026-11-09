model SuspensionActiva "Active suspension PD controller — FMI 2.0 ME"
  // ============================================================================
  // SuspensionActiva.mo
  // Active vehicle suspension controller — PD control with saturation detection.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Simulates an active suspension actuator. A fast first-order filter (tau=0.1s)
  //   conditions the road profile input. A PD controller (proportional + derivative)
  //   generates a counterforce to keep the vehicle body stable. The derivative
  //   channel is also filtered to prevent noise amplification. Three Boolean
  //   outputs indicate bump detection, actuator saturation and comfort mode.
  //
  // Interface:
  //   Inputs  : perfil_bache       (Real)      — wheel vertical displacement
  //             velocidad_vehiculo (Real [0,1]) — normalized vehicle speed
  //   Outputs : fuerza_actuador    (Real [-1,1]) — actuator force (clamped)
  //             bache_detectado    (Boolean)    — significant bump detected
  //             actuador_saturado  (Boolean)    — actuator at force limit
  //             modo_confort       (Boolean)    — low speed + no bump
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real tau_filtro = 0.1 "Filter time constant (s). Small value = fast tracking of road profile";
  parameter Real Kp_susp = 3.0 "Proportional gain. Scales force response to wheel displacement";
  parameter Real Kd_susp = 0.8 "Derivative gain. Scales force response to wheel velocity";
  parameter Real umbral_bache = 0.3 "Bump detection threshold. Filtered position above this triggers the flag";
  parameter Real sat_actuador = 1.0 "Maximum actuator force magnitude (normalized)";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput perfil_bache "Wheel vertical displacement from road profile. Positive = bump, negative = pothole" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput velocidad_vehiculo "Normalized vehicle speed [0,1]. Used for comfort mode detection" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput fuerza_actuador "Actuator force [-1,1]. Positive = upward, negative = downward" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}}), iconTransformation(origin = {0, -4}, extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput bache_detectado "ON when |filtered position| > umbral_bache" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput actuador_saturado "ON when raw force demand exceeds actuator physical limit" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput modo_confort "ON when speed < 0.3 AND no bump detected — soft ride mode" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real posicion_filtrada(start = 0.0) "Filtered wheel position. First-order filter with tau_filtro";
  Real velocidad_filtrada(start = 0.0) "Filtered wheel velocity. Derived from posicion_filtrada, then filtered again";
  Real fuerza_raw "Raw PD controller output before saturation clamp";
equation
// First-order filter on wheel position (fast, tau = 0.1 s)
  der(posicion_filtrada) = (perfil_bache - posicion_filtrada)/tau_filtro;
// Filter the velocity (derivative of filtered position) to reduce noise.
// Directly differentiating sensor signals amplifies high-frequency noise.
  der(velocidad_filtrada) = (der(posicion_filtrada) - velocidad_filtrada)/tau_filtro;
// PD control law: negative feedback — force opposes displacement and velocity.
// Positive position → downward displacement of wheel → actuator pushes UP.
  fuerza_raw = -(Kp_susp*posicion_filtrada + Kd_susp*velocidad_filtrada);
// Clamp actuator output to its physical force limits
  fuerza_actuador = min(sat_actuador, max(-sat_actuador, fuerza_raw));
// Status outputs
  bache_detectado = abs(posicion_filtrada) > umbral_bache;
  actuador_saturado = abs(fuerza_raw) >= sat_actuador;
  modo_confort = velocidad_vehiculo < 0.3 and not bache_detectado;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {245, 245, 250}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {40, 40, 120}, extent = {{-90, 95}, {90, 72}}, textString = "SuspensionActiva"), Rectangle(fillColor = {200, 200, 220}, fillPattern = FillPattern.Solid, extent = {{-50, 50}, {50, 20}}), Ellipse(fillColor = {80, 80, 80}, fillPattern = FillPattern.Solid, extent = {{-20, -20}, {20, -60}}), Line(points = {{0, 20}, {0, -20}}, color = {0, 0, 180}, thickness = 2), Line(points = {{10, 20}, {10, -20}}, color = {180, 0, 0}, thickness = 2), Polygon(lineColor = {180, 0, 0}, fillColor = {180, 0, 0}, fillPattern = FillPattern.Solid, points = {{10, -20}, {6, -10}, {14, -10}, {10, -20}}), Line(points = {{-100, 40}, {-60, 40}}, color = {80, 80, 80}), Text(textColor = {80, 80, 80}, extent = {{-98, 52}, {-52, 62}}, textString = "ROAD"), Line(origin = {0, -4},points = {{-100, -35}, {-70, -35}}, color = {0, 100, 0}), Text(origin = {-10, -12},textColor = {0, 100, 0}, extent = {{-98, -22}, {-52, -12}}, textString = "SPD"), Line(points = {{50, 35}, {100, 35}}, color = {180, 0, 0}), Ellipse(origin = {0, 10}, fillColor = {255, 160, 0}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {0, 10}, textColor = {200, 100, 0}, extent = {{84, -4}, {100, -20}}, textString = "BMP"), Ellipse(origin = {0, 8},fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {0, 8},textColor = {180, 0, 0}, extent = {{84, -40}, {100, -56}}, textString = "SAT"), Ellipse(fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(origin = {0, -2},textColor = {0, 160, 60}, extent = {{84, -70}, {100, -86}}, textString = "CMF"), Text(origin = {-137, 72}, textColor = {170, 85, 0}, extent = {{195, -8}, {232, -43}}, textString = "F_Act")}),
    Documentation(info = "<html>
      <h3>SuspensionActiva — Active Suspension PD Controller</h3>
      <p>PD controller with filtered derivative channel. Generates a counterforce
         against wheel displacement and velocity to stabilize the vehicle body.</p>
    </html>"));
end SuspensionActiva;
