/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "MuchosEstados_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int MuchosEstados_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* u variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int MuchosEstados_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[16].attribute.start;
  
  TRACE_POP
  return 0;
}

int MuchosEstados_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[16].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int MuchosEstados_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[16].info.name;
  
  TRACE_POP
  return 0;
}

int MuchosEstados_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int MuchosEstados_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MuchosEstados_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MuchosEstados_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* y1 variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* y2 variable */);
  data->simulationInfo->outputVars[2] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* y3 variable */);
  data->simulationInfo->outputVars[3] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* y4 variable */);
  data->simulationInfo->outputVars[4] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* y5 variable */);
  data->simulationInfo->outputVars[5] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* y6 variable */);
  data->simulationInfo->outputVars[6] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* y7 variable */);
  data->simulationInfo->outputVars[7] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* y8 variable */);
  
  TRACE_POP
  return 0;
}

int MuchosEstados_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MuchosEstados_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 26
type: SIMPLE_ASSIGN
todos_activos = x1 > 0.01 and x2 > 0.01 and x3 > 0.01 and x4 > 0.01 and x5 > 0.01 and x6 > 0.01 and x7 > 0.01 and x8 > 0.01
*/
void MuchosEstados_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
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
  tmp1 = 1.0;
  tmp2 = 0.01;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */), 0.01, tmp1, tmp2, 0, Greater, GreaterZC);
  tmp4 = 1.0;
  tmp5 = 0.01;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */), 0.01, tmp4, tmp5, 1, Greater, GreaterZC);
  tmp7 = 1.0;
  tmp8 = 0.01;
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */), 0.01, tmp7, tmp8, 2, Greater, GreaterZC);
  tmp10 = 1.0;
  tmp11 = 0.01;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */), 0.01, tmp10, tmp11, 3, Greater, GreaterZC);
  tmp13 = 1.0;
  tmp14 = 0.01;
  relationhysteresis(data, &tmp12, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */), 0.01, tmp13, tmp14, 4, Greater, GreaterZC);
  tmp16 = 1.0;
  tmp17 = 0.01;
  relationhysteresis(data, &tmp15, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */), 0.01, tmp16, tmp17, 5, Greater, GreaterZC);
  tmp19 = 1.0;
  tmp20 = 0.01;
  relationhysteresis(data, &tmp18, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */), 0.01, tmp19, tmp20, 6, Greater, GreaterZC);
  tmp22 = 1.0;
  tmp23 = 0.01;
  relationhysteresis(data, &tmp21, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */), 0.01, tmp22, tmp23, 7, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* todos_activos DISCRETE */) = (((((((tmp0 && tmp3) && tmp6) && tmp9) && tmp12) && tmp15) && tmp18) && tmp21);
  TRACE_POP
}
/*
equation index: 27
type: SIMPLE_ASSIGN
$DER.x8 = (x7 - x8) / tau
*/
void MuchosEstados_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* der(x8) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 28
type: SIMPLE_ASSIGN
$DER.x7 = (x6 - x7) / tau
*/
void MuchosEstados_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* der(x7) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 29
type: SIMPLE_ASSIGN
$DER.x6 = (x5 - x6) / tau
*/
void MuchosEstados_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* der(x6) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 30
type: SIMPLE_ASSIGN
$DER.x5 = (x4 - x5) / tau
*/
void MuchosEstados_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* der(x5) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 31
type: SIMPLE_ASSIGN
$DER.x4 = (x3 - x4) / tau
*/
void MuchosEstados_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* der(x4) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 32
type: SIMPLE_ASSIGN
$DER.x3 = (x2 - x3) / tau
*/
void MuchosEstados_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* der(x3) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 33
type: SIMPLE_ASSIGN
$DER.x2 = (x1 - x2) / tau
*/
void MuchosEstados_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* der(x2) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 34
type: SIMPLE_ASSIGN
$DER.x1 = (u - x1) / tau
*/
void MuchosEstados_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* der(x1) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* u variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */),(data->simulationInfo->realParameter[0] /* tau PARAM */),"tau",equationIndexes);
  TRACE_POP
}
/*
equation index: 35
type: SIMPLE_ASSIGN
y8 = x8
*/
void MuchosEstados_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* y8 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* x8 STATE(1) */);
  TRACE_POP
}
/*
equation index: 36
type: SIMPLE_ASSIGN
y7 = x7
*/
void MuchosEstados_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* y7 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x7 STATE(1) */);
  TRACE_POP
}
/*
equation index: 37
type: SIMPLE_ASSIGN
y6 = x6
*/
void MuchosEstados_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* y6 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* x6 STATE(1) */);
  TRACE_POP
}
/*
equation index: 38
type: SIMPLE_ASSIGN
y5 = x5
*/
void MuchosEstados_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* y5 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* x5 STATE(1) */);
  TRACE_POP
}
/*
equation index: 39
type: SIMPLE_ASSIGN
y4 = x4
*/
void MuchosEstados_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* y4 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x4 STATE(1) */);
  TRACE_POP
}
/*
equation index: 40
type: SIMPLE_ASSIGN
y3 = x3
*/
void MuchosEstados_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* y3 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x3 STATE(1) */);
  TRACE_POP
}
/*
equation index: 41
type: SIMPLE_ASSIGN
y2 = x2
*/
void MuchosEstados_eqFunction_41(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,41};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* y2 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */);
  TRACE_POP
}
/*
equation index: 42
type: SIMPLE_ASSIGN
y1 = x1
*/
void MuchosEstados_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* y1 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1) */);
  TRACE_POP
}

OMC_DISABLE_OPT
int MuchosEstados_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  MuchosEstados_functionLocalKnownVars(data, threadData);
  MuchosEstados_eqFunction_26(data, threadData);

  MuchosEstados_eqFunction_27(data, threadData);

  MuchosEstados_eqFunction_28(data, threadData);

  MuchosEstados_eqFunction_29(data, threadData);

  MuchosEstados_eqFunction_30(data, threadData);

  MuchosEstados_eqFunction_31(data, threadData);

  MuchosEstados_eqFunction_32(data, threadData);

  MuchosEstados_eqFunction_33(data, threadData);

  MuchosEstados_eqFunction_34(data, threadData);

  MuchosEstados_eqFunction_35(data, threadData);

  MuchosEstados_eqFunction_36(data, threadData);

  MuchosEstados_eqFunction_37(data, threadData);

  MuchosEstados_eqFunction_38(data, threadData);

  MuchosEstados_eqFunction_39(data, threadData);

  MuchosEstados_eqFunction_40(data, threadData);

  MuchosEstados_eqFunction_41(data, threadData);

  MuchosEstados_eqFunction_42(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int MuchosEstados_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
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

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[8])(DATA*, threadData_t*) = {
    MuchosEstados_eqFunction_27,
    MuchosEstados_eqFunction_28,
    MuchosEstados_eqFunction_29,
    MuchosEstados_eqFunction_30,
    MuchosEstados_eqFunction_31,
    MuchosEstados_eqFunction_32,
    MuchosEstados_eqFunction_33,
    MuchosEstados_eqFunction_34
  };
  
  static const int eqIndices[8] = {
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34
  };
  
  for (id = 0; id < 8; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int MuchosEstados_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  MuchosEstados_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void MuchosEstados_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
{
  TRACE_PUSH

  size_t i_real = 0;
  size_t i_integer = 0;
  size_t i_boolean = 0;
  size_t i_string = 0;

  realIndex[0] = 0;
  integerIndex[0] = 0;
  booleanIndex[0] = 0;
  stringIndex[0] = 0;

  /* stateVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x1 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x2 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x3 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x4 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x5 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x6 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x7 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x8 STATE(1) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x1) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x2) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x3) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x4) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x5) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x6) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x7) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x8) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y2 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y3 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y4 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y5 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y6 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y7 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y8 variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* todos_activos DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "MuchosEstados_12jac.h"
#include "MuchosEstados_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks MuchosEstados_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   MuchosEstados_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   MuchosEstados_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   MuchosEstados_initializeDAEmodeData,
   MuchosEstados_computeVarIndices,
   MuchosEstados_functionODE,
   MuchosEstados_functionAlgebraics,
   MuchosEstados_functionDAE,
   MuchosEstados_functionLocalKnownVars,
   MuchosEstados_input_function,
   MuchosEstados_input_function_init,
   MuchosEstados_input_function_updateStartValues,
   MuchosEstados_data_function,
   MuchosEstados_output_function,
   MuchosEstados_setc_function,
   MuchosEstados_setb_function,
   MuchosEstados_function_storeDelayed,
   MuchosEstados_function_storeSpatialDistribution,
   MuchosEstados_function_initSpatialDistribution,
   MuchosEstados_updateBoundVariableAttributes,
   MuchosEstados_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   MuchosEstados_functionRemovedInitialEquations,
   MuchosEstados_updateBoundParameters,
   MuchosEstados_checkForAsserts,
   MuchosEstados_function_ZeroCrossingsEquations,
   MuchosEstados_function_ZeroCrossings,
   MuchosEstados_function_updateRelations,
   MuchosEstados_zeroCrossingDescription,
   MuchosEstados_relationDescription,
   MuchosEstados_function_initSample,
   MuchosEstados_INDEX_JAC_A,
   MuchosEstados_INDEX_JAC_B,
   MuchosEstados_INDEX_JAC_C,
   MuchosEstados_INDEX_JAC_D,
   MuchosEstados_INDEX_JAC_F,
   MuchosEstados_INDEX_JAC_H,
   MuchosEstados_initialAnalyticJacobianA,
   MuchosEstados_initialAnalyticJacobianB,
   MuchosEstados_initialAnalyticJacobianC,
   MuchosEstados_initialAnalyticJacobianD,
   MuchosEstados_initialAnalyticJacobianF,
   MuchosEstados_initialAnalyticJacobianH,
   MuchosEstados_functionJacA_column,
   MuchosEstados_functionJacB_column,
   MuchosEstados_functionJacC_column,
   MuchosEstados_functionJacD_column,
   MuchosEstados_functionJacF_column,
   MuchosEstados_functionJacH_column,
   MuchosEstados_linear_model_frame,
   MuchosEstados_linear_model_datarecovery_frame,
   MuchosEstados_mayer,
   MuchosEstados_lagrange,
   MuchosEstados_pickUpBoundsForInputsInOptimization,
   MuchosEstados_setInputData,
   MuchosEstados_getTimeGrid,
   MuchosEstados_symbolicInlineSystem,
   MuchosEstados_function_initSynchronous,
   MuchosEstados_function_updateSynchronous,
   MuchosEstados_function_equationsSynchronous,
   MuchosEstados_inputNames,
   MuchosEstados_dataReconciliationInputNames,
   MuchosEstados_dataReconciliationUnmeasuredVariables,
   MuchosEstados_read_simulation_info,
   MuchosEstados_read_input_fmu,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "ArranqueSuaveMotor"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ArranqueSuaveMotor"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,18,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,88,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "CSPuro_SinME"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,12,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,77,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "CTPID"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CTPID"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,5,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,75,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "CodigoErrorDiagnostico"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,22,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,92,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "Complex"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,7,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,79,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "ContadorEventos"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,15,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,85,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "CrecimientoPoblacional"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CrecimientoPoblacional"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,22,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,92,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "CuerposAcoplados"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CuerposAcoplados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,16,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,86,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "EtapaSecuenciador"
#define _OMC_LIT_RESOURCE_8_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/EtapaSecuenciador"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,17,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,87,_OMC_LIT_RESOURCE_8_dir_data);

#define _OMC_LIT_RESOURCE_9_name_data "FrenadoABS"
#define _OMC_LIT_RESOURCE_9_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/FrenadoABS"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,10,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,80,_OMC_LIT_RESOURCE_9_dir_data);

#define _OMC_LIT_RESOURCE_10_name_data "Mi_Modelo_Nuevo"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/Mi_Modelo_Nuevo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,15,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,85,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "Modelica"
#define _OMC_LIT_RESOURCE_11_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,8,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,80,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,16,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,88,_OMC_LIT_RESOURCE_12_dir_data);

#define _OMC_LIT_RESOURCE_13_name_data "MuchosEstados"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MuchosEstados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,13,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,83,_OMC_LIT_RESOURCE_13_dir_data);

#define _OMC_LIT_RESOURCE_14_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_14_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_name,18,_OMC_LIT_RESOURCE_14_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir,88,_OMC_LIT_RESOURCE_14_dir_data);

#define _OMC_LIT_RESOURCE_15_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_15_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_name,13,_OMC_LIT_RESOURCE_15_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir,83,_OMC_LIT_RESOURCE_15_dir_data);

#define _OMC_LIT_RESOURCE_16_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_16_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_name,10,_OMC_LIT_RESOURCE_16_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir,80,_OMC_LIT_RESOURCE_16_dir_data);

#define _OMC_LIT_RESOURCE_17_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_17_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_name,16,_OMC_LIT_RESOURCE_17_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir,86,_OMC_LIT_RESOURCE_17_dir_data);

#define _OMC_LIT_RESOURCE_18_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_18_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_name,12,_OMC_LIT_RESOURCE_18_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir,82,_OMC_LIT_RESOURCE_18_dir_data);

#define _OMC_LIT_RESOURCE_19_name_data "SuspensionActiva"
#define _OMC_LIT_RESOURCE_19_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SuspensionActiva"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_name,16,_OMC_LIT_RESOURCE_19_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir,86,_OMC_LIT_RESOURCE_19_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,40,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir)}};
void MuchosEstados_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &MuchosEstados_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "MuchosEstados";
  data->modelData->modelFilePrefix = "MuchosEstados";
  data->modelData->modelFileName = "MuchosEstados.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MuchosEstados";
  data->modelData->modelGUID = "{c3a45dfb-0863-485d-8cc5-47ecfd93da7d}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/MuchosEstados_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 8;
  data->modelData->nVariablesRealArray = 25;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 1;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 9;
  data->modelData->nAliasReal = 8;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 8;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 43;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 6;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

