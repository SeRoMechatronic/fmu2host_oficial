#if defined(__cplusplus)
  extern "C" {
#endif
  int CTPID_mayer(DATA* data, modelica_real** res, short*);
  int CTPID_lagrange(DATA* data, modelica_real** res, short *, short *);
  int CTPID_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int CTPID_setInputData(DATA *data, const modelica_boolean file);
  int CTPID_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif