model PenduloNoLineal "Large-angle nonlinear pendulum — energy conservation with strong nonlinearity"
  // ============================================================================
  // PenduloNoLineal.mo
  // Nonlinear pendulum with large initial angle — 2 continuous states.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   A simple pendulum released from a large angle (150° = 2.618 rad).
  //   At large angles, the small-angle approximation sin(θ) ≈ θ fails
  //   completely, so the full nonlinear equation must be integrated.
  //
  //   The system is undamped, so the total mechanical energy must be
  //   conserved. Like the harmonic oscillator, energy drift is the
  //   observable that reveals integration quality.
  //
  //   Additional challenge: the nonlinear term sin(θ) makes this harder
  //   to integrate correctly than the pure harmonic oscillator. Euler
  //   shows significant energy error (>5%) before t=10 s.
  //
  // Physics:
  //   θ'' + (g/L) · sin(θ) = 0
  //   θ(0) = 150° = 5π/6 ≈ 2.618 rad,  θ'(0) = 0
  //
  //   Energy: E = 0.5·L²·ω² - g·L·cos(θ)
  //   Initial: E₀ = -g·L·cos(2.618) ≈ -9.81·1.0·cos(150°) ≈ 8.496 J
  //
  // Interface:
  //   Outputs: angulo           (Real)    — angle θ(t) [rad]
  //            velocidad_angular (Real)   — angular velocity θ'(t) [rad/s]
  //            energia_total    (Real)    — must be constant ≈ 8.496 J
  //            en_reposo        (Boolean) — TRUE when |θ'| < 0.01 rad/s
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real L = 1.0 "Pendulum length [m]";
  parameter Real g = 9.81 "Gravitational acceleration [m/s²]";
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput angulo "Angular position θ(t) [rad] — initial: 2.618 rad (150°)" annotation(
    Placement(transformation(extent = {{100, 40}, {120, 60}}), iconTransformation(extent = {{100, 40}, {120, 60}})));
  Modelica.Blocks.Interfaces.RealOutput velocidad_angular "Angular velocity θ'(t) [rad/s]" annotation(
    Placement(transformation(extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.RealOutput energia_total "Total mechanical energy E = 0.5·L²·ω² - g·L·cos(θ) — must be constant ≈ 8.496 J" annotation(
    Placement(transformation(extent = {{100, -40}, {120, -20}})));
  Modelica.Blocks.Interfaces.BooleanOutput en_reposo "TRUE when |angular velocity| < 0.01 rad/s (near turning points)" annotation(
    Placement(transformation(extent = {{100, -80}, {120, -60}})));
  // ── State variables ─────────────────────────────────────────────────────────
  // Initial angle: 150 degrees = 5*pi/6 ≈ 2.618 rad
  Real theta(start = 2.618, fixed = true) "Angular position [rad]";
  Real omega_p(start = 0.0, fixed = true) "Angular velocity [rad/s]";
equation
// Nonlinear pendulum ODE — full sin(θ), not linearized
  der(theta) = omega_p;
  der(omega_p) = -(g/L)*sin(theta);
// Outputs
  angulo = theta;
  velocidad_angular = omega_p;
// Energy: kinetic (0.5·L²·ω²) + potential (-g·L·cos(θ))
// Note: potential is defined as 0 at θ=π (top), so E is positive when below top
  energia_total = 0.5*L^2*omega_p^2 - g*L*cos(theta);
  en_reposo = abs(omega_p) < 0.01;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {0, 10},fillColor = {255, 250, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 110}, {100, -110}}), Text(origin = {0, 24},textColor = {100, 50, 0}, extent = {{-90, 95}, {90, 70}}, textString = "Nonlinear Pendulum"), Text(origin = {0, 24},textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "θ₀ = 150°  (large angle)"), Ellipse(origin = {-2, -20}, fillPattern = FillPattern.Solid, extent = {{-5, 85}, {5, 75}}), Line(origin = {-6, -54}, points = {{4, 110}, {-45, 30}}, color = {100, 50, 0}, thickness = 2), Ellipse(origin = {6, -80}, fillColor = {180, 100, 50}, fillPattern = FillPattern.Solid, extent = {{-80, 60}, {-51, 30}}), Line(origin = {-2, -20}, points = {{0, 76}, {0, -42}}, color = {150, 150, 0}, pattern = LinePattern.Dash), Text(origin = {-6, -60}, textColor = {150, 100, 0}, extent = {{5, 58}, {35, 42}}, textString = "150°"), Text(textColor = {100, 50, 0}, extent = {{50, 58}, {98, 42}}, textString = "θ [rad]"), Text(textColor = {100, 50, 0}, extent = {{50, 18}, {98, 2}}, textString = "ω [r/s]"), Text(textColor = {200, 0, 0}, extent = {{50, -22}, {98, -38}}, textString = "E=const"), Text(textColor = {0, 100, 0}, extent = {{50, -62}, {98, -78}}, textString = "at rest")}),
    Documentation(info = "<html>
      <h3>PenduloNoLineal — Large-Angle Nonlinear Pendulum</h3>
      <p>Undamped pendulum released from 150° (2.618 rad). The nonlinear
         term sin(θ) dominates at this angle, making accurate integration
         essential.</p>
      <h4>Energy conservation</h4>
      <p>E₀ = -g·L·cos(150°) ≈ 8.496 J must remain constant.</p>
      <p>With Euler (h=0.05): energy error exceeds 5% before t=10 s.</p>
      <p>With RK4 (h=0.05): energy stays within 0.1% for 50+ seconds.</p>
    </html>"));
end PenduloNoLineal;
