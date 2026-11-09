/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "CodigoErrorDiagnostico_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int CodigoErrorDiagnostico_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* temperatura variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tension variable */) = data->simulationInfo->inputVars[1];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* vibracion variable */) = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[1].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[2].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[3].attribute.start;
  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[1].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[2].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[3].attribute.start = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[1].info.name;
  names[1] = (char *) data->modelData->realVarsData[2].info.name;
  names[2] = (char *) data->modelData->realVarsData[3].info.name;
  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* factor_reduccion variable */);
  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CodigoErrorDiagnostico_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 5
type: SIMPLE_ASSIGN
codigo_error = if temperatura > umbral_temperatura then 101 else if tension < umbral_tension then 202 else if vibracion > umbral_vibracion then 303 else 0
*/
void CodigoErrorDiagnostico_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
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
  modelica_integer tmp10;
  modelica_boolean tmp11;
  modelica_integer tmp12;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[0] /* umbral_temperatura PARAM */));
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* temperatura variable */), (data->simulationInfo->realParameter[0] /* umbral_temperatura PARAM */), tmp1, tmp2, 0, Greater, GreaterZC);
  tmp11 = (modelica_boolean)tmp0;
  if(tmp11)
  {
    tmp12 = ((modelica_integer) 101);
  }
  else
  {
    tmp4 = 1.0;
    tmp5 = fabs((data->simulationInfo->realParameter[1] /* umbral_tension PARAM */));
    relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* tension variable */), (data->simulationInfo->realParameter[1] /* umbral_tension PARAM */), tmp4, tmp5, 1, Less, LessZC);
    tmp9 = (modelica_boolean)tmp3;
    if(tmp9)
    {
      tmp10 = ((modelica_integer) 202);
    }
    else
    {
      tmp7 = 1.0;
      tmp8 = fabs((data->simulationInfo->realParameter[2] /* umbral_vibracion PARAM */));
      relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* vibracion variable */), (data->simulationInfo->realParameter[2] /* umbral_vibracion PARAM */), tmp7, tmp8, 2, Greater, GreaterZC);
      tmp10 = (tmp6?((modelica_integer) 303):((modelica_integer) 0));
    }
    tmp12 = tmp10;
  }
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* codigo_error DISCRETE */) = tmp12;
  TRACE_POP
}
/*
equation index: 6
type: SIMPLE_ASSIGN
nivel_prioridad = if codigo_error == 101 then 3 else if codigo_error == 202 then 2 else if codigo_error == 303 then 1 else 0
*/
void CodigoErrorDiagnostico_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* nivel_prioridad DISCRETE */) = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* codigo_error DISCRETE */) == ((modelica_integer) 101))?((modelica_integer) 3):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* codigo_error DISCRETE */) == ((modelica_integer) 202))?((modelica_integer) 2):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* codigo_error DISCRETE */) == ((modelica_integer) 303))?((modelica_integer) 1):((modelica_integer) 0))));
  TRACE_POP
}
/*
equation index: 7
type: SIMPLE_ASSIGN
parada_emergencia = nivel_prioridad >= 3
*/
void CodigoErrorDiagnostico_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  modelica_boolean tmp13;
  tmp13 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* nivel_prioridad DISCRETE */),((modelica_integer) 3));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* parada_emergencia DISCRETE */) = tmp13;
  TRACE_POP
}
/*
equation index: 8
type: SIMPLE_ASSIGN
factor_reduccion = if nivel_prioridad == 0 then 1.0 else if nivel_prioridad == 1 then 0.75 else if nivel_prioridad == 2 then 0.5 else 0.0
*/
void CodigoErrorDiagnostico_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* factor_reduccion variable */) = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* nivel_prioridad DISCRETE */) == ((modelica_integer) 0))?1.0:(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* nivel_prioridad DISCRETE */) == ((modelica_integer) 1))?0.75:(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* nivel_prioridad DISCRETE */) == ((modelica_integer) 2))?0.5:0.0)));
  TRACE_POP
}

OMC_DISABLE_OPT
int CodigoErrorDiagnostico_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  CodigoErrorDiagnostico_functionLocalKnownVars(data, threadData);
  CodigoErrorDiagnostico_eqFunction_5(data, threadData);

  CodigoErrorDiagnostico_eqFunction_6(data, threadData);

  CodigoErrorDiagnostico_eqFunction_7(data, threadData);

  CodigoErrorDiagnostico_eqFunction_8(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int CodigoErrorDiagnostico_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int CodigoErrorDiagnostico_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  CodigoErrorDiagnostico_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void CodigoErrorDiagnostico_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* factor_reduccion variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* temperatura variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tension variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* vibracion variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* codigo_error DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* nivel_prioridad DISCRETE */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* parada_emergencia DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "CodigoErrorDiagnostico_12jac.h"
#include "CodigoErrorDiagnostico_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks CodigoErrorDiagnostico_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   CodigoErrorDiagnostico_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   CodigoErrorDiagnostico_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   CodigoErrorDiagnostico_initializeDAEmodeData,
   CodigoErrorDiagnostico_computeVarIndices,
   CodigoErrorDiagnostico_functionODE,
   CodigoErrorDiagnostico_functionAlgebraics,
   CodigoErrorDiagnostico_functionDAE,
   CodigoErrorDiagnostico_functionLocalKnownVars,
   CodigoErrorDiagnostico_input_function,
   CodigoErrorDiagnostico_input_function_init,
   CodigoErrorDiagnostico_input_function_updateStartValues,
   CodigoErrorDiagnostico_data_function,
   CodigoErrorDiagnostico_output_function,
   CodigoErrorDiagnostico_setc_function,
   CodigoErrorDiagnostico_setb_function,
   CodigoErrorDiagnostico_function_storeDelayed,
   CodigoErrorDiagnostico_function_storeSpatialDistribution,
   CodigoErrorDiagnostico_function_initSpatialDistribution,
   CodigoErrorDiagnostico_updateBoundVariableAttributes,
   CodigoErrorDiagnostico_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   CodigoErrorDiagnostico_functionRemovedInitialEquations,
   CodigoErrorDiagnostico_updateBoundParameters,
   CodigoErrorDiagnostico_checkForAsserts,
   CodigoErrorDiagnostico_function_ZeroCrossingsEquations,
   CodigoErrorDiagnostico_function_ZeroCrossings,
   CodigoErrorDiagnostico_function_updateRelations,
   CodigoErrorDiagnostico_zeroCrossingDescription,
   CodigoErrorDiagnostico_relationDescription,
   CodigoErrorDiagnostico_function_initSample,
   CodigoErrorDiagnostico_INDEX_JAC_A,
   CodigoErrorDiagnostico_INDEX_JAC_B,
   CodigoErrorDiagnostico_INDEX_JAC_C,
   CodigoErrorDiagnostico_INDEX_JAC_D,
   CodigoErrorDiagnostico_INDEX_JAC_F,
   CodigoErrorDiagnostico_INDEX_JAC_H,
   CodigoErrorDiagnostico_initialAnalyticJacobianA,
   CodigoErrorDiagnostico_initialAnalyticJacobianB,
   CodigoErrorDiagnostico_initialAnalyticJacobianC,
   CodigoErrorDiagnostico_initialAnalyticJacobianD,
   CodigoErrorDiagnostico_initialAnalyticJacobianF,
   CodigoErrorDiagnostico_initialAnalyticJacobianH,
   CodigoErrorDiagnostico_functionJacA_column,
   CodigoErrorDiagnostico_functionJacB_column,
   CodigoErrorDiagnostico_functionJacC_column,
   CodigoErrorDiagnostico_functionJacD_column,
   CodigoErrorDiagnostico_functionJacF_column,
   CodigoErrorDiagnostico_functionJacH_column,
   CodigoErrorDiagnostico_linear_model_frame,
   CodigoErrorDiagnostico_linear_model_datarecovery_frame,
   CodigoErrorDiagnostico_mayer,
   CodigoErrorDiagnostico_lagrange,
   CodigoErrorDiagnostico_pickUpBoundsForInputsInOptimization,
   CodigoErrorDiagnostico_setInputData,
   CodigoErrorDiagnostico_getTimeGrid,
   CodigoErrorDiagnostico_symbolicInlineSystem,
   CodigoErrorDiagnostico_function_initSynchronous,
   CodigoErrorDiagnostico_function_updateSynchronous,
   CodigoErrorDiagnostico_function_equationsSynchronous,
   CodigoErrorDiagnostico_inputNames,
   CodigoErrorDiagnostico_dataReconciliationInputNames,
   CodigoErrorDiagnostico_dataReconciliationUnmeasuredVariables,
   CodigoErrorDiagnostico_read_simulation_info,
   CodigoErrorDiagnostico_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_3_name_data "Modelica"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,8,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,80,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,16,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,88,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,10,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,80,_OMC_LIT_RESOURCE_5_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,12,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir)}};
void CodigoErrorDiagnostico_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &CodigoErrorDiagnostico_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "CodigoErrorDiagnostico";
  data->modelData->modelFilePrefix = "CodigoErrorDiagnostico";
  data->modelData->modelFileName = "CodigoErrorDiagnostico.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico";
  data->modelData->modelGUID = "{5d9a5441-4697-4945-99cb-289a15bd1126}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/CodigoErrorDiagnostico_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 4;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 2;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 3;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 3;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 1;
  data->modelData->nAliasInteger = 2;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 3;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 3;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 9;
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

