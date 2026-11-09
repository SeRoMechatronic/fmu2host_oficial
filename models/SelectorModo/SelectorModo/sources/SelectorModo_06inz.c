/* Initialization */
#include "SelectorModo_model.h"
#include "SelectorModo_11mix.h"
#include "SelectorModo_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void SelectorModo_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void SelectorModo_eqFunction_4(DATA *data, threadData_t *threadData);

extern void SelectorModo_eqFunction_5(DATA *data, threadData_t *threadData);

extern void SelectorModo_eqFunction_6(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void SelectorModo_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  SelectorModo_eqFunction_4(data, threadData);
  SelectorModo_eqFunction_5(data, threadData);
  SelectorModo_eqFunction_6(data, threadData);
  TRACE_POP
}

int SelectorModo_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  SelectorModo_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No SelectorModo_functionInitialEquations_lambda0 function */

int SelectorModo_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

