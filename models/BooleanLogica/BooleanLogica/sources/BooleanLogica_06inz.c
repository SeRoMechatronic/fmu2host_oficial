/* Initialization */
#include "BooleanLogica_model.h"
#include "BooleanLogica_11mix.h"
#include "BooleanLogica_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void BooleanLogica_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void BooleanLogica_eqFunction_21(DATA *data, threadData_t *threadData);

extern void BooleanLogica_eqFunction_20(DATA *data, threadData_t *threadData);

extern void BooleanLogica_eqFunction_19(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
$PRE.flancos = 0.0
*/
void BooleanLogica_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->simulationInfo->integerVarsPre[1] /* flancos DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 5
type: SIMPLE_ASSIGN
flancos = $PRE.flancos
*/
void BooleanLogica_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* flancos DISCRETE */) = (data->simulationInfo->integerVarsPre[1] /* flancos DISCRETE */);
  TRACE_POP
}
extern void BooleanLogica_eqFunction_18(DATA *data, threadData_t *threadData);


/*
equation index: 7
type: SIMPLE_ASSIGN
$PRE.latch = false
*/
void BooleanLogica_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->simulationInfo->booleanVarsPre[5] /* latch DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
latch = $PRE.latch
*/
void BooleanLogica_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* latch DISCRETE */) = (data->simulationInfo->booleanVarsPre[5] /* latch DISCRETE */);
  TRACE_POP
}
extern void BooleanLogica_eqFunction_16(DATA *data, threadData_t *threadData);


/*
equation index: 10
type: SIMPLE_ASSIGN
$PRE.clk = clk
*/
void BooleanLogica_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  (data->simulationInfo->booleanVarsPre[4] /* clk variable */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* clk variable */);
  TRACE_POP
}

/*
equation index: 11
type: SIMPLE_ASSIGN
$whenCondition1 = clk and not $PRE.clk
*/
void BooleanLogica_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* clk variable */) && (!(data->simulationInfo->booleanVarsPre[4] /* clk variable */)));
  TRACE_POP
}
extern void BooleanLogica_eqFunction_13(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void BooleanLogica_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  BooleanLogica_eqFunction_21(data, threadData);
  BooleanLogica_eqFunction_20(data, threadData);
  BooleanLogica_eqFunction_19(data, threadData);
  BooleanLogica_eqFunction_4(data, threadData);
  BooleanLogica_eqFunction_5(data, threadData);
  BooleanLogica_eqFunction_18(data, threadData);
  BooleanLogica_eqFunction_7(data, threadData);
  BooleanLogica_eqFunction_8(data, threadData);
  BooleanLogica_eqFunction_16(data, threadData);
  BooleanLogica_eqFunction_10(data, threadData);
  BooleanLogica_eqFunction_11(data, threadData);
  BooleanLogica_eqFunction_13(data, threadData);
  TRACE_POP
}

int BooleanLogica_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  BooleanLogica_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No BooleanLogica_functionInitialEquations_lambda0 function */

int BooleanLogica_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

