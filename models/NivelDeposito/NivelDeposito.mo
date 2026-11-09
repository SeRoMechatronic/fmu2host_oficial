model NivelDeposito "Tank level controller — pump + 3 alarm outputs — FMI 2.0 ME"
  // ============================================================================
  // NivelDeposito.mo
  // Liquid tank level controller with pump output and alarm LEDs.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Models a liquid storage tank level control loop. A first-order low-pass
  //   filter cleans the sensor signal. A proportional controller drives a pump
  //   to maintain the level at 50%. A manual valve input adds a feedforward
  //   disturbance compensation term. Three Boolean outputs signal minimum level
  //   alarm, maximum level alarm and pump active status.
  //
  // Interface:
  //   Inputs  : sensor_nivel    (Real [0,1])  — normalized level sensor
  //             valvula_manual  (Boolean)     — manual outlet valve open/closed
  //   Outputs : bomba           (Real [0,1])  — pump drive signal
  //             alarma_minimo   (Boolean)     — level below 20%
  //             alarma_maximo   (Boolean)     — level above 80%
  //             bomba_activa    (Boolean)     — pump is running (drive > 5%)
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real nivel_min = 0.2 "Low-level alarm threshold (normalized). Default: 20% of capacity";
  parameter Real nivel_max = 0.8 "High-level alarm threshold (normalized). Default: 80% of capacity";
  parameter Real area = 1.0 "Tank cross-sectional area (m²). Reserved for physical extensions";
  parameter Real Q_bomba_max = 0.5 "Maximum pump flow rate (m³/s) at drive signal = 1.0";
  parameter Real Q_valvula = 0.3 "Outlet flow rate when manual valve is open (m³/s)";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput sensor_nivel "Normalized tank level sensor [0,1]. 0=empty, 1=full" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}}), iconTransformation(origin = {0, -10}, extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.BooleanInput valvula_manual "Manual outlet valve state. true=open (flow leaving tank), false=closed" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput bomba "Pump drive signal [0,1]. 0=stopped, 1=full speed" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput alarma_minimo "ON when filtered level drops below nivel_min (20%)" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput alarma_maximo "ON when filtered level exceeds nivel_max (80%)" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput bomba_activa "ON when pump drive signal exceeds 5% — pump is physically running" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real nivel_filtrado(start = 0.5) "First-order filtered level. Time constant = 2.0 s. Initial value = 50%";
  Real error_nivel "Level error: desired level (0.5) minus filtered level";
  Real Q_salida "Current outlet flow rate (m³/s). Zero if valve is closed";
equation
// First-order low-pass filter on the sensor signal (tau = 2.0 s).
// This removes measurement noise and prevents rapid pump oscillation.
  der(nivel_filtrado) = (sensor_nivel - nivel_filtrado)/2.0;
// Error from the fixed setpoint of 50% tank level.
// Positive error → level too low → pump must increase speed.
  error_nivel = 0.5 - nivel_filtrado;
// Feedforward: if the manual valve is open, account for the outgoing flow.
  Q_salida = if valvula_manual then Q_valvula else 0.0;
// Proportional controller output with feedforward compensation.
// Gain = 2.0. Valve feedforward adds Q_salida/Q_bomba_max to compensate
// the flow loss before the level starts dropping.
  bomba = min(1.0, max(0.0, 0.5 + 2.0*error_nivel - Q_salida/Q_bomba_max));
// Alarm outputs based on filtered (not raw) level for noise immunity
  alarma_minimo = nivel_filtrado < nivel_min;
  alarma_maximo = nivel_filtrado > nivel_max;
// Pump active flag: drive signal must exceed a small threshold
  bomba_activa = bomba > 0.05;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {245, 250, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 60, 130}, extent = {{-90, 95}, {90, 72}}, textString = "NivelDeposito"), Rectangle(lineColor = {0, 80, 160}, fillColor = {200, 225, 255}, fillPattern = FillPattern.Solid, lineThickness = 1.5, extent = {{-60, 60}, {-10, -60}}), Rectangle( lineColor = {0, 80, 160}, fillColor = {100, 180, 255}, fillPattern = FillPattern.Solid, extent = {{-59, -60}, {-11, 0}}), Line(points = {{-60, 30}, {-10, 30}}, color = {255, 0, 0}, pattern = LinePattern.Dash), Line(points = {{-60, -30}, {-10, -30}}, color = {255, 140, 0}, pattern = LinePattern.Dash), Line(points = {{-61, 30}, {-101, 30}}, color = {0, 0, 180}), Text(textColor = {0, 0, 180}, extent = {{-52, 50}, {-18, 62}}, textString = "~"), Ellipse(fillColor = {220, 220, 220}, fillPattern = FillPattern.Solid, extent = {{-5, -10}, {25, -40}}), Text(extent = {{-3, -14}, {23, -36}}, textString = "P"), Line(points = {{-10, -25}, {-5, -25}}, color = {0, 80, 160}, thickness = 1.5), Line(points = {{25, -25}, {45, -25}}, color = {0, 80, 160}, thickness = 1.5), Polygon(lineColor = {0, 100, 0}, fillColor = {0, 180, 0}, fillPattern = FillPattern.Solid, points = {{-70, -30}, {-80, -20}, {-80, -40}, {-70, -30}}), Text(origin = {2, 0},textColor = {0, 120, 0}, extent = {{-98, -42}, {-62, -56}}, textString = "V"), Ellipse(origin = {0, 12},fillColor = {255, 140, 0}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {0, 12},textColor = {200, 100, 0}, extent = {{84, -4}, {100, -20}}, textString = "MIN"), Ellipse(origin = {0, 6},fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {0, 6},textColor = {180, 0, 0}, extent = {{84, -40}, {100, -56}}, textString = "MAX"), Ellipse(fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(origin = {-2, -2},textColor = {0, 160, 60}, extent = {{84, -70}, {100, -86}}, textString = "ON"), Line(points = {{45, -25}, {70, 40}}, color = {0, 80, 200}), Line(points = {{70, 40}, {100, 40}}, color = {0, 80, 200})}),
    Documentation(info = "<html>
      <h3>NivelDeposito — Tank Level Controller</h3>
      <p>Proportional level controller for a liquid storage tank.
         A first-order filter (tau=2s) conditions the sensor.
         Feedforward compensates manual valve disturbances.</p>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Signal</th><th>Type</th><th>Description</th></tr>
        <tr><td>sensor_nivel</td><td>RealInput</td><td>Normalized level [0,1]</td></tr>
        <tr><td>valvula_manual</td><td>BooleanInput</td><td>Outlet valve open/closed</td></tr>
        <tr><td>bomba</td><td>RealOutput</td><td>Pump drive [0,1]</td></tr>
        <tr><td>alarma_minimo</td><td>BooleanOutput</td><td>Level &lt; 20%</td></tr>
        <tr><td>alarma_maximo</td><td>BooleanOutput</td><td>Level &gt; 80%</td></tr>
        <tr><td>bomba_activa</td><td>BooleanOutput</td><td>Pump running</td></tr>
      </table>
    </html>"));
end NivelDeposito;
