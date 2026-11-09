/* Initialization */
#include "FrenadoABS_model.h"
#include "FrenadoABS_11mix.h"
#include "FrenadoABS_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void FrenadoABS_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
v_filtrada = $START.v_filtrada
*/
void FrenadoABS_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */) = (data->modelData->realVarsData[4] /* v_filtrada STATE(1,dv_dt) */).attribute .start;
  TRACE_POP
}
extern void FrenadoABS_eqFunction_17(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_18(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
p_filtrada = $START.p_filtrada
*/
void FrenadoABS_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* p_filtrada STATE(1) */) = (data->modelData->realVarsData[3] /* p_filtrada STATE(1) */).attribute .start;
  TRACE_POP
}
extern void FrenadoABS_eqFunction_20(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
dv_filtrada = $START.dv_filtrada
*/
void FrenadoABS_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* dv_filtrada STATE(1) */) = (data->modelData->realVarsData[1] /* dv_filtrada STATE(1) */).attribute .start;
  TRACE_POP
}
extern void FrenadoABS_eqFunction_19(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_21(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_24(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_26(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_27(DATA *data, threadData_t *threadData);


/*
equation index: 12
type: SIMPLE_ASSIGN
oscilador = $START.oscilador
*/
void FrenadoABS_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* oscilador STATE(1) */) = (data->modelData->realVarsData[2] /* oscilador STATE(1) */).attribute .start;
  TRACE_POP
}
extern void FrenadoABS_eqFunction_23(DATA *data, threadData_t *threadData);

extern void FrenadoABS_eqFunction_25(DATA *data, threadData_t *threadData);


/*
equation index: 15
type: SIMPLE_ASSIGN
d_oscilador = $START.d_oscilador
*/
void FrenadoABS_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* d_oscilador STATE(1) */) = (data->modelData->realVarsData[0] /* d_oscilador STATE(1) */).attribute .start;
  TRACE_POP
}
extern void FrenadoABS_eqFunction_22(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void FrenadoABS_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  FrenadoABS_eqFunction_1(data, threadData);
  FrenadoABS_eqFunction_17(data, threadData);
  FrenadoABS_eqFunction_18(data, threadData);
  FrenadoABS_eqFunction_4(data, threadData);
  FrenadoABS_eqFunction_20(data, threadData);
  FrenadoABS_eqFunction_6(data, threadData);
  FrenadoABS_eqFunction_19(data, threadData);
  FrenadoABS_eqFunction_21(data, threadData);
  FrenadoABS_eqFunction_24(data, threadData);
  FrenadoABS_eqFunction_26(data, threadData);
  FrenadoABS_eqFunction_27(data, threadData);
  FrenadoABS_eqFunction_12(data, threadData);
  FrenadoABS_eqFunction_23(data, threadData);
  FrenadoABS_eqFunction_25(data, threadData);
  FrenadoABS_eqFunction_15(data, threadData);
  FrenadoABS_eqFunction_22(data, threadData);
  TRACE_POP
}

int FrenadoABS_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  FrenadoABS_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No FrenadoABS_functionInitialEquations_lambda0 function */

int FrenadoABS_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

