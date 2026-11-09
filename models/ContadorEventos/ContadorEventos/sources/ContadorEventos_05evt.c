/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "ContadorEventos_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void ContadorEventos_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *ContadorEventos_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"mod(contador, 10, 0)",
  "div(contador, 10, 3)"};
  static const int occurEqs0[] = {1,14};
  static const int occurEqs1[] = {1,15};
  static const int *occurEqs[] = {occurEqs0,occurEqs1};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void ContadorEventos_eqFunction_10(DATA* data, threadData_t *threadData);
extern void ContadorEventos_eqFunction_11(DATA* data, threadData_t *threadData);

int ContadorEventos_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  ContadorEventos_eqFunction_10(data, threadData);

  ContadorEventos_eqFunction_11(data, threadData);
  
  TRACE_POP
  return 0;
}

int ContadorEventos_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_real tmp0;
  modelica_real tmp1;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp0 = floor(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */)) / (((modelica_integer) 10)));
  tmp1 = floor((data->simulationInfo->mathEventsValuePre[((modelica_integer) 0)]) / (data->simulationInfo->mathEventsValuePre[((modelica_integer) 0)+1]));
  gout[start_index] = tmp0 != tmp1 ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (trunc(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */))/(((modelica_integer) 10))) != trunc(data->simulationInfo->mathEventsValuePre[((modelica_integer) 3)]/data->simulationInfo->mathEventsValuePre[((modelica_integer) 3)+1])) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *ContadorEventos_relationDescription(int i)
{
  return "empty";
}

int ContadorEventos_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
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

