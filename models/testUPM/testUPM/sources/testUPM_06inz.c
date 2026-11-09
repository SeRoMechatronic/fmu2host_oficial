/* Initialization */
#include "testUPM_model.h"
#include "testUPM_11mix.h"
#include "testUPM_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void testUPM_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void testUPM_eqFunction_6(DATA *data, threadData_t *threadData);

extern void testUPM_eqFunction_7(DATA *data, threadData_t *threadData);

extern void testUPM_eqFunction_8(DATA *data, threadData_t *threadData);

extern void testUPM_eqFunction_9(DATA *data, threadData_t *threadData);

extern void testUPM_eqFunction_10(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void testUPM_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  testUPM_eqFunction_6(data, threadData);
  testUPM_eqFunction_7(data, threadData);
  testUPM_eqFunction_8(data, threadData);
  testUPM_eqFunction_9(data, threadData);
  testUPM_eqFunction_10(data, threadData);
  TRACE_POP
}

int testUPM_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  testUPM_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No testUPM_functionInitialEquations_lambda0 function */

int testUPM_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

