/* Algebraic */
#include "ContadorEventos_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void ContadorEventos_eqFunction_10(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_11(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_13(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_14(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_15(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_16(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[6])(DATA*, threadData_t*) = {
    ContadorEventos_eqFunction_10,
    ContadorEventos_eqFunction_11,
    ContadorEventos_eqFunction_13,
    ContadorEventos_eqFunction_14,
    ContadorEventos_eqFunction_15,
    ContadorEventos_eqFunction_16
  };
  
  static const int eqIndices[6] = {
    10,
    11,
    13,
    14,
    15,
    16
  };
  
  for (id = 0; id < 6; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int ContadorEventos_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ContadorEventos_function_savePreSynchronous(data, threadData);
  
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
