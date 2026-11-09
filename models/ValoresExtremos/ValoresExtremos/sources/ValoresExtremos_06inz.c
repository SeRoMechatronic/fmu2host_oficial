/* Initialization */
#include "ValoresExtremos_model.h"
#include "ValoresExtremos_11mix.h"
#include "ValoresExtremos_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ValoresExtremos_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void ValoresExtremos_eqFunction_6(DATA *data, threadData_t *threadData);


/*
equation index: 2
type: SIMPLE_ASSIGN
y_sat = min(1.0, max(-1.0, u))
*/
void ValoresExtremos_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* y_sat variable */) = fmin(1.0,fmax(-1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)));
  TRACE_POP
}
extern void ValoresExtremos_eqFunction_9(DATA *data, threadData_t *threadData);

extern void ValoresExtremos_eqFunction_10(DATA *data, threadData_t *threadData);

extern void ValoresExtremos_eqFunction_11(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ValoresExtremos_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ValoresExtremos_eqFunction_6(data, threadData);
  ValoresExtremos_eqFunction_2(data, threadData);
  ValoresExtremos_eqFunction_9(data, threadData);
  ValoresExtremos_eqFunction_10(data, threadData);
  ValoresExtremos_eqFunction_11(data, threadData);
  TRACE_POP
}

int ValoresExtremos_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ValoresExtremos_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ValoresExtremos_functionInitialEquations_lambda0 function */

int ValoresExtremos_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

