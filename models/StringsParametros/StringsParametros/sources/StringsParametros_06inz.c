/* Initialization */
#include "StringsParametros_model.h"
#include "StringsParametros_11mix.h"
#include "StringsParametros_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void StringsParametros_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void StringsParametros_eqFunction_2(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void StringsParametros_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  StringsParametros_eqFunction_2(data, threadData);
  TRACE_POP
}

int StringsParametros_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  StringsParametros_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No StringsParametros_functionInitialEquations_lambda0 function */

int StringsParametros_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

