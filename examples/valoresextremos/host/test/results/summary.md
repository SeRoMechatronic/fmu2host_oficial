# Resumen de Test Battery — ValoresExtremos

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 42 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-VE-001](TC-VE-001/report_TC-VE-001.md) | u=0.0 — division por cero y log de cero protegidos | ✅ | 6 | 0 |
| [TC-VE-002](TC-VE-002/report_TC-VE-002.md) | u=-5.0 — negativo: sqrt y log protegidos | ✅ | 5 | 0 |
| [TC-VE-003](TC-VE-003/report_TC-VE-003.md) | u=1.0 — valor nominal: todas las operaciones validas | ✅ | 5 | 0 |
| [TC-VE-004](TC-VE-004/report_TC-VE-004.md) | u=-1.0 — simetrico al nominal positivo | ✅ | 4 | 0 |
| [TC-VE-005](TC-VE-005/report_TC-VE-005.md) | u=2.0 — por encima de saturacion | ✅ | 3 | 0 |
| [TC-VE-006](TC-VE-006/report_TC-VE-006.md) | u=-10.0 — saturacion profunda negativa | ✅ | 3 | 0 |
| [TC-VE-007](TC-VE-007/report_TC-VE-007.md) | u=1e-11 — por debajo del umbral de guarda | ✅ | 4 | 0 |
| [TC-VE-008](TC-VE-008/report_TC-VE-008.md) | u=1e30 — cerca de Inf, es_finito=false | ✅ | 4 | 0 |
| [TC-VE-009](TC-VE-009/report_TC-VE-009.md) | u=100 — valor tipico positivo con resultados conocidos | ✅ | 4 | 0 |
| [TC-VE-010](TC-VE-010/report_TC-VE-010.md) | Sin NaN ni Inf en todos los casos — barrido completo | ✅ | 4 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `ValoresExtremos` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 42 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
