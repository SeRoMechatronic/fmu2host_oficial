/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "BooleanLogica_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int BooleanLogica_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* umbral variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int BooleanLogica_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[0].attribute.start;
  
  TRACE_POP
  return 0;
}

int BooleanLogica_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[0].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int BooleanLogica_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->booleanVarsData[1].info.name;
  names[1] = (char *) data->modelData->booleanVarsData[3].info.name;
  names[2] = (char *) data->modelData->booleanVarsData[4].info.name;
  names[3] = (char *) data->modelData->realVarsData[0].info.name;
  
  TRACE_POP
  return 0;
}

int BooleanLogica_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int BooleanLogica_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int BooleanLogica_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int BooleanLogica_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int BooleanLogica_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int BooleanLogica_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 13
type: SIMPLE_ASSIGN
above_threshold = umbral > 0.5
*/
void BooleanLogica_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = 0.5;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* umbral variable */), 0.5, tmp1, tmp2, 0, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* above_threshold DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 14
type: SIMPLE_ASSIGN
$whenCondition1 = false
*/
void BooleanLogica_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = 0 /* false */;
  TRACE_POP
}
/*
equation index: 15
type: WHEN

when {$whenCondition1} then
  latch = a;
end when;
*/
void BooleanLogica_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* latch DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* a variable */);
  }
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
y_latch = latch
*/
void BooleanLogica_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* y_latch DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* latch DISCRETE */);
  TRACE_POP
}
/*
equation index: 17
type: WHEN

when {$whenCondition1} then
  flancos = 1 + pre(flancos);
end when;
*/
void BooleanLogica_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* flancos DISCRETE */) = ((modelica_integer) 1) + (data->simulationInfo->integerVarsPre[1] /* flancos DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
cuenta_flancos = flancos
*/
void BooleanLogica_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* cuenta_flancos DISCRETE */) = (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* flancos DISCRETE */);
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
y_xor = (a or b) and not (a and b)
*/
void BooleanLogica_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* y_xor DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* a variable */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* b variable */)) && (!((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* a variable */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* b variable */))));
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
y_or = a or b
*/
void BooleanLogica_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* y_or DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* a variable */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* b variable */));
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
y_and = a and b
*/
void BooleanLogica_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* y_and DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* a variable */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* b variable */));
  TRACE_POP
}

OMC_DISABLE_OPT
int BooleanLogica_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  BooleanLogica_functionLocalKnownVars(data, threadData);
  BooleanLogica_eqFunction_13(data, threadData);

  BooleanLogica_eqFunction_14(data, threadData);

  BooleanLogica_eqFunction_15(data, threadData);

  BooleanLogica_eqFunction_16(data, threadData);

  BooleanLogica_eqFunction_17(data, threadData);

  BooleanLogica_eqFunction_18(data, threadData);

  BooleanLogica_eqFunction_19(data, threadData);

  BooleanLogica_eqFunction_20(data, threadData);

  BooleanLogica_eqFunction_21(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int BooleanLogica_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int BooleanLogica_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  BooleanLogica_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void BooleanLogica_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* umbral variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* cuenta_flancos DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* flancos DISCRETE */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition1 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* a variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* above_threshold DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* b variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* clk variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* latch DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* y_and DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* y_latch DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* y_or DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* y_xor DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "BooleanLogica_12jac.h"
#include "BooleanLogica_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks BooleanLogica_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   BooleanLogica_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   BooleanLogica_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   BooleanLogica_initializeDAEmodeData,
   BooleanLogica_computeVarIndices,
   BooleanLogica_functionODE,
   BooleanLogica_functionAlgebraics,
   BooleanLogica_functionDAE,
   BooleanLogica_functionLocalKnownVars,
   BooleanLogica_input_function,
   BooleanLogica_input_function_init,
   BooleanLogica_input_function_updateStartValues,
   BooleanLogica_data_function,
   BooleanLogica_output_function,
   BooleanLogica_setc_function,
   BooleanLogica_setb_function,
   BooleanLogica_function_storeDelayed,
   BooleanLogica_function_storeSpatialDistribution,
   BooleanLogica_function_initSpatialDistribution,
   BooleanLogica_updateBoundVariableAttributes,
   BooleanLogica_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   BooleanLogica_functionRemovedInitialEquations,
   BooleanLogica_updateBoundParameters,
   BooleanLogica_checkForAsserts,
   BooleanLogica_function_ZeroCrossingsEquations,
   BooleanLogica_function_ZeroCrossings,
   BooleanLogica_function_updateRelations,
   BooleanLogica_zeroCrossingDescription,
   BooleanLogica_relationDescription,
   BooleanLogica_function_initSample,
   BooleanLogica_INDEX_JAC_A,
   BooleanLogica_INDEX_JAC_B,
   BooleanLogica_INDEX_JAC_C,
   BooleanLogica_INDEX_JAC_D,
   BooleanLogica_INDEX_JAC_F,
   BooleanLogica_INDEX_JAC_H,
   BooleanLogica_initialAnalyticJacobianA,
   BooleanLogica_initialAnalyticJacobianB,
   BooleanLogica_initialAnalyticJacobianC,
   BooleanLogica_initialAnalyticJacobianD,
   BooleanLogica_initialAnalyticJacobianF,
   BooleanLogica_initialAnalyticJacobianH,
   BooleanLogica_functionJacA_column,
   BooleanLogica_functionJacB_column,
   BooleanLogica_functionJacC_column,
   BooleanLogica_functionJacD_column,
   BooleanLogica_functionJacF_column,
   BooleanLogica_functionJacH_column,
   BooleanLogica_linear_model_frame,
   BooleanLogica_linear_model_datarecovery_frame,
   BooleanLogica_mayer,
   BooleanLogica_lagrange,
   BooleanLogica_pickUpBoundsForInputsInOptimization,
   BooleanLogica_setInputData,
   BooleanLogica_getTimeGrid,
   BooleanLogica_symbolicInlineSystem,
   BooleanLogica_function_initSynchronous,
   BooleanLogica_function_updateSynchronous,
   BooleanLogica_function_equationsSynchronous,
   BooleanLogica_inputNames,
   BooleanLogica_dataReconciliationInputNames,
   BooleanLogica_dataReconciliationUnmeasuredVariables,
   BooleanLogica_read_simulation_info,
   BooleanLogica_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_1_name_data "ArraysVectores"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ArraysVectores"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,14,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,84,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "BooleanLogica"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/BooleanLogica"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,13,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,83,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "CSPuro_SinME"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,12,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,77,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "CTPID"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CTPID"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,5,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,75,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "CodigoErrorDiagnostico"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,22,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,92,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "Complex"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,7,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,79,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "ContadorEventos"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,15,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,85,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "CrecimientoPoblacional"
#define _OMC_LIT_RESOURCE_8_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CrecimientoPoblacional"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,22,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,92,_OMC_LIT_RESOURCE_8_dir_data);

#define _OMC_LIT_RESOURCE_9_name_data "CuerposAcoplados"
#define _OMC_LIT_RESOURCE_9_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CuerposAcoplados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,16,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,86,_OMC_LIT_RESOURCE_9_dir_data);

#define _OMC_LIT_RESOURCE_10_name_data "EtapaSecuenciador"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/EtapaSecuenciador"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,17,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,87,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "FrenadoABS"
#define _OMC_LIT_RESOURCE_11_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/FrenadoABS"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,10,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,80,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "Mi_Modelo_Nuevo"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/Mi_Modelo_Nuevo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,15,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,85,_OMC_LIT_RESOURCE_12_dir_data);

#define _OMC_LIT_RESOURCE_13_name_data "Modelica"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,8,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,80,_OMC_LIT_RESOURCE_13_dir_data);

#define _OMC_LIT_RESOURCE_14_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_14_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_name,16,_OMC_LIT_RESOURCE_14_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir,88,_OMC_LIT_RESOURCE_14_dir_data);

#define _OMC_LIT_RESOURCE_15_name_data "MuchosEstados"
#define _OMC_LIT_RESOURCE_15_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MuchosEstados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_name,13,_OMC_LIT_RESOURCE_15_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir,83,_OMC_LIT_RESOURCE_15_dir_data);

#define _OMC_LIT_RESOURCE_16_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_16_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_name,18,_OMC_LIT_RESOURCE_16_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir,88,_OMC_LIT_RESOURCE_16_dir_data);

#define _OMC_LIT_RESOURCE_17_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_17_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_name,13,_OMC_LIT_RESOURCE_17_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir,83,_OMC_LIT_RESOURCE_17_dir_data);

#define _OMC_LIT_RESOURCE_18_name_data "OsciladorArmonico"
#define _OMC_LIT_RESOURCE_18_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/OsciladorArmonico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_name,17,_OMC_LIT_RESOURCE_18_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir,87,_OMC_LIT_RESOURCE_18_dir_data);

#define _OMC_LIT_RESOURCE_19_name_data "PenduloNoLineal"
#define _OMC_LIT_RESOURCE_19_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PenduloNoLineal"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_name,15,_OMC_LIT_RESOURCE_19_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir,85,_OMC_LIT_RESOURCE_19_dir_data);

#define _OMC_LIT_RESOURCE_20_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_20_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_name,10,_OMC_LIT_RESOURCE_20_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir,80,_OMC_LIT_RESOURCE_20_dir_data);

#define _OMC_LIT_RESOURCE_21_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_21_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_name,16,_OMC_LIT_RESOURCE_21_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir,86,_OMC_LIT_RESOURCE_21_dir_data);

#define _OMC_LIT_RESOURCE_22_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_22_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_name,12,_OMC_LIT_RESOURCE_22_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir,82,_OMC_LIT_RESOURCE_22_dir_data);

#define _OMC_LIT_RESOURCE_23_name_data "SinInputs"
#define _OMC_LIT_RESOURCE_23_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SinInputs"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_name,9,_OMC_LIT_RESOURCE_23_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir,79,_OMC_LIT_RESOURCE_23_dir_data);

#define _OMC_LIT_RESOURCE_24_name_data "SistemaLorenz"
#define _OMC_LIT_RESOURCE_24_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SistemaLorenz"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_24_name,13,_OMC_LIT_RESOURCE_24_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_24_dir,83,_OMC_LIT_RESOURCE_24_dir_data);

#define _OMC_LIT_RESOURCE_25_name_data "StringInputOutput"
#define _OMC_LIT_RESOURCE_25_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_25_name,17,_OMC_LIT_RESOURCE_25_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_25_dir,87,_OMC_LIT_RESOURCE_25_dir_data);

#define _OMC_LIT_RESOURCE_26_name_data "SuspensionActiva"
#define _OMC_LIT_RESOURCE_26_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SuspensionActiva"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_26_name,16,_OMC_LIT_RESOURCE_26_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_26_dir,86,_OMC_LIT_RESOURCE_26_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,54,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_24_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_24_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_25_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_25_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_26_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_26_dir)}};
void BooleanLogica_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &BooleanLogica_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "BooleanLogica";
  data->modelData->modelFilePrefix = "BooleanLogica";
  data->modelData->modelFileName = "BooleanLogica.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/BooleanLogica";
  data->modelData->modelGUID = "{c2452a7d-230b-4fd7-9fca-37ef7e949ad6}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/BooleanLogica_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 1;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 2;
  data->modelData->nVariablesBooleanArray = 10;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 4;
  data->modelData->nOutputVars = 6;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 1;
  data->modelData->nAliasBoolean = 5;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 2;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 1;
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

