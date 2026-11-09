/* Initialization */
#include "CrecimientoPoblacional_model.h"
#include "CrecimientoPoblacional_11mix.h"
#include "CrecimientoPoblacional_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void CrecimientoPoblacional_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
N = $START.N
*/
void CrecimientoPoblacional_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* N STATE(1) */) = (data->modelData->realVarsData[0] /* N STATE(1) */).attribute .start;
  TRACE_POP
}
extern void CrecimientoPoblacional_eqFunction_11(DATA *data, threadData_t *threadData);

extern void CrecimientoPoblacional_eqFunction_8(DATA *data, threadData_t *threadData);

extern void CrecimientoPoblacional_eqFunction_9(DATA *data, threadData_t *threadData);

extern void CrecimientoPoblacional_eqFunction_10(DATA *data, threadData_t *threadData);

extern void CrecimientoPoblacional_eqFunction_7(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void CrecimientoPoblacional_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  CrecimientoPoblacional_eqFunction_1(data, threadData);
  CrecimientoPoblacional_eqFunction_11(data, threadData);
  CrecimientoPoblacional_eqFunction_8(data, threadData);
  CrecimientoPoblacional_eqFunction_9(data, threadData);
  CrecimientoPoblacional_eqFunction_10(data, threadData);
  CrecimientoPoblacional_eqFunction_7(data, threadData);
  TRACE_POP
}

int CrecimientoPoblacional_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  CrecimientoPoblacional_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No CrecimientoPoblacional_functionInitialEquations_lambda0 function */

int CrecimientoPoblacional_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

