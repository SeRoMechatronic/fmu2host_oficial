/* Linearization */
#include "PenduloNoLineal_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *PenduloNoLineal_linear_model_frame()
{
  return "model linearized_model \"PenduloNoLineal\"\n"
  "  parameter Integer n = 2 \"number of states\";\n"
  "  parameter Integer m = 0 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] =\n\t[%s];\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "\n"
  "  Real 'x_omega_p' = x[1];\n"
  "  Real 'x_theta' = x[2];\n"
  "  Real 'y_angulo' = y[1];\n"
  "  Real 'y_en_reposo' = y[2];\n"
  "  Real 'y_energia_total' = y[3];\n"
  "  Real 'y_velocidad_angular' = y[4];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *PenduloNoLineal_linear_model_datarecovery_frame()
{
  return "model linearized_model \"PenduloNoLineal\"\n"
  "  parameter Integer n = 2 \"number of states\";\n"
  "  parameter Integer m = 0 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
  "  parameter Integer nz = 5 \"data recovery variables\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "  parameter Real z0[nz] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] =\n\t[%s];\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "  parameter Real Cz[nz, n] =\n\t[%s];\n\n"
  "  parameter Real Dz[nz, m] = zeros(nz, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'x_omega_p' = x[1];\n"
  "  Real 'x_theta' = x[2];\n"
  "  Real 'y_angulo' = y[1];\n"
  "  Real 'y_en_reposo' = y[2];\n"
  "  Real 'y_energia_total' = y[3];\n"
  "  Real 'y_velocidad_angular' = y[4];\n"
  "  Real 'z_$cse1' = z[1];\n"
  "  Real 'z_$cse2' = z[2];\n"
  "  Real 'z_angulo' = z[3];\n"
  "  Real 'z_energia_total' = z[4];\n"
  "  Real 'z_velocidad_angular' = z[5];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

