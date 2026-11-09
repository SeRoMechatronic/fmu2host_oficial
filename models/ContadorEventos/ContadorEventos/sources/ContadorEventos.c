/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ContadorEventos_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ContadorEventos_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->booleanVarsData[3].info.name;
  names[1] = (char *) data->modelData->booleanVarsData[4].info.name;
  
  TRACE_POP
  return 0;
}

int ContadorEventos_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ContadorEventos_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ContadorEventos_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 10
type: SIMPLE_ASSIGN
$whenCondition1 = false
*/
void ContadorEventos_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = 0 /* false */;
  TRACE_POP
}
/*
equation index: 11
type: SIMPLE_ASSIGN
$whenCondition2 = reset
*/
void ContadorEventos_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* reset variable */);
  TRACE_POP
}
/*
equation index: 12
type: WHEN

when {$whenCondition2, $whenCondition1} then
  contador = if reset then 0 else if pre(contador) >= 99 then 99 else pre(contador) + 1;
end when;
*/
void ContadorEventos_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_integer tmp2;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition2 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    tmp1 = (modelica_boolean)(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* reset variable */);
    if(tmp1)
    {
      tmp2 = ((modelica_integer) 0);
    }
    else
    {
      tmp0 = GreaterEq((data->simulationInfo->integerVarsPre[0] /* contador DISCRETE */),((modelica_integer) 99));
      tmp2 = (tmp0?((modelica_integer) 99):(data->simulationInfo->integerVarsPre[0] /* contador DISCRETE */) + ((modelica_integer) 1));
    }
    (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */) = tmp2;
  }
  TRACE_POP
}
/*
equation index: 13
type: SIMPLE_ASSIGN
desbordamiento = contador >= 99
*/
void ContadorEventos_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  modelica_boolean tmp3;
  tmp3 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */),((modelica_integer) 99));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* desbordamiento DISCRETE */) = tmp3;
  TRACE_POP
}
/*
equation index: 14
type: SIMPLE_ASSIGN
unidades = mod(contador, 10, 0)
*/
void ContadorEventos_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* unidades DISCRETE */) = _event_mod_integer((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */), ((modelica_integer) 10), ((modelica_integer) 0), data, threadData);
  TRACE_POP
}
/*
equation index: 15
type: SIMPLE_ASSIGN
decenas = div(contador, 10, 3)
*/
void ContadorEventos_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* decenas DISCRETE */) = _event_div_integer((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */), ((modelica_integer) 10), ((modelica_integer) 3), data, threadData);
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
cuenta = contador
*/
void ContadorEventos_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* cuenta DISCRETE */) = (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* contador DISCRETE */);
  TRACE_POP
}

OMC_DISABLE_OPT
int ContadorEventos_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ContadorEventos_functionLocalKnownVars(data, threadData);
  ContadorEventos_eqFunction_10(data, threadData);

  ContadorEventos_eqFunction_11(data, threadData);

  ContadorEventos_eqFunction_12(data, threadData);

  ContadorEventos_eqFunction_13(data, threadData);

  ContadorEventos_eqFunction_14(data, threadData);

  ContadorEventos_eqFunction_15(data, threadData);

  ContadorEventos_eqFunction_16(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ContadorEventos_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int ContadorEventos_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  ContadorEventos_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void ContadorEventos_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* contador DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* cuenta DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* decenas DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* unidades DISCRETE */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition1 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition2 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* desbordamiento DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* evento variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* reset variable */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ContadorEventos_12jac.h"
#include "ContadorEventos_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ContadorEventos_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ContadorEventos_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ContadorEventos_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ContadorEventos_initializeDAEmodeData,
   ContadorEventos_computeVarIndices,
   ContadorEventos_functionODE,
   ContadorEventos_functionAlgebraics,
   ContadorEventos_functionDAE,
   ContadorEventos_functionLocalKnownVars,
   ContadorEventos_input_function,
   ContadorEventos_input_function_init,
   ContadorEventos_input_function_updateStartValues,
   ContadorEventos_data_function,
   ContadorEventos_output_function,
   ContadorEventos_setc_function,
   ContadorEventos_setb_function,
   ContadorEventos_function_storeDelayed,
   ContadorEventos_function_storeSpatialDistribution,
   ContadorEventos_function_initSpatialDistribution,
   ContadorEventos_updateBoundVariableAttributes,
   ContadorEventos_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   ContadorEventos_functionRemovedInitialEquations,
   ContadorEventos_updateBoundParameters,
   ContadorEventos_checkForAsserts,
   ContadorEventos_function_ZeroCrossingsEquations,
   ContadorEventos_function_ZeroCrossings,
   ContadorEventos_function_updateRelations,
   ContadorEventos_zeroCrossingDescription,
   ContadorEventos_relationDescription,
   ContadorEventos_function_initSample,
   ContadorEventos_INDEX_JAC_A,
   ContadorEventos_INDEX_JAC_B,
   ContadorEventos_INDEX_JAC_C,
   ContadorEventos_INDEX_JAC_D,
   ContadorEventos_INDEX_JAC_F,
   ContadorEventos_INDEX_JAC_H,
   ContadorEventos_initialAnalyticJacobianA,
   ContadorEventos_initialAnalyticJacobianB,
   ContadorEventos_initialAnalyticJacobianC,
   ContadorEventos_initialAnalyticJacobianD,
   ContadorEventos_initialAnalyticJacobianF,
   ContadorEventos_initialAnalyticJacobianH,
   ContadorEventos_functionJacA_column,
   ContadorEventos_functionJacB_column,
   ContadorEventos_functionJacC_column,
   ContadorEventos_functionJacD_column,
   ContadorEventos_functionJacF_column,
   ContadorEventos_functionJacH_column,
   ContadorEventos_linear_model_frame,
   ContadorEventos_linear_model_datarecovery_frame,
   ContadorEventos_mayer,
   ContadorEventos_lagrange,
   ContadorEventos_pickUpBoundsForInputsInOptimization,
   ContadorEventos_setInputData,
   ContadorEventos_getTimeGrid,
   ContadorEventos_symbolicInlineSystem,
   ContadorEventos_function_initSynchronous,
   ContadorEventos_function_updateSynchronous,
   ContadorEventos_function_equationsSynchronous,
   ContadorEventos_inputNames,
   ContadorEventos_dataReconciliationInputNames,
   ContadorEventos_dataReconciliationUnmeasuredVariables,
   ContadorEventos_read_simulation_info,
   ContadorEventos_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_1_name_data "CodigoErrorDiagnostico"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,22,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,92,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "Complex"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,7,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,79,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "ContadorEventos"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,15,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,85,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "Modelica"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,8,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,80,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,16,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,88,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,10,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,80,_OMC_LIT_RESOURCE_6_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,14,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir)}};
void ContadorEventos_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ContadorEventos_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ContadorEventos";
  data->modelData->modelFilePrefix = "ContadorEventos";
  data->modelData->modelFileName = "ContadorEventos.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos";
  data->modelData->modelGUID = "{74a5f633-cf1b-4cc7-a4bb-0e6d63cf1bac}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ContadorEventos_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 0;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 4;
  data->modelData->nVariablesBooleanArray = 5;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 2;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 3;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 2;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 5;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 17;
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

