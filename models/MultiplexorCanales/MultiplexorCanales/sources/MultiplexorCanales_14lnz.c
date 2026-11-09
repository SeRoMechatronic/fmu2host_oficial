/* Linearization */
#include "MultiplexorCanales_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *MultiplexorCanales_linear_model_frame()
{
  return "model linearized_model \"MultiplexorCanales\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 5 \"number of inputs\";\n"
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
  "  Real 'u_canal_0' = u[1];\n"
  "  Real 'u_canal_1' = u[2];\n"
  "  Real 'u_canal_2' = u[3];\n"
  "  Real 'u_canal_3' = u[4];\n"
  "  Real 'u_canal_seleccion' = u[5];\n"
  "  Real 'y_canal_activo' = y[1];\n"
  "  Real 'y_canal_valido' = y[2];\n"
  "  Real 'y_salida' = y[3];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *MultiplexorCanales_linear_model_datarecovery_frame()
{
  return "model linearized_model \"MultiplexorCanales\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 5 \"number of inputs\";\n"
  "  parameter Integer p = 3 \"number of outputs\";\n"
  "  parameter Integer nz = 5 \"data recovery variables\";\n"
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
  "  Real 'u_canal_0' = u[1];\n"
  "  Real 'u_canal_1' = u[2];\n"
  "  Real 'u_canal_2' = u[3];\n"
  "  Real 'u_canal_3' = u[4];\n"
  "  Real 'u_canal_seleccion' = u[5];\n"
  "  Real 'y_canal_activo' = y[1];\n"
  "  Real 'y_canal_valido' = y[2];\n"
  "  Real 'y_salida' = y[3];\n"
  "  Real 'z_canal_0' = z[1];\n"
  "  Real 'z_canal_1' = z[2];\n"
  "  Real 'z_canal_2' = z[3];\n"
  "  Real 'z_canal_3' = z[4];\n"
  "  Real 'z_salida' = z[5];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

