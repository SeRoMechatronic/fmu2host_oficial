/* Algebraic */
#include "ReguladorBateria_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void ReguladorBateria_eqFunction_12(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_13(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_14(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[3])(DATA*, threadData_t*) = {
    ReguladorBateria_eqFunction_12,
    ReguladorBateria_eqFunction_13,
    ReguladorBateria_eqFunction_14
  };
  
  static const int eqIndices[3] = {
    12,
    13,
    14
  };
  
  for (id = 0; id < 3; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int ReguladorBateria_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ReguladorBateria_function_savePreSynchronous(data, threadData);
  
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
