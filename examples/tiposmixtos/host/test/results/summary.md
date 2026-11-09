# Resumen de Test Battery — TiposMixtos

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 31 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-TM-001](TC-TM-001/report_TC-TM-001.md) | Valores nominales — todos los tipos activos | ✅ | 4 | 0 |
| [TC-TM-002](TC-TM-002/report_TC-TM-002.md) | Real negativo, entero cero, booleano false | ✅ | 4 | 0 |
| [TC-TM-003](TC-TM-003/report_TC-TM-003.md) | Real cero | ✅ | 4 | 0 |
| [TC-TM-004](TC-TM-004/report_TC-TM-004.md) | Entero negativo | ✅ | 3 | 0 |
| [TC-TM-005](TC-TM-005/report_TC-TM-005.md) | Real grande | ✅ | 3 | 0 |
| [TC-TM-006](TC-TM-006/report_TC-TM-006.md) | Real muy pequeño | ✅ | 3 | 0 |
| [TC-TM-007](TC-TM-007/report_TC-TM-007.md) | Entero cerca del maximo de int32 | ✅ | 1 | 0 |
| [TC-TM-008](TC-TM-008/report_TC-TM-008.md) | Bascule booleano — tres pasos | ✅ | 3 | 0 |
| [TC-TM-009](TC-TM-009/report_TC-TM-009.md) | Cambios simultaneos de todos los tipos | ✅ | 4 | 0 |
| [TC-TM-010](TC-TM-010/report_TC-TM-010.md) | Sin NaN ni Inf en todos los tipos | ✅ | 2 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `TiposMixtos` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 31 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
