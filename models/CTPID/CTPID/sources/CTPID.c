/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "CTPID_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int CTPID_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* consigna variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* temperatura variable */) = data->simulationInfo->inputVars[1];
  
  TRACE_POP
  return 0;
}

int CTPID_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[6].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[11].attribute.start;
  
  TRACE_POP
  return 0;
}

int CTPID_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[6].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[11].attribute.start = data->simulationInfo->inputVars[1];
  
  TRACE_POP
  return 0;
}

int CTPID_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[6].info.name;
  names[1] = (char *) data->modelData->realVarsData[11].info.name;
  
  TRACE_POP
  return 0;
}

int CTPID_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int CTPID_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CTPID_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CTPID_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* ventilador variable */);
  
  TRACE_POP
  return 0;
}

int CTPID_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CTPID_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 15
type: SIMPLE_ASSIGN
$DER.consigna_real = 0.0
*/
void CTPID_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* der(consigna_real) DUMMY_DER */) = 0.0;
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
$DER.temperatura_real = 0.0
*/
void CTPID_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(temperatura_real) DUMMY_DER */) = 0.0;
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
derivador = 0.0
*/
void CTPID_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* derivador variable */) = 0.0;
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
$DER.error = 0.0
*/
void CTPID_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(error) DUMMY_DER */) = 0.0;
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
consigna_real = T_min + consigna * (T_max - T_min)
*/
void CTPID_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */) = (data->simulationInfo->realParameter[4] /* T_min PARAM */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* consigna variable */)) * ((data->simulationInfo->realParameter[3] /* T_max PARAM */) - (data->simulationInfo->realParameter[4] /* T_min PARAM */));
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
temperatura_real = T_min + temperatura * (T_max - T_min)
*/
void CTPID_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) = (data->simulationInfo->realParameter[4] /* T_min PARAM */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* temperatura variable */)) * ((data->simulationInfo->realParameter[3] /* T_max PARAM */) - (data->simulationInfo->realParameter[4] /* T_min PARAM */));
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
error = consigna_real - temperatura_real
*/
void CTPID_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */);
  TRACE_POP
}
/*
equation index: 22
type: SIMPLE_ASSIGN
$DER.integrador = error
*/
void CTPID_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* der(integrador) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */);
  TRACE_POP
}
/*
equation index: 23
type: SIMPLE_ASSIGN
pid_raw = Kp * error + Ki * integrador
*/
void CTPID_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pid_raw variable */) = ((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* integrador STATE(1,error) */));
  TRACE_POP
}
/*
equation index: 24
type: SIMPLE_ASSIGN
$cse1 = max(0.0, pid_raw / (T_max - T_min))
*/
void CTPID_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* $cse1 variable */) = fmax(0.0,DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pid_raw variable */),(data->simulationInfo->realParameter[3] /* T_max PARAM */) - (data->simulationInfo->realParameter[4] /* T_min PARAM */),"T_max - T_min",equationIndexes));
  TRACE_POP
}
/*
equation index: 25
type: SIMPLE_ASSIGN
ventilador = min(1.0, $cse1)
*/
void CTPID_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* ventilador variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* $cse1 variable */));
  TRACE_POP
}
/*
equation index: 26
type: SIMPLE_ASSIGN
ledAlcanzado = abs(error) <= epsilon
*/
void CTPID_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  relationhysteresis(data, &tmp0, fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* error DUMMY_STATE */)), (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp1, tmp2, 2, LessEq, LessEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* ledAlcanzado DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 27
type: SIMPLE_ASSIGN
ledPorEncima = consigna_real > temperatura_real + epsilon
*/
void CTPID_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp4 = 1.0;
  tmp5 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) + (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp4, tmp5, 0, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* ledPorEncima DISCRETE */) = tmp3;
  TRACE_POP
}
/*
equation index: 28
type: SIMPLE_ASSIGN
ledPorDebajo = consigna_real < temperatura_real - epsilon
*/
void CTPID_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  tmp7 = 1.0;
  tmp8 = 1.0 + fabs((data->simulationInfo->realParameter[5] /* epsilon PARAM */));
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* consigna_real DUMMY_STATE */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* temperatura_real DUMMY_STATE */) - (data->simulationInfo->realParameter[5] /* epsilon PARAM */), tmp7, tmp8, 1, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* ledPorDebajo DISCRETE */) = tmp6;
  TRACE_POP
}

OMC_DISABLE_OPT
int CTPID_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  CTPID_functionLocalKnownVars(data, threadData);
  CTPID_eqFunction_15(data, threadData);

  CTPID_eqFunction_16(data, threadData);

  CTPID_eqFunction_17(data, threadData);

  CTPID_eqFunction_18(data, threadData);

  CTPID_eqFunction_19(data, threadData);

  CTPID_eqFunction_20(data, threadData);

  CTPID_eqFunction_21(data, threadData);

  CTPID_eqFunction_22(data, threadData);

  CTPID_eqFunction_23(data, threadData);

  CTPID_eqFunction_24(data, threadData);

  CTPID_eqFunction_25(data, threadData);

  CTPID_eqFunction_26(data, threadData);

  CTPID_eqFunction_27(data, threadData);

  CTPID_eqFunction_28(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int CTPID_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void CTPID_eqFunction_19(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_20(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_21(DATA* data, threadData_t *threadData);
extern void CTPID_eqFunction_22(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    CTPID_eqFunction_19,
    CTPID_eqFunction_20,
    CTPID_eqFunction_21,
    CTPID_eqFunction_22
  };
  
  static const int eqIndices[4] = {
    19,
    20,
    21,
    22
  };
  
  for (id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int CTPID_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  CTPID_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void CTPID_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* integrador STATE(1,error) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(integrador) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(consigna_real) DUMMY_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(error) DUMMY_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(temperatura_real) DUMMY_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* consigna variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* consigna_real DUMMY_STATE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* derivador variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* error DUMMY_STATE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* pid_raw variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* temperatura variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* temperatura_real DUMMY_STATE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ventilador variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ledAlcanzado DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ledPorDebajo DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ledPorEncima DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "CTPID_12jac.h"
#include "CTPID_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks CTPID_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   CTPID_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   CTPID_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   CTPID_initializeDAEmodeData,
   CTPID_computeVarIndices,
   CTPID_functionODE,
   CTPID_functionAlgebraics,
   CTPID_functionDAE,
   CTPID_functionLocalKnownVars,
   CTPID_input_function,
   CTPID_input_function_init,
   CTPID_input_function_updateStartValues,
   CTPID_data_function,
   CTPID_output_function,
   CTPID_setc_function,
   CTPID_setb_function,
   CTPID_function_storeDelayed,
   CTPID_function_storeSpatialDistribution,
   CTPID_function_initSpatialDistribution,
   CTPID_updateBoundVariableAttributes,
   CTPID_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   CTPID_functionRemovedInitialEquations,
   CTPID_updateBoundParameters,
   CTPID_checkForAsserts,
   CTPID_function_ZeroCrossingsEquations,
   CTPID_function_ZeroCrossings,
   CTPID_function_updateRelations,
   CTPID_zeroCrossingDescription,
   CTPID_relationDescription,
   CTPID_function_initSample,
   CTPID_INDEX_JAC_A,
   CTPID_INDEX_JAC_B,
   CTPID_INDEX_JAC_C,
   CTPID_INDEX_JAC_D,
   CTPID_INDEX_JAC_F,
   CTPID_INDEX_JAC_H,
   CTPID_initialAnalyticJacobianA,
   CTPID_initialAnalyticJacobianB,
   CTPID_initialAnalyticJacobianC,
   CTPID_initialAnalyticJacobianD,
   CTPID_initialAnalyticJacobianF,
   CTPID_initialAnalyticJacobianH,
   CTPID_functionJacA_column,
   CTPID_functionJacB_column,
   CTPID_functionJacC_column,
   CTPID_functionJacD_column,
   CTPID_functionJacF_column,
   CTPID_functionJacH_column,
   CTPID_linear_model_frame,
   CTPID_linear_model_datarecovery_frame,
   CTPID_mayer,
   CTPID_lagrange,
   CTPID_pickUpBoundsForInputsInOptimization,
   CTPID_setInputData,
   CTPID_getTimeGrid,
   CTPID_symbolicInlineSystem,
   CTPID_function_initSynchronous,
   CTPID_function_updateSynchronous,
   CTPID_function_equationsSynchronous,
   CTPID_inputNames,
   CTPID_dataReconciliationInputNames,
   CTPID_dataReconciliationUnmeasuredVariables,
   CTPID_read_simulation_info,
   CTPID_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_5_name_data "Modelica"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,8,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,80,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,16,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,88,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,10,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,80,_OMC_LIT_RESOURCE_7_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,16,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir)}};
void CTPID_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &CTPID_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "CTPID";
  data->modelData->modelFilePrefix = "CTPID";
  data->modelData->modelFileName = "CTPID.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CTPID";
  data->modelData->modelGUID = "{1e4ce642-3cf9-4c84-8816-d34ec05d4156}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/CTPID_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 1;
  data->modelData->nVariablesRealArray = 14;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 3;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 6;
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
  data->modelData->nRelations = 3;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 29;
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

