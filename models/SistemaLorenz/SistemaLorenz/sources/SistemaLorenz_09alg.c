/* Algebraic */
#include "SistemaLorenz_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void SistemaLorenz_eqFunction_11(DATA* data, threadData_t *threadData);
extern void SistemaLorenz_eqFunction_15(DATA* data, threadData_t *threadData);
extern void SistemaLorenz_eqFunction_16(DATA* data, threadData_t *threadData);
extern void SistemaLorenz_eqFunction_17(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    SistemaLorenz_eqFunction_11,
    SistemaLorenz_eqFunction_15,
    SistemaLorenz_eqFunction_16,
    SistemaLorenz_eqFunction_17
  };
  
  static const int eqIndices[4] = {
    11,
    15,
    16,
    17
  };
  
  for (id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int SistemaLorenz_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  SistemaLorenz_function_savePreSynchronous(data, threadData);
  
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
