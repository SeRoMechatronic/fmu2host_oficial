/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "ArraysVectores_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

OMC_DISABLE_OPT
int ArraysVectores_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating min-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* max ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating max-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* nominal **************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating nominal-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating primary start-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  TRACE_POP
  return 0;
}

void ArraysVectores_updateBoundParameters_0(DATA *data, threadData_t *threadData);
extern void ArraysVectores_eqFunction_18(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_12(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_11(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_10(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_9(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_8(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_7(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_6(DATA *data, threadData_t *threadData);

extern void ArraysVectores_eqFunction_5(DATA *data, threadData_t *threadData);


/*
equation index: 40
type: SIMPLE_ASSIGN
$outputAlias_alguno_true = alguno_true
*/
OMC_DISABLE_OPT
static void ArraysVectores_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  (data->simulationInfo->booleanParameter[0] /* $outputAlias_alguno_true PARAM */) = (data->simulationInfo->booleanParameter[1] /* alguno_true PARAM */);
  TRACE_POP
}
OMC_DISABLE_OPT
void ArraysVectores_updateBoundParameters_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ArraysVectores_eqFunction_18(data, threadData);
  ArraysVectores_eqFunction_12(data, threadData);
  ArraysVectores_eqFunction_11(data, threadData);
  ArraysVectores_eqFunction_10(data, threadData);
  ArraysVectores_eqFunction_9(data, threadData);
  ArraysVectores_eqFunction_8(data, threadData);
  ArraysVectores_eqFunction_7(data, threadData);
  ArraysVectores_eqFunction_6(data, threadData);
  ArraysVectores_eqFunction_5(data, threadData);
  ArraysVectores_eqFunction_40(data, threadData);
  TRACE_POP
}
OMC_DISABLE_OPT
int ArraysVectores_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* v_int[1] DISCRETE */) = ((modelica_integer) 0);
  data->modelData->integerVarsData[1].time_unvarying = 1;
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* v_int[2] DISCRETE */) = ((modelica_integer) 0);
  data->modelData->integerVarsData[2].time_unvarying = 1;
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* v_int[3] DISCRETE */) = ((modelica_integer) 0);
  data->modelData->integerVarsData[3].time_unvarying = 1;
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[4]] /* v_int[4] DISCRETE */) = ((modelica_integer) 0);
  data->modelData->integerVarsData[4].time_unvarying = 1;
  (data->simulationInfo->integerParameter[0] /* N PARAM */) = ((modelica_integer) 4);
  data->modelData->integerParameterData[0].time_unvarying = 1;
  ArraysVectores_updateBoundParameters_0(data, threadData);
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

