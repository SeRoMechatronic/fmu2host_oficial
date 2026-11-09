#if defined(__cplusplus)
  extern "C" {
#endif
  int ArraysVectores_mayer(DATA* data, modelica_real** res, short*);
  int ArraysVectores_lagrange(DATA* data, modelica_real** res, short *, short *);
  int ArraysVectores_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int ArraysVectores_setInputData(DATA *data, const modelica_boolean file);
  int ArraysVectores_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif