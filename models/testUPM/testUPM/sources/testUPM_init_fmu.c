#include "simulation_data.h"

OMC_DISABLE_OPT

void testUPM_read_simulation_info(SIMULATION_INFO* simulationInfo)
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

void testUPM_read_input_fmu(MODEL_DATA* modelData)
{
  modelData->realVarsData[0].info.id = 1000;
  modelData->realVarsData[0].info.name = "pot";
  modelData->realVarsData[0].info.comment = "Señal del potenciómetro, rango normalizado 0.0 a 1.0";
  modelData->realVarsData[0].info.info.filename = "testUPM";
  modelData->realVarsData[0].info.info.lineStart = 4;
  modelData->realVarsData[0].info.info.colStart = 3;
  modelData->realVarsData[0].info.info.lineEnd = 5;
  modelData->realVarsData[0].info.info.colEnd = 67;
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
  modelData->booleanVarsData[0].info.comment = "LED 1 — encendido si pot >= 0.2";
  modelData->booleanVarsData[0].info.info.filename = "testUPM";
  modelData->booleanVarsData[0].info.info.lineStart = 7;
  modelData->booleanVarsData[0].info.info.colStart = 3;
  modelData->booleanVarsData[0].info.info.lineEnd = 8;
  modelData->booleanVarsData[0].info.info.colEnd = 64;
  modelData->booleanVarsData[0].info.info.readonly = 0;
  modelData->booleanVarsData[0].attribute.fixed = 0;
  modelData->booleanVarsData[0].attribute.start = 0;
  modelData->booleanVarsData[1].info.id = 1002;
  modelData->booleanVarsData[1].info.name = "led2";
  modelData->booleanVarsData[1].info.comment = "LED 2 — encendido si pot >= 0.4";
  modelData->booleanVarsData[1].info.info.filename = "testUPM";
  modelData->booleanVarsData[1].info.info.lineStart = 9;
  modelData->booleanVarsData[1].info.info.colStart = 3;
  modelData->booleanVarsData[1].info.info.lineEnd = 10;
  modelData->booleanVarsData[1].info.info.colEnd = 64;
  modelData->booleanVarsData[1].info.info.readonly = 0;
  modelData->booleanVarsData[1].attribute.fixed = 0;
  modelData->booleanVarsData[1].attribute.start = 0;
  modelData->booleanVarsData[2].info.id = 1003;
  modelData->booleanVarsData[2].info.name = "led3";
  modelData->booleanVarsData[2].info.comment = "LED 3 — encendido si pot >= 0.6";
  modelData->booleanVarsData[2].info.info.filename = "testUPM";
  modelData->booleanVarsData[2].info.info.lineStart = 11;
  modelData->booleanVarsData[2].info.info.colStart = 3;
  modelData->booleanVarsData[2].info.info.lineEnd = 12;
  modelData->booleanVarsData[2].info.info.colEnd = 63;
  modelData->booleanVarsData[2].info.info.readonly = 0;
  modelData->booleanVarsData[2].attribute.fixed = 0;
  modelData->booleanVarsData[2].attribute.start = 0;
  modelData->booleanVarsData[3].info.id = 1004;
  modelData->booleanVarsData[3].info.name = "led4";
  modelData->booleanVarsData[3].info.comment = "LED 4 — encendido si pot >= 0.8";
  modelData->booleanVarsData[3].info.info.filename = "testUPM";
  modelData->booleanVarsData[3].info.info.lineStart = 13;
  modelData->booleanVarsData[3].info.info.colStart = 3;
  modelData->booleanVarsData[3].info.info.lineEnd = 14;
  modelData->booleanVarsData[3].info.info.colEnd = 66;
  modelData->booleanVarsData[3].info.info.readonly = 0;
  modelData->booleanVarsData[3].attribute.fixed = 0;
  modelData->booleanVarsData[3].attribute.start = 0;
  modelData->booleanVarsData[4].info.id = 1005;
  modelData->booleanVarsData[4].info.name = "led5";
  modelData->booleanVarsData[4].info.comment = "LED 5 — encendido solo si pot = 1.0 (al tope)";
  modelData->booleanVarsData[4].info.info.filename = "testUPM";
  modelData->booleanVarsData[4].info.info.lineStart = 15;
  modelData->booleanVarsData[4].info.info.colStart = 3;
  modelData->booleanVarsData[4].info.info.lineEnd = 16;
  modelData->booleanVarsData[4].info.info.colEnd = 66;
  modelData->booleanVarsData[4].info.info.readonly = 0;
  modelData->booleanVarsData[4].attribute.fixed = 0;
  modelData->booleanVarsData[4].attribute.start = 0;
}