model ReguladorBateria "Battery charge regulator — 2nd order state-space + anti-windup — FMI 2.0 ME"
  // ============================================================================
  // ReguladorBateria.mo
  // Battery charge regulator — 2nd order controller with anti-windup.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Regulates battery charging current using a second-order resonant
  //   controller in state-space form. The controller maintains the battery
  //   voltage at V_nominal. Anti-windup feedback prevents integrator overflow
  //   when the output current is clamped. Three Boolean outputs indicate
  //   charging status, full-charge detection and overvoltage fault.
  //
  // Interface:
  //   Inputs  : tension_bateria  (Real [0,1]) — normalized battery voltage
  //             carga_conectada  (Boolean)    — charger enable signal
  //   Outputs : corriente_carga  (Real [0,1]) — charging current command
  //             cargando         (Boolean)    — actively charging
  //             carga_completa   (Boolean)    — battery full
  //             fallo_sobretension (Boolean)  — overvoltage fault
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real V_nominal = 0.75 "Target charging voltage (normalized). Regulator holds battery at this level";
  parameter Real V_max = 0.95 "Overvoltage protection threshold. Above this: fault active, charging stops";
  parameter Real V_carga_completa = 0.98 "Full charge threshold. Above this: charging complete";
  parameter Real wn = 10.0 "Natural frequency of the 2nd order controller (rad/s)";
  parameter Real zeta = 0.7 "Damping ratio. 0.7 gives optimal slightly-underdamped response";
  parameter Real I_max = 1.0 "Maximum charging current (normalized)";
  parameter Real Ki_aw = 0.5 "Anti-windup gain. Feeds back saturation error into the state equation";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput tension_bateria "Normalized battery voltage [0,1]. 1.0 = maximum cell voltage" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.BooleanInput carga_conectada "Charger enable. true=charging allowed, false=charger disconnected" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput corriente_carga "Charging current command [0,1]. 0=no charge, 1=maximum current" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput cargando "ON when charger is connected, voltage < full-charge level AND < overvoltage" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput carga_completa "ON when battery voltage reaches or exceeds V_carga_completa" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput fallo_sobretension "ON when battery voltage exceeds V_max — requires immediate intervention" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real x1(start = 0.0) "First state of the 2nd order controller (position-like integrator)";
  Real x2(start = 0.0) "Second state of the 2nd order controller (velocity-like integrator)";
  Real error_v "Voltage error: V_nominal - tension_bateria (zero when disconnected)";
  Real corriente_raw "Unsaturated current output computed from controller states";
  Real corriente_sat "Saturated current after clamping to [0, I_max]";
  Real aw_error "Anti-windup error: difference between saturated and unsaturated output";
equation
// Voltage error — zero when charger disconnected (prevents wind-up at rest)
  error_v = if carga_conectada then (V_nominal - tension_bateria) else 0.0;
// Second-order controller in state-space form.
// Equivalent transfer function: C(s) = wn² / (s² + 2ζωn·s + ωn²)
// x1 acts as a position integrator, x2 as a velocity integrator.
// The wn² * x1 term provides integral action (eliminates steady-state error).
  der(x1) = x2;
  der(x2) = wn*wn*error_v - 2.0*zeta*wn*x2 - wn*wn*x1 + Ki_aw*aw_error;
// Reconstruct output from states
  corriente_raw = x1 + x2/wn;
// Saturate to valid charging current range
  corriente_sat = min(I_max, max(0.0, corriente_raw));
// Anti-windup error fed back into x2 derivative to freeze integrator
// when output saturates, preventing slow recovery after saturation ends
  aw_error = corriente_sat - corriente_raw;
// Final output
  corriente_carga = corriente_sat;
// Status outputs
  cargando = carga_conectada and tension_bateria < V_carga_completa and tension_bateria < V_max;
  carga_completa = tension_bateria >= V_carga_completa;
  fallo_sobretension = tension_bateria > V_max;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {248, 252, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 80, 0}, extent = {{-90, 95}, {90, 72}}, textString = "ReguladorBateria"), Rectangle(fillColor = {220, 240, 200}, fillPattern = FillPattern.Solid, lineThickness = 1.5, extent = {{-60, 50}, {20, -50}}), Rectangle(fillColor = {180, 180, 180}, fillPattern = FillPattern.Solid, extent = {{20, 15}, {30, 35}}), Rectangle(lineColor = {0, 150, 0}, fillColor = {100, 200, 100}, fillPattern = FillPattern.Solid, extent = {{-58, -48}, {18, -10}}), Rectangle(lineColor = {200, 200, 0}, fillColor = {220, 220, 80}, fillPattern = FillPattern.Solid, extent = {{-58, -10}, {18, 30}}), Text(textColor = {0, 80, 0}, extent = {{-55, 35}, {15, 55}}, textString = "V"), Rectangle(lineColor = {0, 0, 180}, fillColor = {200, 215, 255}, fillPattern = FillPattern.Solid, extent = {{-85, 65}, {-35, 35}}), Text(origin = {-2, 2}, textColor = {0, 0, 180}, extent = {{-83, 62}, {-37, 38}}, textString = "2nd"), Ellipse(origin = {0, 12},fillColor = {0, 120, 255}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {0, 12},textColor = {0, 80, 220}, extent = {{84, -4}, {100, -20}}, textString = "CHG"), Ellipse(origin = {0, 6},fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {0, 6},textColor = {0, 160, 60}, extent = {{84, -40}, {100, -56}}, textString = "FUL"), Ellipse(fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(textColor = {180, 0, 0}, extent = {{84, -70}, {100, -86}}, textString = "OVR"), Line(points = {{30, 25}, {100, 40}}, color = {0, 0, 200}), Line(points = {{30, 25}, {62, 4}}, color = {0, 120, 255}), Line(points = {{30, 25}, {68, -34}}, color = {0, 200, 80}), Line(points = {{30, 25}, {66, -70}}, color = {200, 0, 0}), Text(origin = {-18, 56}, textColor = {0, 80, 220}, extent = {{84, -4}, {100, -20}}, textString = "I")}),
    Documentation(info = "<html>
      <h3>ReguladorBateria — Battery Charge Regulator</h3>
      <p>Second-order state-space controller with anti-windup for battery
         charge regulation. Provides smooth current control and prevents
         integrator wind-up during saturation.</p>
    </html>"));
end ReguladorBateria;
