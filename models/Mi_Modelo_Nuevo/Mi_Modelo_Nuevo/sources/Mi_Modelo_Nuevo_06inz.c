/* Initialization */
#include "Mi_Modelo_Nuevo_model.h"
#include "Mi_Modelo_Nuevo_11mix.h"
#include "Mi_Modelo_Nuevo_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void Mi_Modelo_Nuevo_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x = $START.x
*/
void Mi_Modelo_Nuevo_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */) = (data->modelData->realVarsData[0] /* x STATE(1) */).attribute .start;
  TRACE_POP
}
extern void Mi_Modelo_Nuevo_eqFunction_7(DATA *data, threadData_t *threadData);

extern void Mi_Modelo_Nuevo_eqFunction_6(DATA *data, threadData_t *threadData);

extern void Mi_Modelo_Nuevo_eqFunction_5(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void Mi_Modelo_Nuevo_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  Mi_Modelo_Nuevo_eqFunction_1(data, threadData);
  Mi_Modelo_Nuevo_eqFunction_7(data, threadData);
  Mi_Modelo_Nuevo_eqFunction_6(data, threadData);
  Mi_Modelo_Nuevo_eqFunction_5(data, threadData);
  TRACE_POP
}

int Mi_Modelo_Nuevo_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  Mi_Modelo_Nuevo_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No Mi_Modelo_Nuevo_functionInitialEquations_lambda0 function */

int Mi_Modelo_Nuevo_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

