/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "CuerposAcoplados_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int CuerposAcoplados_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* fuerza_externa variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[9].attribute.start;
  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[9].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[9].info.name;
  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int CuerposAcoplados_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* energia_total variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pos1 variable */);
  data->simulationInfo->outputVars[2] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* pos2 variable */);
  data->simulationInfo->outputVars[3] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* vel1 variable */);
  data->simulationInfo->outputVars[4] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* vel2 variable */);
  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int CuerposAcoplados_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 15
type: SIMPLE_ASSIGN
en_fase = x1 >= 0.0 and x2 >= 0.0 or x1 < 0.0 and x2 < 0.0
*/
void CuerposAcoplados_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
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
  modelica_real tmp10;
  modelica_real tmp11;
  tmp1 = 1.0;
  tmp2 = 0.0;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */), 0.0, tmp1, tmp2, 0, GreaterEq, GreaterEqZC);
  tmp4 = 1.0;
  tmp5 = 0.0;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */), 0.0, tmp4, tmp5, 1, GreaterEq, GreaterEqZC);
  tmp7 = 1.0;
  tmp8 = 0.0;
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */), 0.0, tmp7, tmp8, 2, Less, LessZC);
  tmp10 = 1.0;
  tmp11 = 0.0;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */), 0.0, tmp10, tmp11, 3, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* en_fase DISCRETE */) = ((tmp0 && tmp3) || (tmp6 && tmp9));
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
energia_total = 0.5 * (m1 * v1 ^ 2.0 + m2 * v2 ^ 2.0 + k1 * x1 ^ 2.0 + k2 * x2 ^ 2.0 + kc * (x1 - x2) ^ 2.0)
*/
void CuerposAcoplados_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  modelica_real tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_real tmp15;
  modelica_real tmp16;
  tmp12 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* v1 STATE(1) */);
  tmp13 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* v2 STATE(1) */);
  tmp14 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */);
  tmp15 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */);
  tmp16 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* energia_total variable */) = (0.5) * (((data->simulationInfo->realParameter[3] /* m1 PARAM */)) * ((tmp12 * tmp12)) + ((data->simulationInfo->realParameter[4] /* m2 PARAM */)) * ((tmp13 * tmp13)) + ((data->simulationInfo->realParameter[0] /* k1 PARAM */)) * ((tmp14 * tmp14)) + ((data->simulationInfo->realParameter[1] /* k2 PARAM */)) * ((tmp15 * tmp15)) + ((data->simulationInfo->realParameter[2] /* kc PARAM */)) * ((tmp16 * tmp16)));
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
$DER.v2 = (kc * x1 + ((-k2) - kc) * x2) / m2
*/
void CuerposAcoplados_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(v2) STATE_DER */) = DIVISION_SIM(((data->simulationInfo->realParameter[2] /* kc PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */)) + ((-(data->simulationInfo->realParameter[1] /* k2 PARAM */)) - (data->simulationInfo->realParameter[2] /* kc PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */)),(data->simulationInfo->realParameter[4] /* m2 PARAM */),"m2",equationIndexes);
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
$DER.v1 = (kc * x2 + ((-k1) - kc) * x1 + fuerza_externa) / m1
*/
void CuerposAcoplados_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(v1) STATE_DER */) = DIVISION_SIM(((data->simulationInfo->realParameter[2] /* kc PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */)) + ((-(data->simulationInfo->realParameter[0] /* k1 PARAM */)) - (data->simulationInfo->realParameter[2] /* kc PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */)) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* fuerza_externa variable */),(data->simulationInfo->realParameter[3] /* m1 PARAM */),"m1",equationIndexes);
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
$DER.x2 = v2
*/
void CuerposAcoplados_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* der(x2) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* v2 STATE(1) */);
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
$DER.x1 = v1
*/
void CuerposAcoplados_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* der(x1) STATE_DER */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* v1 STATE(1) */);
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
vel2 = v2
*/
void CuerposAcoplados_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* vel2 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* v2 STATE(1) */);
  TRACE_POP
}
/*
equation index: 22
type: SIMPLE_ASSIGN
vel1 = v1
*/
void CuerposAcoplados_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* vel1 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* v1 STATE(1) */);
  TRACE_POP
}
/*
equation index: 23
type: SIMPLE_ASSIGN
pos2 = x2
*/
void CuerposAcoplados_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* pos2 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* x2 STATE(1,v2) */);
  TRACE_POP
}
/*
equation index: 24
type: SIMPLE_ASSIGN
pos1 = x1
*/
void CuerposAcoplados_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* pos1 variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* x1 STATE(1,v1) */);
  TRACE_POP
}

OMC_DISABLE_OPT
int CuerposAcoplados_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  CuerposAcoplados_functionLocalKnownVars(data, threadData);
  CuerposAcoplados_eqFunction_15(data, threadData);

  CuerposAcoplados_eqFunction_16(data, threadData);

  CuerposAcoplados_eqFunction_17(data, threadData);

  CuerposAcoplados_eqFunction_18(data, threadData);

  CuerposAcoplados_eqFunction_19(data, threadData);

  CuerposAcoplados_eqFunction_20(data, threadData);

  CuerposAcoplados_eqFunction_21(data, threadData);

  CuerposAcoplados_eqFunction_22(data, threadData);

  CuerposAcoplados_eqFunction_23(data, threadData);

  CuerposAcoplados_eqFunction_24(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int CuerposAcoplados_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void CuerposAcoplados_eqFunction_17(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_18(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_19(DATA* data, threadData_t *threadData);
extern void CuerposAcoplados_eqFunction_20(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    CuerposAcoplados_eqFunction_17,
    CuerposAcoplados_eqFunction_18,
    CuerposAcoplados_eqFunction_19,
    CuerposAcoplados_eqFunction_20
  };
  
  static const int eqIndices[4] = {
    17,
    18,
    19,
    20
  };
  
  for (id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int CuerposAcoplados_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  CuerposAcoplados_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void CuerposAcoplados_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* v1 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* v2 STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x1 STATE(1,v1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x2 STATE(1,v2) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(v1) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(v2) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x1) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x2) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* energia_total variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* fuerza_externa variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* pos1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* pos2 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* vel1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* vel2 variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* en_fase DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "CuerposAcoplados_12jac.h"
#include "CuerposAcoplados_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks CuerposAcoplados_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   CuerposAcoplados_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   CuerposAcoplados_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   CuerposAcoplados_initializeDAEmodeData,
   CuerposAcoplados_computeVarIndices,
   CuerposAcoplados_functionODE,
   CuerposAcoplados_functionAlgebraics,
   CuerposAcoplados_functionDAE,
   CuerposAcoplados_functionLocalKnownVars,
   CuerposAcoplados_input_function,
   CuerposAcoplados_input_function_init,
   CuerposAcoplados_input_function_updateStartValues,
   CuerposAcoplados_data_function,
   CuerposAcoplados_output_function,
   CuerposAcoplados_setc_function,
   CuerposAcoplados_setb_function,
   CuerposAcoplados_function_storeDelayed,
   CuerposAcoplados_function_storeSpatialDistribution,
   CuerposAcoplados_function_initSpatialDistribution,
   CuerposAcoplados_updateBoundVariableAttributes,
   CuerposAcoplados_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   CuerposAcoplados_functionRemovedInitialEquations,
   CuerposAcoplados_updateBoundParameters,
   CuerposAcoplados_checkForAsserts,
   CuerposAcoplados_function_ZeroCrossingsEquations,
   CuerposAcoplados_function_ZeroCrossings,
   CuerposAcoplados_function_updateRelations,
   CuerposAcoplados_zeroCrossingDescription,
   CuerposAcoplados_relationDescription,
   CuerposAcoplados_function_initSample,
   CuerposAcoplados_INDEX_JAC_A,
   CuerposAcoplados_INDEX_JAC_B,
   CuerposAcoplados_INDEX_JAC_C,
   CuerposAcoplados_INDEX_JAC_D,
   CuerposAcoplados_INDEX_JAC_F,
   CuerposAcoplados_INDEX_JAC_H,
   CuerposAcoplados_initialAnalyticJacobianA,
   CuerposAcoplados_initialAnalyticJacobianB,
   CuerposAcoplados_initialAnalyticJacobianC,
   CuerposAcoplados_initialAnalyticJacobianD,
   CuerposAcoplados_initialAnalyticJacobianF,
   CuerposAcoplados_initialAnalyticJacobianH,
   CuerposAcoplados_functionJacA_column,
   CuerposAcoplados_functionJacB_column,
   CuerposAcoplados_functionJacC_column,
   CuerposAcoplados_functionJacD_column,
   CuerposAcoplados_functionJacF_column,
   CuerposAcoplados_functionJacH_column,
   CuerposAcoplados_linear_model_frame,
   CuerposAcoplados_linear_model_datarecovery_frame,
   CuerposAcoplados_mayer,
   CuerposAcoplados_lagrange,
   CuerposAcoplados_pickUpBoundsForInputsInOptimization,
   CuerposAcoplados_setInputData,
   CuerposAcoplados_getTimeGrid,
   CuerposAcoplados_symbolicInlineSystem,
   CuerposAcoplados_function_initSynchronous,
   CuerposAcoplados_function_updateSynchronous,
   CuerposAcoplados_function_equationsSynchronous,
   CuerposAcoplados_inputNames,
   CuerposAcoplados_dataReconciliationInputNames,
   CuerposAcoplados_dataReconciliationUnmeasuredVariables,
   CuerposAcoplados_read_simulation_info,
   CuerposAcoplados_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_1_name_data "CSPuro_SinME"
#define _OMC_LIT_RESOURCE_1_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,12,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,77,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "CTPID"
#define _OMC_LIT_RESOURCE_2_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CTPID"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,5,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,75,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "CodigoErrorDiagnostico"
#define _OMC_LIT_RESOURCE_3_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CodigoErrorDiagnostico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,22,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,92,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "Complex"
#define _OMC_LIT_RESOURCE_4_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Complex 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,7,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,79,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "ContadorEventos"
#define _OMC_LIT_RESOURCE_5_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ContadorEventos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,15,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,85,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "CrecimientoPoblacional"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CrecimientoPoblacional"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,22,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,92,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "CuerposAcoplados"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CuerposAcoplados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,16,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,86,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "EtapaSecuenciador"
#define _OMC_LIT_RESOURCE_8_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/EtapaSecuenciador"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,17,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,87,_OMC_LIT_RESOURCE_8_dir_data);

#define _OMC_LIT_RESOURCE_9_name_data "FrenadoABS"
#define _OMC_LIT_RESOURCE_9_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/FrenadoABS"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,10,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,80,_OMC_LIT_RESOURCE_9_dir_data);

#define _OMC_LIT_RESOURCE_10_name_data "Modelica"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,8,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,80,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_11_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,16,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,88,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,18,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,88,_OMC_LIT_RESOURCE_12_dir_data);

#define _OMC_LIT_RESOURCE_13_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,13,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,83,_OMC_LIT_RESOURCE_13_dir_data);

#define _OMC_LIT_RESOURCE_14_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_14_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_name,10,_OMC_LIT_RESOURCE_14_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir,80,_OMC_LIT_RESOURCE_14_dir_data);

#define _OMC_LIT_RESOURCE_15_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_15_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_name,16,_OMC_LIT_RESOURCE_15_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir,86,_OMC_LIT_RESOURCE_15_dir_data);

#define _OMC_LIT_RESOURCE_16_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_16_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_name,12,_OMC_LIT_RESOURCE_16_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir,82,_OMC_LIT_RESOURCE_16_dir_data);

#define _OMC_LIT_RESOURCE_17_name_data "SuspensionActiva"
#define _OMC_LIT_RESOURCE_17_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SuspensionActiva"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_name,16,_OMC_LIT_RESOURCE_17_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir,86,_OMC_LIT_RESOURCE_17_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,36,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir)}};
void CuerposAcoplados_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &CuerposAcoplados_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "CuerposAcoplados";
  data->modelData->modelFilePrefix = "CuerposAcoplados";
  data->modelData->modelFileName = "CuerposAcoplados.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CuerposAcoplados";
  data->modelData->modelGUID = "{524f87b0-4900-4b8c-a309-98239f39e4fa}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/CuerposAcoplados_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 4;
  data->modelData->nVariablesRealArray = 14;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 5;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 6;
  data->modelData->nAliasReal = 5;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 4;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 25;
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

