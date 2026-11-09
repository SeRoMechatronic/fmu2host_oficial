#if defined(__cplusplus)
  extern "C" {
#endif
  int StringInputOutput_mayer(DATA* data, modelica_real** res, short*);
  int StringInputOutput_lagrange(DATA* data, modelica_real** res, short *, short *);
  int StringInputOutput_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int StringInputOutput_setInputData(DATA *data, const modelica_boolean file);
  int StringInputOutput_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif