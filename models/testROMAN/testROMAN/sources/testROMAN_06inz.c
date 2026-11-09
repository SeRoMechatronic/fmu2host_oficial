/* Initialization */
#include "testROMAN_model.h"
#include "testROMAN_11mix.h"
#include "testROMAN_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void testROMAN_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void testROMAN_eqFunction_6(DATA *data, threadData_t *threadData);

extern void testROMAN_eqFunction_7(DATA *data, threadData_t *threadData);

extern void testROMAN_eqFunction_8(DATA *data, threadData_t *threadData);

extern void testROMAN_eqFunction_9(DATA *data, threadData_t *threadData);

extern void testROMAN_eqFunction_10(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void testROMAN_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  testROMAN_eqFunction_6(data, threadData);
  testROMAN_eqFunction_7(data, threadData);
  testROMAN_eqFunction_8(data, threadData);
  testROMAN_eqFunction_9(data, threadData);
  testROMAN_eqFunction_10(data, threadData);
  TRACE_POP
}

int testROMAN_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  testROMAN_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No testROMAN_functionInitialEquations_lambda0 function */

int testROMAN_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

