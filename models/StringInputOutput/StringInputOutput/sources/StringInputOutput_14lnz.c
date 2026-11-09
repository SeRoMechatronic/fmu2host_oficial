/* Linearization */
#include "StringInputOutput_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *StringInputOutput_linear_model_frame()
{
  return "model linearized_model \"StringInputOutput\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 3 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
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
  "  Real 'u_mode_operation' = u[1];\n"
  "  Real 'u_tag_sensor' = u[2];\n"
  "  Real 'u_value' = u[3];\n"
  "  Real 'y_alarm' = y[1];\n"
  "  Real 'y_alert_msg' = y[2];\n"
  "  Real 'y_scaled_value' = y[3];\n"
  "  Real 'y_status' = y[4];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *StringInputOutput_linear_model_datarecovery_frame()
{
  return "model linearized_model \"StringInputOutput\"\n"
  "  parameter Integer n = 0 \"number of states\";\n"
  "  parameter Integer m = 3 \"number of inputs\";\n"
  "  parameter Integer p = 4 \"number of outputs\";\n"
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
  "  Real 'u_mode_operation' = u[1];\n"
  "  Real 'u_tag_sensor' = u[2];\n"
  "  Real 'u_value' = u[3];\n"
  "  Real 'y_alarm' = y[1];\n"
  "  Real 'y_alert_msg' = y[2];\n"
  "  Real 'y_scaled_value' = y[3];\n"
  "  Real 'y_status' = y[4];\n"
  "  Real 'z_scaled_value' = z[1];\n"
  "  Real 'z_value' = z[2];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

