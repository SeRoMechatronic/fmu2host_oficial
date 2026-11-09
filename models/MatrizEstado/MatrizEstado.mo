model MatrizEstado "Linear state-space system with 3x3 matrix — vector/matrix ODE stress test"
  // ============================================================================
  // MatrizEstado.mo
  // Linear time-invariant (LTI) state-space system with matrix parameters.
  // FMI 2.0 Model Exchange compatible — fmi-c-embedded ready.
  //
  // Description:
  //   Implements the classic state-space representation:
  //     dx/dt = A·x + B·u
  //   where A is a 3×3 diagonal matrix and B is a 3×1 input matrix.
  //
  //   This model tests the codegen's ability to handle:
  //     - Matrix parameters (A[3,3], B[3,1]) unrolled as scalar FMI parameters
  //     - Vector state (x[3]) producing 3 scalar FMI outputs
  //     - Matrix-vector multiplication in the ODE right-hand side
  //     - Scalar outputs derived from vector operations (norm, trace)
  //
  //   With A diagonal (eigenvalues 1, 2, 3) and initial state zero, the system
  //   is unstable — states grow exponentially. This is intentional to make
  //   the integration result clearly observable and time-dependent.
  //
  // Physics:
  //   A = diag(1, 2, 3),  B = [1; 1; 1],  x(0) = [0; 0; 0]
  //   With u=1: xi(t) = (e^(λi·t) - 1) / λi
  //
  // Interface:
  //   Params  : A[3,3] (Real) — system matrix (9 scalar FMI parameters)
  //             B[3,1] (Real) — input matrix  (3 scalar FMI parameters)
  //   Inputs  : u[1]   (Real) — scalar control input
  //   Outputs : x[3]   (Real) — state vector (3 scalar FMI outputs)
  //             y_norma (Real) — Euclidean norm ‖x‖
  //             traza   (Real) — trace of A (constant: A[1,1]+A[2,2]+A[3,3])
  // ============================================================================
  // ── Parameters: system matrices ─────────────────────────────────────────────
  parameter Real A[3, 3] = [1, 0, 0; 0, 2, 0; 0, 0, 3] "3×3 system matrix A — diagonal with eigenvalues 1, 2, 3 (unstable system)";
  parameter Real B[3, 1] = [1; 1; 1] "3×1 input matrix B — uniform input to all three states";
  // ── Inputs ──────────────────────────────────────────────────────────────────
  input Real u[1] = {0.0} "Scalar control input (wrapped as 1-element vector for matrix multiplication)" annotation(
    Dialog(group = "Input"));
  // ── Outputs ─────────────────────────────────────────────────────────────────
  output Real x[3] "State vector x(t) — 3 individual Real FMI output variables" annotation(
    Dialog(group = "State Outputs"));
  Modelica.Blocks.Interfaces.RealOutput y_norma "Euclidean norm of the state vector: ‖x‖ = √(x₁²+x₂²+x₃²)" annotation(
    Placement(transformation(extent = {{100, 20}, {120, 40}}), iconTransformation(origin = {0, 6}, extent = {{100, 20}, {120, 40}})));
  Modelica.Blocks.Interfaces.RealOutput traza "Trace of matrix A: A[1,1]+A[2,2]+A[3,3] = 6.0 (constant)" annotation(
    Placement(transformation(extent = {{100, -20}, {120, 0}}), iconTransformation(origin = {0, -30}, extent = {{100, -20}, {120, 0}})));
  // ── State variables ─────────────────────────────────────────────────────────
  Real x_state[3](each start = 0.0, each fixed = true) "Internal state vector — initialized to zero";
equation
// State-space ODE: dx/dt = A·x + B·u
  der(x_state) = A*x_state + B*u;
// Assign state to output (x is an alias for x_state)
  x = x_state;
// Scalar outputs derived from the state vector
  y_norma = sqrt(x_state*x_state);
// ‖x‖ = √(x·x)
  traza = A[1, 1] + A[2, 2] + A[3, 3];
// sum of diagonal elements
  annotation(
    Icon(coordinateSystem(preserveAspectRatio = false), graphics = {Rectangle( fillColor = {245, 255, 250}, fillPattern = FillPattern.Solid, extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 4},textColor = {0, 100, 60}, extent = {{-90, 95}, {90, 72}}, textString = "MatrizEstado"), Text(origin = {0, 8},textColor = {100, 100, 100}, extent = {{-90, 70}, {90, 55}}, textString = "dx/dt = Ax + Bu   (3×3 LTI)"), Rectangle(origin = {-6, 4},lineColor = {0, 100, 60}, fillColor = {210, 240, 225}, fillPattern = FillPattern.Solid, extent = {{-85, 45}, {-35, 5}}), Text(origin = {-6, 4},textColor = {0, 100, 60}, extent = {{-83, 43}, {-37, 28}}, textString = "A[3×3]"), Text(origin = {-6, 4},textColor = {0, 80, 50}, extent = {{-83, 26}, {-37, 8}}, textString = "diag(1,2,3)"), Rectangle(origin = {-6, -6},lineColor = {0, 100, 60}, fillColor = {210, 240, 225}, fillPattern = FillPattern.Solid, extent = {{-85, 0}, {-55, -30}}), Text(origin = {-6, -6},textColor = {0, 100, 60}, extent = {{-83, -2}, {-57, -12}}, textString = "B[3×1]"), Text(origin = {-6, -6},textColor = {0, 80, 50}, extent = {{-83, -14}, {-57, -28}}, textString = "[1;1;1]"), Rectangle(origin = {-6, -14},lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{-85, -40}, {-55, -60}}), Text(origin = {-6, -14},textColor = {0, 0, 180}, extent = {{-83, -42}, {-57, -58}}, textString = "u[1]"), Rectangle(origin = {-2, -28},lineColor = {0, 80, 50}, fillColor = {230, 245, 235}, fillPattern = FillPattern.Solid, extent = {{-20, 40}, {20, -20}}), Text(origin = {-2, -28},textColor = {0, 80, 50}, extent = {{-18, 35}, {18, -15}}, textString = "dx/dt
=Ax
+Bu"), Rectangle(origin = {-8, -40},lineColor = {0, 100, 60}, fillColor = {210, 240, 225}, fillPattern = FillPattern.Solid, extent = {{41, 65}, {104, 45}}), Text(origin = {2, -40},textColor = {0, 100, 60}, extent = {{37, 63}, {88, 47}}, textString = "x[3] states"), Rectangle(origin = {2, -48},lineColor = {0, 0, 180}, fillColor = {210, 220, 255}, fillPattern = FillPattern.Solid, extent = {{35, 38}, {90, 22}}), Text(origin = {2, -48},textColor = {0, 0, 180}, extent = {{37, 36}, {88, 24}}, textString = "‖x‖ norm"), Rectangle(origin = {2, -56},lineColor = {150, 80, 0}, fillColor = {255, 235, 210}, fillPattern = FillPattern.Solid, extent = {{35, 15}, {90, -1}}), Text(origin = {2, -56},textColor = {150, 80, 0}, extent = {{37, 13}, {88, 1}}, textString = "tr(A) = 6"), Line(origin = {0, -30},points = {{-41, 59}, {-22, 35}}, color = {0, 100, 60}), Line(origin = {0, -30},points = {{-61, 9}, {-22, 9}}, color = {0, 100, 60}), Line(origin = {0, -30},points = {{-61, -34}, {-22, -10}}, color = {0, 0, 180}), Line(origin = {0, -30},points = {{18, 34}, {33, 45}}, color = {0, 100, 60}), Line(origin = {0, -30},points = {{18, 11}, {37, 12}}, color = {0, 0, 180}), Line(origin = {0, -30},points = {{18, -8}, {37, -19}}, color = {150, 80, 0})}),
    Documentation(info = "<html>
      <h3>MatrizEstado — LTI State-Space System with 3×3 Matrix</h3>
      <p>Implements dx/dt = A·x + B·u with A = diag(1,2,3) and B=[1;1;1].</p>
      <p>This model tests matrix parameter unrolling (9+3=12 scalar FMI parameters),
         vector state outputs (3 scalars), and matrix-vector multiply in the ODE.</p>
      <h4>Key property</h4>
      <p>With all eigenvalues positive, the system is unstable and states grow
         exponentially. Analytical solution with u=1: xᵢ(t) = (eˡⁱᵗ - 1)/λᵢ</p>
      <p><b>traza</b> = A[1,1]+A[2,2]+A[3,3] = 1+2+3 = 6.0 (constant at all times)</p>
    </html>"));
end MatrizEstado;
