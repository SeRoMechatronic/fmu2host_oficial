# Resumen de Test Battery — NivelDeposito

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 22 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-ND-001](TC-ND-001/report_TC-ND-001.md) | Estado estacionario en setpoint — valvula cerrada | ✅ | 4 | 0 |
| [TC-ND-002](TC-ND-002/report_TC-ND-002.md) | Nivel exactamente en umbral minimo — sin alarma | ✅ | 2 | 0 |
| [TC-ND-003](TC-ND-003/report_TC-ND-003.md) | Nivel por debajo del umbral minimo — alarma activa | ✅ | 2 | 0 |
| [TC-ND-004](TC-ND-004/report_TC-ND-004.md) | Nivel exactamente en umbral maximo — sin alarma | ✅ | 2 | 0 |
| [TC-ND-005](TC-ND-005/report_TC-ND-005.md) | Nivel por encima del umbral maximo — alarma alta | ✅ | 2 | 0 |
| [TC-ND-006](TC-ND-006/report_TC-ND-006.md) | Valvula manual abierta — compensacion feedforward | ✅ | 1 | 0 |
| [TC-ND-007](TC-ND-007/report_TC-ND-007.md) | Nivel bajo con valvula abierta — demanda combinada | ✅ | 2 | 0 |
| [TC-ND-008](TC-ND-008/report_TC-ND-008.md) | Deposito vacio — bomba al maximo | ✅ | 2 | 0 |
| [TC-ND-009](TC-ND-009/report_TC-ND-009.md) | Deposito lleno — bomba apagada | ✅ | 3 | 0 |
| [TC-ND-010](TC-ND-010/report_TC-ND-010.md) | Transitorio del filtro — sensor baja de 0.5 a 0.2 en t=2 s | ✅ | 2 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `NivelDeposito` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 22 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
