/* Initialization */
#include "StringInputOutput_model.h"
#include "StringInputOutput_11mix.h"
#include "StringInputOutput_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void StringInputOutput_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void StringInputOutput_eqFunction_5(DATA *data, threadData_t *threadData);

extern void StringInputOutput_eqFunction_6(DATA *data, threadData_t *threadData);

extern void StringInputOutput_eqFunction_7(DATA *data, threadData_t *threadData);

extern void StringInputOutput_eqFunction_8(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void StringInputOutput_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  StringInputOutput_eqFunction_5(data, threadData);
  StringInputOutput_eqFunction_6(data, threadData);
  StringInputOutput_eqFunction_7(data, threadData);
  StringInputOutput_eqFunction_8(data, threadData);
  TRACE_POP
}

int StringInputOutput_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  StringInputOutput_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No StringInputOutput_functionInitialEquations_lambda0 function */

int StringInputOutput_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

