#if defined(__cplusplus)
  extern "C" {
#endif
  int Mi_Modelo_Nuevo_mayer(DATA* data, modelica_real** res, short*);
  int Mi_Modelo_Nuevo_lagrange(DATA* data, modelica_real** res, short *, short *);
  int Mi_Modelo_Nuevo_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int Mi_Modelo_Nuevo_setInputData(DATA *data, const modelica_boolean file);
  int Mi_Modelo_Nuevo_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif