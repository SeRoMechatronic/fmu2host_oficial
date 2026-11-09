/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "EtapaSecuenciador_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int EtapaSecuenciador_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* sensor_confirmacion variable */) = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[1].attribute.start;
  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[1].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->booleanVarsData[4].info.name;
  names[1] = (char *) data->modelData->booleanVarsData[5].info.name;
  names[2] = (char *) data->modelData->realVarsData[1].info.name;
  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int EtapaSecuenciador_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* progreso_etapa variable */);
  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int EtapaSecuenciador_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 19
type: SIMPLE_ASSIGN
secuencia_completa = pre(etapa) == 0 and pre(etapa_ant) == N_ETAPAS
*/
void EtapaSecuenciador_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* secuencia_completa DISCRETE */) = (((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */) == ((modelica_integer) 0)) && ((data->simulationInfo->integerVarsPre[2] /* etapa_ant DISCRETE */) == (data->simulationInfo->integerParameter[0] /* N_ETAPAS PARAM */)));
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
progreso_etapa = if pre(etapa) > 0 then min(1.0, pre(tiempo_en_etapa) / duracion_etapa) else 0.0
*/
void EtapaSecuenciador_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  modelica_boolean tmp0;
  tmp0 = Greater((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),((modelica_integer) 0));
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* progreso_etapa variable */) = (tmp0?fmin(1.0,DIVISION_SIM((data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */),(data->simulationInfo->realParameter[1] /* duracion_etapa PARAM */),"duracion_etapa",equationIndexes)):0.0);
  TRACE_POP
}
/*
equation index: 21
type: ALGORITHM

  t_inicio := pre(t_inicio);
  etapa_ant := pre(etapa_ant);
  etapa := pre(etapa);
  $whenCondition4 := pre($whenCondition4);
  $whenCondition3 := pre($whenCondition3);
  $whenCondition2 := pre($whenCondition2);
  $whenCondition2 := false;
  $whenCondition3 := false;
  $whenCondition4 := pre(tiempo_en_etapa) >= duracion_etapa and pre(sensor_s) > 0.5 and pre(etapa) > 0;
  when {$whenCondition2, $whenCondition3, $whenCondition4} then
    if pre(tiempo_en_etapa) >= duracion_etapa and pre(sensor_s) > 0.5 and pre(etapa) > 0 then
      etapa_ant := pre(etapa);
      t_inicio := time;
      if pre(etapa) < N_ETAPAS then
        etapa := pre(etapa) + 1;
      else
        etapa := 0;
      end if;
    end if;
  end when;
*/
void EtapaSecuenciador_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  modelica_boolean tmp4;
  modelica_boolean tmp5;
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* t_inicio DISCRETE */) = (data->simulationInfo->realVarsPre[3] /* t_inicio DISCRETE */);

  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* etapa_ant DISCRETE */) = (data->simulationInfo->integerVarsPre[2] /* etapa_ant DISCRETE */);

  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* etapa DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition4 DISCRETE */) = (data->simulationInfo->booleanVarsPre[3] /* $whenCondition4 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition3 DISCRETE */) = (data->simulationInfo->booleanVarsPre[2] /* $whenCondition3 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) = (data->simulationInfo->booleanVarsPre[1] /* $whenCondition2 DISCRETE */);

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) = 0 /* false */;

  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition3 DISCRETE */) = 0 /* false */;

  tmp1 = GreaterEq((data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */),(data->simulationInfo->realParameter[1] /* duracion_etapa PARAM */));
  tmp2 = Greater((data->simulationInfo->realVarsPre[2] /* sensor_s DISCRETE */),0.5);
  tmp3 = Greater((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),((modelica_integer) 0));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition4 DISCRETE */) = ((tmp1 && tmp2) && tmp3);

  if(data->simulationInfo->discreteCall == 1)
  {
    if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition4 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[3] /* $whenCondition4 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition3 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[2] /* $whenCondition3 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition2 DISCRETE */) /* edge */))
    {
      tmp4 = GreaterEq((data->simulationInfo->realVarsPre[4] /* tiempo_en_etapa DISCRETE */),(data->simulationInfo->realParameter[1] /* duracion_etapa PARAM */));
      tmp5 = Greater((data->simulationInfo->realVarsPre[2] /* sensor_s DISCRETE */),0.5);
      tmp6 = Greater((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),((modelica_integer) 0));
      if(((tmp4 && tmp5) && tmp6))
      {
        (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* etapa_ant DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */);

        (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* t_inicio DISCRETE */) = data->localData[0]->timeValue;

        tmp7 = Less((data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */),(data->simulationInfo->integerParameter[0] /* N_ETAPAS PARAM */));
        if(tmp7)
        {
          (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* etapa DISCRETE */) = (data->simulationInfo->integerVarsPre[0] /* etapa DISCRETE */) + ((modelica_integer) 1);
        }
        else
        {
          (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* etapa DISCRETE */) = ((modelica_integer) 0);
        }
      }
    }
  }
  TRACE_POP
}
/*
equation index: 22
type: SIMPLE_ASSIGN
etapa_previa = etapa_ant
*/
void EtapaSecuenciador_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* etapa_previa DISCRETE */) = (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* etapa_ant DISCRETE */);
  TRACE_POP
}
/*
equation index: 23
type: SIMPLE_ASSIGN
etapa_actual = etapa
*/
void EtapaSecuenciador_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* etapa_actual DISCRETE */) = (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* etapa DISCRETE */);
  TRACE_POP
}
/*
equation index: 24
type: SIMPLE_ASSIGN
$whenCondition1 = sample(1, 0.0, Ts)
*/
void EtapaSecuenciador_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = data->simulationInfo->samples[0];
  TRACE_POP
}
/*
equation index: 25
type: WHEN

when {$whenCondition1} then
  tiempo_en_etapa = time - pre(t_inicio);
end when;
*/
void EtapaSecuenciador_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* tiempo_en_etapa DISCRETE */) = data->localData[0]->timeValue - (data->simulationInfo->realVarsPre[3] /* t_inicio DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 26
type: WHEN

when {$whenCondition1} then
  sensor_s = sensor_confirmacion;
end when;
*/
void EtapaSecuenciador_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* sensor_s DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* sensor_confirmacion variable */);
  }
  TRACE_POP
}

OMC_DISABLE_OPT
int EtapaSecuenciador_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  EtapaSecuenciador_functionLocalKnownVars(data, threadData);
  EtapaSecuenciador_eqFunction_19(data, threadData);

  EtapaSecuenciador_eqFunction_20(data, threadData);

  EtapaSecuenciador_eqFunction_21(data, threadData);

  EtapaSecuenciador_eqFunction_22(data, threadData);

  EtapaSecuenciador_eqFunction_23(data, threadData);

  EtapaSecuenciador_eqFunction_24(data, threadData);

  EtapaSecuenciador_eqFunction_25(data, threadData);

  EtapaSecuenciador_eqFunction_26(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int EtapaSecuenciador_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


int EtapaSecuenciador_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  EtapaSecuenciador_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void EtapaSecuenciador_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
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
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* progreso_etapa variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sensor_confirmacion variable */
  
  /* discreteAlgVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sensor_s DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* t_inicio DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* tiempo_en_etapa DISCRETE */
  
  /* realOptimizeConstraintsVars */
  
  /* realOptimizeFinalConstraintsVars */
  
  
  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* etapa DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* etapa_actual DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* etapa_ant DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* etapa_previa DISCRETE */
  
  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition1 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition2 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition3 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition4 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* arrancar variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* parar variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* secuencia_completa DISCRETE */
  
  /* stringAlgVars */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "EtapaSecuenciador_12jac.h"
#include "EtapaSecuenciador_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks EtapaSecuenciador_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   EtapaSecuenciador_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   EtapaSecuenciador_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   EtapaSecuenciador_initializeDAEmodeData,
   EtapaSecuenciador_computeVarIndices,
   EtapaSecuenciador_functionODE,
   EtapaSecuenciador_functionAlgebraics,
   EtapaSecuenciador_functionDAE,
   EtapaSecuenciador_functionLocalKnownVars,
   EtapaSecuenciador_input_function,
   EtapaSecuenciador_input_function_init,
   EtapaSecuenciador_input_function_updateStartValues,
   EtapaSecuenciador_data_function,
   EtapaSecuenciador_output_function,
   EtapaSecuenciador_setc_function,
   EtapaSecuenciador_setb_function,
   EtapaSecuenciador_function_storeDelayed,
   EtapaSecuenciador_function_storeSpatialDistribution,
   EtapaSecuenciador_function_initSpatialDistribution,
   EtapaSecuenciador_updateBoundVariableAttributes,
   EtapaSecuenciador_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   EtapaSecuenciador_functionRemovedInitialEquations,
   EtapaSecuenciador_updateBoundParameters,
   EtapaSecuenciador_checkForAsserts,
   EtapaSecuenciador_function_ZeroCrossingsEquations,
   EtapaSecuenciador_function_ZeroCrossings,
   EtapaSecuenciador_function_updateRelations,
   EtapaSecuenciador_zeroCrossingDescription,
   EtapaSecuenciador_relationDescription,
   EtapaSecuenciador_function_initSample,
   EtapaSecuenciador_INDEX_JAC_A,
   EtapaSecuenciador_INDEX_JAC_B,
   EtapaSecuenciador_INDEX_JAC_C,
   EtapaSecuenciador_INDEX_JAC_D,
   EtapaSecuenciador_INDEX_JAC_F,
   EtapaSecuenciador_INDEX_JAC_H,
   EtapaSecuenciador_initialAnalyticJacobianA,
   EtapaSecuenciador_initialAnalyticJacobianB,
   EtapaSecuenciador_initialAnalyticJacobianC,
   EtapaSecuenciador_initialAnalyticJacobianD,
   EtapaSecuenciador_initialAnalyticJacobianF,
   EtapaSecuenciador_initialAnalyticJacobianH,
   EtapaSecuenciador_functionJacA_column,
   EtapaSecuenciador_functionJacB_column,
   EtapaSecuenciador_functionJacC_column,
   EtapaSecuenciador_functionJacD_column,
   EtapaSecuenciador_functionJacF_column,
   EtapaSecuenciador_functionJacH_column,
   EtapaSecuenciador_linear_model_frame,
   EtapaSecuenciador_linear_model_datarecovery_frame,
   EtapaSecuenciador_mayer,
   EtapaSecuenciador_lagrange,
   EtapaSecuenciador_pickUpBoundsForInputsInOptimization,
   EtapaSecuenciador_setInputData,
   EtapaSecuenciador_getTimeGrid,
   EtapaSecuenciador_symbolicInlineSystem,
   EtapaSecuenciador_function_initSynchronous,
   EtapaSecuenciador_function_updateSynchronous,
   EtapaSecuenciador_function_equationsSynchronous,
   EtapaSecuenciador_inputNames,
   EtapaSecuenciador_dataReconciliationInputNames,
   EtapaSecuenciador_dataReconciliationUnmeasuredVariables,
   EtapaSecuenciador_read_simulation_info,
   EtapaSecuenciador_read_input_fmu,
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

#define _OMC_LIT_RESOURCE_6_name_data "Modelica"
#define _OMC_LIT_RESOURCE_6_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/Modelica 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,8,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,80,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_7_dir_data "C:/fmu2host/xxxx/AppData/Roaming/.openmodelica/libraries/ModelicaServices 4.0.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,16,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,88,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "PotVumetro"
#define _OMC_LIT_RESOURCE_8_dir_data "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,10,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,80,_OMC_LIT_RESOURCE_8_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,18,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir)}};
void EtapaSecuenciador_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &EtapaSecuenciador_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "EtapaSecuenciador";
  data->modelData->modelFilePrefix = "EtapaSecuenciador";
  data->modelData->modelFileName = "EtapaSecuenciador.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/EtapaSecuenciador";
  data->modelData->modelGUID = "{8dd659c4-cec8-4fc5-ba83-5de4a39c0d1f}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/EtapaSecuenciador_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 0;
  data->modelData->nVariablesRealArray = 5;
  data->modelData->nDiscreteReal = 3;
  data->modelData->nVariablesIntegerArray = 4;
  data->modelData->nVariablesBooleanArray = 7;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 2;
  data->modelData->nParametersInteger = 1;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 3;
  data->modelData->nOutputVars = 4;
  data->modelData->nAliasReal = 1;
  data->modelData->nAliasInteger = 2;
  data->modelData->nAliasBoolean = 1;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 1;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 27;
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

