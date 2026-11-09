/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "ValoresExtremos_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void ValoresExtremos_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *ValoresExtremos_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"abs(u) < 1e29",
  "u > 1e-10",
  "u >= 0.0",
  "abs(u) > 1e-10"};
  static const int occurEqs0[] = {1,6};
  static const int occurEqs1[] = {1,6};
  static const int occurEqs2[] = {1,6};
  static const int occurEqs3[] = {1,6};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int ValoresExtremos_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int ValoresExtremos_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 1e29;
  tmp0 = LessZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e29, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 1e-10;
  tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 1e-10, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 0.0;
  tmp6 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 0.0, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = 1e-10;
  tmp9 = GreaterZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e-10, tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *ValoresExtremos_relationDescription(int i)
{
  const char *res[] = {"abs(u) < 1e29",
  "u > 1e-10",
  "u >= 0.0",
  "abs(u) > 1e-10"};
  return res[i];
}

int ValoresExtremos_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_boolean tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp13 = 1.0;
    tmp14 = 1e29;
    tmp12 = LessZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e29, tmp13, tmp14, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp12;
    current_index++;

    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = 1e-10;
    tmp15 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 1e-10, tmp16, tmp17, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;

    start_index = current_index;
    tmp19 = 1.0;
    tmp20 = 0.0;
    tmp18 = GreaterEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 0.0, tmp19, tmp20, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp18;
    current_index++;

    start_index = current_index;
    tmp22 = 1.0;
    tmp23 = 1e-10;
    tmp21 = GreaterZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e-10, tmp22, tmp23, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp21;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = (fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)) < 1e29);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */) > 1e-10);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */) >= 0.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)) > 1e-10);
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

