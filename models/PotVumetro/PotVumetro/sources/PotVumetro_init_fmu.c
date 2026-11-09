#include "simulation_data.h"

OMC_DISABLE_OPT

void PotVumetro_read_simulation_info(SIMULATION_INFO* simulationInfo)
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

void PotVumetro_read_input_fmu(MODEL_DATA* modelData)
{
  modelData->realVarsData[0].info.id = 1000;
  modelData->realVarsData[0].info.name = "pot";
  modelData->realVarsData[0].info.comment = "Normalized potentiometer signal in range [0.0, 1.0]";
  modelData->realVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->realVarsData[0].info.info.lineStart = 28;
  modelData->realVarsData[0].info.info.colStart = 3;
  modelData->realVarsData[0].info.info.lineEnd = 32;
  modelData->realVarsData[0].info.info.colEnd = 74;
  modelData->realVarsData[0].info.info.readonly = 0;
  modelData->realVarsData[0].attribute.unit = "";
  modelData->realVarsData[0].attribute.displayUnit = "";
  modelData->realVarsData[0].attribute.min = 0.0;
  modelData->realVarsData[0].attribute.max = 1.0;
  modelData->realVarsData[0].attribute.fixed = 1;
  modelData->realVarsData[0].attribute.useNominal = 0;
  modelData->realVarsData[0].attribute.nominal = 1.0;
  modelData->realVarsData[0].attribute.start = 0.0;
  modelData->booleanVarsData[0].info.id = 1001;
  modelData->booleanVarsData[0].info.name = "led1";
  modelData->booleanVarsData[0].info.comment = "LED 1 (green)  — ON when pot >= 0.20";
  modelData->booleanVarsData[0].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->booleanVarsData[0].info.info.lineStart = 35;
  modelData->booleanVarsData[0].info.info.colStart = 3;
  modelData->booleanVarsData[0].info.info.lineEnd = 37;
  modelData->booleanVarsData[0].info.info.colEnd = 71;
  modelData->booleanVarsData[0].info.info.readonly = 0;
  modelData->booleanVarsData[0].attribute.fixed = 0;
  modelData->booleanVarsData[0].attribute.start = 0;
  modelData->booleanVarsData[1].info.id = 1002;
  modelData->booleanVarsData[1].info.name = "led2";
  modelData->booleanVarsData[1].info.comment = "LED 2 (green)  — ON when pot >= 0.40";
  modelData->booleanVarsData[1].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->booleanVarsData[1].info.info.lineStart = 39;
  modelData->booleanVarsData[1].info.info.colStart = 3;
  modelData->booleanVarsData[1].info.info.lineEnd = 41;
  modelData->booleanVarsData[1].info.info.colEnd = 71;
  modelData->booleanVarsData[1].info.info.readonly = 0;
  modelData->booleanVarsData[1].attribute.fixed = 0;
  modelData->booleanVarsData[1].attribute.start = 0;
  modelData->booleanVarsData[2].info.id = 1003;
  modelData->booleanVarsData[2].info.name = "led3";
  modelData->booleanVarsData[2].info.comment = "LED 3 (yellow) — ON when pot >= 0.60";
  modelData->booleanVarsData[2].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->booleanVarsData[2].info.info.lineStart = 43;
  modelData->booleanVarsData[2].info.info.colStart = 3;
  modelData->booleanVarsData[2].info.info.lineEnd = 45;
  modelData->booleanVarsData[2].info.info.colEnd = 70;
  modelData->booleanVarsData[2].info.info.readonly = 0;
  modelData->booleanVarsData[2].attribute.fixed = 0;
  modelData->booleanVarsData[2].attribute.start = 0;
  modelData->booleanVarsData[3].info.id = 1004;
  modelData->booleanVarsData[3].info.name = "led4";
  modelData->booleanVarsData[3].info.comment = "LED 4 (orange) — ON when pot >= 0.80";
  modelData->booleanVarsData[3].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->booleanVarsData[3].info.info.lineStart = 47;
  modelData->booleanVarsData[3].info.info.colStart = 3;
  modelData->booleanVarsData[3].info.info.lineEnd = 49;
  modelData->booleanVarsData[3].info.info.colEnd = 73;
  modelData->booleanVarsData[3].info.info.readonly = 0;
  modelData->booleanVarsData[3].attribute.fixed = 0;
  modelData->booleanVarsData[3].attribute.start = 0;
  modelData->booleanVarsData[4].info.id = 1005;
  modelData->booleanVarsData[4].info.name = "led5";
  modelData->booleanVarsData[4].info.comment = "LED 5 (red)    — ON when pot >= 1.00 (full scale)";
  modelData->booleanVarsData[4].info.info.filename = "C:/fmu2host/xxxx/OneDrive - UPV EHU/Escritorio/OMEdit_Examples/models/PotVumetro/PotVumetro.mo";
  modelData->booleanVarsData[4].info.info.lineStart = 51;
  modelData->booleanVarsData[4].info.info.colStart = 3;
  modelData->booleanVarsData[4].info.info.lineEnd = 53;
  modelData->booleanVarsData[4].info.info.colEnd = 73;
  modelData->booleanVarsData[4].info.info.readonly = 0;
  modelData->booleanVarsData[4].attribute.fixed = 0;
  modelData->booleanVarsData[4].attribute.start = 0;
}