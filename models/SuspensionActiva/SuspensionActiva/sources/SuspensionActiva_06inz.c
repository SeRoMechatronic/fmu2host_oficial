/* Initialization */
#include "SuspensionActiva_model.h"
#include "SuspensionActiva_11mix.h"
#include "SuspensionActiva_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void SuspensionActiva_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
posicion_filtrada = $START.posicion_filtrada
*/
void SuspensionActiva_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* posicion_filtrada STATE(1) */) = (data->modelData->realVarsData[0] /* posicion_filtrada STATE(1) */).attribute .start;
  TRACE_POP
}
extern void SuspensionActiva_eqFunction_10(DATA *data, threadData_t *threadData);

extern void SuspensionActiva_eqFunction_15(DATA *data, threadData_t *threadData);

extern void SuspensionActiva_eqFunction_17(DATA *data, threadData_t *threadData);


/*
equation index: 5
type: SIMPLE_ASSIGN
velocidad_filtrada = $START.velocidad_filtrada
*/
void SuspensionActiva_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* velocidad_filtrada STATE(1) */) = (data->modelData->realVarsData[1] /* velocidad_filtrada STATE(1) */).attribute .start;
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
$DER.velocidad_filtrada = ($DER.posicion_filtrada - velocidad_filtrada) / tau_filtro
*/
void SuspensionActiva_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(velocidad_filtrada) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* der(posicion_filtrada) STATE_DER */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* velocidad_filtrada STATE(1) */),(data->simulationInfo->realParameter[3] /* tau_filtro PARAM */),"tau_filtro",equationIndexes);
  TRACE_POP
}
extern void SuspensionActiva_eqFunction_12(DATA *data, threadData_t *threadData);


/*
equation index: 8
type: SIMPLE_ASSIGN
fuerza_actuador = min(sat_actuador, max(-sat_actuador, fuerza_raw))
*/
void SuspensionActiva_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* fuerza_actuador variable */) = fmin((data->simulationInfo->realParameter[2] /* sat_actuador PARAM */),fmax((-(data->simulationInfo->realParameter[2] /* sat_actuador PARAM */)),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* fuerza_raw variable */)));
  TRACE_POP
}
extern void SuspensionActiva_eqFunction_16(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void SuspensionActiva_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  SuspensionActiva_eqFunction_1(data, threadData);
  SuspensionActiva_eqFunction_10(data, threadData);
  SuspensionActiva_eqFunction_15(data, threadData);
  SuspensionActiva_eqFunction_17(data, threadData);
  SuspensionActiva_eqFunction_5(data, threadData);
  SuspensionActiva_eqFunction_6(data, threadData);
  SuspensionActiva_eqFunction_12(data, threadData);
  SuspensionActiva_eqFunction_8(data, threadData);
  SuspensionActiva_eqFunction_16(data, threadData);
  TRACE_POP
}

int SuspensionActiva_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  SuspensionActiva_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No SuspensionActiva_functionInitialEquations_lambda0 function */

int SuspensionActiva_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

