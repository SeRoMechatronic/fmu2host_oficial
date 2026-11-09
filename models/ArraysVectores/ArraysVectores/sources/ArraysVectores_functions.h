#ifndef ArraysVectores__H
#define ArraysVectores__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif


DLLDirection
modelica_boolean omc_Modelica_Math_BooleanVectors_anyTrue(threadData_t *threadData, boolean_array _b);
DLLDirection
modelica_metatype boxptr_Modelica_Math_BooleanVectors_anyTrue(threadData_t *threadData, modelica_metatype _b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_Math_BooleanVectors_anyTrue,2,0) {(void*) boxptr_Modelica_Math_BooleanVectors_anyTrue,0}};
#define boxvar_Modelica_Math_BooleanVectors_anyTrue MMC_REFSTRUCTLIT(boxvar_lit_Modelica_Math_BooleanVectors_anyTrue)
#include "ArraysVectores_model.h"


#ifdef __cplusplus
}
#endif
#endif

