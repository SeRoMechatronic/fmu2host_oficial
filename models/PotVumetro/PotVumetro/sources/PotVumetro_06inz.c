/* Initialization */
#include "PotVumetro_model.h"
#include "PotVumetro_11mix.h"
#include "PotVumetro_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void PotVumetro_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void PotVumetro_eqFunction_6(DATA *data, threadData_t *threadData);

extern void PotVumetro_eqFunction_7(DATA *data, threadData_t *threadData);

extern void PotVumetro_eqFunction_8(DATA *data, threadData_t *threadData);

extern void PotVumetro_eqFunction_9(DATA *data, threadData_t *threadData);

extern void PotVumetro_eqFunction_10(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void PotVumetro_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  PotVumetro_eqFunction_6(data, threadData);
  PotVumetro_eqFunction_7(data, threadData);
  PotVumetro_eqFunction_8(data, threadData);
  PotVumetro_eqFunction_9(data, threadData);
  PotVumetro_eqFunction_10(data, threadData);
  TRACE_POP
}

int PotVumetro_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  PotVumetro_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No PotVumetro_functionInitialEquations_lambda0 function */

int PotVumetro_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

