#if defined(__cplusplus)
  extern "C" {
#endif
  int CSPuro_SinME_mayer(DATA* data, modelica_real** res, short*);
  int CSPuro_SinME_lagrange(DATA* data, modelica_real** res, short *, short *);
  int CSPuro_SinME_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int CSPuro_SinME_setInputData(DATA *data, const modelica_boolean file);
  int CSPuro_SinME_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif