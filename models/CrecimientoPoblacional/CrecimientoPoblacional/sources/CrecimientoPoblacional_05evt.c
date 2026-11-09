/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "CrecimientoPoblacional_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void CrecimientoPoblacional_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *CrecimientoPoblacional_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"N > K"};
  static const int occurEqs0[] = {1,7};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void CrecimientoPoblacional_eqFunction_8(DATA* data, threadData_t *threadData);
extern void CrecimientoPoblacional_eqFunction_9(DATA* data, threadData_t *threadData);
extern void CrecimientoPoblacional_eqFunction_10(DATA* data, threadData_t *threadData);

int CrecimientoPoblacional_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  CrecimientoPoblacional_eqFunction_8(data, threadData);

  CrecimientoPoblacional_eqFunction_9(data, threadData);

  CrecimientoPoblacional_eqFunction_10(data, threadData);
  
  TRACE_POP
  return 0;
}

int CrecimientoPoblacional_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[0] /* K PARAM */));
  tmp0 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* N STATE(1) */), (data->simulationInfo->realParameter[0] /* K PARAM */), tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *CrecimientoPoblacional_relationDescription(int i)
{
  const char *res[] = {"N > K"};
  return res[i];
}

int CrecimientoPoblacional_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp4 = 1.0;
    tmp5 = fabs((data->simulationInfo->realParameter[0] /* K PARAM */));
    tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* N STATE(1) */), (data->simulationInfo->realParameter[0] /* K PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp3;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* N STATE(1) */) > (data->simulationInfo->realParameter[0] /* K PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

