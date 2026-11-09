/* Initialization */
#include "CSPuro_SinME_model.h"
#include "CSPuro_SinME_11mix.h"
#include "CSPuro_SinME_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void CSPuro_SinME_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void CSPuro_SinME_eqFunction_4(DATA *data, threadData_t *threadData);

extern void CSPuro_SinME_eqFunction_5(DATA *data, threadData_t *threadData);

extern void CSPuro_SinME_eqFunction_6(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void CSPuro_SinME_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  CSPuro_SinME_eqFunction_4(data, threadData);
  CSPuro_SinME_eqFunction_5(data, threadData);
  CSPuro_SinME_eqFunction_6(data, threadData);
  TRACE_POP
}

int CSPuro_SinME_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  CSPuro_SinME_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No CSPuro_SinME_functionInitialEquations_lambda0 function */

int CSPuro_SinME_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

