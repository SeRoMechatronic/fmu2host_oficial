/* Initialization */
#include "MatrizEstado_model.h"
#include "MatrizEstado_11mix.h"
#include "MatrizEstado_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void MatrizEstado_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
u[1] = 0.0
*/
void MatrizEstado_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* u[1] variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
$outputAlias_traza = A[1,1] + A[2,2] + A[3,3]
*/
void MatrizEstado_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* $outputAlias_traza variable */) = (data->simulationInfo->realParameter[0] /* A[1,1] PARAM */) + (data->simulationInfo->realParameter[4] /* A[2,2] PARAM */) + (data->simulationInfo->realParameter[8] /* A[3,3] PARAM */);
  TRACE_POP
}
extern void MatrizEstado_eqFunction_21(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
x_state[1] = $START.x_state[1]
*/
void MatrizEstado_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x_state[1] STATE(1) */) = (data->modelData->realVarsData[0] /* x_state[1] STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MatrizEstado_eqFunction_20(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
x_state[2] = $START.x_state[2]
*/
void MatrizEstado_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x_state[2] STATE(1) */) = (data->modelData->realVarsData[1] /* x_state[2] STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MatrizEstado_eqFunction_19(DATA *data, threadData_t *threadData);


/*
equation index: 8
type: SIMPLE_ASSIGN
x_state[3] = $START.x_state[3]
*/
void MatrizEstado_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x_state[3] STATE(1) */) = (data->modelData->realVarsData[2] /* x_state[3] STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MatrizEstado_eqFunction_18(DATA *data, threadData_t *threadData);

extern void MatrizEstado_eqFunction_17(DATA *data, threadData_t *threadData);

extern void MatrizEstado_eqFunction_16(DATA *data, threadData_t *threadData);

extern void MatrizEstado_eqFunction_15(DATA *data, threadData_t *threadData);

extern void MatrizEstado_eqFunction_14(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void MatrizEstado_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  MatrizEstado_eqFunction_1(data, threadData);
  MatrizEstado_eqFunction_2(data, threadData);
  MatrizEstado_eqFunction_21(data, threadData);
  MatrizEstado_eqFunction_4(data, threadData);
  MatrizEstado_eqFunction_20(data, threadData);
  MatrizEstado_eqFunction_6(data, threadData);
  MatrizEstado_eqFunction_19(data, threadData);
  MatrizEstado_eqFunction_8(data, threadData);
  MatrizEstado_eqFunction_18(data, threadData);
  MatrizEstado_eqFunction_17(data, threadData);
  MatrizEstado_eqFunction_16(data, threadData);
  MatrizEstado_eqFunction_15(data, threadData);
  MatrizEstado_eqFunction_14(data, threadData);
  TRACE_POP
}

int MatrizEstado_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  MatrizEstado_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No MatrizEstado_functionInitialEquations_lambda0 function */

int MatrizEstado_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

