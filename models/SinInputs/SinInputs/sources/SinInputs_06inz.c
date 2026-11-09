/* Initialization */
#include "SinInputs_model.h"
#include "SinInputs_11mix.h"
#include "SinInputs_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void SinInputs_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x = $START.x
*/
void SinInputs_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x STATE(1,v) */) = (data->modelData->realVarsData[1] /* x STATE(1,v) */).attribute .start;
  TRACE_POP
}
extern void SinInputs_eqFunction_12(DATA *data, threadData_t *threadData);


/*
equation index: 3
type: SIMPLE_ASSIGN
v = $START.v
*/
void SinInputs_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* v STATE(1) */) = (data->modelData->realVarsData[0] /* v STATE(1) */).attribute .start;
  TRACE_POP
}
extern void SinInputs_eqFunction_11(DATA *data, threadData_t *threadData);

extern void SinInputs_eqFunction_10(DATA *data, threadData_t *threadData);

extern void SinInputs_eqFunction_9(DATA *data, threadData_t *threadData);

extern void SinInputs_eqFunction_8(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void SinInputs_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  SinInputs_eqFunction_1(data, threadData);
  SinInputs_eqFunction_12(data, threadData);
  SinInputs_eqFunction_3(data, threadData);
  SinInputs_eqFunction_11(data, threadData);
  SinInputs_eqFunction_10(data, threadData);
  SinInputs_eqFunction_9(data, threadData);
  SinInputs_eqFunction_8(data, threadData);
  TRACE_POP
}

int SinInputs_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  SinInputs_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No SinInputs_functionInitialEquations_lambda0 function */

int SinInputs_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

