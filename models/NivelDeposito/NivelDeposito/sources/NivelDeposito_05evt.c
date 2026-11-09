/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "NivelDeposito_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void NivelDeposito_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *NivelDeposito_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"bomba > 0.05",
  "nivel_filtrado > nivel_max",
  "nivel_filtrado < nivel_min"};
  static const int occurEqs0[] = {1,16};
  static const int occurEqs1[] = {1,15};
  static const int occurEqs2[] = {1,14};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void NivelDeposito_eqFunction_9(DATA* data, threadData_t *threadData);
extern void NivelDeposito_eqFunction_10(DATA* data, threadData_t *threadData);
extern void NivelDeposito_eqFunction_11(DATA* data, threadData_t *threadData);
extern void NivelDeposito_eqFunction_12(DATA* data, threadData_t *threadData);
extern void NivelDeposito_eqFunction_13(DATA* data, threadData_t *threadData);

int NivelDeposito_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  NivelDeposito_eqFunction_9(data, threadData);

  NivelDeposito_eqFunction_10(data, threadData);

  NivelDeposito_eqFunction_11(data, threadData);

  NivelDeposito_eqFunction_12(data, threadData);

  NivelDeposito_eqFunction_13(data, threadData);
  
  TRACE_POP
  return 0;
}

int NivelDeposito_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 0.05;
  tmp0 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* bomba variable */), 0.05, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[3] /* nivel_max PARAM */));
  tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */), (data->simulationInfo->realParameter[3] /* nivel_max PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[4] /* nivel_min PARAM */));
  tmp6 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */), (data->simulationInfo->realParameter[4] /* nivel_min PARAM */), tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *NivelDeposito_relationDescription(int i)
{
  const char *res[] = {"bomba > 0.05",
  "nivel_filtrado > nivel_max",
  "nivel_filtrado < nivel_min"};
  return res[i];
}

int NivelDeposito_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp10 = 1.0;
    tmp11 = 0.05;
    tmp9 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* bomba variable */), 0.05, tmp10, tmp11, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp9;
    current_index++;

    start_index = current_index;
    tmp13 = 1.0;
    tmp14 = fabs((data->simulationInfo->realParameter[3] /* nivel_max PARAM */));
    tmp12 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */), (data->simulationInfo->realParameter[3] /* nivel_max PARAM */), tmp13, tmp14, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp12;
    current_index++;

    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = fabs((data->simulationInfo->realParameter[4] /* nivel_min PARAM */));
    tmp15 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */), (data->simulationInfo->realParameter[4] /* nivel_min PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* bomba variable */) > 0.05);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */) > (data->simulationInfo->realParameter[3] /* nivel_max PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* nivel_filtrado STATE(1) */) < (data->simulationInfo->realParameter[4] /* nivel_min PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

