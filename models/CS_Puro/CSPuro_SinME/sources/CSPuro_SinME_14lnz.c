/* Linearization */
#include "CSPuro_SinME_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *CSPuro_SinME_linear_model_frame()
{
  return "model linearized_model \"CSPuro_SinME\"\n"
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
  "  Real 'u_u1' = u[1];\n"
  "  Real 'u_u2' = u[2];\n"
  "  Real 'y_active' = y[1];\n"
  "  Real 'y_y_prod' = y[2];\n"
  "  Real 'y_y_sum' = y[3];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *CSPuro_SinME_linear_model_datarecovery_frame()
{
  return "model linearized_model \"CSPuro_SinME\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 2 \"number of inputs\";\n"
  "  parameter Integer p = 3 \"number of outputs\";\n"
  "  parameter Integer nz = 4 \"data recovery variables\";\n"
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
  "  Real 'u_u1' = u[1];\n"
  "  Real 'u_u2' = u[2];\n"
  "  Real 'y_active' = y[1];\n"
  "  Real 'y_y_prod' = y[2];\n"
  "  Real 'y_y_sum' = y[3];\n"
  "  Real 'z_u1' = z[1];\n"
  "  Real 'z_u2' = z[2];\n"
  "  Real 'z_y_prod' = z[3];\n"
  "  Real 'z_y_sum' = z[4];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

