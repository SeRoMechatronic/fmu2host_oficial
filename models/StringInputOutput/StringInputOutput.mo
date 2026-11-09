model StringInputOutput "String variables as FMI 2.0 inputs and outputs — exercises fmi2SetString / fmi2GetString"
  // ============================================================================
  // StringInputOutput.mo
  // FMU with String variables as true inputs and outputs (not just parameters).
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Most FMU models use String only as parameters (read once at init).
  //   This model uses String as runtime input and output variables, which
  //   exercises the fmi2SetString / fmi2GetString code paths in the codegen.
  //   These paths are structurally different from fmi2SetReal / fmi2GetReal.
  //
  //   The model classifies a real sensor value and produces:
  //     - A string status label: "HIGH", "NORMAL", or "LOW"
  //     - A string alert message with context
  //     - A scaled real output
  //     - A boolean alarm flag
  //
  // Interface:
  //   Inputs  : value          (Real)    — sensor reading
  //             mode_operation (String)  — operating mode tag (runtime)
  //             tag_sensor     (String)  — sensor identifier (runtime)
  //   Outputs : status         (String)  — "HIGH" / "NORMAL" / "LOW"
  //             alert_msg      (String)  — human-readable alert string
  //             scaled_value   (Real)    — value * 1.5
  //             alarm          (Boolean) — true when out of normal range
  //
  // Export note:
  //   String inputs/outputs require fmi2SetString before doStep and
  //   fmi2GetString after. Verify the codegen generates both call sites.
  // ============================================================================

  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput value
    "Sensor reading — expected range [0.0, 200.0]"
    annotation(Placement(transformation(origin = {0, -40}, extent = {{-120, 30}, {-100, 50}}), iconTransformation(extent = {{-120, 30}, {-100, 50}})));

  input String mode_operation = "AUTO"
    "Operating mode identifier — runtime String input (e.g. AUTO, MANUAL, TEST)"
    annotation(Dialog(group = "String Inputs"));

  input String tag_sensor = "SEN_001"
    "Sensor tag — runtime String input identifying the data source"
    annotation(Dialog(group = "String Inputs"));

  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput scaled_value
    "Input value multiplied by 1.5"
    annotation(Placement(transformation(extent = {{100, 30}, {120, 50}})));

  Modelica.Blocks.Interfaces.BooleanOutput alarm
    "TRUE when value is outside the normal range [10.0, 100.0]"
    annotation(Placement(transformation(origin = {0, -40}, extent = {{100, -10}, {120, 10}}), iconTransformation(extent = {{100, -10}, {120, 10}})));

  output String status
    "Classification of the sensor value: HIGH | NORMAL | LOW"
    annotation(Dialog(group = "String Outputs"));

  output String alert_msg
    "Human-readable alert string, empty string when NORMAL"
    annotation(Dialog(group = "String Outputs"));

equation
  // Classify the sensor value into a status string
  status = if value > 100.0 then "HIGH"
           else if value < 10.0 then "LOW"
           else "NORMAL";

  // Produce an alert message only when out of range
  alert_msg = if value > 100.0 then "ALERT: value above upper limit (100.0)"
              else if value < 10.0 then "ALERT: value below lower limit (10.0)"
              else "";

  // Numeric outputs
  scaled_value = value * 1.5;
  alarm        = value > 100.0 or value < 10.0;

  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {
      // Outer frame
      Rectangle(extent = {{-100, 100}, {100, -100}},
        lineColor = {0, 0, 0},
        fillColor = {255, 248, 220},
        fillPattern = FillPattern.Solid),
      // Title
      Text(extent = {{-90, 95}, {90, 70}},
        lineColor = {128, 64, 0},
        textString = "String I/O"),
      // Subtitle
      Text(extent = {{-90, 68}, {90, 52}},
        lineColor = {100, 100, 100},
        textString = "fmi2SetString / GetString"),
      // String symbol — quote marks
      Text(extent = {{-30, 30}, {30, -10}},
        lineColor = {180, 100, 0},
        textString = "\" \""),
      // Input labels
      Text(extent = {{-98, 48}, {-42, 32}},
        lineColor = {0, 0, 0},
        textString = "value"),
      Text(extent = {{-98, 10}, {-42, -5}},
        lineColor = {128, 64, 0},
        textString = "mode"),
      Text(extent = {{-98, -20}, {-42, -35}},
        lineColor = {128, 64, 0},
        textString = "tag"),
      // Output labels
      Text(extent = {{45, 48}, {98, 32}},
        lineColor = {0, 0, 200},
        textString = "scaled"),
      Text(extent = {{45, 8}, {98, -6}},
        lineColor = {200, 0, 0},
        textString = "alarm"),
      Text(extent = {{45, -20}, {98, -34}},
        lineColor = {128, 64, 0},
        textString = "status"),
      Text(extent = {{45, -45}, {98, -59}},
        lineColor = {128, 64, 0},
        textString = "msg"),
      // Connector lines
      Line(points = {{-100, 40}, {-30, 10}},  color = {0, 0, 200}),
      Line(points = {{30, 10}, {100, 40}},    color = {0, 0, 200}),
      Line(points = {{30, 10}, {100, 0}},     color = {200, 0, 0}),
      Line(points = {{30, 10}, {100, -30}},   color = {128, 64, 0}),
      Line(points = {{30, 10}, {100, -55}},   color = {128, 64, 0})}),
    Documentation(info = "<html>
      <h3>StringInputOutput — String variables as FMI 2.0 I/O</h3>
      <p>This model exercises <b>String as runtime input and output</b>, not just
         as parameters. This forces the codegen to generate <code>fmi2SetString</code>
         call sites (for inputs) and <code>fmi2GetString</code> call sites (for outputs),
         which are structurally different from the Real/Integer/Boolean paths.</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Direction</th><th>Description</th></tr>
        <tr><td>value</td><td>Real</td><td>Input</td><td>Sensor reading [0..200]</td></tr>
        <tr><td>mode_operation</td><td>String</td><td>Input</td><td>Operating mode tag</td></tr>
        <tr><td>tag_sensor</td><td>String</td><td>Input</td><td>Sensor identifier</td></tr>
        <tr><td>scaled_value</td><td>Real</td><td>Output</td><td>value × 1.5</td></tr>
        <tr><td>alarm</td><td>Boolean</td><td>Output</td><td>Out-of-range flag</td></tr>
        <tr><td>status</td><td>String</td><td>Output</td><td>HIGH / NORMAL / LOW</td></tr>
        <tr><td>alert_msg</td><td>String</td><td>Output</td><td>Alert text or empty</td></tr>
      </table>
    </html>"));
end StringInputOutput;
