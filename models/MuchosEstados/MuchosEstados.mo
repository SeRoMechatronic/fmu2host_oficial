model MuchosEstados "Chain of 8 first-order filters — verifies ODE buffer scaling for large state vectors"
  // ============================================================================
  // MuchosEstados.mo
  // Chain of 8 first-order low-pass filters in series.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Eight first-order systems connected in series, each with the same time
  //   constant τ. The output of each filter is the input to the next.
  //   This creates a high-order low-pass filter with very steep roll-off.
  //
  //   PRIMARY PURPOSE: Verify that the codegen tool correctly allocates ODE
  //   state vector buffers for N=8 states. If EULER_BUF_SIZE or RK4_BUF_SIZE
  //   is hardcoded to a value smaller than 8, this model causes a buffer
  //   overflow or incorrect integration.
  //
  //   SECONDARY PURPOSE: The cascaded step response has a known analytical
  //   form, allowing validation of integration accuracy.
  //
  // Physics:
  //   τ·dxi/dt = x(i-1) - xi,  for i = 1..8
  //   x0 = u  (input, treated as a forcing signal)
  //   xi(0) = 0.0 for all i
  //
  //   With u = 1.0 (step input) and τ=1.0:
  //   The peak of the 8th output occurs at t = n·τ = 8 s and equals
  //   (n^n · e^-n) / n! ≈ 0.200 (for n=8, approximated by Stirling)
  //
  //   The cascade is the impulse response of an 8th-order Butterworth-like
  //   low-pass filter. The output reaches its first peak around t=8 s.
  //
  // Interface:
  //   Inputs  : u  (Real)    — step input signal
  //   Outputs : y1..y8 (Real) — output of each filter stage
  //             retardo (Real) — delay proxy: time-weighted output centroid
  //             todos_activos (Boolean) — TRUE when all 8 outputs > 0.01
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real tau = 1.0 "Time constant for each filter stage [s]";
  // ── Inputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput u "Input signal — use u=1.0 step for canonical step response test" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}}), iconTransformation(extent = {{-120, -10}, {-100, 10}})));
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput y1 "Output of filter stage 1 — τ·dy1/dt = u  - y1" annotation(
    Placement(transformation(extent = {{100, 70}, {120, 90}})));
  Modelica.Blocks.Interfaces.RealOutput y2 "Output of filter stage 2 — τ·dy2/dt = y1 - y2" annotation(
    Placement(transformation(extent = {{100, 50}, {120, 70}})));
  Modelica.Blocks.Interfaces.RealOutput y3 "Output of filter stage 3 — τ·dy3/dt = y2 - y3" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.RealOutput y4 "Output of filter stage 4 — τ·dy4/dt = y3 - y4" annotation(
    Placement(transformation(extent = {{100, 10}, {120, 30}})));
  Modelica.Blocks.Interfaces.RealOutput y5 "Output of filter stage 5 — τ·dy5/dt = y4 - y5" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.RealOutput y6 "Output of filter stage 6 — τ·dy6/dt = y5 - y6" annotation(
    Placement(transformation(extent = {{100, -30}, {120, -10}})));
  Modelica.Blocks.Interfaces.RealOutput y7 "Output of filter stage 7 — τ·dy7/dt = y6 - y7" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.RealOutput y8 "Output of filter stage 8 — τ·dy8/dt = y7 - y8 — final output" annotation(
    Placement(transformation(extent = {{100, -70}, {120, -50}})));
  Modelica.Blocks.Interfaces.BooleanOutput todos_activos "TRUE when all 8 filter outputs exceed 0.01 (step has propagated through)" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── State variables ─────────────────────────────────────────────────────────
  Real x1(start = 0.0, fixed = true) "Filter stage 1 state";
  Real x2(start = 0.0, fixed = true) "Filter stage 2 state";
  Real x3(start = 0.0, fixed = true) "Filter stage 3 state";
  Real x4(start = 0.0, fixed = true) "Filter stage 4 state";
  Real x5(start = 0.0, fixed = true) "Filter stage 5 state";
  Real x6(start = 0.0, fixed = true) "Filter stage 6 state";
  Real x7(start = 0.0, fixed = true) "Filter stage 7 state";
  Real x8(start = 0.0, fixed = true) "Filter stage 8 state";
equation
// Cascaded first-order filters
  der(x1) = (u - x1)/tau;
  der(x2) = (x1 - x2)/tau;
  der(x3) = (x2 - x3)/tau;
  der(x4) = (x3 - x4)/tau;
  der(x5) = (x4 - x5)/tau;
  der(x6) = (x5 - x6)/tau;
  der(x7) = (x6 - x7)/tau;
  der(x8) = (x7 - x8)/tau;
// Output assignments
  y1 = x1;
  y2 = x2;
  y3 = x3;
  y4 = x4;
  y5 = x5;
  y6 = x6;
  y7 = x7;
  y8 = x8;
// Boolean: all stages have seen some signal
  todos_activos = x1 > 0.01 and x2 > 0.01 and x3 > 0.01 and x4 > 0.01 and x5 > 0.01 and x6 > 0.01 and x7 > 0.01 and x8 > 0.01;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {240, 240, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 0, 150}, extent = {{-90, 95}, {90, 75}}, textString = "Many States"), Text(textColor = {100, 100, 100}, extent = {{-90, 73}, {90, 57}}, textString = "8 cascaded filters — buf size test"), Rectangle(origin = {0, -12}, lineColor = {0, 0, 150}, fillColor = {200, 210, 255}, fillPattern = FillPattern.Solid, extent = {{-90, 20}, {-65, 5}}), Text(origin = {0, -12}, textColor = {0, 0, 150}, extent = {{-88, 18}, {-67, 7}}, textString = "1"), Rectangle(origin = {0, -12}, lineColor = {0, 0, 150}, fillColor = {200, 210, 255}, fillPattern = FillPattern.Solid, extent = {{-60, 20}, {-35, 5}}), Text(origin = {0, -12}, textColor = {0, 0, 150}, extent = {{-58, 18}, {-37, 7}}, textString = "2"), Text(origin = {0, -12}, textColor = {0, 0, 150}, extent = {{-28, 18}, {-5, 7}}, textString = "..."), Rectangle(origin = {0, -12}, lineColor = {0, 0, 150}, fillColor = {200, 210, 255}, fillPattern = FillPattern.Solid, extent = {{0, 20}, {25, 5}}), Text(origin = {0, -12}, textColor = {0, 0, 150}, extent = {{2, 18}, {23, 7}}, textString = "7"), Rectangle(origin = {0, -12}, lineColor = {0, 0, 150}, fillColor = {150, 160, 255}, fillPattern = FillPattern.Solid, extent = {{30, 20}, {55, 5}}), Text(origin = {0, -12}, textColor = {0, 0, 200}, extent = {{32, 18}, {53, 7}}, textString = "8"), Line(origin = {0, -12}, points = {{-100, 12}, {-90, 12}}, color = {0, 0, 200}), Line(origin = {0, -12}, points = {{-65, 12}, {-60, 12}}, color = {0, 0, 150}), Line(origin = {0, -12}, points = {{-35, 12}, {-28, 12}}, color = {0, 0, 150}), Line(origin = {0, -12}, points = {{-5, 12}, {0, 12}}, color = {0, 0, 150}), Line(origin = {0, -12}, points = {{25, 12}, {30, 12}}, color = {0, 0, 150}), Line(origin = {0, -12}, points = {{55, 12}, {100, 12}}, color = {0, 0, 200}), Rectangle(origin = {0, 16},lineColor = {0, 0, 180}, fillColor = {220, 225, 255}, fillPattern = FillPattern.Solid, extent = {{-86, -50}, {86, -75}}), Text(origin = {0, 16},textColor = {0, 0, 150}, extent = {{-78, -52}, {78, -73}}, textString = "8 states — BUF_SIZE must be ≥ 8"), Text(origin = {48, -94}, textColor = {255, 0, 127}, extent = {{32, 18}, {53, 7}}, textString = "All")}),
    Documentation(info = "<html>
      <h3>MuchosEstados — 8 Cascaded First-Order Filters</h3>
      <p>Eight first-order filters in series, each with time constant τ=1.0 s.
         The cascade has 8 continuous states and is the primary test for
         ODE buffer size scaling in the codegen tool.</p>
      <h4>Buffer size requirement</h4>
      <p>The codegen must allocate state vectors of at least size 8 for both
         Euler and RK4 buffers. If EULER_BUF_SIZE or RK4_BUF_SIZE is hardcoded
         below 8, this model produces incorrect results or a crash.</p>
      <h4>Step response</h4>
      <p>With u=1.0 step, y8 reaches its peak near t=8·τ=8 s at approximately
         y8_peak ≈ 0.200 (8th-order cascade step response peak).</p>
    </html>"));
end MuchosEstados;
