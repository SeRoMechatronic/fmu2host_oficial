/* Initialization */
#include "PenduloNoLineal_model.h"
#include "PenduloNoLineal_11mix.h"
#include "PenduloNoLineal_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void PenduloNoLineal_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
theta = $START.theta
*/
void PenduloNoLineal_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* theta STATE(1,omega_p) */) = (data->modelData->realVarsData[1] /* theta STATE(1,omega_p) */).attribute .start;
  TRACE_POP
}
extern void PenduloNoLineal_eqFunction_12(DATA *data, threadData_t *threadData);


/*
equation index: 3
type: SIMPLE_ASSIGN
$DER.omega_p = (-sin(theta)) * g / L
*/
void PenduloNoLineal_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* der(omega_p) STATE_DER */) = ((-sin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* theta STATE(1,omega_p) */)))) * (DIVISION_SIM((data->simulationInfo->realParameter[1] /* g PARAM */),(data->simulationInfo->realParameter[0] /* L PARAM */),"L",equationIndexes));
  TRACE_POP
}

/*
equation index: 4
type: SIMPLE_ASSIGN
omega_p = $START.omega_p
*/
void PenduloNoLineal_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* omega_p STATE(1) */) = (data->modelData->realVarsData[0] /* omega_p STATE(1) */).attribute .start;
  TRACE_POP
}
extern void PenduloNoLineal_eqFunction_11(DATA *data, threadData_t *threadData);

extern void PenduloNoLineal_eqFunction_10(DATA *data, threadData_t *threadData);


/*
equation index: 7
type: SIMPLE_ASSIGN
energia_total = 0.5 * (L * omega_p) ^ 2.0 - g * L * cos(theta)
*/
void PenduloNoLineal_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  modelica_real tmp0;
  tmp0 = ((data->simulationInfo->realParameter[0] /* L PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* omega_p STATE(1) */));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* energia_total variable */) = (0.5) * ((tmp0 * tmp0)) - (((data->simulationInfo->realParameter[1] /* g PARAM */)) * (((data->simulationInfo->realParameter[0] /* L PARAM */)) * (cos((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* theta STATE(1,omega_p) */)))));
  TRACE_POP
}
extern void PenduloNoLineal_eqFunction_9(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void PenduloNoLineal_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  PenduloNoLineal_eqFunction_1(data, threadData);
  PenduloNoLineal_eqFunction_12(data, threadData);
  PenduloNoLineal_eqFunction_3(data, threadData);
  PenduloNoLineal_eqFunction_4(data, threadData);
  PenduloNoLineal_eqFunction_11(data, threadData);
  PenduloNoLineal_eqFunction_10(data, threadData);
  PenduloNoLineal_eqFunction_7(data, threadData);
  PenduloNoLineal_eqFunction_9(data, threadData);
  TRACE_POP
}

int PenduloNoLineal_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  PenduloNoLineal_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No PenduloNoLineal_functionInitialEquations_lambda0 function */

int PenduloNoLineal_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

