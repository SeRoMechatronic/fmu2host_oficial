/* Initialization */
#include "EtapaSecuenciador_model.h"
#include "EtapaSecuenciador_11mix.h"
#include "EtapaSecuenciador_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void EtapaSecuenciador_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
$PRE.etapa = $START.etapa
*/
void EtapaSecuenciador_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */) = (data->modelData->integerVarsData[0] /* etapa DISCRETE */).attribute .start;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
etapa = $PRE.etapa
*/
void EtapaSecuenciador_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* etapa DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */);
  TRACE_POP
}
extern void EtapaSecuenciador_eqFunction_23(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
$PRE.etapa_ant = $START.etapa_ant
*/
void EtapaSecuenciador_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->simulationInfo->integerVarsPre[2] /* etapa_ant DISCRETE */) = (data->modelData->integerVarsData[2] /* etapa_ant DISCRETE */).attribute .start;
  TRACE_POP
}

/*
equation index: 5
type: SIMPLE_ASSIGN
etapa_ant = $PRE.etapa_ant
*/
void EtapaSecuenciador_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* etapa_ant DISCRETE */) = (data->simulationInfo->integerVarsPre[2] /* etapa_ant DISCRETE */);
  TRACE_POP
}
extern void EtapaSecuenciador_eqFunction_22(DATA *data, threadData_t *threadData);


/*
equation index: 7
type: SIMPLE_ASSIGN
secuencia_completa = $PRE.etapa == 0 and $PRE.etapa_ant == N_ETAPAS
*/
void EtapaSecuenciador_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* secuencia_completa DISCRETE */) = (((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */) == ((modelica_integer) 0)) && ((data->simulationInfo->integerVarsPre[2] /* etapa_ant DISCRETE */) == (data->simulationInfo->integerParameter[0] /* N_ETAPAS PARAM */)));
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
$PRE.tiempo_en_etapa = $START.tiempo_en_etapa
*/
void EtapaSecuenciador_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */) = (data->modelData->realVarsData[4] /* tiempo_en_etapa DISCRETE */).attribute .start;
  TRACE_POP
}

/*
equation index: 9
type: SIMPLE_ASSIGN
tiempo_en_etapa = $PRE.tiempo_en_etapa
*/
void EtapaSecuenciador_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* tiempo_en_etapa DISCRETE */) = (data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */);
  TRACE_POP
}

/*
equation index: 10
type: SIMPLE_ASSIGN
progreso_etapa = if $PRE.etapa > 0 then min(1.0, $PRE.tiempo_en_etapa / duracion_etapa) else 0.0
*/
void EtapaSecuenciador_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp0;
  tmp0 = Greater((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),((modelica_integer) 0));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* progreso_etapa variable */) = (tmp0?fmin(1.0,DIVISION_SIM((data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */),(data->simulationInfo->realParameter[1] /* duracion_etapa PARAM */),"duracion_etapa",equationIndexes)):0.0);
  TRACE_POP
}

/*
equation index: 11
type: SIMPLE_ASSIGN
$PRE.sensor_s = $START.sensor_s
*/
void EtapaSecuenciador_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->simulationInfo->realVarsPre[2] /* sensor_s DISCRETE */) = (data->modelData->realVarsData[2] /* sensor_s DISCRETE */).attribute .start;
  TRACE_POP
}

/*
equation index: 12
type: SIMPLE_ASSIGN
sensor_s = $PRE.sensor_s
*/
void EtapaSecuenciador_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* sensor_s DISCRETE */) = (data->simulationInfo->realVarsPre[2] /* sensor_s DISCRETE */);
  TRACE_POP
}

/*
equation index: 13
type: SIMPLE_ASSIGN
$PRE.arrancar = arrancar
*/
void EtapaSecuenciador_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->simulationInfo->booleanVarsPre[4] /* arrancar variable */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* arrancar variable */);
  TRACE_POP
}

/*
equation index: 14
type: SIMPLE_ASSIGN
$PRE.parar = parar
*/
void EtapaSecuenciador_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->simulationInfo->booleanVarsPre[5] /* parar variable */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* parar variable */);
  TRACE_POP
}

/*
equation index: 15
type: ALGORITHM

  $whenCondition4 := $START.$whenCondition4;
  $whenCondition3 := $START.$whenCondition3;
  $whenCondition2 := $START.$whenCondition2;
  $whenCondition2 := parar and not $PRE.parar;
  $whenCondition3 := arrancar and not $PRE.arrancar;
  $whenCondition4 := $PRE.tiempo_en_etapa >= duracion_etapa and $PRE.sensor_s > 0.5 and $PRE.etapa > 0;
*/
void EtapaSecuenciador_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition4 DISCRETE */) = (data->modelData->booleanVarsData[3] /* $whenCondition4 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition3 DISCRETE */) = (data->modelData->booleanVarsData[2] /* $whenCondition3 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) = (data->modelData->booleanVarsData[1] /* $whenCondition2 DISCRETE */).attribute .start;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* parar variable */) && (!(data->simulationInfo->booleanVarsPre[5] /* parar variable */)));

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition3 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* arrancar variable */) && (!(data->simulationInfo->booleanVarsPre[4] /* arrancar variable */)));

  tmp1 = GreaterEq((data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */),(data->simulationInfo->realParameter[1] /* duracion_etapa PARAM */));
  tmp2 = Greater((data->simulationInfo->realVarsPre[2] /* sensor_s DISCRETE */),0.5);
  tmp3 = Greater((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),((modelica_integer) 0));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition4 DISCRETE */) = ((tmp1 && tmp2) && tmp3);
  TRACE_POP
}

/*
equation index: 16
type: SIMPLE_ASSIGN
$whenCondition1 = false
*/
void EtapaSecuenciador_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 17
type: SIMPLE_ASSIGN
$PRE.t_inicio = $START.t_inicio
*/
void EtapaSecuenciador_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->simulationInfo->realVarsPre[3] /* t_inicio DISCRETE */) = (data->modelData->realVarsData[3] /* t_inicio DISCRETE */).attribute .start;
  TRACE_POP
}

/*
equation index: 18
type: SIMPLE_ASSIGN
t_inicio = $PRE.t_inicio
*/
void EtapaSecuenciador_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* t_inicio DISCRETE */) = (data->simulationInfo->realVarsPre[3] /* t_inicio DISCRETE */);
  TRACE_POP
}
OMC_DISABLE_OPT
void EtapaSecuenciador_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  EtapaSecuenciador_eqFunction_1(data, threadData);
  EtapaSecuenciador_eqFunction_2(data, threadData);
  EtapaSecuenciador_eqFunction_23(data, threadData);
  EtapaSecuenciador_eqFunction_4(data, threadData);
  EtapaSecuenciador_eqFunction_5(data, threadData);
  EtapaSecuenciador_eqFunction_22(data, threadData);
  EtapaSecuenciador_eqFunction_7(data, threadData);
  EtapaSecuenciador_eqFunction_8(data, threadData);
  EtapaSecuenciador_eqFunction_9(data, threadData);
  EtapaSecuenciador_eqFunction_10(data, threadData);
  EtapaSecuenciador_eqFunction_11(data, threadData);
  EtapaSecuenciador_eqFunction_12(data, threadData);
  EtapaSecuenciador_eqFunction_13(data, threadData);
  EtapaSecuenciador_eqFunction_14(data, threadData);
  EtapaSecuenciador_eqFunction_15(data, threadData);
  EtapaSecuenciador_eqFunction_16(data, threadData);
  EtapaSecuenciador_eqFunction_17(data, threadData);
  EtapaSecuenciador_eqFunction_18(data, threadData);
  TRACE_POP
}

int EtapaSecuenciador_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  EtapaSecuenciador_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No EtapaSecuenciador_functionInitialEquations_lambda0 function */

int EtapaSecuenciador_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

