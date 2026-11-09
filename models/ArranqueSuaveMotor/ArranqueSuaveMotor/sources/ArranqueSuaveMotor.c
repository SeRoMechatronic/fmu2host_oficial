/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ArranqueSuaveMotor_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ArranqueSuaveMotor_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* carga_motor variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[7].attribute.start;
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[7].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[7].info.name;
  names[1] = (char *) data->modelData->booleanVarsData[3].info.name;
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_aplicada variable */);
  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ArranqueSuaveMotor_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 12
type: SIMPLE_ASSIGN
$cse1 = max(0.0, tension_filtrada)
*/
void ArranqueSuaveMotor_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* $cse1 variable */) = fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */));
  TRACE_POP
}
/*
equation index: 13
type: SIMPLE_ASSIGN
tension_aplicada = min(1.0, $cse1)
*/
void ArranqueSuaveMotor_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* tension_aplicada variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* $cse1 variable */));
  TRACE_POP
}
/*
equation index: 14
type: SIMPLE_ASSIGN
referencia_rampa = if orden_arranque then 1.0 else 0.0
*/
void ArranqueSuaveMotor_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* referencia_rampa variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* orden_arranque variable */)?1.0:0.0);
  TRACE_POP
}
/*
equation index: 15
type: SIMPLE_ASSIGN
$DER.rampa = (referencia_rampa - rampa) / tau_rampa
*/
void ArranqueSuaveMotor_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(rampa) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* referencia_rampa variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* rampa STATE(1) */),(data->simulationInfo->realParameter[2] /* tau_rampa PARAM */),"tau_rampa",equationIndexes);
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
$DER.tension_filtrada = (rampa - tension_filtrada) / tau_pt1
*/
void ArranqueSuaveMotor_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(tension_filtrada) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* rampa STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */),(data->simulationInfo->realParameter[1] /* tau_pt1 PARAM */),"tau_pt1",equationIndexes);
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
$DER.tiempo_sobrecarga = if carga_motor > umbral_sobrecarga then 1.0 else (-2.0) * tiempo_sobrecarga
*/
void ArranqueSuaveMotor_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */));
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* carga_motor variable */), (data->simulationInfo->realParameter[3] /* umbral_sobrecarga PARAM */), tmp1, tmp2, 3, Greater, GreaterZC);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(tiempo_sobrecarga) STATE_DER */) = (tmp0?1.0:(-2.0) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */)));
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
motor_en_marcha = orden_arranque and tension_filtrada > 0.9
*/
void ArranqueSuaveMotor_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = 1.0;
  tmp5 = 0.9;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp4, tmp5, 2, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* motor_en_marcha DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* orden_arranque variable */) && tmp3);
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
fallo_sobrecarga = tiempo_sobrecarga > t_retardo
*/
void ArranqueSuaveMotor_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[0] /* t_retardo PARAM */));
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tiempo_sobrecarga STATE(1) */), (data->simulationInfo->realParameter[0] /* t_retardo PARAM */), tmp7, tmp8, 1, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* fallo_sobrecarga DISCRETE */) = tmp6;
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
en_rampa = orden_arranque and tension_filtrada < 0.9 and not fallo_sobrecarga
*/
void ArranqueSuaveMotor_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  tmp10 = 1.0;
  tmp11 = 0.9;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* tension_filtrada STATE(1) */), 0.9, tmp10, tmp11, 0, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* en_rampa DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* orden_arranque variable */) && tmp9) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* fallo_sobrecarga DISCRETE */)));
  TRACE_POP
}

OMC_DISABLE_OPT
int ArranqueSuaveMotor_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ArranqueSuaveMotor_functionLocalKnownVars(data, threadData);
  ArranqueSuaveMotor_eqFunction_12(data, threadData);

  ArranqueSuaveMotor_eqFunction_13(data, threadData);

  ArranqueSuaveMotor_eqFunction_14(data, threadData);

  ArranqueSuaveMotor_eqFunction_15(data, threadData);

  ArranqueSuaveMotor_eqFunction_16(data, threadData);

  ArranqueSuaveMotor_eqFunction_17(data, threadData);

  ArranqueSuaveMotor_eqFunction_18(data, threadData);

  ArranqueSuaveMotor_eqFunction_19(data, threadData);

  ArranqueSuaveMotor_eqFunction_20(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ArranqueSuaveMotor_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void ArranqueSuaveMotor_eqFunction_14(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_15(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_16(DATA* data, threadData_t *threadData);
extern void ArranqueSuaveMotor_eqFunction_17(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    ArranqueSuaveMotor_eqFunction_14,
    ArranqueSuaveMotor_eqFunction_15,
    ArranqueSuaveMotor_eqFunction_16,
    ArranqueSuaveMotor_eqFunction_17
  };
  
  static const int eqIndices[4] = {
    14,
    15,
    16,
    17
  };
  
  for (id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int ArranqueSuaveMotor_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  ArranqueSuaveMotor_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void ArranqueSuaveMotor_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* rampa STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tension_filtrada STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tiempo_sobrecarga STATE(1) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(rampa) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(tension_filtrada) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(tiempo_sobrecarga) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* carga_motor variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* referencia_rampa variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tension_aplicada variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* en_rampa DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* fallo_sobrecarga DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* motor_en_marcha DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* orden_arranque variable */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ArranqueSuaveMotor_12jac.h"
#include "ArranqueSuaveMotor_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ArranqueSuaveMotor_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ArranqueSuaveMotor_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ArranqueSuaveMotor_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ArranqueSuaveMotor_initializeDAEmodeData,
   ArranqueSuaveMotor_computeVarIndices,
   ArranqueSuaveMotor_functionODE,
   ArranqueSuaveMotor_functionAlgebraics,
   ArranqueSuaveMotor_functionDAE,
   ArranqueSuaveMotor_functionLocalKnownVars,
   ArranqueSuaveMotor_input_function,
   ArranqueSuaveMotor_input_function_init,
   ArranqueSuaveMotor_input_function_updateStartValues,
   ArranqueSuaveMotor_data_function,
   ArranqueSuaveMotor_output_function,
   ArranqueSuaveMotor_setc_function,
   ArranqueSuaveMotor_setb_function,
   ArranqueSuaveMotor_function_storeDelayed,
   ArranqueSuaveMotor_function_storeSpatialDistribution,
   ArranqueSuaveMotor_function_initSpatialDistribution,
   ArranqueSuaveMotor_updateBoundVariableAttributes,
   ArranqueSuaveMotor_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   ArranqueSuaveMotor_functionRemovedInitialEquations,
   ArranqueSuaveMotor_updateBoundParameters,
   ArranqueSuaveMotor_checkForAsserts,
   ArranqueSuaveMotor_function_ZeroCrossingsEquations,
   ArranqueSuaveMotor_function_ZeroCrossings,
   ArranqueSuaveMotor_function_updateRelations,
   ArranqueSuaveMotor_zeroCrossingDescription,
   ArranqueSuaveMotor_relationDescription,
   ArranqueSuaveMotor_function_initSample,
   ArranqueSuaveMotor_INDEX_JAC_A,
   ArranqueSuaveMotor_INDEX_JAC_B,
   ArranqueSuaveMotor_INDEX_JAC_C,
   ArranqueSuaveMotor_INDEX_JAC_D,
   ArranqueSuaveMotor_INDEX_JAC_F,
   ArranqueSuaveMotor_INDEX_JAC_H,
   ArranqueSuaveMotor_initialAnalyticJacobianA,
   ArranqueSuaveMotor_initialAnalyticJacobianB,
   ArranqueSuaveMotor_initialAnalyticJacobianC,
   ArranqueSuaveMotor_initialAnalyticJacobianD,
   ArranqueSuaveMotor_initialAnalyticJacobianF,
   ArranqueSuaveMotor_initialAnalyticJacobianH,
   ArranqueSuaveMotor_functionJacA_column,
   ArranqueSuaveMotor_functionJacB_column,
   ArranqueSuaveMotor_functionJacC_column,
   ArranqueSuaveMotor_functionJacD_column,
   ArranqueSuaveMotor_functionJacF_column,
   ArranqueSuaveMotor_functionJacH_column,
   ArranqueSuaveMotor_linear_model_frame,
   ArranqueSuaveMotor_linear_model_datarecovery_frame,
   ArranqueSuaveMotor_mayer,
   ArranqueSuaveMotor_lagrange,
   ArranqueSuaveMotor_pickUpBoundsForInputsInOptimization,
   ArranqueSuaveMotor_setInputData,
   ArranqueSuaveMotor_getTimeGrid,
   ArranqueSuaveMotor_symbolicInlineSystem,
   ArranqueSuaveMotor_function_initSynchronous,
   ArranqueSuaveMotor_function_updateSynchronous,
   ArranqueSuaveMotor_function_equationsSynchronous,
   ArranqueSuaveMotor_inputNames,
   ArranqueSuaveMotor_dataReconciliationInputNames,
   ArranqueSuaveMotor_dataReconciliationUnmeasuredVariables,
   ArranqueSuaveMotor_read_simulation_info,
   ArranqueSuaveMotor_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_1_name_data "Complex"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,7,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,79,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "Modelica"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,8,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,80,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,16,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,88,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,10,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,80,_OMC_LIT_RESOURCE_4_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,10,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir)}};
void ArranqueSuaveMotor_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ArranqueSuaveMotor_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ArranqueSuaveMotor";
  data->modelData->modelFilePrefix = "ArranqueSuaveMotor";
  data->modelData->modelFileName = "ArranqueSuaveMotor.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ArranqueSuaveMotor";
  data->modelData->modelGUID = "{9b76140e-9465-4bfc-ae96-7c5a06fa5352}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ArranqueSuaveMotor_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 3;
  data->modelData->nVariablesRealArray = 10;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 4;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 4;
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
  data->modelData->nRelations = 4;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 21;
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

