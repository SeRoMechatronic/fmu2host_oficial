model CTPID "Temperature PID controller — fan output + 3 status LEDs — FMI 2.0 ME"
  // ============================================================================
  // CTPID.mo
  // Temperature PID controller with fan output and 3 status LEDs.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Receives a normalized temperature sensor reading and a normalized setpoint
  //   from a potentiometer. Runs a continuous PID controller and drives a fan
  //   output. Three Boolean outputs indicate whether the setpoint is above,
  //   below or equal to the measured temperature (within a dead-band epsilon).
  //
  // Interface:
  //   Inputs  : temperatura      (Real [0,1]) — normalized temperature sensor
  //             consigna         (Real [0,1]) — normalized setpoint potentiometer
  //   Outputs : ventilador       (Real [0,1]) — fan drive signal
  //             ledPorEncima     (Boolean)    — setpoint above temperature
  //             ledPorDebajo     (Boolean)    — setpoint below temperature
  //             ledAlcanzado     (Boolean)    — setpoint reached (within epsilon)
  //
  // PID gains (tunable via parameters):
  //   Kp = 2.0,  Ki = 0.5,  Kd = 0.1
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real Kp = 2.0 "Proportional gain of the PID controller";
  parameter Real Ki = 0.5 "Integral gain of the PID controller";
  parameter Real Kd = 0.1 "Derivative gain of the PID controller";
  parameter Real T_min = 0.0 "Minimum physical temperature mapped to input 0.0 (degrees)";
  parameter Real T_max = 100.0 "Maximum physical temperature mapped to input 1.0 (degrees)";
  parameter Real epsilon = 1.0 "Dead-band around setpoint (degrees). Within this band ledAlcanzado fires";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput temperatura "Normalized temperature sensor reading [0,1] — maps to [T_min, T_max]" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput consigna "Normalized setpoint from potentiometer [0,1] — maps to [T_min, T_max]" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput ventilador "Fan drive signal [0,1]. 0 = off, 1 = full speed" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput ledPorEncima "ON when setpoint is more than epsilon ABOVE measured temperature" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput ledPorDebajo "ON when setpoint is more than epsilon BELOW measured temperature" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput ledAlcanzado "ON when |error| <= epsilon — setpoint has been reached" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real error "Control error in physical units: setpoint_real - temperatura_real";
  Real integrador(start = 0.0) "Integral accumulator of the error over time";
  Real derivador "Derivative of the error with respect to time";
  Real error_prev(start = 0.0) "Previous error value (kept for reference; der() used for derivative)";
  Real pid_raw "Raw PID output before normalization and clamping";
  Real consigna_real "Setpoint converted to physical temperature units";
  Real temperatura_real "Measured temperature converted to physical units";
equation
// Denormalize both signals to physical temperature range [T_min, T_max]
  consigna_real = T_min + consigna*(T_max - T_min);
  temperatura_real = T_min + temperatura*(T_max - T_min);
// Control error (positive → temperature is below setpoint → need more cooling)
  error = consigna_real - temperatura_real;
// Integral term: accumulate error over time
  der(integrador) = error;
// Derivative term: rate of change of error
  derivador = der(error);
// PID output in physical units
  pid_raw = Kp*error + Ki*integrador + Kd*derivador;
// Normalize PID output to [0,1] fan signal and clamp to valid range
  ventilador = min(1.0, max(0.0, pid_raw/(T_max - T_min)));
// Status LEDs based on physical error and dead-band
  ledPorEncima = consigna_real > temperatura_real + epsilon;
  ledPorDebajo = consigna_real < temperatura_real - epsilon;
  ledAlcanzado = abs(error) <= epsilon;
// Track previous error (algebraic assignment — no dynamic effect here)
  error_prev = error;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {240, 248, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 0, 128}, extent = {{-90, 95}, {90, 72}}, textString = "CTPID"), Rectangle(lineColor = {0, 0, 180}, fillColor = {200, 220, 255}, fillPattern = FillPattern.Solid, lineThickness = 1, extent = {{-35, 35}, {35, -35}}), Text(textColor = {0, 0, 180}, extent = {{-28, 18}, {28, -18}}, textString = "PID", fontSize = 18), Rectangle(origin = {-6, -6},lineColor = {180, 0, 0}, fillColor = {255, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-88, 55}, {-72, 35}}), Ellipse(origin = {-6, -6},lineColor = {180, 0, 0}, fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{-90, 32}, {-70, 22}}), Text(origin = {-6, -6},textColor = {180, 0, 0}, extent = {{-98, 68}, {-62, 58}}, textString = "T", fontSize = 20), Rectangle(origin = {-6, -6},lineColor = {0, 100, 0}, fillColor = {200, 240, 200}, fillPattern = FillPattern.Solid, extent = {{-88, -25}, {-62, -45}}), Line(origin = {-6, -6},points = {{-75, -25}, {-75, -15}}, color = {0, 100, 0}), Text(origin = {-4, -6},textColor = {0, 100, 0}, extent = {{-98, -48}, {-52, -60}}, textString = "SP", fontSize = 20), Ellipse(lineColor = {0, 0, 180}, fillColor = {220, 235, 255}, fillPattern = FillPattern.Solid, extent = {{68, 52}, {92, 28}}), Line(points = {{80, 50}, {80, 42}}, color = {0, 0, 200}, thickness = 1.5), Line(points = {{80, 38}, {80, 30}}, color = {0, 0, 200}, thickness = 1.5), Line(points = {{72, 40}, {90, 40}}, color = {0, 0, 200}, thickness = 1.5), Text(textColor = {0, 0, 180}, extent = {{64, 56}, {96, 66}}, textString = "FAN", fontSize = 20), Ellipse(origin = {2, 12},fillColor = {0, 100, 255}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {0, 14},textColor = {0, 80, 200}, extent = {{84, -4}, {100, -20}}, textString = "▲"), Ellipse(origin = {2, 8},fillColor = {220, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {0, 6},textColor = {180, 0, 0}, extent = {{84, -40}, {100, -56}}, textString = "▼"), Ellipse(origin = {2, 0},fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(textColor = {0, 160, 60}, extent = {{84, -70}, {100, -86}}, textString = "="), Line(points = {{-78, 38}, {-35, 15}}, color = {180, 0, 0}), Line(points = {{-68, -41}, {-35, -15}}, color = {0, 100, 0}), Line(points = {{35, 20}, {68, 38}}, color = {0, 0, 200}), Line(points = {{35, 0}, {64, 0}}, color = {0, 80, 200}), Line(points = {{35, -5}, {66, -34}}, color = {180, 0, 0}), Line(points = {{35, -10}, {68, -70}}, color = {0, 160, 60})}),
    Documentation(info = "<html>
      <h3>CTPID — Temperature PID Controller</h3>
      <p>Continuous PID controller that regulates temperature using a fan.
         Both the sensor and setpoint are normalized inputs [0,1] that are
         mapped to a physical range [T_min, T_max].</p>
      <h4>Inputs</h4>
      <ul>
        <li><b>temperatura</b>: normalized sensor reading [0,1]</li>
        <li><b>consigna</b>: normalized setpoint from potentiometer [0,1]</li>
      </ul>
      <h4>Outputs</h4>
      <ul>
        <li><b>ventilador</b>: fan drive [0,1]</li>
        <li><b>ledPorEncima</b>: setpoint above temperature (heating needed)</li>
        <li><b>ledPorDebajo</b>: setpoint below temperature (cooling needed)</li>
        <li><b>ledAlcanzado</b>: within epsilon dead-band</li>
      </ul>
    </html>"));
end CTPID;
