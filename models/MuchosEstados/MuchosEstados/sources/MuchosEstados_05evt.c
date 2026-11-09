/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "MuchosEstados_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void MuchosEstados_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *MuchosEstados_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"x1 > 0.01 and x2 > 0.01 and x3 > 0.01 and x4 > 0.01 and x5 > 0.01 and x6 > 0.01 and x7 > 0.01 and x8 > 0.01"};
  static const int occurEqs0[] = {1,26};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void MuchosEstados_eqFunction_27(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_28(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_29(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_30(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_31(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_32(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_33(DATA* data, threadData_t *threadData);
extern void MuchosEstados_eqFunction_34(DATA* data, threadData_t *threadData);

int MuchosEstados_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  MuchosEstados_eqFunction_27(data, threadData);

  MuchosEstados_eqFunction_28(data, threadData);

  MuchosEstados_eqFunction_29(data, threadData);

  MuchosEstados_eqFunction_30(data, threadData);

  MuchosEstados_eqFunction_31(data, threadData);

  MuchosEstados_eqFunction_32(data, threadData);

  MuchosEstados_eqFunction_33(data, threadData);

  MuchosEstados_eqFunction_34(data, threadData);
  
  TRACE_POP
  return 0;
}

int MuchosEstados_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
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
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 0.01;
  tmp0 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */), 0.01, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  tmp4 = 1.0;
  tmp5 = 0.01;
  tmp3 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */), 0.01, tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  tmp7 = 1.0;
  tmp8 = 0.01;
  tmp6 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */), 0.01, tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  tmp10 = 1.0;
  tmp11 = 0.01;
  tmp9 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */), 0.01, tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  tmp13 = 1.0;
  tmp14 = 0.01;
  tmp12 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */), 0.01, tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  tmp16 = 1.0;
  tmp17 = 0.01;
  tmp15 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */), 0.01, tmp16, tmp17, data->simulationInfo->storedRelations[5]);
  tmp19 = 1.0;
  tmp20 = 0.01;
  tmp18 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */), 0.01, tmp19, tmp20, data->simulationInfo->storedRelations[6]);
  tmp22 = 1.0;
  tmp23 = 0.01;
  tmp21 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */), 0.01, tmp22, tmp23, data->simulationInfo->storedRelations[7]);
  gout[start_index] = ((((((((tmp0 && tmp3) && tmp6) && tmp9) && tmp12) && tmp15) && tmp18) && tmp21)) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *MuchosEstados_relationDescription(int i)
{
  const char *res[] = {"x1 > 0.01",
  "x2 > 0.01",
  "x3 > 0.01",
  "x4 > 0.01",
  "x5 > 0.01",
  "x6 > 0.01",
  "x7 > 0.01",
  "x8 > 0.01"};
  return res[i];
}

int MuchosEstados_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp24;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_boolean tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_boolean tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_boolean tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  modelica_boolean tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_boolean tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  modelica_boolean tmp42;
  modelica_real tmp43;
  modelica_real tmp44;
  modelica_boolean tmp45;
  modelica_real tmp46;
  modelica_real tmp47;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp25 = 1.0;
    tmp26 = 0.01;
    tmp24 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */), 0.01, tmp25, tmp26, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp24;
    current_index++;

    start_index = current_index;
    tmp28 = 1.0;
    tmp29 = 0.01;
    tmp27 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */), 0.01, tmp28, tmp29, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp27;
    current_index++;

    start_index = current_index;
    tmp31 = 1.0;
    tmp32 = 0.01;
    tmp30 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */), 0.01, tmp31, tmp32, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp30;
    current_index++;

    start_index = current_index;
    tmp34 = 1.0;
    tmp35 = 0.01;
    tmp33 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */), 0.01, tmp34, tmp35, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp33;
    current_index++;

    start_index = current_index;
    tmp37 = 1.0;
    tmp38 = 0.01;
    tmp36 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */), 0.01, tmp37, tmp38, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[start_index] = tmp36;
    current_index++;

    start_index = current_index;
    tmp40 = 1.0;
    tmp41 = 0.01;
    tmp39 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */), 0.01, tmp40, tmp41, data->simulationInfo->storedRelations[5]);
    data->simulationInfo->relations[start_index] = tmp39;
    current_index++;

    start_index = current_index;
    tmp43 = 1.0;
    tmp44 = 0.01;
    tmp42 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */), 0.01, tmp43, tmp44, data->simulationInfo->storedRelations[6]);
    data->simulationInfo->relations[start_index] = tmp42;
    current_index++;

    start_index = current_index;
    tmp46 = 1.0;
    tmp47 = 0.01;
    tmp45 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */), 0.01, tmp46, tmp47, data->simulationInfo->storedRelations[7]);
    data->simulationInfo->relations[start_index] = tmp45;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */) > 0.01);
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

