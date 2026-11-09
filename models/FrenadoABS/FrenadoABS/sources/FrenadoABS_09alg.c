/* Algebraic */
#include "FrenadoABS_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void FrenadoABS_eqFunction_21(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_24(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_25(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_26(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_27(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[5])(DATA*, threadData_t*) = {
    FrenadoABS_eqFunction_21,
    FrenadoABS_eqFunction_24,
    FrenadoABS_eqFunction_25,
    FrenadoABS_eqFunction_26,
    FrenadoABS_eqFunction_27
  };
  
  static const int eqIndices[5] = {
    21,
    24,
    25,
    26,
    27
  };
  
  for (id = 0; id < 5; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int FrenadoABS_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  FrenadoABS_function_savePreSynchronous(data, threadData);
  
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
