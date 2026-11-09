/* Algebraic */
#include "MultiplexorCanales_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void MultiplexorCanales_eqFunction_4(DATA* data, threadData_t *threadData);
extern void MultiplexorCanales_eqFunction_5(DATA* data, threadData_t *threadData);
extern void MultiplexorCanales_eqFunction_6(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[3])(DATA*, threadData_t*) = {
    MultiplexorCanales_eqFunction_4,
    MultiplexorCanales_eqFunction_5,
    MultiplexorCanales_eqFunction_6
  };
  
  static const int eqIndices[3] = {
    4,
    5,
    6
  };
  
  for (id = 0; id < 3; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int MultiplexorCanales_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  MultiplexorCanales_function_savePreSynchronous(data, threadData);
  
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
