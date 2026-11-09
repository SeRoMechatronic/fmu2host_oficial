/* Algebraic */
#include "ArranqueSuaveMotor_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void ArranqueSuaveMotor_eqFunction_12(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_13(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_18(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_19(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_20(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[5])(DATA*, threadData_t*) = {
    ArranqueSuaveMotor_eqFunction_12,
    ArranqueSuaveMotor_eqFunction_13,
    ArranqueSuaveMotor_eqFunction_18,
    ArranqueSuaveMotor_eqFunction_19,
    ArranqueSuaveMotor_eqFunction_20
  };
  
  static const int eqIndices[5] = {
    12,
    13,
    18,
    19,
    20
  };
  
  for (id = 0; id < 5; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int ArranqueSuaveMotor_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  ArranqueSuaveMotor_function_savePreSynchronous(data, threadData);
  
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
