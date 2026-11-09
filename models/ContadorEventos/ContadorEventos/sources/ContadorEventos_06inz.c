/* Initialization */
#include "ContadorEventos_model.h"
#include "ContadorEventos_11mix.h"
#include "ContadorEventos_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ContadorEventos_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
$PRE.contador = 0.0
*/
void ContadorEventos_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->simulationInfo->integerVarsPre[0] /* contador DISCRETE */) = 0.0;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
contador = $PRE.contador
*/
void ContadorEventos_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* contador DISCRETE */);
  TRACE_POP
}
extern void ContadorEventos_eqFunction_16(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
decenas = div(contador, 10)
*/
void ContadorEventos_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  modelica_integer tmp0;
  tmp0 = ((modelica_integer) 10);
  if (tmp0 == 0) {throwStreamPrint(threadData, "Division by zero %s", "div(contador, 10)");}
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* decenas DISCRETE */) = modelica_div_integer((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */),tmp0).quot;
  TRACE_POP
}

/*
equation index: 5
type: SIMPLE_ASSIGN
unidades = mod(contador, 10)
*/
void ContadorEventos_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  modelica_integer tmp1;
  tmp1 = ((modelica_integer) 10);
  if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s", "mod(contador, 10)");}
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* unidades DISCRETE */) = modelica_integer_mod((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */), tmp1);
  TRACE_POP
}
extern void ContadorEventos_eqFunction_13(DATA *data, threadData_t *threadData);


/*
equation index: 7
type: SIMPLE_ASSIGN
$PRE.evento = evento
*/
void ContadorEventos_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->simulationInfo->booleanVarsPre[3] /* evento variable */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* evento variable */);
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
$whenCondition1 = evento and not $PRE.evento
*/
void ContadorEventos_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* evento variable */) && (!(data->simulationInfo->booleanVarsPre[3] /* evento variable */)));
  TRACE_POP
}
extern void ContadorEventos_eqFunction_11(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ContadorEventos_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ContadorEventos_eqFunction_1(data, threadData);
  ContadorEventos_eqFunction_2(data, threadData);
  ContadorEventos_eqFunction_16(data, threadData);
  ContadorEventos_eqFunction_4(data, threadData);
  ContadorEventos_eqFunction_5(data, threadData);
  ContadorEventos_eqFunction_13(data, threadData);
  ContadorEventos_eqFunction_7(data, threadData);
  ContadorEventos_eqFunction_8(data, threadData);
  ContadorEventos_eqFunction_11(data, threadData);
  TRACE_POP
}

int ContadorEventos_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ContadorEventos_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ContadorEventos_functionInitialEquations_lambda0 function */

int ContadorEventos_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

