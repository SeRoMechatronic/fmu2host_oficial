/* Algebraic */
#include "TiposMixtos_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void TiposMixtos_eqFunction_5(DATA* data, threadData_t *threadData);
extern void TiposMixtos_eqFunction_6(DATA* data, threadData_t *threadData);
extern void TiposMixtos_eqFunction_7(DATA* data, threadData_t *threadData);
extern void TiposMixtos_eqFunction_8(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    TiposMixtos_eqFunction_5,
    TiposMixtos_eqFunction_6,
    TiposMixtos_eqFunction_7,
    TiposMixtos_eqFunction_8
  };
  
  static const int eqIndices[4] = {
    5,
    6,
    7,
    8
  };
  
  for (id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int TiposMixtos_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  TiposMixtos_function_savePreSynchronous(data, threadData);
  
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
