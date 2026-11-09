/* Algebraic */
#include "ValoresExtremos_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void ValoresExtremos_eqFunction_6(DATA* data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_7(DATA* data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_8(DATA* data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_9(DATA* data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_10(DATA* data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_11(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[6])(DATA*, threadData_t*) = {
    ValoresExtremos_eqFunction_6,
    ValoresExtremos_eqFunction_7,
    ValoresExtremos_eqFunction_8,
    ValoresExtremos_eqFunction_9,
    ValoresExtremos_eqFunction_10,
    ValoresExtremos_eqFunction_11
  };
  
  static const int eqIndices[6] = {
    6,
    7,
    8,
    9,
    10,
    11
  };
  
  for (id = 0; id < 6; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int ValoresExtremos_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ValoresExtremos_function_savePreSynchronous(data, threadData);
  
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
