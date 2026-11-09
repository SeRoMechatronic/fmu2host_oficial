/* Algebraic */
#include "MatrizEstado_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void MatrizEstado_eqFunction_14(DATA* data, threadData_t *threadData);
extern void MatrizEstado_eqFunction_18(DATA* data, threadData_t *threadData);
extern void MatrizEstado_eqFunction_19(DATA* data, threadData_t *threadData);
extern void MatrizEstado_eqFunction_20(DATA* data, threadData_t *threadData);
extern void MatrizEstado_eqFunction_21(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[5])(DATA*, threadData_t*) = {
    MatrizEstado_eqFunction_14,
    MatrizEstado_eqFunction_18,
    MatrizEstado_eqFunction_19,
    MatrizEstado_eqFunction_20,
    MatrizEstado_eqFunction_21
  };
  
  static const int eqIndices[5] = {
    14,
    18,
    19,
    20,
    21
  };
  
  for (id = 0; id < 5; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int MatrizEstado_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  MatrizEstado_function_savePreSynchronous(data, threadData);
  
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
