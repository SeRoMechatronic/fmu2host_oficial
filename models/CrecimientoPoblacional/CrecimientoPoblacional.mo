model CrecimientoPoblacional "Logistic population growth — fast dynamics near inflection point"
  // ============================================================================
  // CrecimientoPoblacional.mo
  // Logistic growth model with external immigration rate.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   The logistic equation models population growth with a carrying capacity.
  //   The growth rate is fastest at N = K/2 (inflection point), creating
  //   a rapid transient that challenges numerical integrators.
  //
  //   Euler overshoots the equilibrium K and oscillates around it.
  //   RK4 converges smoothly to K from below.
  //
  //   With a small initial population (N=2) and high growth rate (r=3.5),
  //   the system reaches the inflection point quickly, and the difference
  //   between Euler and RK4 is visible within the first few time units.
  //
  // Physics:
  //   dN/dt = r·N·(1 - N/K) + u
  //   N(0) = 2.0,  K = 100.0,  r = 3.5
  //   u = external immigration rate (input, default 0)
  //
  //   Steady state: N* = K = 100 (when u = 0)
  //   Inflection: N_inf = K/2 = 50
  //   Max growth rate: r·K/4 = 87.5 (at N = K/2)
  //
  // Interface:
  //   Inputs  : tasa_entrada (Real)    — external immigration [individuals/time]
  //   Outputs : poblacion    (Real)    — population N(t)
  //             tasa_crecimiento (Real) — instantaneous growth rate dN/dt
  //             saturacion   (Real)    — N/K ∈ [0,1], degree of saturation
  //             superpoblacion (Boolean) — TRUE when N > K (overshoot)
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real r = 3.5 "Intrinsic growth rate [1/time]";
  parameter Real K = 100.0 "Carrying capacity [individuals]";
  // ── Inputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput tasa_entrada "External immigration rate [individuals/time] — set to 0 for pure logistic growth" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}})));
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput poblacion "Population N(t) — converges to K=100 when tasa_entrada=0" annotation(
    Placement(transformation(extent = {{100, 40}, {120, 60}})));
  Modelica.Blocks.Interfaces.RealOutput tasa_crecimiento "Instantaneous growth rate dN/dt [individuals/time]" annotation(
    Placement(transformation(extent = {{100, 0}, {120, 20}})));
  Modelica.Blocks.Interfaces.RealOutput saturacion "Saturation level N/K ∈ [0, 1] — reaches 1.0 at carrying capacity" annotation(
    Placement(transformation(extent = {{100, -40}, {120, -20}})));
  Modelica.Blocks.Interfaces.BooleanOutput superpoblacion "TRUE when N exceeds carrying capacity K=100 (overshoot detection)" annotation(
    Placement(transformation(extent = {{100, -80}, {120, -60}})));
  // ── State variable ──────────────────────────────────────────────────────────
  Real N(start = 2.0, fixed = true) "Population count — initial: 2 individuals";
equation
// Logistic growth ODE with immigration
  der(N) = r*N*(1.0 - N/K) + tasa_entrada;
// Output assignments
  poblacion = N;
  tasa_crecimiento = r*N*(1.0 - N/K);
  saturacion = N/K;
  superpoblacion = N > K;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {240, 255, 240}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {0, 100, 0}, extent = {{-90, 95}, {90, 70}}, textString = "Population Growth"), Text(origin = {-20, 2},textColor = {100, 100, 100}, extent = {{-90, 68}, {90, 52}}, textString = "r=3.5  K=100  N₀=2"), Line(origin = {-16, -18},points = {{-70, -30}, {-60, -28}, {-45, -20}, {-30, 5}, {-15, 30}, {0, 40}, {15, 42}, {30, 43}, {50, 43}, {70, 43}}, color = {0, 150, 0}, thickness = 2, smooth = Smooth.Bezier), Line(origin = {4, -18},points = {{-70, 43}, {70, 43}}, color = {200, 0, 0}, pattern = LinePattern.Dash), Text(origin = {-28, -18}, textColor = {200, 0, 0}, extent = {{-70, 50}, {-40, 38}}, textString = "K=100"), Text(origin = {-17, 2},extent = {{-87, 6}, {-40, -6}}, textString = "rate_in"), Text(origin = {8, 2},textColor = {0, 100, 0}, extent = {{50, 58}, {98, 42}}, textString = "N(t)"), Text(origin = {4, 0},textColor = {0, 100, 0}, extent = {{50, 18}, {98, 2}}, textString = "dN/dt"), Text(origin = {8, 0},textColor = {0, 100, 0}, extent = {{50, -22}, {98, -38}}, textString = "N/K"), Text(textColor = {200, 0, 0}, extent = {{50, -62}, {98, -78}}, textString = "overload")}),
    Documentation(info = "<html>
      <h3>CrecimientoPoblacional — Logistic Population Growth</h3>
      <p>Classic logistic equation with carrying capacity K=100 and growth rate r=3.5.</p>
      <p>Starting from N=2, the population grows through the inflection point (N=50)
         and converges to K=100.</p>
      <h4>Integration challenge</h4>
      <p>Near N=K/2=50, the growth rate is maximum (87.5/time). Euler overshoots K
         and oscillates; RK4 converges monotonically.</p>
      <p>Use tasa_entrada=0 for the pure logistic test case.</p>
    </html>"));
end CrecimientoPoblacional;
