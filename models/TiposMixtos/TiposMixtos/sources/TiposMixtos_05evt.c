/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "TiposMixtos_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void TiposMixtos_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *TiposMixtos_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"not b_in"};
  static const int occurEqs0[] = {1,5};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int TiposMixtos_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int TiposMixtos_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  gout[start_index] = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* b_in variable */))) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *TiposMixtos_relationDescription(int i)
{
  return "empty";
}

int TiposMixtos_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
  } else {
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

