/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "PotVumetro_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int PotVumetro_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int PotVumetro_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[0].attribute.start;
  
  TRACE_POP
  return 0;
}

int PotVumetro_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[0].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int PotVumetro_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[0].info.name;
  
  TRACE_POP
  return 0;
}

int PotVumetro_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int PotVumetro_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int PotVumetro_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int PotVumetro_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int PotVumetro_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int PotVumetro_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 6
type: SIMPLE_ASSIGN
led5 = pot >= 1.0
*/
void PotVumetro_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = 1.0;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 1.0, tmp1, tmp2, 0, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* led5 DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 7
type: SIMPLE_ASSIGN
led4 = pot >= 0.8
*/
void PotVumetro_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = 1.0;
  tmp5 = 0.8;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.8, tmp4, tmp5, 1, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* led4 DISCRETE */) = tmp3;
  TRACE_POP
}
/*
equation index: 8
type: SIMPLE_ASSIGN
led3 = pot >= 0.6
*/
void PotVumetro_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  tmp7 = 1.0;
  tmp8 = 0.6;
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.6, tmp7, tmp8, 2, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* led3 DISCRETE */) = tmp6;
  TRACE_POP
}
/*
equation index: 9
type: SIMPLE_ASSIGN
led2 = pot >= 0.4
*/
void PotVumetro_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  tmp10 = 1.0;
  tmp11 = 0.4;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.4, tmp10, tmp11, 3, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* led2 DISCRETE */) = tmp9;
  TRACE_POP
}
/*
equation index: 10
type: SIMPLE_ASSIGN
led1 = pot >= 0.2
*/
void PotVumetro_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  tmp13 = 1.0;
  tmp14 = 0.2;
  relationhysteresis(data, &tmp12, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* pot variable */), 0.2, tmp13, tmp14, 4, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* led1 DISCRETE */) = tmp12;
  TRACE_POP
}

OMC_DISABLE_OPT
int PotVumetro_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  PotVumetro_functionLocalKnownVars(data, threadData);
  PotVumetro_eqFunction_6(data, threadData);

  PotVumetro_eqFunction_7(data, threadData);

  PotVumetro_eqFunction_8(data, threadData);

  PotVumetro_eqFunction_9(data, threadData);

  PotVumetro_eqFunction_10(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int PotVumetro_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int PotVumetro_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  PotVumetro_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void PotVumetro_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* pot variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* led1 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* led2 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* led3 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* led4 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* led5 DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "PotVumetro_12jac.h"
#include "PotVumetro_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks PotVumetro_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   PotVumetro_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   PotVumetro_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   PotVumetro_initializeDAEmodeData,
   PotVumetro_computeVarIndices,
   PotVumetro_functionODE,
   PotVumetro_functionAlgebraics,
   PotVumetro_functionDAE,
   PotVumetro_functionLocalKnownVars,
   PotVumetro_input_function,
   PotVumetro_input_function_init,
   PotVumetro_input_function_updateStartValues,
   PotVumetro_data_function,
   PotVumetro_output_function,
   PotVumetro_setc_function,
   PotVumetro_setb_function,
   PotVumetro_function_storeDelayed,
   PotVumetro_function_storeSpatialDistribution,
   PotVumetro_function_initSpatialDistribution,
   PotVumetro_updateBoundVariableAttributes,
   PotVumetro_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   PotVumetro_functionRemovedInitialEquations,
   PotVumetro_updateBoundParameters,
   PotVumetro_checkForAsserts,
   PotVumetro_function_ZeroCrossingsEquations,
   PotVumetro_function_ZeroCrossings,
   PotVumetro_function_updateRelations,
   PotVumetro_zeroCrossingDescription,
   PotVumetro_relationDescription,
   PotVumetro_function_initSample,
   PotVumetro_INDEX_JAC_A,
   PotVumetro_INDEX_JAC_B,
   PotVumetro_INDEX_JAC_C,
   PotVumetro_INDEX_JAC_D,
   PotVumetro_INDEX_JAC_F,
   PotVumetro_INDEX_JAC_H,
   PotVumetro_initialAnalyticJacobianA,
   PotVumetro_initialAnalyticJacobianB,
   PotVumetro_initialAnalyticJacobianC,
   PotVumetro_initialAnalyticJacobianD,
   PotVumetro_initialAnalyticJacobianF,
   PotVumetro_initialAnalyticJacobianH,
   PotVumetro_functionJacA_column,
   PotVumetro_functionJacB_column,
   PotVumetro_functionJacC_column,
   PotVumetro_functionJacD_column,
   PotVumetro_functionJacF_column,
   PotVumetro_functionJacH_column,
   PotVumetro_linear_model_frame,
   PotVumetro_linear_model_datarecovery_frame,
   PotVumetro_mayer,
   PotVumetro_lagrange,
   PotVumetro_pickUpBoundsForInputsInOptimization,
   PotVumetro_setInputData,
   PotVumetro_getTimeGrid,
   PotVumetro_symbolicInlineSystem,
   PotVumetro_function_initSynchronous,
   PotVumetro_function_updateSynchronous,
   PotVumetro_function_equationsSynchronous,
   PotVumetro_inputNames,
   PotVumetro_dataReconciliationInputNames,
   PotVumetro_dataReconciliationUnmeasuredVariables,
   PotVumetro_read_simulation_info,
   PotVumetro_read_input_fmu,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "Complex"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,7,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,79,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "Modelica"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,8,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,80,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,16,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,88,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,10,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,80,_OMC_LIT_RESOURCE_3_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,8,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir)}};
void PotVumetro_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &PotVumetro_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "PotVumetro";
  data->modelData->modelFilePrefix = "PotVumetro";
  data->modelData->modelFileName = "PotVumetro.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro";
  data->modelData->modelGUID = "{ab7bb8fe-cb29-4aff-b8cc-95d1c27f2d3b}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/PotVumetro_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 1;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 5;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 5;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 5;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 5;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 5;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 11;
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

