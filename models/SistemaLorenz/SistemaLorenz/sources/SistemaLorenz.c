/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "SistemaLorenz_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int SistemaLorenz_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int SistemaLorenz_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x_out variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* y_out variable */);
  data->simulationInfo->outputVars[2] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* z_out variable */);
  
  TRACE_POP
  return 0;
}

int SistemaLorenz_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SistemaLorenz_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 11
type: SIMPLE_ASSIGN
on_attractor = z >= 0.0 and z <= 60.0 and abs(x) < 30.0 and abs(y) < 35.0
*/
void SistemaLorenz_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
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
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */), 0.0, tmp1, tmp2, 0, GreaterEq, GreaterEqZC);
  tmp4 = 1.0;
  tmp5 = 60.0;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */), 60.0, tmp4, tmp5, 1, LessEq, LessEqZC);
  tmp7 = 1.0;
  tmp8 = 30.0;
  relationhysteresis(data, &tmp6, fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */)), 30.0, tmp7, tmp8, 2, Less, LessZC);
  tmp10 = 1.0;
  tmp11 = 35.0;
  relationhysteresis(data, &tmp9, fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */)), 35.0, tmp10, tmp11, 3, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* on_attractor DISCRETE */) = (((tmp0 && tmp3) && tmp6) && tmp9);
  TRACE_POP
}
/*
equation index: 12
type: SIMPLE_ASSIGN
$DER.z = x * y - beta * z
*/
void SistemaLorenz_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(z) STATE_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */)) - (((data->simulationInfo->realParameter[0] /* beta PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */)));
  TRACE_POP
}
/*
equation index: 13
type: SIMPLE_ASSIGN
$DER.y = x * (rho - z) - y
*/
void SistemaLorenz_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(y) STATE_DER */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */)) * ((data->simulationInfo->realParameter[1] /* rho PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */)) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */);
  TRACE_POP
}
/*
equation index: 14
type: SIMPLE_ASSIGN
$DER.x = sigma * (y - x)
*/
void SistemaLorenz_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* der(x) STATE_DER */) = ((data->simulationInfo->realParameter[2] /* sigma PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */));
  TRACE_POP
}
/*
equation index: 15
type: SIMPLE_ASSIGN
z_out = z
*/
void SistemaLorenz_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* z_out variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* z STATE(1) */);
  TRACE_POP
}
/*
equation index: 16
type: SIMPLE_ASSIGN
y_out = y
*/
void SistemaLorenz_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* y_out variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* y STATE(1) */);
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
x_out = x
*/
void SistemaLorenz_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* x_out variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* x STATE(1) */);
  TRACE_POP
}

OMC_DISABLE_OPT
int SistemaLorenz_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  SistemaLorenz_functionLocalKnownVars(data, threadData);
  SistemaLorenz_eqFunction_11(data, threadData);

  SistemaLorenz_eqFunction_12(data, threadData);

  SistemaLorenz_eqFunction_13(data, threadData);

  SistemaLorenz_eqFunction_14(data, threadData);

  SistemaLorenz_eqFunction_15(data, threadData);

  SistemaLorenz_eqFunction_16(data, threadData);

  SistemaLorenz_eqFunction_17(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int SistemaLorenz_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void SistemaLorenz_eqFunction_12(DATA* data, threadData_t *threadData);
extern void SistemaLorenz_eqFunction_13(DATA* data, threadData_t *threadData);
extern void SistemaLorenz_eqFunction_14(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[3])(DATA*, threadData_t*) = {
    SistemaLorenz_eqFunction_12,
    SistemaLorenz_eqFunction_13,
    SistemaLorenz_eqFunction_14
  };
  
  static const int eqIndices[3] = {
    12,
    13,
    14
  };
  
  for (id = 0; id < 3; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int SistemaLorenz_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  SistemaLorenz_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void SistemaLorenz_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* z STATE(1) */
  
  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(x) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(y) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(z) STATE_DER */
  
  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* x_out variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y_out variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* z_out variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* on_attractor DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "SistemaLorenz_12jac.h"
#include "SistemaLorenz_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks SistemaLorenz_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   SistemaLorenz_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   SistemaLorenz_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   SistemaLorenz_initializeDAEmodeData,
   SistemaLorenz_computeVarIndices,
   SistemaLorenz_functionODE,
   SistemaLorenz_functionAlgebraics,
   SistemaLorenz_functionDAE,
   SistemaLorenz_functionLocalKnownVars,
   SistemaLorenz_input_function,
   SistemaLorenz_input_function_init,
   SistemaLorenz_input_function_updateStartValues,
   SistemaLorenz_data_function,
   SistemaLorenz_output_function,
   SistemaLorenz_setc_function,
   SistemaLorenz_setb_function,
   SistemaLorenz_function_storeDelayed,
   SistemaLorenz_function_storeSpatialDistribution,
   SistemaLorenz_function_initSpatialDistribution,
   SistemaLorenz_updateBoundVariableAttributes,
   SistemaLorenz_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   SistemaLorenz_functionRemovedInitialEquations,
   SistemaLorenz_updateBoundParameters,
   SistemaLorenz_checkForAsserts,
   SistemaLorenz_function_ZeroCrossingsEquations,
   SistemaLorenz_function_ZeroCrossings,
   SistemaLorenz_function_updateRelations,
   SistemaLorenz_zeroCrossingDescription,
   SistemaLorenz_relationDescription,
   SistemaLorenz_function_initSample,
   SistemaLorenz_INDEX_JAC_A,
   SistemaLorenz_INDEX_JAC_B,
   SistemaLorenz_INDEX_JAC_C,
   SistemaLorenz_INDEX_JAC_D,
   SistemaLorenz_INDEX_JAC_F,
   SistemaLorenz_INDEX_JAC_H,
   SistemaLorenz_initialAnalyticJacobianA,
   SistemaLorenz_initialAnalyticJacobianB,
   SistemaLorenz_initialAnalyticJacobianC,
   SistemaLorenz_initialAnalyticJacobianD,
   SistemaLorenz_initialAnalyticJacobianF,
   SistemaLorenz_initialAnalyticJacobianH,
   SistemaLorenz_functionJacA_column,
   SistemaLorenz_functionJacB_column,
   SistemaLorenz_functionJacC_column,
   SistemaLorenz_functionJacD_column,
   SistemaLorenz_functionJacF_column,
   SistemaLorenz_functionJacH_column,
   SistemaLorenz_linear_model_frame,
   SistemaLorenz_linear_model_datarecovery_frame,
   SistemaLorenz_mayer,
   SistemaLorenz_lagrange,
   SistemaLorenz_pickUpBoundsForInputsInOptimization,
   SistemaLorenz_setInputData,
   SistemaLorenz_getTimeGrid,
   SistemaLorenz_symbolicInlineSystem,
   SistemaLorenz_function_initSynchronous,
   SistemaLorenz_function_updateSynchronous,
   SistemaLorenz_function_equationsSynchronous,
   SistemaLorenz_inputNames,
   SistemaLorenz_dataReconciliationInputNames,
   SistemaLorenz_dataReconciliationUnmeasuredVariables,
   SistemaLorenz_read_simulation_info,
   SistemaLorenz_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_10_name_data "Mi_Modelo_Nuevo"
#define _OMC_LIT_RESOURCE_10_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/Mi_Modelo_Nuevo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,15,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,85,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "Modelica"
#define _OMC_LIT_RESOURCE_11_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,8,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,80,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,16,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,88,_OMC_LIT_RESOURCE_12_dir_data);

#define _OMC_LIT_RESOURCE_13_name_data "MuchosEstados"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MuchosEstados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,13,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,83,_OMC_LIT_RESOURCE_13_dir_data);

#define _OMC_LIT_RESOURCE_14_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_14_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_name,18,_OMC_LIT_RESOURCE_14_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir,88,_OMC_LIT_RESOURCE_14_dir_data);

#define _OMC_LIT_RESOURCE_15_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_15_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_name,13,_OMC_LIT_RESOURCE_15_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir,83,_OMC_LIT_RESOURCE_15_dir_data);

#define _OMC_LIT_RESOURCE_16_name_data "OsciladorArmonico"
#define _OMC_LIT_RESOURCE_16_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/OsciladorArmonico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_name,17,_OMC_LIT_RESOURCE_16_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir,87,_OMC_LIT_RESOURCE_16_dir_data);

#define _OMC_LIT_RESOURCE_17_name_data "PenduloNoLineal"
#define _OMC_LIT_RESOURCE_17_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PenduloNoLineal"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_name,15,_OMC_LIT_RESOURCE_17_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir,85,_OMC_LIT_RESOURCE_17_dir_data);

#define _OMC_LIT_RESOURCE_18_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_18_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_name,10,_OMC_LIT_RESOURCE_18_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir,80,_OMC_LIT_RESOURCE_18_dir_data);

#define _OMC_LIT_RESOURCE_19_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_19_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_name,16,_OMC_LIT_RESOURCE_19_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir,86,_OMC_LIT_RESOURCE_19_dir_data);

#define _OMC_LIT_RESOURCE_20_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_20_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_name,12,_OMC_LIT_RESOURCE_20_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir,82,_OMC_LIT_RESOURCE_20_dir_data);

#define _OMC_LIT_RESOURCE_21_name_data "SinInputs"
#define _OMC_LIT_RESOURCE_21_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SinInputs"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_name,9,_OMC_LIT_RESOURCE_21_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir,79,_OMC_LIT_RESOURCE_21_dir_data);

#define _OMC_LIT_RESOURCE_22_name_data "SistemaLorenz"
#define _OMC_LIT_RESOURCE_22_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SistemaLorenz"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_name,13,_OMC_LIT_RESOURCE_22_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir,83,_OMC_LIT_RESOURCE_22_dir_data);

#define _OMC_LIT_RESOURCE_23_name_data "SuspensionActiva"
#define _OMC_LIT_RESOURCE_23_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SuspensionActiva"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_name,16,_OMC_LIT_RESOURCE_23_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir,86,_OMC_LIT_RESOURCE_23_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,48,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir)}};
void SistemaLorenz_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &SistemaLorenz_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "SistemaLorenz";
  data->modelData->modelFilePrefix = "SistemaLorenz";
  data->modelData->modelFileName = "SistemaLorenz.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SistemaLorenz";
  data->modelData->modelGUID = "{e184239f-b020-43fc-8477-5b9da822fb88}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/SistemaLorenz_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 3;
  data->modelData->nVariablesRealArray = 9;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 3;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 3;
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
  data->modelData->modelDataXml.nEquations = 18;
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

