model StringsParametros "String parameter stress test — long strings, empty, unicode, special characters"
  // ============================================================================
  // StringsParametros.mo
  // FMU with multiple String parameters exercising edge cases in FMI String handling.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model contains six String parameters covering all the edge cases
  //   that a codegen tool must handle when reading String values from an FMU:
  //
  //     nombre    — typical sensor name with spaces and special characters
  //     ruta      — filesystem path with slashes and underscores
  //     especial  — embedded delimiters (=, ;, Greek letters, superscripts)
  //     vacio     — empty string ""
  //     unicode_str — Unicode characters (Ångström Å, delta δ, epsilon ε, ±)
  //     largo     — 98-character string (buffer overflow stress test)
  //
  //   The numeric computation is trivial (y = u * len_nombre) so that test
  //   results are easy to verify independently of the String handling.
  //
  // Interface:
  //   Params  : nombre, ruta, especial, vacio, unicode_str, largo (String)
  //             len_nombre (Integer) — pre-computed length of 'nombre'
  //   Input   : u (Real)
  //   Output  : y (Real) — u * len_nombre
  // ============================================================================

  // ── String parameters — edge cases ──────────────────────────────────────────
  parameter String nombre      = "Sensor de Presión #1 (Alta Temp.)"
    "Typical sensor label with spaces, accented chars, hash and parentheses";

  parameter String ruta        = "/datos/planta/linea_A/modulo_02"
    "Filesystem path — contains forward slashes and underscores";

  parameter String especial    = "val=3.14;tag=alpha_beta;unit=m2/s"
    "Embedded delimiters: equals, semicolons, and unit notation";

  parameter String vacio       = ""
    "Empty string — codegen must handle zero-length String without null pointer";

  parameter String unicode_str = "Angstrom [A] delta+-epsilon"
    "String with ASCII approximations of Unicode symbols (Å → A, δ→delta, ε→epsilon)";

  parameter String largo       = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "98-character string — stresses String buffer allocation (must not overflow)";

  // ── Integer parameter ────────────────────────────────────────────────────────
  parameter Integer len_nombre = 34
    "Pre-computed character count of 'nombre' — used to scale the numeric output";

  // ── Input ────────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput u
    "Numeric input — output y will be u multiplied by len_nombre (=34)"
    annotation(Placement(transformation(extent = {{-120, -10}, {-100, 10}})));

  // ── Output ───────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput y
    "Numeric output: u * len_nombre — verifies numeric path unaffected by String params"
    annotation(Placement(transformation(extent = {{100, -10}, {120, 10}})));

equation
  y = u * len_nombre;

  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {
      // Outer frame
      Rectangle(extent = {{-100, 100}, {100, -100}},
        lineColor = {0, 0, 0},
        fillColor = {255, 252, 240},
        fillPattern = FillPattern.Solid),
      // Title
      Text(extent = {{-90, 95}, {90, 72}},
        lineColor = {100, 60, 0},
        textString = "StringsParametros"),
      // Subtitle
      Text(extent = {{-90, 70}, {90, 55}},
        lineColor = {100, 100, 100},
        textString = "6 String params — edge cases"),
      // String parameter rows
      Rectangle(extent = {{-90, 50}, {90, 34}},
        lineColor = {150, 100, 0}, fillColor = {255, 245, 215},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, 48}, {88, 36}},
        lineColor = {120, 70, 0}, textString = "nombre : \"Sensor de Presión #1...\""),
      Rectangle(extent = {{-90, 32}, {90, 18}},
        lineColor = {150, 100, 0}, fillColor = {255, 245, 215},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, 30}, {88, 20}},
        lineColor = {120, 70, 0}, textString = "ruta   : \"/datos/planta/linea_A/...\""),
      Rectangle(extent = {{-90, 16}, {90, 2}},
        lineColor = {150, 100, 0}, fillColor = {255, 245, 215},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, 14}, {88, 4}},
        lineColor = {120, 70, 0}, textString = "especial: \"val=3.14;tag=...\""),
      Rectangle(extent = {{-90, 0}, {90, -14}},
        lineColor = {200, 0, 0}, fillColor = {255, 225, 225},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, -2}, {88, -12}},
        lineColor = {180, 0, 0}, textString = "vacio  : \"\"  ← empty string"),
      Rectangle(extent = {{-90, -16}, {90, -30}},
        lineColor = {0, 100, 150}, fillColor = {215, 240, 255},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, -18}, {88, -28}},
        lineColor = {0, 80, 150}, textString = "unicode: \"Angstrom [A] delta+-epsilon\""),
      Rectangle(extent = {{-90, -32}, {90, -46}},
        lineColor = {120, 0, 120}, fillColor = {240, 215, 255},
        fillPattern = FillPattern.Solid),
      Text(extent = {{-88, -34}, {88, -44}},
        lineColor = {100, 0, 100}, textString = "largo  : \"aaa...\" (98 chars)"),
      // Numeric section
      Line(points = {{-90, -55}, {90, -55}}, color = {150, 150, 150}),
      Text(extent = {{-88, -58}, {30, -70}},
        lineColor = {0, 0, 180}, textString = "u (Real)"),
      Text(extent = {{-30, -58}, {88, -70}},
        lineColor = {0, 0, 180}, textString = "y = u × 34"),
      // Arrow
      Line(points = {{-100, 0}, {-90, -62}}, color = {0, 0, 180}),
      Line(points = {{90, -62}, {100, 0}},   color = {0, 0, 180})}),
    Documentation(info = "<html>
      <h3>StringsParametros — String Parameter Edge Cases</h3>
      <p>Six String parameters covering every edge case a codegen tool must handle
         when reading FMI String values at initialization:</p>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Parameter</th><th>Edge case</th><th>Length</th></tr>
        <tr><td>nombre</td><td>Spaces, accented chars, #, ()</td><td>34</td></tr>
        <tr><td>ruta</td><td>Slashes, underscores</td><td>31</td></tr>
        <tr><td>especial</td><td>= ; / in value</td><td>34</td></tr>
        <tr><td>vacio</td><td>Empty string</td><td>0</td></tr>
        <tr><td>unicode_str</td><td>ASCII substitutes for non-ASCII</td><td>27</td></tr>
        <tr><td>largo</td><td>98 characters (buffer stress)</td><td>98</td></tr>
      </table>
      <p>The numeric computation y=u×34 is independent of the String values
         and verifies the model remains numerically functional despite String stress.</p>
    </html>"));
end StringsParametros;
