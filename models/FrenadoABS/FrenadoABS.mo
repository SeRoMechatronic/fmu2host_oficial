model FrenadoABS "ABS braking model — slip detection + harmonic pressure modulator — FMI 2.0 ME"
  // ============================================================================
  // FrenadoABS.mo
  // Anti-lock Braking System (ABS) — slip detection + pressure modulation.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Simplified ABS model. Filters the wheel speed signal and computes a
  //   slip index (lambda) from the normalized deceleration rate. When lambda
  //   exceeds the threshold, a harmonic oscillator generates the periodic
  //   pressure modulation characteristic of ABS operation. The modulator
  //   scales the pedal pressure to oscillate between 0% and 100% at the
  //   configured frequency (default 10 Hz).
  //
  // Interface:
  //   Inputs  : velocidad_rueda (Real [0,1]) — normalized wheel speed
  //             presion_pedal   (Real [0,1]) — normalized brake pedal pressure
  //   Outputs : presion_modulada (Real [0,1]) — effective brake pressure
  //             abs_activo       (Boolean)   — ABS intervention active
  //             rueda_bloqueada  (Boolean)   — wheel nearly locked (slip > 0.9)
  //             frenado_normal   (Boolean)   — braking without ABS
  // ============================================================================
  // ── Parameters ────────────────────────────────────────────────────────────
  parameter Real lambda_umbral = 0.15 "Slip threshold for ABS activation. Above this the modulator engages";
  parameter Real tau_filtro_v = 0.05 "Wheel speed filter time constant (s). Removes mechanical vibrations";
  parameter Real tau_filtro_p = 0.08 "Pedal pressure filter time constant (s). Removes driver jitter";
  parameter Real f_modulacion = 10.0 "ABS pressure modulation frequency (Hz). Typical range: 8-15 Hz";
  parameter Real P_max = 1.0 "Maximum brake pressure (normalized)";
  // ── Inputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput velocidad_rueda "Normalized wheel rotational speed [0,1]. Drops fast when wheel locks" annotation(
    Placement(transformation(extent = {{-120, 30}, {-100, 50}})));
  Modelica.Blocks.Interfaces.RealInput presion_pedal "Normalized brake pedal pressure [0,1]. 1.0 = full emergency braking" annotation(
    Placement(transformation(extent = {{-120, -50}, {-100, -30}})));
  // ── Outputs ───────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput presion_modulada "Effective brake pressure after ABS modulation [0,1]" annotation(
    Placement(transformation(extent = {{100, 30}, {120, 50}})));
  Modelica.Blocks.Interfaces.BooleanOutput abs_activo "ON when slip index lambda > lambda_umbral — ABS is intervening" annotation(
    Placement(transformation(extent = {{100, -10}, {120, 10}})));
  Modelica.Blocks.Interfaces.BooleanOutput rueda_bloqueada "ON when lambda > 0.9 — wheel is nearly or fully locked" annotation(
    Placement(transformation(extent = {{100, -50}, {120, -30}})));
  Modelica.Blocks.Interfaces.BooleanOutput frenado_normal "ON when ABS not active AND pedal pressure > 5% — normal braking" annotation(
    Placement(transformation(extent = {{100, -90}, {120, -70}})));
  // ── Internal variables ────────────────────────────────────────────────────
  Real v_filtrada(start = 0.0) "Filtered wheel speed. Smoothed with tau_filtro_v";
  Real p_filtrada(start = 0.0) "Filtered pedal pressure. Smoothed with tau_filtro_p";
  Real dv_dt "Instantaneous derivative of filtered wheel speed (deceleration)";
  Real dv_filtrada(start = 0.0) "Filtered deceleration — avoids noise amplification in slip calculation";
  Real lambda "Slip index [0,1]. Ratio of deceleration to speed. High = wheel locking";
  Real oscilador(start = 0.0) "Sine component of the harmonic oscillator. Generates periodic modulation";
  Real d_oscilador(start = 1.0) "Cosine component. Together with oscilador, forms an undamped oscillator";
equation
// First-order low-pass filter on wheel speed
  der(v_filtrada) = (velocidad_rueda - v_filtrada)/tau_filtro_v;
// Instantaneous deceleration from filtered speed
  dv_dt = der(v_filtrada);
// Filter the deceleration itself to avoid double-differentiation noise
  der(dv_filtrada) = (dv_dt - dv_filtrada)/tau_filtro_v;
// First-order filter on pedal pressure
  der(p_filtrada) = (presion_pedal - p_filtrada)/tau_filtro_p;
// Slip index calculation.
// When the wheel rotates freely: dv_filtrada ≈ 0 → lambda ≈ 0.
// When the wheel locks: dv_filtrada becomes strongly negative → lambda → 1.
// Guard condition v_filtrada > 0.01 avoids division by zero at standstill.
  lambda = if v_filtrada > 0.01 then min(1.0, max(0.0, (-dv_filtrada)/(v_filtrada*20.0))) else 0.0;
// Undamped harmonic oscillator at f_modulacion Hz.
// This generates a clean sinusoidal modulation signal without calling
// sin()/cos() at every time step — both approaches are mathematically
// equivalent but the state-space form is more efficient in embedded C.
  der(oscilador) = d_oscilador*2.0*Modelica.Constants.pi*f_modulacion;
  der(d_oscilador) = -oscilador*2.0*Modelica.Constants.pi*f_modulacion;
// Pressure output:
// Normal braking: pass through filtered pedal pressure.
// ABS active:     modulate between 0% and 100% of pedal pressure at 10 Hz.
//                 (0.5 + 0.5*sin) oscillates between 0 and 1.
  presion_modulada = if lambda > lambda_umbral then min(P_max, max(0.0, p_filtrada*(0.5 + 0.5*oscilador))) else min(P_max, max(0.0, p_filtrada));
// Status outputs
  abs_activo = lambda > lambda_umbral;
  rueda_bloqueada = lambda > 0.9;
  frenado_normal = lambda <= lambda_umbral and presion_pedal > 0.05;
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(fillColor = {248, 248, 248}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(textColor = {60, 0, 0}, extent = {{-90, 95}, {90, 72}}, textString = "FrenadoABS"), Ellipse(origin = {-8, 6},fillColor = {80, 80, 80}, fillPattern = FillPattern.Solid, extent = {{-70, 60}, {-10, 0}}), Ellipse(origin = {-8, 6},lineColor = {200, 200, 200}, fillColor = {160, 160, 160}, fillPattern = FillPattern.Solid, extent = {{-60, 50}, {-20, 10}}), Rectangle(origin = {-8, 6},lineColor = {180, 0, 0}, fillColor = {255, 80, 80}, fillPattern = FillPattern.Solid, extent = {{-72, 35}, {-8, 25}}), Rectangle(origin = {0, 6},lineColor = {0, 0, 160}, fillColor = {200, 210, 255}, fillPattern = FillPattern.Solid, extent = {{-5, 55}, {45, 5}}), Text(origin = {0, 16},textColor = {0, 0, 160}, extent = {{-3, 52}, {43, 8}}, textString = "ABS"), Line(points = {{-3, 20}, {5, 30}, {13, 20}, {21, 30}, {29, 20}, {37, 30}, {43, 20}}, color = {0, 0, 200}, thickness = 1), Line(origin = {0, -4},points = {{-100, -35}, {-75, -35}}, color = {80, 40, 0}, thickness = 1.5), Text(origin = {-8, -16},textColor = {80, 40, 0}, extent = {{-98, -20}, {-60, -10}}, textString = "PED"), Line(points = {{-100, 40}, {-80, 40}}, color = {0, 80, 0}, thickness = 1.5), Text(origin = {-8, -4},textColor = {0, 80, 0}, extent = {{-98, 52}, {-62, 62}}, textString = "VEL"), Line(points = {{45, 39}, {100, 40}}, color = {0, 0, 160}), Ellipse(origin = {0, 12}, fillColor = {0, 80, 220}, fillPattern = FillPattern.Solid, extent = {{62, -2}, {82, -22}}), Text(origin = {0, 12}, textColor = {0, 60, 180}, extent = {{84, -4}, {100, -20}}, textString = "ABS"), Ellipse(origin = {0, 6},fillColor = {200, 0, 0}, fillPattern = FillPattern.Solid, extent = {{62, -38}, {82, -58}}), Text(origin = {0, 6},textColor = {180, 0, 0}, extent = {{84, -40}, {100, -56}}, textString = "LCK"), Ellipse(fillColor = {0, 200, 80}, fillPattern = FillPattern.Solid, extent = {{62, -68}, {82, -88}}), Text(origin = {0, -2},textColor = {0, 160, 60}, extent = {{84, -70}, {100, -86}}, textString = "NRM")}),
    Documentation(info = "<html>
      <h3>FrenadoABS — Anti-lock Braking System</h3>
      <p>Slip-based ABS with harmonic oscillator pressure modulator.
         Engages when wheel slip exceeds 15%, modulates brake pressure
         at 10 Hz to restore wheel rotation and maintain vehicle control.</p>
    </html>"));
end FrenadoABS;
