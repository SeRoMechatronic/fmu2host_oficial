# Resumen de Test Battery — SelectorModo

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 26 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-SM-001](TC-SM-001/report_TC-SM-001.md) | Modo Manual — consigna pasada directamente | ✅ | 3 | 0 |
| [TC-SM-002](TC-SM-002/report_TC-SM-002.md) | Modo Manual — consigna minima | ✅ | 2 | 0 |
| [TC-SM-003](TC-SM-003/report_TC-SM-003.md) | Modo Manual — consigna maxima | ✅ | 2 | 0 |
| [TC-SM-004](TC-SM-004/report_TC-SM-004.md) | Modo Manual — consigna recortada por encima de 1.0 | ✅ | 2 | 0 |
| [TC-SM-005](TC-SM-005/report_TC-SM-005.md) | Modo Manual — consigna recortada por debajo de 0.0 | ✅ | 2 | 0 |
| [TC-SM-006](TC-SM-006/report_TC-SM-006.md) | Modo Automatico — salida fija al 50% | ✅ | 3 | 0 |
| [TC-SM-007](TC-SM-007/report_TC-SM-007.md) | Modo Emergencia — salida forzada a cero | ✅ | 3 | 0 |
| [TC-SM-008](TC-SM-008/report_TC-SM-008.md) | Modo invalido — por debajo del rango | ✅ | 3 | 0 |
| [TC-SM-009](TC-SM-009/report_TC-SM-009.md) | Modo invalido — por encima del rango | ✅ | 3 | 0 |
| [TC-SM-010](TC-SM-010/report_TC-SM-010.md) | Limite de modo — exactamente 2 es Emergencia valida | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `SelectorModo` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 26 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
