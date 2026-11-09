/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "FrenadoABS_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void FrenadoABS_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *FrenadoABS_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"lambda <= lambda_umbral and presion_pedal > 0.05",
  "lambda > 0.9",
  "lambda > lambda_umbral",
  "v_filtrada > 0.01"};
  static const int occurEqs0[] = {1,27};
  static const int occurEqs1[] = {1,26};
  static const int occurEqs2[] = {1,24};
  static const int occurEqs3[] = {1,21};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void FrenadoABS_eqFunction_17(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_18(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_19(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_21(DATA* data, threadData_t *threadData);

int FrenadoABS_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  FrenadoABS_eqFunction_17(data, threadData);

  FrenadoABS_eqFunction_18(data, threadData);

  FrenadoABS_eqFunction_19(data, threadData);

  FrenadoABS_eqFunction_21(data, threadData);
  
  TRACE_POP
  return 0;
}

int FrenadoABS_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  tmp2 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
  tmp0 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  tmp4 = 1.0;
  tmp5 = 0.05;
  tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */), 0.05, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = ((tmp0 && tmp3)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 0.9;
  tmp6 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), 0.9, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
  tmp9 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp13 = 1.0;
  tmp14 = 0.01;
  tmp12 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */), 0.01, tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  gout[start_index] = (tmp12) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *FrenadoABS_relationDescription(int i)
{
  const char *res[] = {"lambda <= lambda_umbral",
  "presion_pedal > 0.05",
  "lambda > 0.9",
  "lambda > lambda_umbral",
  "v_filtrada > 0.01"};
  return res[i];
}

int FrenadoABS_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
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
    tmp17 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
    tmp15 = LessEqZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;

    start_index = current_index;
    tmp19 = 1.0;
    tmp20 = 0.05;
    tmp18 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */), 0.05, tmp19, tmp20, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp18;
    current_index++;

    start_index = current_index;
    tmp22 = 1.0;
    tmp23 = 0.9;
    tmp21 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), 0.9, tmp22, tmp23, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp21;
    current_index++;

    start_index = current_index;
    tmp25 = 1.0;
    tmp26 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
    tmp24 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp25, tmp26, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp24;
    current_index++;

    start_index = current_index;
    tmp28 = 1.0;
    tmp29 = 0.01;
    tmp27 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */), 0.01, tmp28, tmp29, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[start_index] = tmp27;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */) <= (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */) > 0.05);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */) > 0.9);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */) > (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */) > 0.01);
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

