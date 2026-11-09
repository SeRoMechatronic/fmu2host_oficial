/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ValoresExtremos_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ValoresExtremos_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ValoresExtremos_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[1].attribute.start;
  
  TRACE_POP
  return 0;
}

int ValoresExtremos_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[1].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int ValoresExtremos_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[1].info.name;
  
  TRACE_POP
  return 0;
}

int ValoresExtremos_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ValoresExtremos_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ValoresExtremos_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ValoresExtremos_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* y_inv variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* y_log variable */);
  data->simulationInfo->outputVars[2] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* y_sat variable */);
  data->simulationInfo->outputVars[3] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* y_sqrt variable */);
  
  TRACE_POP
  return 0;
}

int ValoresExtremos_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int ValoresExtremos_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 6
type: SIMPLE_ASSIGN
es_finito = abs(u) < 1e29
*/
void ValoresExtremos_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = 1e29;
  relationhysteresis(data, &tmp0, fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e29, tmp1, tmp2, 0, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* es_finito DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 7
type: SIMPLE_ASSIGN
$cse1 = max(-1.0, u)
*/
void ValoresExtremos_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* $cse1 variable */) = fmax(-1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */));
  TRACE_POP
}
/*
equation index: 8
type: SIMPLE_ASSIGN
y_sat = min(1.0, $cse1)
*/
void ValoresExtremos_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* y_sat variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* $cse1 variable */));
  TRACE_POP
}
/*
equation index: 9
type: SIMPLE_ASSIGN
y_log = if u > 1e-10 then log(u) else -1e30
*/
void ValoresExtremos_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_boolean tmp7;
  modelica_real tmp8;
  tmp4 = 1.0;
  tmp5 = 1e-10;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 1e-10, tmp4, tmp5, 1, Greater, GreaterZC);
  tmp7 = (modelica_boolean)tmp3;
  if(tmp7)
  {
    tmp6 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */);
    if(!(tmp6 > 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of log(u) was %g should be > 0", tmp6);
      }
    }
    tmp8 = log(tmp6);
  }
  else
  {
    tmp8 = -1e30;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* y_log variable */) = tmp8;
  TRACE_POP
}
/*
equation index: 10
type: SIMPLE_ASSIGN
y_sqrt = if u >= 0.0 then sqrt(u) else 0.0
*/
void ValoresExtremos_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_real tmp12;
  modelica_boolean tmp13;
  modelica_real tmp14;
  tmp10 = 1.0;
  tmp11 = 0.0;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */), 0.0, tmp10, tmp11, 2, GreaterEq, GreaterEqZC);
  tmp13 = (modelica_boolean)tmp9;
  if(tmp13)
  {
    tmp12 = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */);
    if(!(tmp12 >= 0.0))
    {
      if (data->simulationInfo->noThrowAsserts) {
        FILE_INFO info = {"",0,0,0,0,0};
        infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        data->simulationInfo->needToReThrow = 1;
      } else {
        FILE_INFO info = {"",0,0,0,0,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        throwStreamPrintWithEquationIndexes(threadData, info, equationIndexes, "Model error: Argument of sqrt(u) was %g should be >= 0", tmp12);
      }
    }
    tmp14 = sqrt(tmp12);
  }
  else
  {
    tmp14 = 0.0;
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* y_sqrt variable */) = tmp14;
  TRACE_POP
}
/*
equation index: 11
type: SIMPLE_ASSIGN
y_inv = if abs(u) > 1e-10 then 1.0 / u else 1e30
*/
void ValoresExtremos_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  tmp16 = 1.0;
  tmp17 = 1e-10;
  relationhysteresis(data, &tmp15, fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */)), 1e-10, tmp16, tmp17, 3, Greater, GreaterZC);
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* y_inv variable */) = (tmp15?DIVISION_SIM(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* u variable */),"u",equationIndexes):1e30);
  TRACE_POP
}

OMC_DISABLE_OPT
int ValoresExtremos_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ValoresExtremos_functionLocalKnownVars(data, threadData);
  ValoresExtremos_eqFunction_6(data, threadData);

  ValoresExtremos_eqFunction_7(data, threadData);

  ValoresExtremos_eqFunction_8(data, threadData);

  ValoresExtremos_eqFunction_9(data, threadData);

  ValoresExtremos_eqFunction_10(data, threadData);

  ValoresExtremos_eqFunction_11(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ValoresExtremos_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int ValoresExtremos_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  ValoresExtremos_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void ValoresExtremos_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y_inv variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y_log variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y_sat variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* y_sqrt variable */
  
  /* discreteAlgVars */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* es_finito DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ValoresExtremos_12jac.h"
#include "ValoresExtremos_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ValoresExtremos_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ValoresExtremos_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ValoresExtremos_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ValoresExtremos_initializeDAEmodeData,
   ValoresExtremos_computeVarIndices,
   ValoresExtremos_functionODE,
   ValoresExtremos_functionAlgebraics,
   ValoresExtremos_functionDAE,
   ValoresExtremos_functionLocalKnownVars,
   ValoresExtremos_input_function,
   ValoresExtremos_input_function_init,
   ValoresExtremos_input_function_updateStartValues,
   ValoresExtremos_data_function,
   ValoresExtremos_output_function,
   ValoresExtremos_setc_function,
   ValoresExtremos_setb_function,
   ValoresExtremos_function_storeDelayed,
   ValoresExtremos_function_storeSpatialDistribution,
   ValoresExtremos_function_initSpatialDistribution,
   ValoresExtremos_updateBoundVariableAttributes,
   ValoresExtremos_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   ValoresExtremos_functionRemovedInitialEquations,
   ValoresExtremos_updateBoundParameters,
   ValoresExtremos_checkForAsserts,
   ValoresExtremos_function_ZeroCrossingsEquations,
   ValoresExtremos_function_ZeroCrossings,
   ValoresExtremos_function_updateRelations,
   ValoresExtremos_zeroCrossingDescription,
   ValoresExtremos_relationDescription,
   ValoresExtremos_function_initSample,
   ValoresExtremos_INDEX_JAC_A,
   ValoresExtremos_INDEX_JAC_B,
   ValoresExtremos_INDEX_JAC_C,
   ValoresExtremos_INDEX_JAC_D,
   ValoresExtremos_INDEX_JAC_F,
   ValoresExtremos_INDEX_JAC_H,
   ValoresExtremos_initialAnalyticJacobianA,
   ValoresExtremos_initialAnalyticJacobianB,
   ValoresExtremos_initialAnalyticJacobianC,
   ValoresExtremos_initialAnalyticJacobianD,
   ValoresExtremos_initialAnalyticJacobianF,
   ValoresExtremos_initialAnalyticJacobianH,
   ValoresExtremos_functionJacA_column,
   ValoresExtremos_functionJacB_column,
   ValoresExtremos_functionJacC_column,
   ValoresExtremos_functionJacD_column,
   ValoresExtremos_functionJacF_column,
   ValoresExtremos_functionJacH_column,
   ValoresExtremos_linear_model_frame,
   ValoresExtremos_linear_model_datarecovery_frame,
   ValoresExtremos_mayer,
   ValoresExtremos_lagrange,
   ValoresExtremos_pickUpBoundsForInputsInOptimization,
   ValoresExtremos_setInputData,
   ValoresExtremos_getTimeGrid,
   ValoresExtremos_symbolicInlineSystem,
   ValoresExtremos_function_initSynchronous,
   ValoresExtremos_function_updateSynchronous,
   ValoresExtremos_function_equationsSynchronous,
   ValoresExtremos_inputNames,
   ValoresExtremos_dataReconciliationInputNames,
   ValoresExtremos_dataReconciliationUnmeasuredVariables,
   ValoresExtremos_read_simulation_info,
   ValoresExtremos_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_12_name_data "MatrizEstado"
#define _OMC_LIT_RESOURCE_12_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MatrizEstado"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,12,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,82,_OMC_LIT_RESOURCE_12_dir_data);

#define _OMC_LIT_RESOURCE_13_name_data "Mi_Modelo_Nuevo"
#define _OMC_LIT_RESOURCE_13_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/Mi_Modelo_Nuevo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_name,15,_OMC_LIT_RESOURCE_13_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir,85,_OMC_LIT_RESOURCE_13_dir_data);

#define _OMC_LIT_RESOURCE_14_name_data "Modelica"
#define _OMC_LIT_RESOURCE_14_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_name,8,_OMC_LIT_RESOURCE_14_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir,80,_OMC_LIT_RESOURCE_14_dir_data);

#define _OMC_LIT_RESOURCE_15_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_15_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_name,16,_OMC_LIT_RESOURCE_15_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir,88,_OMC_LIT_RESOURCE_15_dir_data);

#define _OMC_LIT_RESOURCE_16_name_data "MuchosEstados"
#define _OMC_LIT_RESOURCE_16_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MuchosEstados"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_name,13,_OMC_LIT_RESOURCE_16_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir,83,_OMC_LIT_RESOURCE_16_dir_data);

#define _OMC_LIT_RESOURCE_17_name_data "MultiplexorCanales"
#define _OMC_LIT_RESOURCE_17_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/MultiplexorCanales"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_name,18,_OMC_LIT_RESOURCE_17_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir,88,_OMC_LIT_RESOURCE_17_dir_data);

#define _OMC_LIT_RESOURCE_18_name_data "NivelDeposito"
#define _OMC_LIT_RESOURCE_18_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/NivelDeposito"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_name,13,_OMC_LIT_RESOURCE_18_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir,83,_OMC_LIT_RESOURCE_18_dir_data);

#define _OMC_LIT_RESOURCE_19_name_data "OsciladorArmonico"
#define _OMC_LIT_RESOURCE_19_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/OsciladorArmonico"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_name,17,_OMC_LIT_RESOURCE_19_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir,87,_OMC_LIT_RESOURCE_19_dir_data);

#define _OMC_LIT_RESOURCE_20_name_data "PenduloNoLineal"
#define _OMC_LIT_RESOURCE_20_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PenduloNoLineal"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_name,15,_OMC_LIT_RESOURCE_20_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir,85,_OMC_LIT_RESOURCE_20_dir_data);

#define _OMC_LIT_RESOURCE_21_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_21_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_name,10,_OMC_LIT_RESOURCE_21_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir,80,_OMC_LIT_RESOURCE_21_dir_data);

#define _OMC_LIT_RESOURCE_22_name_data "ReguladorBateria"
#define _OMC_LIT_RESOURCE_22_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ReguladorBateria"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_name,16,_OMC_LIT_RESOURCE_22_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir,86,_OMC_LIT_RESOURCE_22_dir_data);

#define _OMC_LIT_RESOURCE_23_name_data "SelectorModo"
#define _OMC_LIT_RESOURCE_23_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SelectorModo"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_name,12,_OMC_LIT_RESOURCE_23_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir,82,_OMC_LIT_RESOURCE_23_dir_data);

#define _OMC_LIT_RESOURCE_24_name_data "SinInputs"
#define _OMC_LIT_RESOURCE_24_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SinInputs"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_24_name,9,_OMC_LIT_RESOURCE_24_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_24_dir,79,_OMC_LIT_RESOURCE_24_dir_data);

#define _OMC_LIT_RESOURCE_25_name_data "SistemaLorenz"
#define _OMC_LIT_RESOURCE_25_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SistemaLorenz"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_25_name,13,_OMC_LIT_RESOURCE_25_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_25_dir,83,_OMC_LIT_RESOURCE_25_dir_data);

#define _OMC_LIT_RESOURCE_26_name_data "StringInputOutput"
#define _OMC_LIT_RESOURCE_26_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_26_name,17,_OMC_LIT_RESOURCE_26_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_26_dir,87,_OMC_LIT_RESOURCE_26_dir_data);

#define _OMC_LIT_RESOURCE_27_name_data "StringsParametros"
#define _OMC_LIT_RESOURCE_27_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringsParametros"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_27_name,17,_OMC_LIT_RESOURCE_27_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_27_dir,87,_OMC_LIT_RESOURCE_27_dir_data);

#define _OMC_LIT_RESOURCE_28_name_data "SuspensionActiva"
#define _OMC_LIT_RESOURCE_28_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/SuspensionActiva"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_28_name,16,_OMC_LIT_RESOURCE_28_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_28_dir,86,_OMC_LIT_RESOURCE_28_dir_data);

#define _OMC_LIT_RESOURCE_29_name_data "TiposMixtos"
#define _OMC_LIT_RESOURCE_29_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/TiposMixtos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_29_name,11,_OMC_LIT_RESOURCE_29_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_29_dir,81,_OMC_LIT_RESOURCE_29_dir_data);

#define _OMC_LIT_RESOURCE_30_name_data "ValoresExtremos"
#define _OMC_LIT_RESOURCE_30_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ValoresExtremos"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_30_name,15,_OMC_LIT_RESOURCE_30_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_30_dir,85,_OMC_LIT_RESOURCE_30_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,62,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_13_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_14_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_15_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_16_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_17_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_18_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_19_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_20_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_21_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_22_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_23_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_24_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_24_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_25_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_25_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_26_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_26_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_27_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_27_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_28_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_28_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_29_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_29_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_30_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_30_dir)}};
void ValoresExtremos_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ValoresExtremos_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ValoresExtremos";
  data->modelData->modelFilePrefix = "ValoresExtremos";
  data->modelData->modelFileName = "ValoresExtremos.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/ValoresExtremos";
  data->modelData->modelGUID = "{4c9968b8-d207-48b0-8a5a-5fb81577d374}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ValoresExtremos_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 6;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 0;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 5;
  data->modelData->nAliasReal = 4;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 4;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 4;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 12;
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

