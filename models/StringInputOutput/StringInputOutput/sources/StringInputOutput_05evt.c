/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "StringInputOutput_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void StringInputOutput_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *StringInputOutput_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"value > 100.0",
  "value < 10.0"};
  static const int occurEqs0[] = {1,5};
  static const int occurEqs1[] = {1,5};
  static const int *occurEqs[] = {occurEqs0,occurEqs1};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int StringInputOutput_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int StringInputOutput_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 100.0;
  tmp0 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */), 100.0, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 10.0;
  tmp3 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */), 10.0, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *StringInputOutput_relationDescription(int i)
{
  const char *res[] = {"value > 100.0",
  "value < 10.0"};
  return res[i];
}

int StringInputOutput_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp7 = 1.0;
    tmp8 = 100.0;
    tmp6 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */), 100.0, tmp7, tmp8, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp6;
    current_index++;

    start_index = current_index;
    tmp10 = 1.0;
    tmp11 = 10.0;
    tmp9 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */), 10.0, tmp10, tmp11, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp9;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */) > 100.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* value variable */) < 10.0);
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

