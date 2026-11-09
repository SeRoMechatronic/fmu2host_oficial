/* Initialization */
#include "MuchosEstados_model.h"
#include "MuchosEstados_11mix.h"
#include "MuchosEstados_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void MuchosEstados_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x1 = $START.x1
*/
void MuchosEstados_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */) = (data->modelData->realVarsData[0] /* x1 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_42(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_34(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
x2 = $START.x2
*/
void MuchosEstados_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */) = (data->modelData->realVarsData[1] /* x2 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_41(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_33(DATA *data, threadData_t *threadData);


/*
equation index: 7
type: SIMPLE_ASSIGN
x3 = $START.x3
*/
void MuchosEstados_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */) = (data->modelData->realVarsData[2] /* x3 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_40(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_32(DATA *data, threadData_t *threadData);


/*
equation index: 10
type: SIMPLE_ASSIGN
x4 = $START.x4
*/
void MuchosEstados_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */) = (data->modelData->realVarsData[3] /* x4 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_39(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_31(DATA *data, threadData_t *threadData);


/*
equation index: 13
type: SIMPLE_ASSIGN
x5 = $START.x5
*/
void MuchosEstados_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */) = (data->modelData->realVarsData[4] /* x5 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_38(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_30(DATA *data, threadData_t *threadData);


/*
equation index: 16
type: SIMPLE_ASSIGN
x6 = $START.x6
*/
void MuchosEstados_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */) = (data->modelData->realVarsData[5] /* x6 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_37(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_29(DATA *data, threadData_t *threadData);


/*
equation index: 19
type: SIMPLE_ASSIGN
x7 = $START.x7
*/
void MuchosEstados_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */) = (data->modelData->realVarsData[6] /* x7 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_36(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_28(DATA *data, threadData_t *threadData);


/*
equation index: 22
type: SIMPLE_ASSIGN
x8 = $START.x8
*/
void MuchosEstados_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */) = (data->modelData->realVarsData[7] /* x8 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void MuchosEstados_eqFunction_35(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_27(DATA *data, threadData_t *threadData);

extern void MuchosEstados_eqFunction_26(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void MuchosEstados_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  MuchosEstados_eqFunction_1(data, threadData);
  MuchosEstados_eqFunction_42(data, threadData);
  MuchosEstados_eqFunction_34(data, threadData);
  MuchosEstados_eqFunction_4(data, threadData);
  MuchosEstados_eqFunction_41(data, threadData);
  MuchosEstados_eqFunction_33(data, threadData);
  MuchosEstados_eqFunction_7(data, threadData);
  MuchosEstados_eqFunction_40(data, threadData);
  MuchosEstados_eqFunction_32(data, threadData);
  MuchosEstados_eqFunction_10(data, threadData);
  MuchosEstados_eqFunction_39(data, threadData);
  MuchosEstados_eqFunction_31(data, threadData);
  MuchosEstados_eqFunction_13(data, threadData);
  MuchosEstados_eqFunction_38(data, threadData);
  MuchosEstados_eqFunction_30(data, threadData);
  MuchosEstados_eqFunction_16(data, threadData);
  MuchosEstados_eqFunction_37(data, threadData);
  MuchosEstados_eqFunction_29(data, threadData);
  MuchosEstados_eqFunction_19(data, threadData);
  MuchosEstados_eqFunction_36(data, threadData);
  MuchosEstados_eqFunction_28(data, threadData);
  MuchosEstados_eqFunction_22(data, threadData);
  MuchosEstados_eqFunction_35(data, threadData);
  MuchosEstados_eqFunction_27(data, threadData);
  MuchosEstados_eqFunction_26(data, threadData);
  TRACE_POP
}

int MuchosEstados_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  MuchosEstados_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No MuchosEstados_functionInitialEquations_lambda0 function */

int MuchosEstados_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

