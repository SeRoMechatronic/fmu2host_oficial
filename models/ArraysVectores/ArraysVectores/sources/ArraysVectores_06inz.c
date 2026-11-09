/* Initialization */
#include "ArraysVectores_model.h"
#include "ArraysVectores_11mix.h"
#include "ArraysVectores_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ArraysVectores_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
v_int[1] = 0.0
*/
void ArraysVectores_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* v_int[1] DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
v_int[2] = 0.0
*/
void ArraysVectores_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* v_int[2] DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
v_int[3] = 0.0
*/
void ArraysVectores_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* v_int[3] DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 4
type: SIMPLE_ASSIGN
v_int[4] = 0.0
*/
void ArraysVectores_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[4]] /* v_int[4] DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 5
type: SIMPLE_ASSIGN
v_bool[1] = false
*/
void ArraysVectores_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* v_bool[1] DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
v_bool[2] = false
*/
void ArraysVectores_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* v_bool[2] DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 7
type: SIMPLE_ASSIGN
v_bool[3] = false
*/
void ArraysVectores_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* v_bool[3] DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
v_bool[4] = false
*/
void ArraysVectores_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* v_bool[4] DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 9
type: SIMPLE_ASSIGN
v_real[1] = 0.0
*/
void ArraysVectores_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* v_real[1] variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 10
type: SIMPLE_ASSIGN
v_real[2] = 0.0
*/
void ArraysVectores_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* v_real[2] variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 11
type: SIMPLE_ASSIGN
v_real[3] = 0.0
*/
void ArraysVectores_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* v_real[3] variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 12
type: SIMPLE_ASSIGN
v_real[4] = 0.0
*/
void ArraysVectores_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* v_real[4] variable */) = 0.0;
  TRACE_POP
}
extern void ArraysVectores_eqFunction_21(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_22(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_23(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_24(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_25(DATA *data, threadData_t *threadData);


/*
equation index: 18
type: SIMPLE_ASSIGN
alguno_true = Modelica.Math.BooleanVectors.anyTrue({false, false, false, false})
*/
void ArraysVectores_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->simulationInfo->booleanParameter[1] /* alguno_true PARAM */) = omc_Modelica_Math_BooleanVectors_anyTrue(threadData, _OMC_LIT0);
  TRACE_POP
}
extern void ArraysVectores_eqFunction_20(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ArraysVectores_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ArraysVectores_eqFunction_1(data, threadData);
  ArraysVectores_eqFunction_2(data, threadData);
  ArraysVectores_eqFunction_3(data, threadData);
  ArraysVectores_eqFunction_4(data, threadData);
  ArraysVectores_eqFunction_5(data, threadData);
  ArraysVectores_eqFunction_6(data, threadData);
  ArraysVectores_eqFunction_7(data, threadData);
  ArraysVectores_eqFunction_8(data, threadData);
  ArraysVectores_eqFunction_9(data, threadData);
  ArraysVectores_eqFunction_10(data, threadData);
  ArraysVectores_eqFunction_11(data, threadData);
  ArraysVectores_eqFunction_12(data, threadData);
  ArraysVectores_eqFunction_21(data, threadData);
  ArraysVectores_eqFunction_22(data, threadData);
  ArraysVectores_eqFunction_23(data, threadData);
  ArraysVectores_eqFunction_24(data, threadData);
  ArraysVectores_eqFunction_25(data, threadData);
  ArraysVectores_eqFunction_18(data, threadData);
  ArraysVectores_eqFunction_20(data, threadData);
  TRACE_POP
}

int ArraysVectores_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ArraysVectores_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ArraysVectores_functionInitialEquations_lambda0 function */

int ArraysVectores_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

