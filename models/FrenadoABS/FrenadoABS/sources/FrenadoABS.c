/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "FrenadoABS_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int FrenadoABS_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* velocidad_rueda variable */) = data->simulationInfo->inputVars[1];
  
  TRACE_POP
  return 0;
}

int FrenadoABS_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[13].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[14].attribute.start;
  
  TRACE_POP
  return 0;
}

int FrenadoABS_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[13].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[14].attribute.start = data->simulationInfo->inputVars[1];
  
  TRACE_POP
  return 0;
}

int FrenadoABS_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[13].info.name;
  names[1] = (char *) data->modelData->realVarsData[14].info.name;
  
  TRACE_POP
  return 0;
}

int FrenadoABS_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int FrenadoABS_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FrenadoABS_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FrenadoABS_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* presion_modulada variable */);
  
  TRACE_POP
  return 0;
}

int FrenadoABS_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FrenadoABS_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 17
type: SIMPLE_ASSIGN
dv_dt = (velocidad_rueda - v_filtrada) / tau_filtro_v
*/
void FrenadoABS_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* dv_dt variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* velocidad_rueda variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */),(data->simulationInfo->realParameter[4] /* tau_filtro_v PARAM */),"tau_filtro_v",equationIndexes);
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
$DER.v_filtrada = dv_dt
*/
void FrenadoABS_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* der(v_filtrada) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* dv_dt variable */);
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
$DER.dv_filtrada = (dv_dt - dv_filtrada) / tau_filtro_v
*/
void FrenadoABS_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* der(dv_filtrada) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* dv_dt variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* dv_filtrada STATE(1) */),(data->simulationInfo->realParameter[4] /* tau_filtro_v PARAM */),"tau_filtro_v",equationIndexes);
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
$DER.p_filtrada = (presion_pedal - p_filtrada) / tau_filtro_p
*/
void FrenadoABS_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* der(p_filtrada) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* p_filtrada STATE(1) */),(data->simulationInfo->realParameter[3] /* tau_filtro_p PARAM */),"tau_filtro_p",equationIndexes);
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
lambda = if v_filtrada > 0.01 then min(1.0, max(0.0, dv_filtrada / ((-v_filtrada) * 20.0))) else 0.0
*/
void FrenadoABS_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = 0.01;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */), 0.01, tmp1, tmp2, 4, Greater, GreaterZC);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */) = (tmp0?fmin(1.0,fmax(0.0,DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* dv_filtrada STATE(1) */),((-(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* v_filtrada STATE(1,dv_dt) */))) * (20.0),"(-v_filtrada) * 20.0",equationIndexes))):0.0);
  TRACE_POP
}
/*
equation index: 22
type: SIMPLE_ASSIGN
$DER.oscilador = 6.283185307179586 * d_oscilador * f_modulacion
*/
void FrenadoABS_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* der(oscilador) STATE_DER */) = (6.283185307179586) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* d_oscilador STATE(1) */)) * ((data->simulationInfo->realParameter[1] /* f_modulacion PARAM */)));
  TRACE_POP
}
/*
equation index: 23
type: SIMPLE_ASSIGN
$DER.d_oscilador = (-6.283185307179586) * oscilador * f_modulacion
*/
void FrenadoABS_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(d_oscilador) STATE_DER */) = (-6.283185307179586) * (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* oscilador STATE(1) */)) * ((data->simulationInfo->realParameter[1] /* f_modulacion PARAM */)));
  TRACE_POP
}
/*
equation index: 24
type: SIMPLE_ASSIGN
abs_activo = lambda > lambda_umbral
*/
void FrenadoABS_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp4, tmp5, 3, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* abs_activo DISCRETE */) = tmp3;
  TRACE_POP
}
/*
equation index: 25
type: SIMPLE_ASSIGN
presion_modulada = if abs_activo then min(P_max, max(0.0, p_filtrada * (0.5 + 0.5 * oscilador))) else min(P_max, max(0.0, p_filtrada))
*/
void FrenadoABS_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* presion_modulada variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* abs_activo DISCRETE */)?fmin((data->simulationInfo->realParameter[0] /* P_max PARAM */),fmax(0.0,((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* p_filtrada STATE(1) */)) * (0.5 + (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* oscilador STATE(1) */))))):fmin((data->simulationInfo->realParameter[0] /* P_max PARAM */),fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* p_filtrada STATE(1) */))));
  TRACE_POP
}
/*
equation index: 26
type: SIMPLE_ASSIGN
rueda_bloqueada = lambda > 0.9
*/
void FrenadoABS_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  tmp7 = 1.0;
  tmp8 = 0.9;
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), 0.9, tmp7, tmp8, 2, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* rueda_bloqueada DISCRETE */) = tmp6;
  TRACE_POP
}
/*
equation index: 27
type: SIMPLE_ASSIGN
frenado_normal = lambda <= lambda_umbral and presion_pedal > 0.05
*/
void FrenadoABS_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */));
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* lambda variable */), (data->simulationInfo->realParameter[2] /* lambda_umbral PARAM */), tmp10, tmp11, 0, LessEq, LessEqZC);
  tmp13 = 1.0;
  tmp14 = 0.05;
  relationhysteresis(data, &tmp12, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* presion_pedal variable */), 0.05, tmp13, tmp14, 1, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* frenado_normal DISCRETE */) = (tmp9 && tmp12);
  TRACE_POP
}

OMC_DISABLE_OPT
int FrenadoABS_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  FrenadoABS_functionLocalKnownVars(data, threadData);
  FrenadoABS_eqFunction_17(data, threadData);

  FrenadoABS_eqFunction_18(data, threadData);

  FrenadoABS_eqFunction_19(data, threadData);

  FrenadoABS_eqFunction_20(data, threadData);

  FrenadoABS_eqFunction_21(data, threadData);

  FrenadoABS_eqFunction_22(data, threadData);

  FrenadoABS_eqFunction_23(data, threadData);

  FrenadoABS_eqFunction_24(data, threadData);

  FrenadoABS_eqFunction_25(data, threadData);

  FrenadoABS_eqFunction_26(data, threadData);

  FrenadoABS_eqFunction_27(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int FrenadoABS_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void FrenadoABS_eqFunction_17(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_18(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_19(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_20(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_22(DATA* data, threadData_t *threadData);
extern void FrenadoABS_eqFunction_23(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[6])(DATA*, threadData_t*) = {
    FrenadoABS_eqFunction_17,
    FrenadoABS_eqFunction_18,
    FrenadoABS_eqFunction_19,
    FrenadoABS_eqFunction_20,
    FrenadoABS_eqFunction_22,
    FrenadoABS_eqFunction_23
  };
  
  static const int eqIndices[6] = {
    17,
    18,
    19,
    20,
    22,
    23
  };
  
  for (id = 0; id < 6; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int FrenadoABS_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  FrenadoABS_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void FrenadoABS_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* d_oscilador STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* dv_filtrada STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* oscilador STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* p_filtrada STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* v_filtrada STATE(1,dv_dt) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(d_oscilador) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(dv_filtrada) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(oscilador) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(p_filtrada) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(v_filtrada) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* dv_dt variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* lambda variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* presion_modulada variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* presion_pedal variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* velocidad_rueda variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* abs_activo DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* frenado_normal DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* rueda_bloqueada DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "FrenadoABS_12jac.h"
#include "FrenadoABS_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks FrenadoABS_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   FrenadoABS_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   FrenadoABS_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   FrenadoABS_initializeDAEmodeData,
   FrenadoABS_computeVarIndices,
   FrenadoABS_functionODE,
   FrenadoABS_functionAlgebraics,
   FrenadoABS_functionDAE,
   FrenadoABS_functionLocalKnownVars,
   FrenadoABS_input_function,
   FrenadoABS_input_function_init,
   FrenadoABS_input_function_updateStartValues,
   FrenadoABS_data_function,
   FrenadoABS_output_function,
   FrenadoABS_setc_function,
   FrenadoABS_setb_function,
   FrenadoABS_function_storeDelayed,
   FrenadoABS_function_storeSpatialDistribution,
   FrenadoABS_function_initSpatialDistribution,
   FrenadoABS_updateBoundVariableAttributes,
   FrenadoABS_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   FrenadoABS_functionRemovedInitialEquations,
   FrenadoABS_updateBoundParameters,
   FrenadoABS_checkForAsserts,
   FrenadoABS_function_ZeroCrossingsEquations,
   FrenadoABS_function_ZeroCrossings,
   FrenadoABS_function_updateRelations,
   FrenadoABS_zeroCrossingDescription,
   FrenadoABS_relationDescription,
   FrenadoABS_function_initSample,
   FrenadoABS_INDEX_JAC_A,
   FrenadoABS_INDEX_JAC_B,
   FrenadoABS_INDEX_JAC_C,
   FrenadoABS_INDEX_JAC_D,
   FrenadoABS_INDEX_JAC_F,
   FrenadoABS_INDEX_JAC_H,
   FrenadoABS_initialAnalyticJacobianA,
   FrenadoABS_initialAnalyticJacobianB,
   FrenadoABS_initialAnalyticJacobianC,
   FrenadoABS_initialAnalyticJacobianD,
   FrenadoABS_initialAnalyticJacobianF,
   FrenadoABS_initialAnalyticJacobianH,
   FrenadoABS_functionJacA_column,
   FrenadoABS_functionJacB_column,
   FrenadoABS_functionJacC_column,
   FrenadoABS_functionJacD_column,
   FrenadoABS_functionJacF_column,
   FrenadoABS_functionJacH_column,
   FrenadoABS_linear_model_frame,
   FrenadoABS_linear_model_datarecovery_frame,
   FrenadoABS_mayer,
   FrenadoABS_lagrange,
   FrenadoABS_pickUpBoundsForInputsInOptimization,
   FrenadoABS_setInputData,
   FrenadoABS_getTimeGrid,
   FrenadoABS_symbolicInlineSystem,
   FrenadoABS_function_initSynchronous,
   FrenadoABS_function_updateSynchronous,
   FrenadoABS_function_equationsSynchronous,
   FrenadoABS_inputNames,
   FrenadoABS_dataReconciliationInputNames,
   FrenadoABS_dataReconciliationUnmeasuredVariables,
   FrenadoABS_read_simulation_info,
   FrenadoABS_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_1_name_data "CTPID"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CTPID"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,5,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,75,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "CodigoErrorDiagnostico"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,22,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,92,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "Complex"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,7,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,79,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "ContadorEventos"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,15,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,85,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "EtapaSecuenciador"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/EtapaSecuenciador"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,17,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,87,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "FrenadoABS"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/FrenadoABS"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,10,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,80,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "Modelica"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,8,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,80,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_8_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,16,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,88,_OMC_LIT_RESOURCE_8_dir_data);

#define _OMC_LIT_RESOURCE_9_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_9_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,10,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,80,_OMC_LIT_RESOURCE_9_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,20,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir)}};
void FrenadoABS_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &FrenadoABS_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "FrenadoABS";
  data->modelData->modelFilePrefix = "FrenadoABS";
  data->modelData->modelFileName = "FrenadoABS.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/FrenadoABS";
  data->modelData->modelGUID = "{46fc3434-2fca-47d6-8ce3-46700e75280c}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/FrenadoABS_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 5;
  data->modelData->nVariablesRealArray = 15;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 3;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 5;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 2;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 1;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 3;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 4;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 5;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 28;
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

