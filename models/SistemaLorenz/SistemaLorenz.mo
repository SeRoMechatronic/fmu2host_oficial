model SistemaLorenz "Lorenz chaotic attractor — 3 states, extreme sensitivity to integration method"
  // ============================================================================
  // SistemaLorenz.mo
  // The Lorenz system — a 3-state chaotic attractor.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   The Lorenz system is the canonical example of deterministic chaos.
  //   Its three coupled nonlinear ODEs produce a trajectory that orbits the
  //   famous butterfly-shaped attractor in phase space.
  //
  //   This model is an extreme stress test for numerical integration:
  //     - With Euler (h=0.01): the trajectory leaves the attractor before t=5 s
  //     - With RK4 (h=0.01):  the trajectory stays on the attractor for 50+ s
  //
  //   The trajectory divergence between Euler and RK4 is so dramatic that it
  //   is unmistakable in any plot of x_out, y_out, or z_out.
  //
  // Physics (classical Lorenz parameters):
  //   dx/dt = σ·(y - x)
  //   dy/dt = x·(ρ - z) - y
  //   dz/dt = x·y - β·z
  //
  //   With σ=10, ρ=28, β=8/3:
  //     - Two unstable fixed points at (±√(β(ρ-1)), ±√(β(ρ-1)), ρ-1)
  //     - Chaotic behavior for all non-equilibrium initial conditions
  //     - Attractor bounds: x ∈ [-25,25], y ∈ [-30,30], z ∈ [0,50]
  //
  // Interface:
  //   Outputs: x_out, y_out, z_out (Real) — trajectory coordinates
  //            on_attractor (Boolean)     — TRUE when z ∈ [0,60] and |x|<30
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real sigma = 10.0 "Prandtl number σ — controls x-y coupling";
  parameter Real rho = 28.0 "Rayleigh number ρ — controls instability";
  parameter Real beta = 8.0/3.0 "Geometric parameter β = 8/3 ≈ 2.667";
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput x_out "x-coordinate of the Lorenz trajectory — attractor range: [-25, 25]" annotation(
    Placement(transformation(extent = {{100, 40}, {120, 60}})));
  Modelica.Blocks.Interfaces.RealOutput y_out "y-coordinate of the Lorenz trajectory — attractor range: [-30, 30]" annotation(
    Placement(transformation(extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.RealOutput z_out "z-coordinate of the Lorenz trajectory — attractor range: [0, 50]" annotation(
    Placement(transformation(extent = {{100, -40}, {120, -20}})));
  Modelica.Blocks.Interfaces.BooleanOutput on_attractor "TRUE when trajectory is within expected attractor bounds: z ∈ [0,60], |x|<30, |y|<35" annotation(
    Placement(transformation(extent = {{100, -80}, {120, -60}})));
  // ── State variables ─────────────────────────────────────────────────────────
  Real x(start = 1.0, fixed = true) "Lorenz x state";
  Real y(start = 1.0, fixed = true) "Lorenz y state";
  Real z(start = 1.5, fixed = true) "Lorenz z state — must be > 0 initially";
equation
// Lorenz system ODEs — highly nonlinear, chaotic
  der(x) = sigma*(y - x);
  der(y) = x*(rho - z) - y;
  der(z) = x*y - beta*z;
// Outputs
  x_out = x;
  y_out = y;
  z_out = z;
// Attractor bounds check — FALSE means the trajectory has escaped (bad integration)
  on_attractor = z >= 0.0 and z <= 60.0 and abs(x) < 30.0 and abs(y) < 35.0;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {245, 240, 255}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {60, 0, 120}, extent = {{-90, 95}, {90, 70}}, textString = "Lorenz Attractor"), Text(origin = {0, -6},textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "σ=10  ρ=28  β=8/3"), Ellipse(lineColor = {120, 0, 180}, lineThickness = 1.5, extent = {{-70, 30}, {-20, -10}}), Ellipse(lineColor = {120, 0, 180}, lineThickness = 1.5, extent = {{20, 30}, {70, -10}}), Line(points = {{-45, 10}, {45, 10}}, color = {120, 0, 180}, thickness = 0.5), Text(origin = {18, 0},textColor = {60, 0, 120}, extent = {{50, 58}, {98, 42}}, textString = "x"), Text(origin = {18, 2},textColor = {60, 0, 120}, extent = {{50, 18}, {98, 2}}, textString = "y"), Text(origin = {18, 2},textColor = {60, 0, 120}, extent = {{50, -22}, {98, -38}}, textString = "z"), Text(textColor = {200, 0, 0}, extent = {{50, -62}, {98, -78}}, textString = "bounded"), Rectangle(origin = {-24, 7},lineColor = {180, 0, 180}, fillColor = {240, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-67, -46}, {67, -67}}), Text(origin = {-24, -2}, textColor = {100, 0, 150}, extent = {{-63, -41}, {63, -56}}, textString = "Euler diverges at t≈5 s")}),
    Documentation(info = "<html>
      <h3>SistemaLorenz — Lorenz Chaotic Attractor</h3>
      <p>The Lorenz system is the canonical test for numerical integration quality.
         With the classical parameters (σ=10, ρ=28, β=8/3), the trajectory orbits
         the butterfly attractor indefinitely.</p>
      <h4>Integration sensitivity</h4>
      <ul>
        <li><b>Euler (h=0.01)</b>: trajectory escapes attractor before t=5 s.
            on_attractor becomes FALSE.</li>
        <li><b>RK4 (h=0.01)</b>: trajectory stays bounded for 50+ seconds.
            on_attractor stays TRUE.</li>
      </ul>
      <h4>Attractor bounds</h4>
      <p>x ∈ [-25,25],  y ∈ [-30,30],  z ∈ [0,50] (approximate)</p>
    </html>"));
end SistemaLorenz;
