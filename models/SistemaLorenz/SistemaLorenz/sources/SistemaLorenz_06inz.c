/* Initialization */
#include "SistemaLorenz_model.h"
#include "SistemaLorenz_11mix.h"
#include "SistemaLorenz_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void SistemaLorenz_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x = $START.x
*/
void SistemaLorenz_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */) = (data->modelData->realVarsData[0] /* x STATE(1) */).attribute .start;
  TRACE_POP
}
extern void SistemaLorenz_eqFunction_17(DATA *data, threadData_t *threadData);


/*
equation index: 3
type: SIMPLE_ASSIGN
y = $START.y
*/
void SistemaLorenz_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */) = (data->modelData->realVarsData[1] /* y STATE(1) */).attribute .start;
  TRACE_POP
}
extern void SistemaLorenz_eqFunction_16(DATA *data, threadData_t *threadData);

extern void SistemaLorenz_eqFunction_14(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
z = $START.z
*/
void SistemaLorenz_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */) = (data->modelData->realVarsData[2] /* z STATE(1) */).attribute .start;
  TRACE_POP
}
extern void SistemaLorenz_eqFunction_15(DATA *data, threadData_t *threadData);

extern void SistemaLorenz_eqFunction_13(DATA *data, threadData_t *threadData);

extern void SistemaLorenz_eqFunction_12(DATA *data, threadData_t *threadData);

extern void SistemaLorenz_eqFunction_11(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void SistemaLorenz_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  SistemaLorenz_eqFunction_1(data, threadData);
  SistemaLorenz_eqFunction_17(data, threadData);
  SistemaLorenz_eqFunction_3(data, threadData);
  SistemaLorenz_eqFunction_16(data, threadData);
  SistemaLorenz_eqFunction_14(data, threadData);
  SistemaLorenz_eqFunction_6(data, threadData);
  SistemaLorenz_eqFunction_15(data, threadData);
  SistemaLorenz_eqFunction_13(data, threadData);
  SistemaLorenz_eqFunction_12(data, threadData);
  SistemaLorenz_eqFunction_11(data, threadData);
  TRACE_POP
}

int SistemaLorenz_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  SistemaLorenz_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No SistemaLorenz_functionInitialEquations_lambda0 function */

int SistemaLorenz_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

