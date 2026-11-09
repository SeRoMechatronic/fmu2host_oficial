/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "MultiplexorCanales_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void MultiplexorCanales_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *MultiplexorCanales_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"canal_seleccion >= 0 and canal_seleccion <= 3",
  "canal_seleccion >= 0",
  "canal_seleccion <= 3",
  "canal_seleccion == 0",
  "canal_seleccion == 1",
  "canal_seleccion == 2",
  "canal_seleccion == 3"};
  static const int occurEqs0[] = {1,4};
  static const int occurEqs1[] = {1,4};
  static const int occurEqs2[] = {1,4};
  static const int occurEqs3[] = {1,4};
  static const int occurEqs4[] = {1,4};
  static const int occurEqs5[] = {1,4};
  static const int occurEqs6[] = {1,4};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3,occurEqs4,occurEqs5,occurEqs6};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int MultiplexorCanales_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int MultiplexorCanales_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp0 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 0));
  tmp1 = LessEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 3));
  gout[start_index] = ((tmp0 && tmp1)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp2 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 0));
  gout[start_index] = (tmp2) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp3 = LessEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 3));
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 0))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 1))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 2))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 3))) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *MultiplexorCanales_relationDescription(int i)
{
  const char *res[] = {"canal_seleccion >= 0",
  "canal_seleccion <= 3",
  "canal_seleccion == 0",
  "canal_seleccion == 1",
  "canal_seleccion == 2",
  "canal_seleccion == 3"};
  return res[i];
}

int MultiplexorCanales_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp4;
  modelica_boolean tmp5;
  modelica_integer current_index = 0;
  modelica_integer start_index;
  
  if(evalforZeroCross) {
    start_index = current_index;
    tmp4 = GreaterEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 0));
    data->simulationInfo->relations[start_index] = tmp4;
    current_index++;

    start_index = current_index;
    tmp5 = LessEq((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */),((modelica_integer) 3));
    data->simulationInfo->relations[start_index] = tmp5;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 0));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 3));
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) >= ((modelica_integer) 0));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) <= ((modelica_integer) 3));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 0));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* canal_seleccion variable */) == ((modelica_integer) 3));
    current_index++;
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

