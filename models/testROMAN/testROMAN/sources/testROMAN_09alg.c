/* Algebraic */
#include "testROMAN_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void testROMAN_eqFunction_6(DATA* data, threadData_t *threadData);
extern void testROMAN_eqFunction_7(DATA* data, threadData_t *threadData);
extern void testROMAN_eqFunction_8(DATA* data, threadData_t *threadData);
extern void testROMAN_eqFunction_9(DATA* data, threadData_t *threadData);
extern void testROMAN_eqFunction_10(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[5])(DATA*, threadData_t*) = {
    testROMAN_eqFunction_6,
    testROMAN_eqFunction_7,
    testROMAN_eqFunction_8,
    testROMAN_eqFunction_9,
    testROMAN_eqFunction_10
  };
  
  static const int eqIndices[5] = {
    6,
    7,
    8,
    9,
    10
  };
  
  for (id = 0; id < 5; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int testROMAN_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  testROMAN_function_savePreSynchronous(data, threadData);
  
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
