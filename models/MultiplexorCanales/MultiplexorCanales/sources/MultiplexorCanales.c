/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "MultiplexorCanales_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int MultiplexorCanales_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* canal_0 variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* canal_1 variable */) = data->simulationInfo->inputVars[1];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* canal_2 variable */) = data->simulationInfo->inputVars[2];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* canal_3 variable */) = data->simulationInfo->inputVars[3];
  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[0].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[1].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[2].attribute.start;
  data->simulationInfo->inputVars[3] = data->modelData->realVarsData[3].attribute.start;
  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[0].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[1].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[2].attribute.start = data->simulationInfo->inputVars[2];
  data->modelData->realVarsData[3].attribute.start = data->simulationInfo->inputVars[3];
  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[0].info.name;
  names[1] = (char *) data->modelData->realVarsData[1].info.name;
  names[2] = (char *) data->modelData->realVarsData[2].info.name;
  names[3] = (char *) data->modelData->realVarsData[3].info.name;
  names[4] = (char *) data->modelData->integerVarsData[1].info.name;
  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int MultiplexorCanales_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* salida variable */);
  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 4
type: SIMPLE_ASSIGN
canal_valido = canal_seleccion >= 0 and canal_seleccion <= 3
*/
void MultiplexorCanales_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  relation(data, &tmp0, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */), ((modelica_integer) 0), 0, GreaterEq);
  relation(data, &tmp1, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */), ((modelica_integer) 3), 1, LessEq);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* canal_valido DISCRETE */) = (tmp0 && tmp1);
  TRACE_POP
}
/*
equation index: 5
type: SIMPLE_ASSIGN
canal_activo = if canal_seleccion >= 0 and canal_seleccion <= 3 then canal_seleccion else -1
*/
void MultiplexorCanales_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  relation(data, &tmp2, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */), ((modelica_integer) 0), 0, GreaterEq);
  relation(data, &tmp3, (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */), ((modelica_integer) 3), 1, LessEq);
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* canal_activo DISCRETE */) = ((tmp2 && tmp3)?(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */):((modelica_integer) -1));
  TRACE_POP
}
/*
equation index: 6
type: SIMPLE_ASSIGN
salida = if canal_seleccion == 0 then canal_0 else if canal_seleccion == 1 then canal_1 else if canal_seleccion == 2 then canal_2 else if canal_seleccion == 3 then canal_3 else 0.0
*/
void MultiplexorCanales_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* salida variable */) = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 0))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* canal_0 variable */):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 1))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* canal_1 variable */):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 2))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* canal_2 variable */):(((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 3))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* canal_3 variable */):0.0))));
  TRACE_POP
}

OMC_DISABLE_OPT
int MultiplexorCanales_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  MultiplexorCanales_functionLocalKnownVars(data, threadData);
  MultiplexorCanales_eqFunction_4(data, threadData);

  MultiplexorCanales_eqFunction_5(data, threadData);

  MultiplexorCanales_eqFunction_6(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int MultiplexorCanales_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int MultiplexorCanales_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  MultiplexorCanales_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void MultiplexorCanales_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* canal_0 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* canal_1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* canal_2 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* canal_3 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* salida variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* canal_activo DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* canal_seleccion variable */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* canal_valido DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "MultiplexorCanales_12jac.h"
#include "MultiplexorCanales_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks MultiplexorCanales_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   MultiplexorCanales_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   MultiplexorCanales_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   MultiplexorCanales_initializeDAEmodeData,
   MultiplexorCanales_computeVarIndices,
   MultiplexorCanales_functionODE,
   MultiplexorCanales_functionAlgebraics,
   MultiplexorCanales_functionDAE,
   MultiplexorCanales_functionLocalKnownVars,
   MultiplexorCanales_input_function,
   MultiplexorCanales_input_function_init,
   MultiplexorCanales_input_function_updateStartValues,
   MultiplexorCanales_data_function,
   MultiplexorCanales_output_function,
   MultiplexorCanales_setc_function,
   MultiplexorCanales_setb_function,
   MultiplexorCanales_function_storeDelayed,
   MultiplexorCanales_function_storeSpatialDistribution,
   MultiplexorCanales_function_initSpatialDistribution,
   MultiplexorCanales_updateBoundVariableAttributes,
   MultiplexorCanales_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   MultiplexorCanales_functionRemovedInitialEquations,
   MultiplexorCanales_updateBoundParameters,
   MultiplexorCanales_checkForAsserts,
   MultiplexorCanales_function_ZeroCrossingsEquations,
   MultiplexorCanales_function_ZeroCrossings,
   MultiplexorCanales_function_updateRelations,
   MultiplexorCanales_zeroCrossingDescription,
   MultiplexorCanales_relationDescription,
   MultiplexorCanales_function_initSample,
   MultiplexorCanales_INDEX_JAC_A,
   MultiplexorCanales_INDEX_JAC_B,
   MultiplexorCanales_INDEX_JAC_C,
   MultiplexorCanales_INDEX_JAC_D,
   MultiplexorCanales_INDEX_JAC_F,
   MultiplexorCanales_INDEX_JAC_H,
   MultiplexorCanales_initialAnalyticJacobianA,
   MultiplexorCanales_initialAnalyticJacobianB,
   MultiplexorCanales_initialAnalyticJacobianC,
   MultiplexorCanales_initialAnalyticJacobianD,
   MultiplexorCanales_initialAnalyticJacobianF,
   MultiplexorCanales_initialAnalyticJacobianH,
   MultiplexorCanales_functionJacA_column,
   MultiplexorCanales_functionJacB_column,
   MultiplexorCanales_functionJacC_column,
   MultiplexorCanales_functionJacD_column,
   MultiplexorCanales_functionJacF_column,
   MultiplexorCanales_functionJacH_column,
   MultiplexorCanales_linear_model_frame,
   MultiplexorCanales_linear_model_datarecovery_frame,
   MultiplexorCanales_mayer,
   MultiplexorCanales_lagrange,
   MultiplexorCanales_pickUpBoundsForInputsInOptimization,
   MultiplexorCanales_setInputData,
   MultiplexorCanales_getTimeGrid,
   MultiplexorCanales_symbolicInlineSystem,
   MultiplexorCanales_function_initSynchronous,
   MultiplexorCanales_function_updateSynchronous,
   MultiplexorCanales_function_equationsSynchronous,
   MultiplexorCanales_inputNames,
   MultiplexorCanales_dataReconciliationInputNames,
   MultiplexorCanales_dataReconciliationUnmeasuredVariables,
   MultiplexorCanales_read_simulation_info,
   MultiplexorCanales_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_10_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,10,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,80,_OMC_LIT_RESOURCE_10_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,22,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir)}};
void MultiplexorCanales_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &MultiplexorCanales_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "MultiplexorCanales";
  data->modelData->modelFilePrefix = "MultiplexorCanales";
  data->modelData->modelFileName = "MultiplexorCanales.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales";
  data->modelData->modelGUID = "{dcf0a32f-6203-4553-8a23-9c7afeb44655}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/MultiplexorCanales_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 5;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 2;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 5;
  data->modelData->nOutputVars = 3;
  data->modelData->nAliasReal = 1;
  data->modelData->nAliasInteger = 1;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 7;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 6;
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

