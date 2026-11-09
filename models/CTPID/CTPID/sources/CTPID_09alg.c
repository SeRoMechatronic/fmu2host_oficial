/* Algebraic */
#include "CTPID_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void CTPID_eqFunction_15(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_16(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_17(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_18(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_23(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_24(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_25(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_26(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_27(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_28(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[10])(DATA*, threadData_t*) = {
    CTPID_eqFunction_15,
    CTPID_eqFunction_16,
    CTPID_eqFunction_17,
    CTPID_eqFunction_18,
    CTPID_eqFunction_23,
    CTPID_eqFunction_24,
    CTPID_eqFunction_25,
    CTPID_eqFunction_26,
    CTPID_eqFunction_27,
    CTPID_eqFunction_28
  };
  
  static const int eqIndices[10] = {
    15,
    16,
    17,
    18,
    23,
    24,
    25,
    26,
    27,
    28
  };
  
  for (id = 0; id < 10; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int CTPID_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  CTPID_function_savePreSynchronous(data, threadData);
  
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
