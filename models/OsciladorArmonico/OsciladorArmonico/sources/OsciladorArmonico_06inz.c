/* Initialization */
#include "OsciladorArmonico_model.h"
#include "OsciladorArmonico_11mix.h"
#include "OsciladorArmonico_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void OsciladorArmonico_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x = $START.x
*/
void OsciladorArmonico_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x STATE(1,v) */) = (data->modelData->realVarsData[1] /* x STATE(1,v) */).attribute .start;
  TRACE_POP
}
extern void OsciladorArmonico_eqFunction_12(DATA *data, threadData_t *threadData);

extern void OsciladorArmonico_eqFunction_9(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
v = $START.v
*/
void OsciladorArmonico_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* v STATE(1) */) = (data->modelData->realVarsData[0] /* v STATE(1) */).attribute .start;
  TRACE_POP
}
extern void OsciladorArmonico_eqFunction_11(DATA *data, threadData_t *threadData);

extern void OsciladorArmonico_eqFunction_10(DATA *data, threadData_t *threadData);

extern void OsciladorArmonico_eqFunction_8(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void OsciladorArmonico_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  OsciladorArmonico_eqFunction_1(data, threadData);
  OsciladorArmonico_eqFunction_12(data, threadData);
  OsciladorArmonico_eqFunction_9(data, threadData);
  OsciladorArmonico_eqFunction_4(data, threadData);
  OsciladorArmonico_eqFunction_11(data, threadData);
  OsciladorArmonico_eqFunction_10(data, threadData);
  OsciladorArmonico_eqFunction_8(data, threadData);
  TRACE_POP
}

int OsciladorArmonico_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  OsciladorArmonico_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No OsciladorArmonico_functionInitialEquations_lambda0 function */

int OsciladorArmonico_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

