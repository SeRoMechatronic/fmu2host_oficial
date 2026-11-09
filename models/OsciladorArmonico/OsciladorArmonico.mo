model OsciladorArmonico "Undamped harmonic oscillator — energy conservation reveals integrator quality"
  // ============================================================================
  // OsciladorArmonico.mo
  // Undamped harmonic oscillator — 2 continuous states.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   A classic undamped harmonic oscillator: no friction, no energy loss.
  //   The total mechanical energy must be EXACTLY conserved for all time.
  //
  //   This property makes it a perfect benchmark for numerical integration
  //   quality:
  //     - A first-order Euler method adds energy artificially over time
  //       (amplitude grows without bound).
  //     - A fourth-order Runge-Kutta method conserves energy very well
  //       for hundreds of cycles.
  //
  //   By plotting the 'energia' output over a long simulation, the codegen
  //   tool's choice of integrator becomes directly observable.
  //
  // Physics:
  //   x'' + ω² · x = 0
  //   x(0) = 1.0,  x'(0) = 0.0
  //   Exact solution: x(t) = cos(ω·t),  E(t) = 0.5·ω²  (constant)
  //
  // Interface:
  //   Outputs: posicion  (Real) — displacement x(t)
  //            velocidad (Real) — velocity x'(t)
  //            energia   (Real) — MUST be constant ≈ 0.5·ω² = 19.739
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real omega = 2.0*Modelica.Constants.pi "Angular frequency [rad/s] — default: 2π (one cycle per second)";
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput posicion "Displacement x(t) [m] — exact: cos(ω·t)" annotation(
    Placement(transformation(extent = {{100, 40}, {120, 60}})));
  Modelica.Blocks.Interfaces.RealOutput velocidad "Velocity x'(t) [m/s] — exact: -ω·sin(ω·t)" annotation(
    Placement(transformation(extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.RealOutput energia "Total mechanical energy E = 0.5·v² + 0.5·ω²·x² — must stay constant ≈ 19.739" annotation(
    Placement(transformation(extent = {{100, -40}, {120, -20}})));
  // ── State variables ─────────────────────────────────────────────────────────
  Real x(start = 1.0, fixed = true) "Displacement [m]";
  Real v(start = 0.0, fixed = true) "Velocity [m/s]";
equation
// Undamped harmonic oscillator ODEs
  der(x) = v;
  der(v) = -(omega^2)*x;
// Output assignments
  posicion = x;
  velocidad = v;
// Energy: kinetic (0.5·v²) + potential (0.5·ω²·x²)
// For x(0)=1, v(0)=0: E₀ = 0.5·ω² = 0.5·(2π)² ≈ 19.739 J
  energia = 0.5*v^2 + 0.5*(omega^2)*x^2;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {0, 2},fillColor = {255, 245, 230}, fillPattern = FillPattern.Solid, extent = {{-100, 102}, {100, -102}}), Text(origin = {0, 8},textColor = {150, 75, 0}, extent = {{-90, 95}, {90, 70}}, textString = "Harmonic Oscillator"), Text(origin = {-2, 8},textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "Energy conservation test"), Line(origin = {-8, -18},points = {{-80, 6}, {-55, 35}, {-40, 20}, {-25, 5}, {-10, 20}, {5, 35}, {20, 20}, {35, 5}, {50, 20}, {65, 35}}, color = {200, 100, 0}, thickness = 1.5, smooth = Smooth.Bezier), Text(origin = {10, 0},textColor = {150, 75, 0}, extent = {{50, 58}, {98, 42}}, textString = "pos"), Text(origin = {10, 0},textColor = {150, 75, 0}, extent = {{50, 18}, {98, 2}}, textString = "vel"), Text(textColor = {200, 0, 0}, extent = {{50, -22}, {98, -38}}, textString = "E = const"), Rectangle(lineColor = {200, 100, 0}, fillColor = {255, 230, 200}, fillPattern = FillPattern.Solid, extent = {{-80, -50}, {80, -75}}), Text(origin = {-1, -5}, textColor = {150, 50, 0}, extent = {{-73, -47}, {73, -66}}, textString = "E₀ = 0.5·ω² ≈ 19.739 J")}),
    Documentation(info = "<html>
      <h3>OsciladorArmonico — Undamped Harmonic Oscillator</h3>
      <p>Classic undamped oscillator. The total mechanical energy <b>must be
         conserved</b> for all time (no damping).</p>
      <p>This model is an integration quality benchmark: Euler adds energy
         artificially (amplitude grows), while RK4 conserves it accurately.</p>
      <h4>Exact solution</h4>
      <p>x(t) = cos(ω·t),  E(t) = 0.5·ω² ≈ 19.739 J (constant)</p>
      <h4>Key observable</h4>
      <p>Plot <code>energia</code> over 50+ seconds. With Euler (h=0.01):
         energy drifts upward. With RK4 (h=0.01): energy stays flat.</p>
    </html>"));
end OsciladorArmonico;
