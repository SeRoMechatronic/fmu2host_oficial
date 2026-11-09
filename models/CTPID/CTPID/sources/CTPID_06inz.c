/* Initialization */
#include "CTPID_model.h"
#include "CTPID_11mix.h"
#include "CTPID_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void CTPID_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void CTPID_eqFunction_16(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_15(DATA *data, threadData_t *threadData);


/*
equation index: 3
type: SIMPLE_ASSIGN
derivador = $DER.consigna_real - $DER.temperatura_real
*/
void CTPID_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* derivador variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* der(consigna_real) DUMMY_DER */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(temperatura_real) DUMMY_DER */);
  TRACE_POP
}

/*
equation index: 4
type: SIMPLE_ASSIGN
$DER.error = derivador
*/
void CTPID_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(error) DUMMY_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* derivador variable */);
  TRACE_POP
}
extern void CTPID_eqFunction_19(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_20(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_27(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_28(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_21(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_22(DATA *data, threadData_t *threadData);

extern void CTPID_eqFunction_26(DATA *data, threadData_t *threadData);


/*
equation index: 12
type: SIMPLE_ASSIGN
integrador = $START.integrador
*/
void CTPID_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* integrador STATE(1,error) */) = (data->modelData->realVarsData[0] /* integrador STATE(1,error) */).attribute .start;
  TRACE_POP
}

/*
equation index: 13
type: SIMPLE_ASSIGN
pid_raw = Kp * error + Ki * integrador + Kd * derivador
*/
void CTPID_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pid_raw variable */) = ((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* integrador STATE(1,error) */)) + ((data->simulationInfo->realParameter[0] /* Kd PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* derivador variable */));
  TRACE_POP
}

/*
equation index: 14
type: SIMPLE_ASSIGN
ventilador = min(1.0, max(0.0, pid_raw / (T_max - T_min)))
*/
void CTPID_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* ventilador variable */) = fmin(1.0,fmax(0.0,DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pid_raw variable */),(data->simulationInfo->realParameter[3] /* T_max PARAM */) - (data->simulationInfo->realParameter[4] /* T_min PARAM */),"T_max - T_min",equationIndexes)));
  TRACE_POP
}
OMC_DISABLE_OPT
void CTPID_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  CTPID_eqFunction_16(data, threadData);
  CTPID_eqFunction_15(data, threadData);
  CTPID_eqFunction_3(data, threadData);
  CTPID_eqFunction_4(data, threadData);
  CTPID_eqFunction_19(data, threadData);
  CTPID_eqFunction_20(data, threadData);
  CTPID_eqFunction_27(data, threadData);
  CTPID_eqFunction_28(data, threadData);
  CTPID_eqFunction_21(data, threadData);
  CTPID_eqFunction_22(data, threadData);
  CTPID_eqFunction_26(data, threadData);
  CTPID_eqFunction_12(data, threadData);
  CTPID_eqFunction_13(data, threadData);
  CTPID_eqFunction_14(data, threadData);
  TRACE_POP
}

int CTPID_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  CTPID_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No CTPID_functionInitialEquations_lambda0 function */

int CTPID_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

