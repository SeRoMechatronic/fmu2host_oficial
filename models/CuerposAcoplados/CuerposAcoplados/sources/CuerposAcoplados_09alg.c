/* Algebraic */
#include "CuerposAcoplados_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void CuerposAcoplados_eqFunction_15(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_16(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_21(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_22(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_23(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_24(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[6])(DATA*, threadData_t*) = {
    CuerposAcoplados_eqFunction_15,
    CuerposAcoplados_eqFunction_16,
    CuerposAcoplados_eqFunction_21,
    CuerposAcoplados_eqFunction_22,
    CuerposAcoplados_eqFunction_23,
    CuerposAcoplados_eqFunction_24
  };
  
  static const int eqIndices[6] = {
    15,
    16,
    21,
    22,
    23,
    24
  };
  
  for (id = 0; id < 6; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}
/* for continuous time variables */
int CuerposAcoplados_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  CuerposAcoplados_function_savePreSynchronous(data, threadData);
  
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
