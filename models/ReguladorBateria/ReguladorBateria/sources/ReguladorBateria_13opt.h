#if defined(__cplusplus)
  extern "C" {
#endif
  int ReguladorBateria_mayer(DATA* data, modelica_real** res, short*);
  int ReguladorBateria_lagrange(DATA* data, modelica_real** res, short *, short *);
  int ReguladorBateria_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int ReguladorBateria_setInputData(DATA *data, const modelica_boolean file);
  int ReguladorBateria_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif