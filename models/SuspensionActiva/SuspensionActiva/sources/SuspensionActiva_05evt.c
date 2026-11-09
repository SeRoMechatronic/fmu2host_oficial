/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "SuspensionActiva_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void SuspensionActiva_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *SuspensionActiva_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"velocidad_vehiculo < 0.3 and not bache_detectado",
  "abs(fuerza_raw) >= sat_actuador",
  "abs(posicion_filtrada) > umbral_bache"};
  static const int occurEqs0[] = {1,17};
  static const int occurEqs1[] = {1,16};
  static const int occurEqs2[] = {1,15};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void SuspensionActiva_eqFunction_10(DATA* data, threadData_t *threadData);
extern void SuspensionActiva_eqFunction_11(DATA* data, threadData_t *threadData);
extern void SuspensionActiva_eqFunction_12(DATA* data, threadData_t *threadData);
extern void SuspensionActiva_eqFunction_15(DATA* data, threadData_t *threadData);

int SuspensionActiva_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  SuspensionActiva_eqFunction_10(data, threadData);

  SuspensionActiva_eqFunction_11(data, threadData);

  SuspensionActiva_eqFunction_12(data, threadData);

  SuspensionActiva_eqFunction_15(data, threadData);
  
  TRACE_POP
  return 0;
}

int SuspensionActiva_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  tmp2 = 0.3;
  tmp0 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* velocidad_vehiculo variable */), 0.3, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = ((tmp0 && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* bache_detectado DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[2] /* sat_actuador PARAM */));
  tmp3 = GreaterEqZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* fuerza_raw variable */)), (data->simulationInfo->realParameter[2] /* sat_actuador PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[4] /* umbral_bache PARAM */));
  tmp6 = GreaterZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* posicion_filtrada STATE(1) */)), (data->simulationInfo->realParameter[4] /* umbral_bache PARAM */), tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *SuspensionActiva_relationDescription(int i)
{
  const char *res[] = {"velocidad_vehiculo < 0.3",
  "abs(fuerza_raw) >= sat_actuador",
  "abs(posicion_filtrada) > umbral_bache"};
  return res[i];
}

int SuspensionActiva_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
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
    tmp11 = 0.3;
    tmp9 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* velocidad_vehiculo variable */), 0.3, tmp10, tmp11, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp9;
    current_index++;

    start_index = current_index;
    tmp13 = 1.0;
    tmp14 = fabs((data->simulationInfo->realParameter[2] /* sat_actuador PARAM */));
    tmp12 = GreaterEqZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* fuerza_raw variable */)), (data->simulationInfo->realParameter[2] /* sat_actuador PARAM */), tmp13, tmp14, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp12;
    current_index++;

    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = fabs((data->simulationInfo->realParameter[4] /* umbral_bache PARAM */));
    tmp15 = GreaterZC(fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* posicion_filtrada STATE(1) */)), (data->simulationInfo->realParameter[4] /* umbral_bache PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* velocidad_vehiculo variable */) < 0.3);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* fuerza_raw variable */)) >= (data->simulationInfo->realParameter[2] /* sat_actuador PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* posicion_filtrada STATE(1) */)) > (data->simulationInfo->realParameter[4] /* umbral_bache PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

