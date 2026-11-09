/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "SelectorModo_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void SelectorModo_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *SelectorModo_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"modo_operacion < MODO_MANUAL or modo_operacion > MODO_EMERGENCIA",
  "modo_operacion == MODO_EMERGENCIA",
  "modo_operacion == MODO_AUTO",
  "modo_operacion == MODO_MANUAL"};
  static const int occurEqs0[] = {1,4};
  static const int occurEqs1[] = {1,4};
  static const int occurEqs2[] = {1,4};
  static const int occurEqs3[] = {1,4};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int SelectorModo_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int SelectorModo_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp0 = Less((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */),(data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */));
  tmp1 = Greater((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */),(data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */));
  gout[start_index] = ((tmp0 || tmp1)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[0] /* MODO_AUTO PARAM */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */))) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *SelectorModo_relationDescription(int i)
{
  const char *res[] = {"modo_operacion < MODO_MANUAL",
  "modo_operacion > MODO_EMERGENCIA",
  "modo_operacion == MODO_EMERGENCIA",
  "modo_operacion == MODO_AUTO",
  "modo_operacion == MODO_MANUAL"};
  return res[i];
}

int SelectorModo_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp2;
  modelica_boolean tmp3;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp2 = Less((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */),(data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */));
    data->simulationInfo->relations[start_index] = tmp2;
    current_index++;

    start_index = current_index;
    tmp3 = Greater((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */),(data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */));
    data->simulationInfo->relations[start_index] = tmp3;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[0] /* MODO_AUTO PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */));
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) < (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) > (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[0] /* MODO_AUTO PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

