/* Linearization */
#include "NivelDeposito_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *NivelDeposito_linear_model_frame()
{
  return "model linearized_model \"NivelDeposito\"\n"
  "  parameter Integer n = 1 \"number of states\";\n"
  "  parameter Integer m = 2 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] =\n\t[%s];\n\n"
  "  parameter Real C[p, n] =\n\t[%s];\n\n"
  "  parameter Real D[p, m] =\n\t[%s];\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m](start=u0);\n"
  "  output Real y[p];\n"
  "\n"
  "  Real 'x_nivel_filtrado' = x[1];\n"
  "  Real 'u_sensor_nivel' = u[1];\n"
  "  Real 'u_valvula_manual' = u[2];\n"
  "  Real 'y_alarma_maximo' = y[1];\n"
  "  Real 'y_alarma_minimo' = y[2];\n"
  "  Real 'y_bomba' = y[3];\n"
  "  Real 'y_bomba_activa' = y[4];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *NivelDeposito_linear_model_datarecovery_frame()
{
  return "model linearized_model \"NivelDeposito\"\n"
  "  parameter Integer n = 1 \"number of states\";\n"
  "  parameter Integer m = 2 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
  "  parameter Integer nz = 5 \"data recovery variables\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "  parameter Real z0[nz] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] =\n\t[%s];\n\n"
  "  parameter Real C[p, n] =\n\t[%s];\n\n"
  "  parameter Real D[p, m] =\n\t[%s];\n\n"
  "  parameter Real Cz[nz, n] =\n\t[%s];\n\n"
  "  parameter Real Dz[nz, m] =\n\t[%s];\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m](start=u0);\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'x_nivel_filtrado' = x[1];\n"
  "  Real 'u_sensor_nivel' = u[1];\n"
  "  Real 'u_valvula_manual' = u[2];\n"
  "  Real 'y_alarma_maximo' = y[1];\n"
  "  Real 'y_alarma_minimo' = y[2];\n"
  "  Real 'y_bomba' = y[3];\n"
  "  Real 'y_bomba_activa' = y[4];\n"
  "  Real 'z_$cse1' = z[1];\n"
  "  Real 'z_Q_salida' = z[2];\n"
  "  Real 'z_bomba' = z[3];\n"
  "  Real 'z_error_nivel' = z[4];\n"
  "  Real 'z_sensor_nivel' = z[5];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

