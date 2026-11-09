model Mi_Modelo_Nuevo "Name-with-hyphens stress test for CMake prefix and FMI function naming"
  // ============================================================================
  // Mi_Modelo_Nuevo.mo
  // Simple filtered signal with dynamic state.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model's primary purpose is NOT to test interesting dynamics —
  //   it is to stress-test the code generator's handling of a model name
  //   that contains hyphens, underscores, and mixed case.
  //
  //   FMI 2.0 requires that function names follow the pattern:
  //     <ModelIdentifier>_fmi2GetReal(...)
  //     <ModelIdentifier>_fmi2DoStep(...)
  //   If the ModelIdentifier contains hyphens, CMake and C compilers will
  //   reject the generated function names (hyphens are illegal in C identifiers).
  //
  //   Test this file in two ways:
  //     A) Saved as "Mi_Modelo_Nuevo.mo" (underscores) — should compile cleanly
  //     B) Saved as "Mi-Modelo-Nuevo.mo" (hyphens in filename) — may break codegen
  //
  //   The model itself is a simple first-order low-pass filter with a Boolean
  //   flag output and a String parameter for additional naming stress.
  //
  // Physics:
  //   τ·dx/dt = u - x  (first-order low-pass filter, time constant τ)
  //   x(0) = 0
  //
  // Interface:
  //   Parameters : nombre_fmu (String) — model display name
  //                tau        (Real)   — filter time constant [s]
  //   Inputs     : entrada_principal (Real)    — signal to filter
  //                flag_activo      (Boolean) — enables/disables filter
  //   Outputs    : salida_filtrada  (Real)    — filtered signal x(t)
  //                flag_salida      (Boolean) — TRUE when output > 0.5
  // ============================================================================

  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real   tau        = 1.0
    "Filter time constant [s] — larger τ = slower response";
  parameter String nombre_fmu = "Mi-Modelo-Nuevo"
    "Display name of this FMU — contains hyphens to stress String parameter handling";

  // ── Inputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput entrada_principal
    "Input signal to be filtered — any real value"
    annotation(Placement(transformation(extent = {{-120, 20}, {-100, 40}})));

  Modelica.Blocks.Interfaces.BooleanInput flag_activo
    "When TRUE: filter tracks input. When FALSE: filter decays to zero"
    annotation(Placement(transformation(extent = {{-120, -40}, {-100, -20}})));

  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput salida_filtrada
    "Filtered output x(t) — exponentially approaches entrada_principal when flag_activo=TRUE"
    annotation(Placement(transformation(extent = {{100, 20}, {120, 40}})));

  Modelica.Blocks.Interfaces.BooleanOutput flag_salida
    "TRUE when salida_filtrada > 0.5"
    annotation(Placement(transformation(extent = {{100, -40}, {120, -20}})));

  // ── State variable ──────────────────────────────────────────────────────────
  Real x(start = 0.0, fixed = true) "Filter state — internal filtered value";

equation
  // First-order low-pass filter
  // When active: track the input with time constant tau
  // When inactive: decay to zero with time constant tau
  der(x) = if flag_activo then (entrada_principal - x) / tau
                           else (0.0 - x) / tau;

  // Outputs
  salida_filtrada = x;
  flag_salida     = x > 0.5;

  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {
      // Outer frame
      Rectangle(extent = {{-100, 100}, {100, -100}},
        lineColor = {0, 0, 0},
        fillColor = {255, 255, 240},
        fillPattern = FillPattern.Solid),
      // Title
      Text(extent = {{-90, 95}, {90, 70}},
        lineColor = {100, 80, 0},
        textString = "Mi-Modelo-Nuevo"),
      // Subtitle
      Text(extent = {{-90, 68}, {90, 52}},
        lineColor = {100, 100, 100},
        textString = "Name hyphens stress test"),
      // Filter symbol
      Rectangle(extent = {{-30, 30}, {30, -10}},
        lineColor = {100, 80, 0},
        fillColor = {255, 250, 200},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-28, 28}, {28, -8}},
        lineColor = {100, 80, 0},
        textString = "1/(τs+1)"),
      // Input connectors
      Line(points = {{-100, 30}, {-30, 10}}, color = {0, 0, 200}),
      Line(points = {{-100, -30}, {-30, 10}}, color = {0, 150, 0}),
      // Output connectors
      Line(points = {{30, 10}, {100, 30}},  color = {0, 0, 200}),
      Line(points = {{30, 10}, {100, -30}}, color = {0, 150, 0}),
      // Labels
      Text(extent = {{-98, 45}, {-45, 30}},
        lineColor = {0, 0, 200},
        textString = "in"),
      Text(extent = {{-98, -20}, {-45, -35}},
        lineColor = {0, 150, 0},
        textString = "active"),
      Text(extent = {{45, 45}, {98, 30}},
        lineColor = {0, 0, 200},
        textString = "filtered"),
      Text(extent = {{45, -20}, {98, -35}},
        lineColor = {0, 150, 0},
        textString = "flag"),
      // Hyphen warning badge
      Rectangle(extent = {{-85, -55}, {85, -80}},
        lineColor = {180, 120, 0},
        fillColor = {255, 240, 200},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-83, -57}, {83, -78}},
        lineColor = {140, 90, 0},
        textString = "nombre = \"Mi-Modelo-Nuevo\"")}),
    Documentation(info = "<html>
      <h3>Mi_Modelo_Nuevo — Name Hyphen Stress Test</h3>
      <p>This model's name contains hyphens (<code>Mi-Modelo-Nuevo</code>) and
         mixed case. It tests whether the codegen tool correctly handles
         the FMI ModelIdentifier when it contains characters that are invalid
         in C identifiers (hyphens).</p>
      <h4>Test variants</h4>
      <ul>
        <li>Save as <code>Mi_Modelo_Nuevo.mo</code> (underscores) — must work</li>
        <li>Save as <code>Mi-Modelo-Nuevo.mo</code> (hyphens in filename) — may break CMake</li>
      </ul>
      <h4>The model dynamics</h4>
      <p>First-order low-pass filter: τ·x' = u - x  (or -x when inactive).
         Time constant τ=1 s. Output reaches 63% of input in 1 s, 99% in ~5 s.</p>
    </html>"));
end Mi_Modelo_Nuevo;
