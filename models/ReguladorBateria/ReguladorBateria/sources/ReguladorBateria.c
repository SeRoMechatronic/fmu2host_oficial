/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ReguladorBateria_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ReguladorBateria_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ReguladorBateria_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[9].attribute.start;
  
  TRACE_POP
  return 0;
}

int ReguladorBateria_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[9].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ReguladorBateria_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->booleanVarsData[1].info.name;
  names[1] = (char *) data->modelData->realVarsData[9].info.name;
  
  TRACE_POP
  return 0;
}

int ReguladorBateria_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ReguladorBateria_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ReguladorBateria_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ReguladorBateria_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* corriente_carga variable */);
  
  TRACE_POP
  return 0;
}

int ReguladorBateria_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ReguladorBateria_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 12
type: SIMPLE_ASSIGN
fallo_sobretension = tension_bateria > V_max
*/
void ReguladorBateria_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[3] /* V_max PARAM */));
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */), (data->simulationInfo->realParameter[3] /* V_max PARAM */), tmp1, tmp2, 0, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* fallo_sobretension DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 13
type: SIMPLE_ASSIGN
carga_completa = tension_bateria >= V_carga_completa
*/
void ReguladorBateria_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[2] /* V_carga_completa PARAM */));
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */), (data->simulationInfo->realParameter[2] /* V_carga_completa PARAM */), tmp4, tmp5, 1, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* carga_completa DISCRETE */) = tmp3;
  TRACE_POP
}
/*
equation index: 14
type: SIMPLE_ASSIGN
cargando = carga_conectada and tension_bateria < V_carga_completa and tension_bateria < V_max
*/
void ReguladorBateria_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[2] /* V_carga_completa PARAM */));
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */), (data->simulationInfo->realParameter[2] /* V_carga_completa PARAM */), tmp7, tmp8, 2, Less, LessZC);
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[3] /* V_max PARAM */));
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */), (data->simulationInfo->realParameter[3] /* V_max PARAM */), tmp10, tmp11, 3, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* cargando DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* carga_conectada variable */) && tmp6) && tmp9);
  TRACE_POP
}
/*
equation index: 15
type: SIMPLE_ASSIGN
error_v = if carga_conectada then V_nominal - tension_bateria else 0.0
*/
void ReguladorBateria_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* error_v variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* carga_conectada variable */)?(data->simulationInfo->realParameter[4] /* V_nominal PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_bateria variable */):0.0);
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
$DER.x1 = x2
*/
void ReguladorBateria_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* der(x1) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */);
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
corriente_raw = x1 + x2 / wn
*/
void ReguladorBateria_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* corriente_raw variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1,x2) */) + DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */),(data->simulationInfo->realParameter[5] /* wn PARAM */),"wn",equationIndexes);
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
$cse1 = max(0.0, corriente_raw)
*/
void ReguladorBateria_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* $cse1 variable */) = fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* corriente_raw variable */));
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
corriente_carga = min(I_max, $cse1)
*/
void ReguladorBateria_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* corriente_carga variable */) = fmin((data->simulationInfo->realParameter[0] /* I_max PARAM */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* $cse1 variable */));
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
aw_error = corriente_carga - corriente_raw
*/
void ReguladorBateria_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* aw_error variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* corriente_carga variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* corriente_raw variable */);
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
$DER.x2 = wn ^ 2.0 * error_v + (-2.0) * zeta * wn * x2 + Ki_aw * aw_error - wn ^ 2.0 * x1
*/
void ReguladorBateria_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  modelica_real tmp12;
  modelica_real tmp13;
  tmp12 = (data->simulationInfo->realParameter[5] /* wn PARAM */);
  tmp13 = (data->simulationInfo->realParameter[5] /* wn PARAM */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(x2) STATE_DER */) = ((tmp12 * tmp12)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* error_v variable */)) + (-2.0) * (((data->simulationInfo->realParameter[6] /* zeta PARAM */)) * (((data->simulationInfo->realParameter[5] /* wn PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* x2 STATE(1) */)))) + ((data->simulationInfo->realParameter[1] /* Ki_aw PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* aw_error variable */)) - (((tmp13 * tmp13)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x1 STATE(1,x2) */)));
  TRACE_POP
}

OMC_DISABLE_OPT
int ReguladorBateria_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ReguladorBateria_functionLocalKnownVars(data, threadData);
  ReguladorBateria_eqFunction_12(data, threadData);

  ReguladorBateria_eqFunction_13(data, threadData);

  ReguladorBateria_eqFunction_14(data, threadData);

  ReguladorBateria_eqFunction_15(data, threadData);

  ReguladorBateria_eqFunction_16(data, threadData);

  ReguladorBateria_eqFunction_17(data, threadData);

  ReguladorBateria_eqFunction_18(data, threadData);

  ReguladorBateria_eqFunction_19(data, threadData);

  ReguladorBateria_eqFunction_20(data, threadData);

  ReguladorBateria_eqFunction_21(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ReguladorBateria_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void ReguladorBateria_eqFunction_15(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_16(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_17(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_18(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_19(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_20(DATA* data, threadData_t *threadData);
extern void ReguladorBateria_eqFunction_21(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[7])(DATA*, threadData_t*) = {
    ReguladorBateria_eqFunction_15,
    ReguladorBateria_eqFunction_16,
    ReguladorBateria_eqFunction_17,
    ReguladorBateria_eqFunction_18,
    ReguladorBateria_eqFunction_19,
    ReguladorBateria_eqFunction_20,
    ReguladorBateria_eqFunction_21
  };
  
  static const int eqIndices[7] = {
    15,
    16,
    17,
    18,
    19,
    20,
    21
  };
  
  for (id = 0; id < 7; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int ReguladorBateria_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  ReguladorBateria_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void ReguladorBateria_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x1 STATE(1,x2) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x2 STATE(1) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x1) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x2) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* aw_error variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* corriente_carga variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* corriente_raw variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* error_v variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tension_bateria variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* carga_completa DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* carga_conectada variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* cargando DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* fallo_sobretension DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ReguladorBateria_12jac.h"
#include "ReguladorBateria_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ReguladorBateria_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ReguladorBateria_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ReguladorBateria_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ReguladorBateria_initializeDAEmodeData,
   ReguladorBateria_computeVarIndices,
   ReguladorBateria_functionODE,
   ReguladorBateria_functionAlgebraics,
   ReguladorBateria_functionDAE,
   ReguladorBateria_functionLocalKnownVars,
   ReguladorBateria_input_function,
   ReguladorBateria_input_function_init,
   ReguladorBateria_input_function_updateStartValues,
   ReguladorBateria_data_function,
   ReguladorBateria_output_function,
   ReguladorBateria_setc_function,
   ReguladorBateria_setb_function,
   ReguladorBateria_function_storeDelayed,
   ReguladorBateria_function_storeSpatialDistribution,
   ReguladorBateria_function_initSpatialDistribution,
   ReguladorBateria_updateBoundVariableAttributes,
   ReguladorBateria_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   ReguladorBateria_functionRemovedInitialEquations,
   ReguladorBateria_updateBoundParameters,
   ReguladorBateria_checkForAsserts,
   ReguladorBateria_function_ZeroCrossingsEquations,
   ReguladorBateria_function_ZeroCrossings,
   ReguladorBateria_function_updateRelations,
   ReguladorBateria_zeroCrossingDescription,
   ReguladorBateria_relationDescription,
   ReguladorBateria_function_initSample,
   ReguladorBateria_INDEX_JAC_A,
   ReguladorBateria_INDEX_JAC_B,
   ReguladorBateria_INDEX_JAC_C,
   ReguladorBateria_INDEX_JAC_D,
   ReguladorBateria_INDEX_JAC_F,
   ReguladorBateria_INDEX_JAC_H,
   ReguladorBateria_initialAnalyticJacobianA,
   ReguladorBateria_initialAnalyticJacobianB,
   ReguladorBateria_initialAnalyticJacobianC,
   ReguladorBateria_initialAnalyticJacobianD,
   ReguladorBateria_initialAnalyticJacobianF,
   ReguladorBateria_initialAnalyticJacobianH,
   ReguladorBateria_functionJacA_column,
   ReguladorBateria_functionJacB_column,
   ReguladorBateria_functionJacC_column,
   ReguladorBateria_functionJacD_column,
   ReguladorBateria_functionJacF_column,
   ReguladorBateria_functionJacH_column,
   ReguladorBateria_linear_model_frame,
   ReguladorBateria_linear_model_datarecovery_frame,
   ReguladorBateria_mayer,
   ReguladorBateria_lagrange,
   ReguladorBateria_pickUpBoundsForInputsInOptimization,
   ReguladorBateria_setInputData,
   ReguladorBateria_getTimeGrid,
   ReguladorBateria_symbolicInlineSystem,
   ReguladorBateria_function_initSynchronous,
   ReguladorBateria_function_updateSynchronous,
   ReguladorBateria_function_equationsSynchronous,
   ReguladorBateria_inputNames,
   ReguladorBateria_dataReconciliationInputNames,
   ReguladorBateria_dataReconciliationUnmeasuredVariables,
   ReguladorBateria_read_simulation_info,
   ReguladorBateria_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_9_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_9_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,18,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,88,_OMC_LIT_RESOURCE_9_dir_data);

#define _OMC_LIT_RESOURCE_10_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,13,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,83,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_11_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,10,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,80,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,16,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,86,_OMC_LIT_RESOURCE_12_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,26,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir)}};
void ReguladorBateria_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ReguladorBateria_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ReguladorBateria";
  data->modelData->modelFilePrefix = "ReguladorBateria";
  data->modelData->modelFileName = "ReguladorBateria.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria";
  data->modelData->modelGUID = "{69132570-939a-43d4-814a-e9b7801e344c}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ReguladorBateria_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 2;
  data->modelData->nVariablesRealArray = 10;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 4;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 7;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 2;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 2;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 3;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 3;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 4;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 22;
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

