/* Linearization */
#include "SelectorModo_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *SelectorModo_linear_model_frame()
{
  return "model linearized_model \"SelectorModo\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 2 \"number of inputs\";\n"
  "  parameter Integer p = 3 \"number of outputs\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = zeros(n, n);%s\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] =\n\t[%s];\n\n"
  "\n"
  "  Real x[n];\n"
  "  input Real u[m](start=u0);\n"
  "  output Real y[p];\n"
  "\n"
  "  Real 'u_consigna_manual' = u[1];\n"
  "  Real 'u_modo_operacion' = u[2];\n"
  "  Real 'y_codigo_estado' = y[1];\n"
  "  Real 'y_fallo_modo' = y[2];\n"
  "  Real 'y_salida_actuador' = y[3];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *SelectorModo_linear_model_datarecovery_frame()
{
  return "model linearized_model \"SelectorModo\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 2 \"number of inputs\";\n"
  "  parameter Integer p = 3 \"number of outputs\";\n"
  "  parameter Integer nz = 2 \"data recovery variables\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "  parameter Real z0[nz] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = zeros(n, n);%s\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] =\n\t[%s];\n\n"
  "  parameter Real Cz[nz, n] = zeros(nz, n);%s\n\n"
  "  parameter Real Dz[nz, m] =\n\t[%s];\n\n"
  "\n"
  "  Real x[n];\n"
  "  input Real u[m](start=u0);\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'u_consigna_manual' = u[1];\n"
  "  Real 'u_modo_operacion' = u[2];\n"
  "  Real 'y_codigo_estado' = y[1];\n"
  "  Real 'y_fallo_modo' = y[2];\n"
  "  Real 'y_salida_actuador' = y[3];\n"
  "  Real 'z_consigna_manual' = z[1];\n"
  "  Real 'z_salida_actuador' = z[2];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

