/* Initialization */
#include "ArranqueSuaveMotor_model.h"
#include "ArranqueSuaveMotor_11mix.h"
#include "ArranqueSuaveMotor_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ArranqueSuaveMotor_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_14(DATA *data, threadData_t *threadData);


/*
equation index: 2
type: SIMPLE_ASSIGN
rampa = $START.rampa
*/
void ArranqueSuaveMotor_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* rampa STATE(1) */) = (data->modelData->realVarsData[0] /* rampa STATE(1) */).attribute .start;
  TRACE_POP
}
extern void ArranqueSuaveMotor_eqFunction_15(DATA *data, threadData_t *threadData);


/*
equation index: 4
type: SIMPLE_ASSIGN
tension_filtrada = $START.tension_filtrada
*/
void ArranqueSuaveMotor_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */) = (data->modelData->realVarsData[1] /* tension_filtrada STATE(1) */).attribute .start;
  TRACE_POP
}
extern void ArranqueSuaveMotor_eqFunction_16(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
tension_aplicada = min(1.0, max(0.0, tension_filtrada))
*/
void ArranqueSuaveMotor_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_aplicada variable */) = fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */)));
  TRACE_POP
}
extern void ArranqueSuaveMotor_eqFunction_18(DATA *data, threadData_t *threadData);


/*
equation index: 8
type: SIMPLE_ASSIGN
tiempo_sobrecarga = $START.tiempo_sobrecarga
*/
void ArranqueSuaveMotor_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */) = (data->modelData->realVarsData[2] /* tiempo_sobrecarga STATE(1) */).attribute .start;
  TRACE_POP
}
extern void ArranqueSuaveMotor_eqFunction_17(DATA *data, threadData_t *threadData);

extern void ArranqueSuaveMotor_eqFunction_19(DATA *data, threadData_t *threadData);

extern void ArranqueSuaveMotor_eqFunction_20(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void ArranqueSuaveMotor_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ArranqueSuaveMotor_eqFunction_14(data, threadData);
  ArranqueSuaveMotor_eqFunction_2(data, threadData);
  ArranqueSuaveMotor_eqFunction_15(data, threadData);
  ArranqueSuaveMotor_eqFunction_4(data, threadData);
  ArranqueSuaveMotor_eqFunction_16(data, threadData);
  ArranqueSuaveMotor_eqFunction_6(data, threadData);
  ArranqueSuaveMotor_eqFunction_18(data, threadData);
  ArranqueSuaveMotor_eqFunction_8(data, threadData);
  ArranqueSuaveMotor_eqFunction_17(data, threadData);
  ArranqueSuaveMotor_eqFunction_19(data, threadData);
  ArranqueSuaveMotor_eqFunction_20(data, threadData);
  TRACE_POP
}

int ArranqueSuaveMotor_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ArranqueSuaveMotor_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No ArranqueSuaveMotor_functionInitialEquations_lambda0 function */

int ArranqueSuaveMotor_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

