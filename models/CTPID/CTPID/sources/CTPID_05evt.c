/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "CTPID_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void CTPID_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *CTPID_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"consigna_real > temperatura_real + epsilon",
  "consigna_real < temperatura_real - epsilon",
  "abs(error) <= epsilon"};
  static const int occurEqs0[] = {1,27};
  static const int occurEqs1[] = {1,28};
  static const int occurEqs2[] = {1,26};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void CTPID_eqFunction_19(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_20(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_21(DATA* data, threadData_t *threadData);

int CTPID_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  CTPID_eqFunction_19(data, threadData);

  CTPID_eqFunction_20(data, threadData);

  CTPID_eqFunction_21(data, threadData);
  
  TRACE_POP
  return 0;
}

int CTPID_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  tmp2 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  tmp0 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) + (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  tmp3 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) - (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  tmp6 = LessEqZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)), (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *CTPID_relationDescription(int i)
{
  const char *res[] = {"consigna_real > temperatura_real + epsilon",
  "consigna_real < temperatura_real - epsilon",
  "abs(error) <= epsilon"};
  return res[i];
}

int CTPID_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
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
    tmp11 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    tmp9 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) + (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp10, tmp11, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp9;
    current_index++;

    start_index = current_index;
    tmp13 = 1.0;
    tmp14 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    tmp12 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) - (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp13, tmp14, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp12;
    current_index++;

    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    tmp15 = LessEqZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)), (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) + (data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) - (data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)) <= (data->simulationInfo->realParameter[5] /* epsilon PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

