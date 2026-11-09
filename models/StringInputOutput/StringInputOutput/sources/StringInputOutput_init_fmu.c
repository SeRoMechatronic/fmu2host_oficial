#include "simulation_data.h"

OMC_DISABLE_OPT

void StringInputOutput_read_simulation_info(SIMULATION_INFO* simulationInfo)
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

void StringInputOutput_read_input_fmu(MODEL_DATA* modelData)
{
  modelData->realVarsData[0].info.id = 1000;
  modelData->realVarsData[0].info.name = "scaled_value";
  modelData->realVarsData[0].info.comment = "Input value multiplied by 1.5";
  modelData->realVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->realVarsData[0].info.info.lineStart = 47;
  modelData->realVarsData[0].info.info.colStart = 3;
  modelData->realVarsData[0].info.info.lineEnd = 49;
  modelData->realVarsData[0].info.info.colEnd = 75;
  modelData->realVarsData[0].info.info.readonly = 0;
  modelData->realVarsData[0].attribute.unit = "";
  modelData->realVarsData[0].attribute.displayUnit = "";
  modelData->realVarsData[0].attribute.min = -DBL_MAX;
  modelData->realVarsData[0].attribute.max = DBL_MAX;
  modelData->realVarsData[0].attribute.fixed = 0;
  modelData->realVarsData[0].attribute.useNominal = 0;
  modelData->realVarsData[0].attribute.nominal = 1.0;
  modelData->realVarsData[0].attribute.start = 0.0;
  modelData->realVarsData[1].info.id = 1001;
  modelData->realVarsData[1].info.name = "value";
  modelData->realVarsData[1].info.comment = "Sensor reading — expected range [0.0, 200.0]";
  modelData->realVarsData[1].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->realVarsData[1].info.info.lineStart = 34;
  modelData->realVarsData[1].info.info.colStart = 3;
  modelData->realVarsData[1].info.info.lineEnd = 36;
  modelData->realVarsData[1].info.info.colEnd = 77;
  modelData->realVarsData[1].info.info.readonly = 0;
  modelData->realVarsData[1].attribute.unit = "";
  modelData->realVarsData[1].attribute.displayUnit = "";
  modelData->realVarsData[1].attribute.min = -DBL_MAX;
  modelData->realVarsData[1].attribute.max = DBL_MAX;
  modelData->realVarsData[1].attribute.fixed = 1;
  modelData->realVarsData[1].attribute.useNominal = 0;
  modelData->realVarsData[1].attribute.nominal = 1.0;
  modelData->realVarsData[1].attribute.start = 0.0;
  modelData->booleanVarsData[0].info.id = 1002;
  modelData->booleanVarsData[0].info.name = "alarm";
  modelData->booleanVarsData[0].info.comment = "TRUE when value is outside the normal range [10.0, 100.0]";
  modelData->booleanVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->booleanVarsData[0].info.info.lineStart = 51;
  modelData->booleanVarsData[0].info.info.colStart = 3;
  modelData->booleanVarsData[0].info.info.lineEnd = 53;
  modelData->booleanVarsData[0].info.info.colEnd = 76;
  modelData->booleanVarsData[0].info.info.readonly = 0;
  modelData->booleanVarsData[0].attribute.fixed = 0;
  modelData->booleanVarsData[0].attribute.start = 0;
  modelData->stringVarsData[0].info.id = 1003;
  modelData->stringVarsData[0].info.name = "alert_msg";
  modelData->stringVarsData[0].info.comment = "Human-readable alert string, empty string when NORMAL";
  modelData->stringVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->stringVarsData[0].info.info.lineStart = 59;
  modelData->stringVarsData[0].info.info.colStart = 3;
  modelData->stringVarsData[0].info.info.lineEnd = 61;
  modelData->stringVarsData[0].info.info.colEnd = 49;
  modelData->stringVarsData[0].info.info.readonly = 0;
  modelData->stringVarsData[0].attribute.start = mmc_mk_scon("");
  modelData->stringVarsData[1].info.id = 1004;
  modelData->stringVarsData[1].info.name = "mode_operation";
  modelData->stringVarsData[1].info.comment = "Operating mode identifier — runtime String input (e.g. AUTO, MANUAL, TEST)";
  modelData->stringVarsData[1].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->stringVarsData[1].info.info.lineStart = 38;
  modelData->stringVarsData[1].info.info.colStart = 3;
  modelData->stringVarsData[1].info.info.lineEnd = 40;
  modelData->stringVarsData[1].info.info.colEnd = 48;
  modelData->stringVarsData[1].info.info.readonly = 0;
  modelData->stringVarsData[1].attribute.start = mmc_mk_scon("");
  modelData->stringVarsData[2].info.id = 1005;
  modelData->stringVarsData[2].info.name = "status";
  modelData->stringVarsData[2].info.comment = "Classification of the sensor value: HIGH | NORMAL | LOW";
  modelData->stringVarsData[2].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->stringVarsData[2].info.info.lineStart = 55;
  modelData->stringVarsData[2].info.info.colStart = 3;
  modelData->stringVarsData[2].info.info.lineEnd = 57;
  modelData->stringVarsData[2].info.info.colEnd = 49;
  modelData->stringVarsData[2].info.info.readonly = 0;
  modelData->stringVarsData[2].attribute.start = mmc_mk_scon("");
  modelData->stringVarsData[3].info.id = 1006;
  modelData->stringVarsData[3].info.name = "tag_sensor";
  modelData->stringVarsData[3].info.comment = "Sensor tag — runtime String input identifying the data source";
  modelData->stringVarsData[3].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/StringInputOutput/StringInputOutput.mo";
  modelData->stringVarsData[3].info.info.lineStart = 42;
  modelData->stringVarsData[3].info.info.colStart = 3;
  modelData->stringVarsData[3].info.info.lineEnd = 44;
  modelData->stringVarsData[3].info.info.colEnd = 48;
  modelData->stringVarsData[3].info.info.readonly = 0;
  modelData->stringVarsData[3].attribute.start = mmc_mk_scon("");
}