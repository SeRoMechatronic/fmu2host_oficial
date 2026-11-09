model CuerposAcoplados "Two coupled masses on springs — 4 states, energy transfer between bodies"
  // ============================================================================
  // CuerposAcoplados.mo
  // Two masses connected by springs and a coupling spring between them.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Two masses (m1, m2) each attached to a wall spring (k1, k2) and
  //   connected to each other by a coupling spring (kc). An external force
  //   can be applied to mass 1.
  //
  //   With no external force and non-zero initial conditions, the system
  //   shows energy exchange between the two bodies (beating phenomenon).
  //   The total mechanical energy must be conserved.
  //
  //   This model has 4 continuous states (x1, x2, v1, v2), which verifies
  //   that the codegen correctly handles state vectors of size > 2, including
  //   buffer allocation (EULER_BUF_SIZE / RK4_BUF_SIZE ≥ 4).
  //
  // Physics:
  //   m1·x1'' = -(k1 + kc)·x1 + kc·x2 + F
  //   m2·x2'' = kc·x1 - (k2 + kc)·x2
  //
  // Initial conditions: x1=1.0, x2=-0.5, v1=0.0, v2=0.5
  // Initial energy: 0.5·m1·v1² + 0.5·m2·v2² + 0.5·k1·x1² + 0.5·k2·x2² + 0.5·kc·(x1-x2)²
  //               = 0 + 0.25 + 2.0 + 0.25 + 1.125 = 3.625 J
  //
  // Interface:
  //   Inputs  : fuerza_externa (Real)    — force applied to mass 1 [N]
  //   Outputs : pos1           (Real)    — displacement of mass 1 [m]
  //             pos2           (Real)    — displacement of mass 2 [m]
  //             vel1           (Real)    — velocity of mass 1 [m/s]
  //             vel2           (Real)    — velocity of mass 2 [m/s]
  //             energia_total  (Real)    — total mechanical energy [J]
  //             en_fase        (Boolean) — TRUE when pos1 and pos2 have the same sign
  // ============================================================================
  // ── Parameters ─────────────────────────────────────────────────────────────
  parameter Real m1 = 1.0 "Mass 1 [kg]";
  parameter Real m2 = 2.0 "Mass 2 [kg]";
  parameter Real k1 = 4.0 "Spring stiffness attached to mass 1 [N/m]";
  parameter Real k2 = 2.0 "Spring stiffness attached to mass 2 [N/m]";
  parameter Real kc = 1.0 "Coupling spring stiffness between mass 1 and 2 [N/m]";
  // ── Inputs ─────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealInput fuerza_externa "External force applied to mass 1 [N] — set to 0 for free oscillation" annotation(
    Placement(transformation(extent = {{-120, -10}, {-100, 10}}), iconTransformation(origin = {-48, 0}, extent = {{-120, -10}, {-100, 10}})));
  // ── Outputs ────────────────────────────────────────────────────────────────
  Modelica.Blocks.Interfaces.RealOutput pos1 "Displacement of mass 1 x1(t) [m]" annotation(
    Placement(transformation(origin = {0, 10}, extent = {{100, 60}, {120, 80}}), iconTransformation(extent = {{100, 60}, {120, 80}})));
  Modelica.Blocks.Interfaces.RealOutput pos2 "Displacement of mass 2 x2(t) [m]" annotation(
    Placement(transformation(origin = {0, 20}, extent = {{100, 20}, {120, 40}}), iconTransformation(extent = {{100, 20}, {120, 40}})));
  Modelica.Blocks.Interfaces.RealOutput vel1 "Velocity of mass 1 v1(t) [m/s]" annotation(
    Placement(transformation(origin = {0, 30}, extent = {{100, -20}, {120, 0}}), iconTransformation(extent = {{100, -20}, {120, 0}})));
  Modelica.Blocks.Interfaces.RealOutput vel2 "Velocity of mass 2 v2(t) [m/s]" annotation(
    Placement(transformation(origin = {0, 36}, extent = {{100, -60}, {120, -40}}), iconTransformation(extent = {{100, -60}, {120, -40}})));
  Modelica.Blocks.Interfaces.RealOutput energia_total "Total mechanical energy [J] — must remain ≈ 3.625 when fuerza_externa=0" annotation(
    Placement(transformation(origin = {0, 44}, extent = {{100, -100}, {120, -80}}), iconTransformation(extent = {{100, -100}, {120, -80}})));
  Modelica.Blocks.Interfaces.BooleanOutput en_fase "TRUE when mass 1 and mass 2 displacements have the same sign (in-phase motion)" annotation(
    Placement(transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}), iconTransformation(origin = {110, -120}, extent = {{-10, -10}, {10, 10}})));
  // ── State variables ─────────────────────────────────────────────────────────
  Real x1(start = 1.0, fixed = true) "Displacement of mass 1 [m]";
  Real x2(start = -0.5, fixed = true) "Displacement of mass 2 [m]";
  Real v1(start = 0.0, fixed = true) "Velocity of mass 1 [m/s]";
  Real v2(start = 0.5, fixed = true) "Velocity of mass 2 [m/s]";
equation
// Equations of motion for two coupled masses
  der(x1) = v1;
  der(x2) = v2;
  der(v1) = (-(k1 + kc)*x1 + kc*x2 + fuerza_externa)/m1;
  der(v2) = (kc*x1 - (k2 + kc)*x2)/m2;
// Output assignments
  pos1 = x1;
  pos2 = x2;
  vel1 = v1;
  vel2 = v2;
// Total mechanical energy: kinetic + wall spring potential + coupling potential
  energia_total = 0.5*m1*v1^2 + 0.5*m2*v2^2 + 0.5*k1*x1^2 + 0.5*k2*x2^2 + 0.5*kc*(x1 - x2)^2;
// In-phase detection
  en_fase = (x1 >= 0.0 and x2 >= 0.0) or (x1 < 0.0 and x2 < 0.0);
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle(origin = {-24, 1}, fillColor = {245, 245, 255}, fillPattern = FillPattern.Solid, extent = {{-124, 135}, {124, -135}}), Text(origin = {-22, 34}, textColor = {0, 0, 150}, extent = {{-90, 95}, {90, 75}}, textString = "Coupled Bodies"), Text(origin = {-24, 28}, textColor = {100, 100, 100}, extent = {{-90, 73}, {90, 57}}, textString = "4 states — energy transfer"), Line(origin = {-36, -10}, points = {{-85, 30}, {-85, -10}}, thickness = 2), Line(origin = {-36, -10}, points = {{-85, 10}, {-70, 10}, {-65, 18}, {-55, 2}, {-45, 18}, {-35, 2}, {-25, 10}, {-20, 10}}, color = {0, 0, 180}), Rectangle(origin = {-36, -10}, fillColor = {150, 150, 220}, fillPattern = FillPattern.Solid, extent = {{-20, 18}, {5, 2}}), Text(origin = {-36, -10}, extent = {{-18, 16}, {3, 4}}, textString = "m1"), Line(origin = {-36, -10}, points = {{5, 10}, {12, 18}, {20, 2}, {28, 18}, {35, 10}}, color = {100, 100, 100}), Rectangle(origin = {-36, -10}, fillColor = {150, 220, 150}, fillPattern = FillPattern.Solid, extent = {{35, 18}, {65, 2}}), Text(origin = {-36, -10}, extent = {{37, 16}, {63, 4}}, textString = "m2"), Line(origin = {-36, -10}, points = {{65, 10}, {70, 10}, {75, 18}, {82, 2}, {85, 10}}, color = {0, 150, 0}), Line(origin = {-36, -10}, points = {{85, 30}, {85, -10}}, thickness = 2), Line(origin = {-66, -10}, points = {{-92, 10}, {-56, 10}}, color = {200, 0, 0}, thickness = 2, arrow = {Arrow.None, Arrow.Filled}), Text(origin = {-36, -10}, textColor = {200, 0, 0}, extent = {{-98, 5}, {-60, -8}}, textString = "F"), Text(origin = {6, 72},textColor = {0, 0, 200}, extent = {{50, -35}, {98, -49}}, textString = "pos2"), Text(origin = {8, 12},textColor = {0, 100, 0}, extent = {{50, -55}, {98, -69}}, textString = "vel2"), Text(origin = {-92, 58}, textColor = {200, 0, 0}, extent = {{95, -134}, {186, -160}}, textString = "EnergyConservation"), Text(origin = {8, 114},textColor = {0, 0, 200}, extent = {{50, -35}, {98, -49}}, textString = "pos1"), Text(origin = {8, 52},textColor = {0, 100, 0}, extent = {{50, -55}, {98, -69}}, textString = "vel1"), Text(origin = {-51, -26}, textColor = {200, 0, 0}, extent = {{73, -82}, {143, -98}}, textString = "BooleanOutput")}),
    Documentation(info = "<html>
      <h3>CuerposAcoplados — Two Coupled Masses</h3>
      <p>Two masses connected by wall springs and a coupling spring. With
         non-zero initial conditions and no external force, the system
         exhibits energy exchange between bodies (beating).</p>
      <h4>Key properties</h4>
      <ul>
        <li><b>4 continuous states</b> — verifies codegen buffer size scaling</li>
        <li><b>Energy conservation</b> — total energy ≈ 3.625 J (when F=0)</li>
        <li><b>Boolean output</b> — en_fase transitions as bodies go in/out of phase</li>
      </ul>
      <p>With Euler (h=0.05) and fuerza_externa=0: energia_total drifts upward.
         With RK4 (h=0.05): energia_total stays within 0.01 J of 3.625 J.</p>
    </html>"),
  Diagram(graphics));
end CuerposAcoplados;
