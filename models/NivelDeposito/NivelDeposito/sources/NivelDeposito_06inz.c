/* Initialization */
#include "NivelDeposito_model.h"
#include "NivelDeposito_11mix.h"
#include "NivelDeposito_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void NivelDeposito_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void NivelDeposito_eqFunction_11(DATA *data, threadData_t *threadData);


/*
equation index: 2
type: SIMPLE_ASSIGN
nivel_filtrado = $START.nivel_filtrado
*/
void NivelDeposito_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */) = (data->modelData->realVarsData[0] /* nivel_filtrado STATE(1) */).attribute .start;
  TRACE_POP
}
extern void NivelDeposito_eqFunction_9(DATA *data, threadData_t *threadData);

extern void NivelDeposito_eqFunction_10(DATA *data, threadData_t *threadData);


/*
equation index: 5
type: SIMPLE_ASSIGN
bomba = min(1.0, max(0.0, 0.5 + 2.0 * error_nivel - Q_salida / Q_bomba_max))
*/
void NivelDeposito_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* bomba variable */) = fmin(1.0,fmax(0.0,0.5 + (2.0) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* error_nivel variable */)) - (DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* Q_salida variable */),(data->simulationInfo->realParameter[0] /* Q_bomba_max PARAM */),"Q_bomba_max",equationIndexes))));
  TRACE_POP
}
extern void NivelDeposito_eqFunction_16(DATA *data, threadData_t *threadData);

extern void NivelDeposito_eqFunction_14(DATA *data, threadData_t *threadData);

extern void NivelDeposito_eqFunction_15(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void NivelDeposito_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  NivelDeposito_eqFunction_11(data, threadData);
  NivelDeposito_eqFunction_2(data, threadData);
  NivelDeposito_eqFunction_9(data, threadData);
  NivelDeposito_eqFunction_10(data, threadData);
  NivelDeposito_eqFunction_5(data, threadData);
  NivelDeposito_eqFunction_16(data, threadData);
  NivelDeposito_eqFunction_14(data, threadData);
  NivelDeposito_eqFunction_15(data, threadData);
  TRACE_POP
}

int NivelDeposito_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  NivelDeposito_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No NivelDeposito_functionInitialEquations_lambda0 function */

int NivelDeposito_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

