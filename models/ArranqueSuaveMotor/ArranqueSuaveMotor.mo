model ArranqueSuaveMotor "Soft-start motor controller with overload detection — FMI 2.0 ME"
  // ============================================================================
  // ArranqueSuaveMotor.mo
  // Soft-start motor controller with overload protection.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Implements a soft-start sequence for an electric motor. When the start
  //   command is given, the applied voltage ramps up gradually via a first-order
  //   filter (the ramp), followed by a second PT1 filter emulating the motor's
  //   electromagnetic response. A time-integrating overload detector with
  //   exponential decay distinguishes sustained overloads from short transient
  //   peaks, triggering a fault only after a configurable delay.
  //
  // Interface:
  //   Inputs  : orden_arranque  (Boolean)    — start/stop command
  //             carga_motor     (Real [0,1]) — normalized motor load
  //   Outputs : tension_aplicada (Real [0,1]) — applied voltage ramp output
  //             motor_en_marcha  (Boolean)   — motor fully started (>90%)
  //             fallo_sobrecarga (Boolean)   — sustained overload fault
  //             en_rampa         (Boolean)   — motor is in start-up ramp
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real tau_rampa = 3.0 "Time constant of the voltage ramp (s). Larger = slower start";
  parameter Real tau_pt1 = 0.5 "Time constant of the PT1 electromagnetic filter (s)";
  parameter Real umbral_sobrecarga = 0.9 "Overload threshold. Load above this level triggers the overload timer";
  parameter Real t_retardo = 2.0 "Time (s) the overload must persist before fallo_sobrecarga fires";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.BooleanInput orden_arranque "Start command. true=start, false=stop. Ramp rises on true, falls on false" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{-120, 30}, {-100, 50}}), iconTransformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput carga_motor "Normalized motor load [0,1]. 1.0 = maximum rated load" annotation(
    Placement(transformation(origin = {0, -10}, extent = {{-120, -50}, {-100, -30}}), iconTransformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput tension_aplicada "Applied voltage after ramp and PT1 filter [0,1]" annotation(
    Placement(transformation(origin = {0, 16}, extent = {{100, 30}, {120, 50}}), iconTransformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput motor_en_marcha "ON when start command is active AND tension_aplicada > 0.90" annotation(
    Placement(transformation(origin = {0, 16}, extent = {{100, -10}, {120, 10}}), iconTransformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput fallo_sobrecarga "ON when overload timer exceeds t_retardo — sustained overload detected" annotation(
    Placement(transformation(origin = {0, 16}, extent = {{100, -50}, {120, -30}}), iconTransformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput en_rampa "ON during start-up: command active but tension not yet at 90%" annotation(
    Placement(transformation(origin = {0, 16}, extent = {{100, -90}, {120, -70}}), iconTransformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real rampa(start = 0.0) "First-order ramp state. Tracks the step reference with time constant tau_rampa";
  Real tension_filtrada(start = 0.0) "PT1 filtered voltage. Emulates motor electromagnetic inertia";
  Real tiempo_sobrecarga(start = 0.0) "Overload accumulator. Counts up during overload, decays when normal";
  Real referencia_rampa "Step reference: 1.0 when start commanded, 0.0 when stop commanded";
equation
// Step reference: instantly switches between 0 and 1 on command change
  referencia_rampa = if orden_arranque then 1.0 else 0.0;
// First-order ramp: smooth transition from 0 to 1 (or back) with tau_rampa.
// At t = 3*tau_rampa (≈9s) the ramp reaches ~95% of its final value.
  der(rampa) = (referencia_rampa - rampa)/tau_rampa;
// PT1 electromagnetic filter on top of the ramp.
// Softens the remaining transients emulating motor winding inductance.
  der(tension_filtrada) = (rampa - tension_filtrada)/tau_pt1;
// Clamp final applied voltage to valid range
  tension_aplicada = min(1.0, max(0.0, tension_filtrada));
// Overload integrator with exponential decay.
// Integrates at rate +1.0 when load exceeds threshold.
// Decays exponentially (tau=0.5s) when load is within limits.
// This prevents brief spikes from triggering the fault.
  der(tiempo_sobrecarga) = if carga_motor > umbral_sobrecarga then 1.0 else -tiempo_sobrecarga/0.5;
// Status outputs
  motor_en_marcha = orden_arranque and tension_filtrada > 0.9;
  fallo_sobrecarga = tiempo_sobrecarga > t_retardo;
  en_rampa = orden_arranque and tension_filtrada < 0.9 and not fallo_sobrecarga;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {248, 245, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {80, 40, 0}, extent = {{-90, 95}, {90, 72}}, textString = "ArranqueSuaveMotor"), Ellipse(origin = {6, 20},fillColor = {220, 210, 190}, fillPattern = FillPattern.Solid, lineThickness = 1.5, extent = {{20, 50}, {80, -10}}), Text(origin = {6, 20},extent = {{25, 45}, {75, -5}}, textString = "M", fontSize = 36), Line(origin = {6, 20},points = {{80, 20}, {95, 20}}, thickness = 2), Rectangle(lineColor = {0, 80, 160}, fillColor = {200, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-60, 55}, {-10, 25}}), Line(points = {{-57, 28}, {-50, 28}, {-20, 52}, {-13, 52}}, color = {0, 80, 200}, thickness = 1.5), Text(textColor = {0, 80, 160}, extent = {{-58, 60}, {-12, 70}}, textString = "RAMP"), Rectangle(origin = {0, -4},lineColor = {180, 0, 0}, fillColor = {255, 210, 210}, fillPattern = FillPattern.Solid, extent = {{-60, -20}, {-10, -55}}), Text(origin = {0, -4},textColor = {180, 0, 0}, extent = {{-58, -22}, {-12, -38}}, textString = "OL"), Text(origin = {0, -4},textColor = {180, 0, 0}, extent = {{-58, -38}, {-12, -54}}, textString = "DET"), Line(points = {{-100, 40}, {-60, 40}}, color = {0, 120, 0}, thickness = 1.5), Text(textColor = {0, 120, 0}, extent = {{-98, 52}, {-62, 62}}, textString = "START"), Line(origin = {0, -4},points = {{-100, -35}, {-60, -35}}, color = {180, 80, 0}, thickness = 1.5), Text(textColor = {180, 80, 0}, extent = {{-98, -22}, {-62, -10}}, textString = "LOAD"), Ellipse(origin = {-4, 8},fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {-2, 10},textColor = {0, 160, 60}, extent = {{84, -4}, {100, -20}}, textString = "RUN"), Ellipse(origin = {-4, 6},fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {-2, 6},textColor = {180, 0, 0}, extent = {{84, -40}, {100, -56}}, textString = "FLT"), Ellipse(origin = {-4, 0},fillColor = {220, 200, 0}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(origin = {-2, 0},textColor = {180, 160, 0}, extent = {{84, -70}, {100, -86}}, textString = "RMP"), Line(points = {{-10, 40}, {26, 39}}, color = {0, 80, 160}), Line(points = {{88, 41}, {100, 40}}, color = {0, 80, 160}), Line(origin = {-30, 4},points = {{20, 31}, {88, -8}}, color = {0, 200, 80}), Line(points = {{-10, -41}, {58, -42}}, color = {200, 0, 0}), Line(origin = {-30, 4}, points = {{20, 25}, {88, -78}}, color = {220, 200, 0})}),
    Documentation(info = "<html>
      <h3>ArranqueSuaveMotor — Soft-Start Motor Controller</h3>
      <p>Two cascaded first-order filters create a smooth voltage ramp on start.
         An integrating overload detector with exponential decay protects the
         motor from sustained overloads without tripping on transient peaks.</p>
    </html>"));
end ArranqueSuaveMotor;
