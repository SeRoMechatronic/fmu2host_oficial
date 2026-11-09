/* Initialization */
#include "MultiplexorCanales_model.h"
#include "MultiplexorCanales_11mix.h"
#include "MultiplexorCanales_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void MultiplexorCanales_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void MultiplexorCanales_eqFunction_4(DATA *data, threadData_t *threadData);

extern void MultiplexorCanales_eqFunction_5(DATA *data, threadData_t *threadData);

extern void MultiplexorCanales_eqFunction_6(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void MultiplexorCanales_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  MultiplexorCanales_eqFunction_4(data, threadData);
  MultiplexorCanales_eqFunction_5(data, threadData);
  MultiplexorCanales_eqFunction_6(data, threadData);
  TRACE_POP
}

int MultiplexorCanales_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  MultiplexorCanales_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No MultiplexorCanales_functionInitialEquations_lambda0 function */

int MultiplexorCanales_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

