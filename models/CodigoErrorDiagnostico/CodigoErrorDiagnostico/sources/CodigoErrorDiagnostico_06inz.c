/* Initialization */
#include "CodigoErrorDiagnostico_model.h"
#include "CodigoErrorDiagnostico_11mix.h"
#include "CodigoErrorDiagnostico_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void CodigoErrorDiagnostico_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void CodigoErrorDiagnostico_eqFunction_5(DATA *data, threadData_t *threadData);

extern void CodigoErrorDiagnostico_eqFunction_6(DATA *data, threadData_t *threadData);

extern void CodigoErrorDiagnostico_eqFunction_7(DATA *data, threadData_t *threadData);

extern void CodigoErrorDiagnostico_eqFunction_8(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void CodigoErrorDiagnostico_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  CodigoErrorDiagnostico_eqFunction_5(data, threadData);
  CodigoErrorDiagnostico_eqFunction_6(data, threadData);
  CodigoErrorDiagnostico_eqFunction_7(data, threadData);
  CodigoErrorDiagnostico_eqFunction_8(data, threadData);
  TRACE_POP
}

int CodigoErrorDiagnostico_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  CodigoErrorDiagnostico_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No CodigoErrorDiagnostico_functionInitialEquations_lambda0 function */

int CodigoErrorDiagnostico_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

