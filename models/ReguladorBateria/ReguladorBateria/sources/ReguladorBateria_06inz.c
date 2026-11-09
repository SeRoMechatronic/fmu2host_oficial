/* Initialization */
#include "ReguladorBateria_model.h"
#include "ReguladorBateria_11mix.h"
#include "ReguladorBateria_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ReguladorBateria_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_12(DATA *data, threadData_t *threadData);

extern void ReguladorBateria_eqFunction_13(DATA *data, threadData_t *threadData);

extern void ReguladorBateria_eqFunction_14(DATA *data, threadData_t *threadData);

extern void ReguladorBateria_eqFunction_15(DATA *data, threadData_t *threadData);


/*
equation index: 5
type: SIMPLE_ASSIGN
x1 = $START.x1
*/
void ReguladorBateria_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1,x2) */) = (data->modelData->realVarsData[0] /* x1 STATE(1,x2) */).attribute .start;
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
x2 = $START.x2
*/
void ReguladorBateria_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */) = (data->modelData->realVarsData[1] /* x2 STATE(1) */).attribute .start;
  TRACE_POP
}
extern void ReguladorBateria_eqFunction_16(DATA *data, threadData_t *threadData);

extern void ReguladorBateria_eqFunction_17(DATA *data, threadData_t *threadData);


/*
equation index: 9
type: SIMPLE_ASSIGN
corriente_carga = min(I_max, max(0.0, corriente_raw))
*/
void ReguladorBateria_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* corriente_carga variable */) = fmin((data->simulationInfo->realParameter[0] /* I_max PARAM */),fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* corriente_raw variable */)));
  TRACE_POP
}
extern void ReguladorBateria_eqFunction_20(DATA *data, threadData_t *threadData);

extern void ReguladorBateria_eqFunction_21(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ReguladorBateria_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ReguladorBateria_eqFunction_12(data, threadData);
  ReguladorBateria_eqFunction_13(data, threadData);
  ReguladorBateria_eqFunction_14(data, threadData);
  ReguladorBateria_eqFunction_15(data, threadData);
  ReguladorBateria_eqFunction_5(data, threadData);
  ReguladorBateria_eqFunction_6(data, threadData);
  ReguladorBateria_eqFunction_16(data, threadData);
  ReguladorBateria_eqFunction_17(data, threadData);
  ReguladorBateria_eqFunction_9(data, threadData);
  ReguladorBateria_eqFunction_20(data, threadData);
  ReguladorBateria_eqFunction_21(data, threadData);
  TRACE_POP
}

int ReguladorBateria_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ReguladorBateria_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ReguladorBateria_functionInitialEquations_lambda0 function */

int ReguladorBateria_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

