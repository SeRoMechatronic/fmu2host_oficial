/* Algebraic */
#include "MuchosEstados_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void MuchosEstados_eqFunction_26(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_35(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_36(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_37(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_38(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_39(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_40(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_41(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_42(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[9])(DATA*, threadData_t*) = {
    MuchosEstados_eqFunction_26,
    MuchosEstados_eqFunction_35,
    MuchosEstados_eqFunction_36,
    MuchosEstados_eqFunction_37,
    MuchosEstados_eqFunction_38,
    MuchosEstados_eqFunction_39,
    MuchosEstados_eqFunction_40,
    MuchosEstados_eqFunction_41,
    MuchosEstados_eqFunction_42
  };
  
  static const int eqIndices[9] = {
    26,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42
  };
  
  for (id = 0; id < 9; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int MuchosEstados_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  MuchosEstados_function_savePreSynchronous(data, threadData);
  
  functionAlg_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ALGEBRAICS);
#endif

  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
