model ArraysVectores "Fixed-size arrays of Real, Integer and Boolean — vector I/O stress test"
  // ============================================================================
  // ArraysVectores.mo
  // FMU with fixed-size arrays of Real, Integer and Boolean variables.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   FMI 2.0 does not natively support vector connectors; arrays are
  //   represented as N individual scalar variables in the modelDescription.xml.
  //   This model declares arrays of size N=4 for each type, forcing the codegen
  //   to generate N individual fmi2Set*/fmi2Get* calls per array.
  //
  //   This exercises:
  //     - Correct unrolling of array variables into scalar FMI variables
  //     - Proper indexing: v_real[1], v_real[2], v_real[3], v_real[4]
  //     - Mixed-type array operations (sum, logical OR, double)
  //     - Output array v_doble — N individual Real outputs
  //
  // Interface:
  //   Parameter: N        (Integer) — array size = 4 (fixed)
  //   Inputs   : v_real[N] (Real)   — array of N real values
  //              v_int[N]  (Integer)— array of N integer values
  //              v_bool[N] (Boolean)— array of N boolean flags
  //   Outputs  : suma_real  (Real)   — sum of v_real elements
  //              suma_int   (Integer)— sum of v_int elements
  //              alguno_true(Boolean)— OR of all v_bool elements
  //              v_doble[N] (Real)   — each element of v_real doubled
  // ============================================================================
  // ── Parameter ───────────────────────────────────────────────────────────────
  parameter Integer N = 4 "Fixed array size — all arrays have this many elements";
  // ── Inputs ──────────────────────────────────────────────────────────────────
  input Real v_real[N] = zeros(N) "Real input array of size N — each element is an independent FMI variable" annotation(
    Dialog(group = "Array Inputs"));
  input Boolean v_bool[N] = fill(false, N) "Boolean input array of size N" annotation(
    Dialog(group = "Array Inputs"));
  input Integer v_int[N] = zeros(N) "Integer input array of size N" annotation(
    Dialog(group = "Array Inputs"));
  // ── Outputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput suma_real "Sum of all real input elements: v_real[1]+v_real[2]+v_real[3]+v_real[4]" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{100, 50}, {120, 70}}), iconTransformation(extent = {{100, 50}, {120, 70}})));
  Modelica.Blocks.Interfaces.IntegerOutput suma_int "Sum of all integer input elements" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{100, 10}, {120, 30}}), iconTransformation(extent = {{100, 10}, {120, 30}})));
  Modelica.Blocks.Interfaces.BooleanOutput alguno_true "TRUE if any element of v_bool is TRUE (logical OR across the array)" annotation(
    Placement(transformation(origin = {0, -20}, extent = {{100, -30}, {120, -10}}), iconTransformation(extent = {{100, -30}, {120, -10}})));
  output Real v_doble[N] "Each element of v_real multiplied by 2.0 — N individual Real outputs" annotation(
    Dialog(group = "Array Outputs"));
equation
  suma_real = sum(v_real);
  suma_int = sum(v_int);
  alguno_true = Modelica.Math.BooleanVectors.anyTrue(v_bool);
  v_doble = 2.0*v_real;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {-1, 14},fillColor = {255, 250, 245}, fillPattern = FillPattern.Solid, extent = {{-101, 114}, {101, -114}}), Text(origin = {2, 28},textColor = {120, 60, 0}, extent = {{-90, 95}, {90, 72}}, textString = "ArraysVectores"), Text(origin = {-2, 24}, textColor = {100, 100, 100}, extent = {{-90, 70}, {90, 55}}, textString = "N=4  Real[] · Int[] · Bool[]"), Rectangle(lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-95, 45}, {-45, 5}}), Text(textColor = {0, 0, 180}, extent = {{-93, 43}, {-47, 28}}, textString = "v_real[4]"), Text(textColor = {100, 100, 200}, extent = {{-93, 23}, {-47, 8}}, textString = "[·][·][·][·]"), Rectangle(lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{-95, -5}, {-45, -35}}), Text(textColor = {0, 150, 0}, extent = {{-93, -7}, {-47, -22}}, textString = "v_int[4]"), Text(textColor = {100, 180, 100}, extent = {{-93, -22}, {-47, -33}}, textString = "[·][·][·][·]"), Rectangle(lineColor = {180, 80, 0}, fillColor = {255, 230, 200}, fillPattern = FillPattern.Solid, extent = {{-95, -45}, {-45, -75}}), Text(textColor = {180, 80, 0}, extent = {{-93, -47}, {-47, -62}}, textString = "v_bool[4]"), Text(textColor = {200, 120, 50}, extent = {{-93, -62}, {-47, -73}}, textString = "[T][F][T][F]"), Rectangle(lineColor = {80, 80, 80}, fillColor = {235, 235, 235}, fillPattern = FillPattern.Solid, extent = {{-20, 35}, {20, -35}}), Text(textColor = {50, 50, 50}, extent = {{-18, 30}, {18, -30}}, textString = "Σ
×2
OR"), Line(points = {{-45, 25}, {-20, 15}}, color = {0, 0, 180}), Line(points = {{-45, -20}, {-20, 0}}, color = {0, 150, 0}), Line(points = {{-45, -60}, {-20, -15}}, color = {180, 80, 0}), Rectangle(lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{45, 72}, {95, 52}}), Text(textColor = {0, 0, 180}, extent = {{47, 70}, {93, 54}}, textString = "suma_real"), Rectangle(lineColor = {0, 150, 0}, fillColor = {210, 255, 210}, fillPattern = FillPattern.Solid, extent = {{45, 32}, {95, 12}}), Text(textColor = {0, 150, 0}, extent = {{47, 30}, {93, 14}}, textString = "suma_int"), Rectangle(lineColor = {180, 80, 0}, fillColor = {255, 230, 200}, fillPattern = FillPattern.Solid, extent = {{45, -8}, {95, -28}}), Text(textColor = {180, 80, 0}, extent = {{47, -10}, {93, -26}}, textString = "alguno_true"), Rectangle(lineColor = {120, 0, 120}, fillColor = {240, 210, 255}, fillPattern = FillPattern.Solid, extent = {{45, -48}, {95, -78}}), Text(textColor = {120, 0, 120}, extent = {{47, -50}, {93, -65}}, textString = "v_doble[4]"), Text(textColor = {160, 60, 160}, extent = {{47, -65}, {93, -76}}, textString = "[·][·][·][·]"), Line(points = {{20, 20}, {45, 62}}, color = {0, 0, 180}), Line(points = {{20, 5}, {45, 22}}, color = {0, 150, 0}), Line(points = {{20, -10}, {45, -18}}, color = {180, 80, 0}), Line(points = {{20, -25}, {45, -63}}, color = {120, 0, 120})}),
    Documentation(info = "<html>
      <h3>ArraysVectores — Fixed-Size Arrays of All Types</h3>
      <p>This model declares input and output arrays of size N=4 for Real,
         Integer, and Boolean types. In FMI 2.0, arrays are represented as
         N individual scalar variables in the modelDescription.xml.</p>
      <p>The codegen must unroll each array into N separate fmi2Set*/fmi2Get*
         calls using the correct index notation (v_real[1] .. v_real[4]).</p>
      <h4>Interface</h4>
      <table border='1' cellspacing='0' cellpadding='4'>
        <tr><th>Variable</th><th>Type</th><th>Size</th><th>Direction</th></tr>
        <tr><td>v_real</td><td>Real</td><td>N=4</td><td>Input</td></tr>
        <tr><td>v_int</td><td>Integer</td><td>N=4</td><td>Input</td></tr>
        <tr><td>v_bool</td><td>Boolean</td><td>N=4</td><td>Input</td></tr>
        <tr><td>suma_real</td><td>Real</td><td>scalar</td><td>Output</td></tr>
        <tr><td>suma_int</td><td>Integer</td><td>scalar</td><td>Output</td></tr>
        <tr><td>alguno_true</td><td>Boolean</td><td>scalar</td><td>Output</td></tr>
        <tr><td>v_doble</td><td>Real</td><td>N=4</td><td>Output</td></tr>
      </table>
    </html>"));
end ArraysVectores;
