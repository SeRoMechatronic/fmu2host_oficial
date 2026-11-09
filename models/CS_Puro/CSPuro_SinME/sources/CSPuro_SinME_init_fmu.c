#include "simulation_data.h"

OMC_DISABLE_OPT

void CSPuro_SinME_read_simulation_info(SIMULATION_INFO* simulationInfo)
{
  simulationInfo->startTime = 0.0;
  simulationInfo->stopTime = 1.0;
  simulationInfo->stepSize = 0.002;
  simulationInfo->tolerance = 1e-6;
  simulationInfo->solverMethod = "dassl";
  simulationInfo->outputFormat = "mat";
  simulationInfo->variableFilter = ".*";
  simulationInfo->OPENMODELICAHOME = "C:/Program Files/OpenModelica1.25.7-64bit";
}

void CSPuro_SinME_read_input_fmu(MODEL_DATA* modelData)
{
  modelData->realVarsData[0].info.id = 1000;
  modelData->realVarsData[0].info.name = "u1";
  modelData->realVarsData[0].info.comment = "First operand — any real value";
  modelData->realVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro/CSPuro_SinME.mo";
  modelData->realVarsData[0].info.info.lineStart = 31;
  modelData->realVarsData[0].info.info.colStart = 3;
  modelData->realVarsData[0].info.info.lineEnd = 33;
  modelData->realVarsData[0].info.info.colEnd = 77;
  modelData->realVarsData[0].info.info.readonly = 0;
  modelData->realVarsData[0].attribute.unit = "";
  modelData->realVarsData[0].attribute.displayUnit = "";
  modelData->realVarsData[0].attribute.min = -DBL_MAX;
  modelData->realVarsData[0].attribute.max = DBL_MAX;
  modelData->realVarsData[0].attribute.fixed = 1;
  modelData->realVarsData[0].attribute.useNominal = 0;
  modelData->realVarsData[0].attribute.nominal = 1.0;
  modelData->realVarsData[0].attribute.start = 0.0;
  modelData->realVarsData[1].info.id = 1001;
  modelData->realVarsData[1].info.name = "u2";
  modelData->realVarsData[1].info.comment = "Second operand — any real value";
  modelData->realVarsData[1].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro/CSPuro_SinME.mo";
  modelData->realVarsData[1].info.info.lineStart = 35;
  modelData->realVarsData[1].info.info.colStart = 3;
  modelData->realVarsData[1].info.info.lineEnd = 37;
  modelData->realVarsData[1].info.info.colEnd = 79;
  modelData->realVarsData[1].info.info.readonly = 0;
  modelData->realVarsData[1].attribute.unit = "";
  modelData->realVarsData[1].attribute.displayUnit = "";
  modelData->realVarsData[1].attribute.min = -DBL_MAX;
  modelData->realVarsData[1].attribute.max = DBL_MAX;
  modelData->realVarsData[1].attribute.fixed = 1;
  modelData->realVarsData[1].attribute.useNominal = 0;
  modelData->realVarsData[1].attribute.nominal = 1.0;
  modelData->realVarsData[1].attribute.start = 0.0;
  modelData->realVarsData[2].info.id = 1002;
  modelData->realVarsData[2].info.name = "y_prod";
  modelData->realVarsData[2].info.comment = "Product of both inputs: u1 * u2";
  modelData->realVarsData[2].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro/CSPuro_SinME.mo";
  modelData->realVarsData[2].info.info.lineStart = 44;
  modelData->realVarsData[2].info.info.colStart = 3;
  modelData->realVarsData[2].info.info.lineEnd = 46;
  modelData->realVarsData[2].info.info.colEnd = 76;
  modelData->realVarsData[2].info.info.readonly = 0;
  modelData->realVarsData[2].attribute.unit = "";
  modelData->realVarsData[2].attribute.displayUnit = "";
  modelData->realVarsData[2].attribute.min = -DBL_MAX;
  modelData->realVarsData[2].attribute.max = DBL_MAX;
  modelData->realVarsData[2].attribute.fixed = 0;
  modelData->realVarsData[2].attribute.useNominal = 0;
  modelData->realVarsData[2].attribute.nominal = 1.0;
  modelData->realVarsData[2].attribute.start = 0.0;
  modelData->realVarsData[3].info.id = 1003;
  modelData->realVarsData[3].info.name = "y_sum";
  modelData->realVarsData[3].info.comment = "Sum of both inputs: u1 + u2";
  modelData->realVarsData[3].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro/CSPuro_SinME.mo";
  modelData->realVarsData[3].info.info.lineStart = 40;
  modelData->realVarsData[3].info.info.colStart = 3;
  modelData->realVarsData[3].info.info.lineEnd = 42;
  modelData->realVarsData[3].info.info.colEnd = 75;
  modelData->realVarsData[3].info.info.readonly = 0;
  modelData->realVarsData[3].attribute.unit = "";
  modelData->realVarsData[3].attribute.displayUnit = "";
  modelData->realVarsData[3].attribute.min = -DBL_MAX;
  modelData->realVarsData[3].attribute.max = DBL_MAX;
  modelData->realVarsData[3].attribute.fixed = 0;
  modelData->realVarsData[3].attribute.useNominal = 0;
  modelData->realVarsData[3].attribute.nominal = 1.0;
  modelData->realVarsData[3].attribute.start = 0.0;
  modelData->booleanVarsData[0].info.id = 1004;
  modelData->booleanVarsData[0].info.name = "active";
  modelData->booleanVarsData[0].info.comment = "TRUE when u1 is strictly greater than u2";
  modelData->booleanVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/CS_Puro/CSPuro_SinME.mo";
  modelData->booleanVarsData[0].info.info.lineStart = 48;
  modelData->booleanVarsData[0].info.info.colStart = 3;
  modelData->booleanVarsData[0].info.info.lineEnd = 50;
  modelData->booleanVarsData[0].info.info.colEnd = 77;
  modelData->booleanVarsData[0].info.info.readonly = 0;
  modelData->booleanVarsData[0].attribute.fixed = 0;
  modelData->booleanVarsData[0].attribute.start = 0;
}