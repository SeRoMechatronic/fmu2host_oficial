model ValoresExtremos "Extreme and edge-case real values — Inf, near-zero, saturation, log/sqrt protection"
  // ============================================================================
  // ValoresExtremos.mo
  // FMU that exercises extreme floating-point inputs and protected operations.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   This model receives a single real input and applies five different
  //   transformations, each designed to handle a potential floating-point
  //   edge case gracefully:
  //
  //     y_inv  — protected reciprocal (avoids 1/0 → Inf)
  //     y_sqrt — protected square root (avoids sqrt(negative) → NaN)
  //     y_log  — protected natural log (avoids log(0) → -Inf)
  //     y_sat  — saturation clamp to [-1, +1]
  //     es_finito — Boolean: TRUE when the value is within a finite range
  //
  //   A codegen tool must correctly handle the if/else guards that protect
  //   each operation. If the guards are dropped or incorrectly compiled,
  //   the generated code produces NaN or Inf at runtime.
  //
  // Interface:
  //   Input  : u       (Real)    — any value, including 0, negative, very large
  //   Outputs: y_inv   (Real)    — 1/u (guarded) or 1e30 when |u| ≤ 1e-10
  //            y_sqrt  (Real)    — √u when u≥0, 0 otherwise
  //            y_log   (Real)    — ln(u) when u>1e-10, -1e30 otherwise
  //            y_sat   (Real)    — clamp(u, -1, +1)
  //            es_finito (Boolean) — TRUE when |u| < 1e29
  // ============================================================================
  // ── Input ───────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput u "Input signal — test with 0, negative, very large, very small values" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}})));
  // ── Outputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput y_inv "Protected reciprocal: 1/u when |u|>1e-10, returns 1e30 near zero" annotation(
    Placement(transformation(extent = {{100, 60}, {120, 80}})));
  Modelica.Blocks.Interfaces.RealOutput y_sqrt "Protected square root: √u when u≥0, returns 0 for negative input" annotation(
    Placement(transformation(extent = {{100, 20}, {120, 40}})));
  Modelica.Blocks.Interfaces.RealOutput y_log "Protected natural log: ln(u) when u>1e-10, returns -1e30 near/below zero" annotation(
    Placement(transformation(extent = {{100, -20}, {120, 0}})));
  Modelica.Blocks.Interfaces.RealOutput y_sat "Saturated output: clamp(u, -1.0, +1.0) — always in range [-1, 1]" annotation(
    Placement(transformation(extent = {{100, -60}, {120, -40}})));
  Modelica.Blocks.Interfaces.BooleanOutput es_finito "TRUE when |u| < 1e29 (finite range check — FALSE for Inf-like inputs)" annotation(
    Placement(transformation(extent = {{100, -100}, {120, -80}}), iconTransformation(extent = {{100, -100}, {120, -80}})));
equation
// Protected division — avoids 1/0
  y_inv = if abs(u) > 1.0e-10 then 1.0/u else 1.0e30;
// Protected square root — avoids sqrt(negative)
  y_sqrt = if u >= 0.0 then sqrt(u) else 0.0;
// Protected logarithm — avoids log(0) and log(negative)
  y_log = if u > 1.0e-10 then log(u) else -1.0e30;
// Saturation clamp — hard limits at ±1
  y_sat = min(1.0, max(-1.0, u));
// Finite range detector
  es_finito = abs(u) < 1.0e29;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {0, 11},fillColor = {255, 245, 245}, fillPattern = FillPattern.Solid, extent = {{-100, 119}, {100, -119}}), Text(origin = {-2, 34},textColor = {150, 0, 0}, extent = {{-90, 95}, {90, 72}}, textString = "ValoresExtremos"), Text(origin = {0, 36},textColor = {100, 100, 100}, extent = {{-90, 70}, {90, 55}}, textString = "Inf · NaN · zero · saturation"), Text(extent = {{-98, 10}, {-45, -5}}, textString = "u (any)"), Rectangle(origin = {-3, 0},lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{16, 78}, {97, 62}}), Text(origin = {2, 0},textColor = {0, 0, 180}, extent = {{17, 76}, {88, 64}}, textString = "y_inv  = 1/u guard"), Rectangle(origin = {-3, -20},lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{16, 58}, {97, 42}}), Text(origin = {4, -20},textColor = {0, 150, 0}, extent = {{17, 56}, {88, 44}}, textString = "y_sqrt = √u guard"), Rectangle(origin = {-3, -40},lineColor = {150, 80, 0}, fillColor = {255, 235, 210}, fillPattern = FillPattern.Solid, extent = {{16, 38}, {97, 22}}), Text(origin = {2, -40},textColor = {150, 80, 0}, extent = {{17, 36}, {88, 24}}, textString = "y_log  = ln(u) guard"), Rectangle(origin = {-3, -60},lineColor = {120, 0, 120}, fillColor = {240, 210, 255}, fillPattern = FillPattern.Solid, extent = {{16, 18}, {97, 2}}), Text(origin = {0, -60},textColor = {120, 0, 120}, extent = {{17, 16}, {88, 4}}, textString = "y_sat  = clamp[-1,+1]"), Rectangle(origin = {-3, -80}, lineColor = {180, 0, 0}, fillColor = {255, 210, 210}, fillPattern = FillPattern.Solid, extent = {{16, -2}, {97, -18}}), Text(origin = {0, -80}, textColor = {180, 0, 0}, extent = {{17, -4}, {88, -16}}, textString = "es_finito: |u|<1e29"), Line(origin = {-8, 2},points = {{-40, -2}, {21, 68}}, color = {0, 0, 180}), Line(points = {{-48, 0}, {13, 30}}, color = {0, 150, 0}), Line(origin = {-8, 0},points = {{-40, 0}, {21, -10}}, color = {150, 80, 0}), Line(origin = {-8, 0},points = {{-40, 0}, {21, -50}}, color = {120, 0, 120}), Line(origin = {-8, 0},points = {{-40, 0}, {21, -92}}, color = {180, 0, 0})}),
    Documentation(info = "<html>
      <h3>ValoresExtremos — Extreme Floating-Point Values</h3>
      <p>This model exercises five floating-point operations that can produce
         NaN, Inf, or undefined results when their inputs are at boundary values.
         Each operation is protected by an if/else guard.</p>
      <h4>Operations</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Output</th><th>Operation</th><th>Guard condition</th><th>Fallback</th></tr>
        <tr><td>y_inv</td><td>1/u</td><td>|u| &gt; 1e-10</td><td>1e30</td></tr>
        <tr><td>y_sqrt</td><td>√u</td><td>u ≥ 0</td><td>0.0</td></tr>
        <tr><td>y_log</td><td>ln(u)</td><td>u &gt; 1e-10</td><td>-1e30</td></tr>
        <tr><td>y_sat</td><td>clamp(u,-1,1)</td><td>always safe</td><td>—</td></tr>
        <tr><td>es_finito</td><td>|u|&lt;1e29</td><td>—</td><td>FALSE</td></tr>
      </table>
    </html>"));
end ValoresExtremos;
