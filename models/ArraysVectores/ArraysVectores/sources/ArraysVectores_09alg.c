/* Algebraic */
#include "ArraysVectores_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void ArraysVectores_eqFunction_20(DATA* data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_21(DATA* data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_22(DATA* data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_23(DATA* data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_24(DATA* data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_25(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[6])(DATA*, threadData_t*) = {
    ArraysVectores_eqFunction_20,
    ArraysVectores_eqFunction_21,
    ArraysVectores_eqFunction_22,
    ArraysVectores_eqFunction_23,
    ArraysVectores_eqFunction_24,
    ArraysVectores_eqFunction_25
  };
  
  static const int eqIndices[6] = {
    20,
    21,
    22,
    23,
    24,
    25
  };
  
  for (id = 0; id < 6; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int ArraysVectores_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ArraysVectores_function_savePreSynchronous(data, threadData);
  
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
