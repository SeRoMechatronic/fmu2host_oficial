# Resumen de Test Battery — MultiplexorCanales

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 25 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-MC-001](TC-MC-001/report_TC-MC-001.md) | Seleccion canal 0 | ✅ | 3 | 0 |
| [TC-MC-002](TC-MC-002/report_TC-MC-002.md) | Seleccion canal 1 | ✅ | 3 | 0 |
| [TC-MC-003](TC-MC-003/report_TC-MC-003.md) | Seleccion canal 2 | ✅ | 2 | 0 |
| [TC-MC-004](TC-MC-004/report_TC-MC-004.md) | Seleccion canal 3 | ✅ | 2 | 0 |
| [TC-MC-005](TC-MC-005/report_TC-MC-005.md) | Selector invalido por defecto — demasiado bajo | ✅ | 3 | 0 |
| [TC-MC-006](TC-MC-006/report_TC-MC-006.md) | Selector invalido — demasiado alto | ✅ | 3 | 0 |
| [TC-MC-007](TC-MC-007/report_TC-MC-007.md) | Canal 0 con valor cero | ✅ | 3 | 0 |
| [TC-MC-008](TC-MC-008/report_TC-MC-008.md) | Canal 3 a escala completa | ✅ | 3 | 0 |
| [TC-MC-009](TC-MC-009/report_TC-MC-009.md) | Cambio de canal — conmutacion instantanea | ✅ | 2 | 0 |
| [TC-MC-010](TC-MC-010/report_TC-MC-010.md) | Valores limite del selector: 0 y 3 son validos | ✅ | 1 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `MultiplexorCanales` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 25 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
