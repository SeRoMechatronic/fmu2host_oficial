/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "testROMAN_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void testROMAN_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *testROMAN_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"pot >= 0.95",
  "pot >= 0.8",
  "pot >= 0.6",
  "pot >= 0.4",
  "pot >= 0.2"};
  static const int occurEqs0[] = {1,6};
  static const int occurEqs1[] = {1,6};
  static const int occurEqs2[] = {1,6};
  static const int occurEqs3[] = {1,6};
  static const int occurEqs4[] = {1,6};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3,occurEqs4};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int testROMAN_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int testROMAN_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 0.95;
  tmp0 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.95, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 0.8;
  tmp3 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.8, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 0.6;
  tmp6 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.6, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = 0.4;
  tmp9 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.4, tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp13 = 1.0;
  tmp14 = 0.2;
  tmp12 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.2, tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  gout[start_index] = (tmp12) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *testROMAN_relationDescription(int i)
{
  const char *res[] = {"pot >= 0.95",
  "pot >= 0.8",
  "pot >= 0.6",
  "pot >= 0.4",
  "pot >= 0.2"};
  return res[i];
}

int testROMAN_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_boolean tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  modelica_boolean tmp24;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_boolean tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = 0.95;
    tmp15 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.95, tmp16, tmp17, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;

    start_index = current_index;
    tmp19 = 1.0;
    tmp20 = 0.8;
    tmp18 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.8, tmp19, tmp20, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp18;
    current_index++;

    start_index = current_index;
    tmp22 = 1.0;
    tmp23 = 0.6;
    tmp21 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.6, tmp22, tmp23, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp21;
    current_index++;

    start_index = current_index;
    tmp25 = 1.0;
    tmp26 = 0.4;
    tmp24 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.4, tmp25, tmp26, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp24;
    current_index++;

    start_index = current_index;
    tmp28 = 1.0;
    tmp29 = 0.2;
    tmp27 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.2, tmp28, tmp29, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[start_index] = tmp27;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) >= 0.95);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) >= 0.8);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) >= 0.6);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) >= 0.4);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) >= 0.2);
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

