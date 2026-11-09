model CSPuro_SinME "Purely algebraic Co-Simulation FMU — no continuous states, no Model Exchange"
  // ============================================================================
  // CSPuro_SinME.mo
  // Purely algebraic model intended for Co-Simulation export only.
  // FMI 2.0 Co-Simulation compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model contains ZERO continuous states and ZERO differential equations.
  //   It exercises the Co-Simulation code path (doStep loop) which is entirely
  //   different from the Model Exchange path. There is no solver involved —
  //   outputs are computed as direct algebraic functions of inputs at every
  //   communication step.
  //
  //   This is the minimal stress test for a codegen tool: does it generate a
  //   coherent doStep() body when there is nothing to integrate?
  //
  // Interface:
  //   Inputs  : u1     (Real)    — first operand
  //             u2     (Real)    — second operand
  //   Outputs : y_sum  (Real)    — u1 + u2
  //             y_prod (Real)    — u1 * u2
  //             active (Boolean) — true when u1 > u2
  //
  // Export note:
  //   When exporting from OpenModelica, select Co-Simulation (NOT Model Exchange)
  //   in the FMU export dialog. This ensures doStep() is generated instead of
  //   getContinuousStates() / setContinuousStates().
  // ============================================================================
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput u1 "First operand — any real value" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput u2 "Second operand — any real value" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput y_sum "Sum of both inputs: u1 + u2" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.RealOutput y_prod "Product of both inputs: u1 * u2" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput active "TRUE when u1 is strictly greater than u2" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
equation
// Purely algebraic — no der(), no when, no state variables.
// Every output is recalculated at each communication step.
  y_sum = u1 + u2;
  y_prod = u1*u2;
  active = u1 > u2;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {240, 248, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 0, 128}, extent = {{-90, 95}, {90, 70}}, textString = "CS Pure"), Text(origin = {0, 2},textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "No States / Co-Sim only"), Text(origin = {-18, -4}, extent = {{-95, 55}, {-45, 38}}, textString = "u1"), Text(origin = {-20, -4},extent = {{-95, -25}, {-45, -42}}, textString = "u2"), Ellipse(origin = {-5, -10},lineColor = {0, 0, 200}, fillColor = {200, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-25, 38}, {25, -13}}), Text(origin = {-5, -9},textColor = {0, 0, 200}, extent = {{-18, 32}, {18, -6}}, textString = "+×"), Line(points = {{14, 18}, {100, 40}}, color = {0, 0, 200}), Line(points = {{20, 2}, {100, 0}}, color = {0, 100, 0}), Line(origin = {0, -12},points = {{16, 2}, {100, -40}}, color = {200, 0, 0}), Text(origin = {0, -18},textColor = {0, 0, 200}, extent = {{50, 52}, {98, 38}}, textString = "sum"), Text(origin = {0, -10},textColor = {0, 100, 0}, extent = {{50, 12}, {98, -2}}, textString = "prod"), Text(origin = {0, -14},textColor = {200, 0, 0}, extent = {{50, -28}, {98, -42}}, textString = "active")}),
    Documentation(info = "<html>
      <h3>CSPuro_SinME — Purely Algebraic Co-Simulation FMU</h3>
      <p>This model contains <b>no continuous states</b> and <b>no differential equations</b>.
         It is designed to exercise the <b>Co-Simulation code path</b> (doStep loop) of a
         code generation tool, which is structurally different from the Model Exchange path.</p>
      <p>When there is nothing to integrate, the codegen must still produce a coherent
         <code>doStep()</code> body that simply evaluates algebraic expressions and updates outputs.</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Direction</th><th>Description</th></tr>
        <tr><td>u1</td><td>Real</td><td>Input</td><td>First operand</td></tr>
        <tr><td>u2</td><td>Real</td><td>Input</td><td>Second operand</td></tr>
        <tr><td>y_sum</td><td>Real</td><td>Output</td><td>u1 + u2</td></tr>
        <tr><td>y_prod</td><td>Real</td><td>Output</td><td>u1 * u2</td></tr>
        <tr><td>active</td><td>Boolean</td><td>Output</td><td>u1 &gt; u2</td></tr>
      </table>
      <h4>Export</h4>
      <p>Export as <b>Co-Simulation</b> (not Model Exchange) from the FMU dialog.</p>
    </html>"));
end CSPuro_SinME;
