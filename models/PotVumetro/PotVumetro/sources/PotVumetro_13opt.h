#if defined(__cplusplus)
  extern "C" {
#endif
  int PotVumetro_mayer(DATA* data, modelica_real** res, short*);
  int PotVumetro_lagrange(DATA* data, modelica_real** res, short *, short *);
  int PotVumetro_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int PotVumetro_setInputData(DATA *data, const modelica_boolean file);
  int PotVumetro_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif