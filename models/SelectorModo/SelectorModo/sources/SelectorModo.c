/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "SelectorModo_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int SelectorModo_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* consigna_manual variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int SelectorModo_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[0].attribute.start;
  
  TRACE_POP
  return 0;
}

int SelectorModo_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[0].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int SelectorModo_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[0].info.name;
  names[1] = (char *) data->modelData->integerVarsData[1].info.name;
  
  TRACE_POP
  return 0;
}

int SelectorModo_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int SelectorModo_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SelectorModo_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SelectorModo_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* salida_actuador variable */);
  
  TRACE_POP
  return 0;
}

int SelectorModo_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SelectorModo_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 4
type: SIMPLE_ASSIGN
fallo_modo = modo_operacion < MODO_MANUAL or modo_operacion > MODO_EMERGENCIA
*/
void SelectorModo_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  relation(data, &tmp0, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */), (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */), 0, Less);
  relation(data, &tmp1, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */), (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */), 1, Greater);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* fallo_modo DISCRETE */) = (tmp0 || tmp1);
  TRACE_POP
}
/*
equation index: 5
type: SIMPLE_ASSIGN
codigo_estado = if modo_operacion == MODO_EMERGENCIA then 99 else if modo_operacion == MODO_AUTO then 10 else if modo_operacion == MODO_MANUAL then 1 else -1
*/
void SelectorModo_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* codigo_estado DISCRETE */) = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[1] /* MODO_EMERGENCIA PARAM */))?((modelica_integer) 99):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[0] /* MODO_AUTO PARAM */))?((modelica_integer) 10):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */))?((modelica_integer) 1):((modelica_integer) -1))));
  TRACE_POP
}
/*
equation index: 6
type: SIMPLE_ASSIGN
salida_actuador = if modo_operacion == MODO_MANUAL then min(1.0, max(0.0, consigna_manual)) else if modo_operacion == MODO_AUTO then 0.5 else 0.0
*/
void SelectorModo_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* salida_actuador variable */) = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[2] /* MODO_MANUAL PARAM */))?fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* consigna_manual variable */))):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* modo_operacion variable */) == (data->simulationInfo->integerParameter[0] /* MODO_AUTO PARAM */))?0.5:0.0));
  TRACE_POP
}

OMC_DISABLE_OPT
int SelectorModo_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  SelectorModo_functionLocalKnownVars(data, threadData);
  SelectorModo_eqFunction_4(data, threadData);

  SelectorModo_eqFunction_5(data, threadData);

  SelectorModo_eqFunction_6(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int SelectorModo_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int SelectorModo_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  SelectorModo_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void SelectorModo_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  
  /* derivativeVars */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* consigna_manual variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* salida_actuador variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* codigo_estado DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* modo_operacion variable */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* fallo_modo DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "SelectorModo_12jac.h"
#include "SelectorModo_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks SelectorModo_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   SelectorModo_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   SelectorModo_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   SelectorModo_initializeDAEmodeData,
   SelectorModo_computeVarIndices,
   SelectorModo_functionODE,
   SelectorModo_functionAlgebraics,
   SelectorModo_functionDAE,
   SelectorModo_functionLocalKnownVars,
   SelectorModo_input_function,
   SelectorModo_input_function_init,
   SelectorModo_input_function_updateStartValues,
   SelectorModo_data_function,
   SelectorModo_output_function,
   SelectorModo_setc_function,
   SelectorModo_setb_function,
   SelectorModo_function_storeDelayed,
   SelectorModo_function_storeSpatialDistribution,
   SelectorModo_function_initSpatialDistribution,
   SelectorModo_updateBoundVariableAttributes,
   SelectorModo_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   SelectorModo_functionRemovedInitialEquations,
   SelectorModo_updateBoundParameters,
   SelectorModo_checkForAsserts,
   SelectorModo_function_ZeroCrossingsEquations,
   SelectorModo_function_ZeroCrossings,
   SelectorModo_function_updateRelations,
   SelectorModo_zeroCrossingDescription,
   SelectorModo_relationDescription,
   SelectorModo_function_initSample,
   SelectorModo_INDEX_JAC_A,
   SelectorModo_INDEX_JAC_B,
   SelectorModo_INDEX_JAC_C,
   SelectorModo_INDEX_JAC_D,
   SelectorModo_INDEX_JAC_F,
   SelectorModo_INDEX_JAC_H,
   SelectorModo_initialAnalyticJacobianA,
   SelectorModo_initialAnalyticJacobianB,
   SelectorModo_initialAnalyticJacobianC,
   SelectorModo_initialAnalyticJacobianD,
   SelectorModo_initialAnalyticJacobianF,
   SelectorModo_initialAnalyticJacobianH,
   SelectorModo_functionJacA_column,
   SelectorModo_functionJacB_column,
   SelectorModo_functionJacC_column,
   SelectorModo_functionJacD_column,
   SelectorModo_functionJacF_column,
   SelectorModo_functionJacH_column,
   SelectorModo_linear_model_frame,
   SelectorModo_linear_model_datarecovery_frame,
   SelectorModo_mayer,
   SelectorModo_lagrange,
   SelectorModo_pickUpBoundsForInputsInOptimization,
   SelectorModo_setInputData,
   SelectorModo_getTimeGrid,
   SelectorModo_symbolicInlineSystem,
   SelectorModo_function_initSynchronous,
   SelectorModo_function_updateSynchronous,
   SelectorModo_function_equationsSynchronous,
   SelectorModo_inputNames,
   SelectorModo_dataReconciliationInputNames,
   SelectorModo_dataReconciliationUnmeasuredVariables,
   SelectorModo_read_simulation_info,
   SelectorModo_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_13_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,12,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,82,_OMC_LIT_RESOURCE_13_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,28,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir)}};
void SelectorModo_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &SelectorModo_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "SelectorModo";
  data->modelData->modelFilePrefix = "SelectorModo";
  data->modelData->modelFileName = "SelectorModo.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo";
  data->modelData->modelGUID = "{1a2b3f1f-16f4-4130-bc9c-3c8938410178}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/SelectorModo_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 2;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 2;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 3;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 2;
  data->modelData->nOutputVars = 3;
  data->modelData->nAliasReal = 1;
  data->modelData->nAliasInteger = 1;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 4;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 5;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 7;
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

