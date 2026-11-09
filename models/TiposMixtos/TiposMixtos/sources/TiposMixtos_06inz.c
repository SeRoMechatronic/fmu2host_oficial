/* Initialization */
#include "TiposMixtos_model.h"
#include "TiposMixtos_11mix.h"
#include "TiposMixtos_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void TiposMixtos_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void TiposMixtos_eqFunction_8(DATA *data, threadData_t *threadData);

extern void TiposMixtos_eqFunction_7(DATA *data, threadData_t *threadData);

extern void TiposMixtos_eqFunction_6(DATA *data, threadData_t *threadData);

extern void TiposMixtos_eqFunction_5(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void TiposMixtos_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  TiposMixtos_eqFunction_8(data, threadData);
  TiposMixtos_eqFunction_7(data, threadData);
  TiposMixtos_eqFunction_6(data, threadData);
  TiposMixtos_eqFunction_5(data, threadData);
  TRACE_POP
}

int TiposMixtos_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  TiposMixtos_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No TiposMixtos_functionInitialEquations_lambda0 function */

int TiposMixtos_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

