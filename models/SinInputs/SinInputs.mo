model SinInputs "Autonomous mass-spring-damper — zero inputs, exercises codegen with no fmi2SetReal calls"
  // ============================================================================
  // SinInputs.mo
  // Autonomous oscillator with NO inputs of any kind.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model has zero input variables. It is a classic mass-spring-damper
  //   system that runs autonomously from its initial conditions. The only
  //   external interface is through parameters (set at initialization) and
  //   outputs (read during simulation).
  //
  //   The key challenge for a codegen tool: when there are no inputs, the
  //   generated main.c must still be coherent — it must NOT generate any
  //   fmi2SetReal / fmi2SetBoolean calls in the step loop, and it must still
  //   correctly read outputs via fmi2GetReal.
  //
  // Physics:
  //   m * x'' + c * x' + k * x = 0
  //   Initial conditions: x(0) = x0, x'(0) = v0
  //
  //   With default parameters (m=1.5, c=0.3, k=10.0, x0=1.0, v0=0.0) the
  //   system produces a decaying oscillation at approximately 0.41 Hz.
  //
  // Interface:
  //   Parameters: masa, amortiguacion, rigidez, x0, v0
  //   Outputs   : posicion  (Real)    — displacement x(t)
  //               velocidad (Real)    — velocity     x'(t)
  //               energia   (Real)    — total mechanical energy (decays over time)
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real masa = 1.5 "Mass [kg]";
  parameter Real amortiguacion = 0.3 "Damping coefficient [N·s/m]";
  parameter Real rigidez = 10.0 "Spring stiffness [N/m]";
  parameter Real x0 = 1.0 "Initial displacement [m]";
  parameter Real v0 = 0.0 "Initial velocity [m/s]";
  // ── NO INPUTS — intentional ───────────────────────────────────────────────
  //   This model deliberately exposes no input connectors.
  //   The codegen must handle the case where the step loop has nothing to set.
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput posicion "Displacement of the mass: x(t) [m]" annotation(
    Placement(transformation(extent = {{100, 40}, {120, 60}}), iconTransformation(origin = {0, -10}, extent = {{100, 40}, {120, 60}})));
  Modelica.Blocks.Interfaces.RealOutput velocidad "Velocity of the mass: x'(t) [m/s]" annotation(
    Placement(transformation(extent = {{100, 0}, {120, 20}}), iconTransformation(origin = {0, -10}, extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.RealOutput energia "Total mechanical energy: 0.5*m*v² + 0.5*k*x² [J] — decays due to damping" annotation(
    Placement(transformation(extent = {{100, -40}, {120, -20}}), iconTransformation(origin = {0, -10}, extent = {{100, -40}, {120, -20}})));
  // ── State variables ────────────────────────────────────────────────────────
  Real x(start = 1.0, fixed = true) "Displacement state [m]";
  Real v(start = 0.0, fixed = true) "Velocity state [m/s]";
equation
// Second-order ODE: m*x'' + c*x' + k*x = 0
// Split into two first-order equations:
  der(x) = v;
  der(v) = -(rigidez/masa)*x - (amortiguacion/masa)*v;
// Output assignments
  posicion = x;
  velocidad = v;
  energia = 0.5*masa*v^2 + 0.5*rigidez*x^2;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {240, 255, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 100, 0}, extent = {{-90, 95}, {90, 70}}, textString = "No Inputs"), Text(textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "Autonomous mass-spring-damper"), Line( origin = {-20, -8},points = {{-60, 10}, {-50, 20}, {-40, 0}, {-30, 20}, {-20, 0}, {-10, 20}, {0, 10}}, color = {0, 120, 0}, thickness = 1.5), Rectangle( origin = {-20, -8},fillColor = {150, 200, 150}, fillPattern = FillPattern.Solid, extent = {{0, 20}, {30, 0}}), Text( origin = {-20, -8},extent = {{0, 18}, {30, 2}}, textString = "m"), Line( origin = {-20, -8},points = {{30, 10}, {45, 10}}, color = {0, 100, 0}), Rectangle( origin = {-20, -8},fillColor = {180, 180, 180}, fillPattern = FillPattern.Solid, extent = {{45, 18}, {60, 2}}), Line(origin = {-20, -8},points = {{60, 10}, {70, 10}}, color = {0, 100, 0}), Line( origin = {-20, -8},points = {{-60, 25}, {-60, -5}}, thickness = 2), Line( origin = {-20, -8},points = {{70, 25}, {70, -5}}, thickness = 2), Text(origin = {12, -8},textColor = {0, 100, 0}, extent = {{50, 58}, {98, 42}}, textString = "pos"), Text( origin = {14, -8},textColor = {0, 100, 0}, extent = {{50, 18}, {98, 2}}, textString = "vel"), Text(origin = {2, -6},textColor = {0, 100, 0}, extent = {{50, -22}, {98, -38}}, textString = "energy"), Rectangle(lineColor = {200, 0, 0}, fillColor = {255, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-90, -55}, {-10, -75}}), Text(textColor = {200, 0, 0}, extent = {{-88, -57}, {-12, -73}}, textString = "NO INPUT")}),
    Documentation(info = "<html>
      <h3>SinInputs — Autonomous Mass-Spring-Damper</h3>
      <p>This model has <b>zero input variables</b>. It is designed to verify that
         a codegen tool generates coherent <code>main.c</code> code when there is
         nothing to set via <code>fmi2SetReal</code> in the step loop.</p>
      <h4>Physics</h4>
      <p>m·x'' + c·x' + k·x = 0 with x(0)=1.0, x'(0)=0.0</p>
      <p>Default parameters: m=1.5 kg, c=0.3 N·s/m, k=10.0 N/m</p>
      <p>Natural frequency: ω₀ = √(k/m) ≈ 2.58 rad/s ≈ 0.41 Hz</p>
      <p>The <b>energia</b> output decays monotonically due to damping and can be
         used to verify correct integration.</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Direction</th><th>Description</th></tr>
        <tr><td>posicion</td><td>Real</td><td>Output</td><td>Displacement x(t)</td></tr>
        <tr><td>velocidad</td><td>Real</td><td>Output</td><td>Velocity x'(t)</td></tr>
        <tr><td>energia</td><td>Real</td><td>Output</td><td>Mechanical energy (decreasing)</td></tr>
      </table>
    </html>"));
end SinInputs;
