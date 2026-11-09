/* Algebraic */
#include "BooleanLogica_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void BooleanLogica_eqFunction_13(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_14(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_16(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_18(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_19(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_20(DATA* data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_21(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[7])(DATA*, threadData_t*) = {
    BooleanLogica_eqFunction_13,
    BooleanLogica_eqFunction_14,
    BooleanLogica_eqFunction_16,
    BooleanLogica_eqFunction_18,
    BooleanLogica_eqFunction_19,
    BooleanLogica_eqFunction_20,
    BooleanLogica_eqFunction_21
  };
  
  static const int eqIndices[7] = {
    13,
    14,
    16,
    18,
    19,
    20,
    21
  };
  
  for (id = 0; id < 7; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int BooleanLogica_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  BooleanLogica_function_savePreSynchronous(data, threadData);
  
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
