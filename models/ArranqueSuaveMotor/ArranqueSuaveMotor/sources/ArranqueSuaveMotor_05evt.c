/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "ArranqueSuaveMotor_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void ArranqueSuaveMotor_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *ArranqueSuaveMotor_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"orden_arranque and tension_filtrada < 0.9 and not fallo_sobrecarga",
  "tiempo_sobrecarga > t_retardo",
  "orden_arranque and tension_filtrada > 0.9",
  "carga_motor > umbral_sobrecarga"};
  static const int occurEqs0[] = {1,20};
  static const int occurEqs1[] = {1,19};
  static const int occurEqs2[] = {1,18};
  static const int occurEqs3[] = {1,17};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void ArranqueSuaveMotor_eqFunction_14(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_15(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_16(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_17(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_19(DATA* data, threadData_t *threadData);

int ArranqueSuaveMotor_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  ArranqueSuaveMotor_eqFunction_14(data, threadData);

  ArranqueSuaveMotor_eqFunction_15(data, threadData);

  ArranqueSuaveMotor_eqFunction_16(data, threadData);

  ArranqueSuaveMotor_eqFunction_17(data, threadData);

  ArranqueSuaveMotor_eqFunction_19(data, threadData);
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  tmp2 = 0.9;
  tmp0 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = ((((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* orden_arranque variable */) && tmp0) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* fallo_sobrecarga DISCRETE */)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[0] /* t_retardo PARAM */));
  tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */), (data->simulationInfo->realParameter[0] /* t_retardo PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 0.9;
  tmp6 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* orden_arranque variable */) && tmp6)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */));
  tmp9 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* carga_motor variable */), (data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */), tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *ArranqueSuaveMotor_relationDescription(int i)
{
  const char *res[] = {"tension_filtrada < 0.9",
  "tiempo_sobrecarga > t_retardo",
  "tension_filtrada > 0.9",
  "carga_motor > umbral_sobrecarga"};
  return res[i];
}

int ArranqueSuaveMotor_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
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
    tmp14 = 0.9;
    tmp12 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp13, tmp14, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp12;
    current_index++;

    start_index = current_index;
    tmp16 = 1.0;
    tmp17 = fabs((data->simulationInfo->realParameter[0] /* t_retardo PARAM */));
    tmp15 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */), (data->simulationInfo->realParameter[0] /* t_retardo PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp15;
    current_index++;

    start_index = current_index;
    tmp19 = 1.0;
    tmp20 = 0.9;
    tmp18 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp19, tmp20, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp18;
    current_index++;

    start_index = current_index;
    tmp22 = 1.0;
    tmp23 = fabs((data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */));
    tmp21 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* carga_motor variable */), (data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */), tmp22, tmp23, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp21;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */) < 0.9);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */) > (data->simulationInfo->realParameter[0] /* t_retardo PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */) > 0.9);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* carga_motor variable */) > (data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

