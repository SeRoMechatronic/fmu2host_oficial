# Resumen de Test Battery — StringInputOutput

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 27 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-SIO-001](TC-SIO-001/report_TC-SIO-001.md) | Rango nominal — scaled_value=82.5, alarm=false | ✅ | 2 | 0 |
| [TC-SIO-002](TC-SIO-002/report_TC-SIO-002.md) | Valor por encima del limite superior — alarm=true | ✅ | 2 | 0 |
| [TC-SIO-003](TC-SIO-003/report_TC-SIO-003.md) | Valor por debajo del limite inferior — alarm=true | ✅ | 2 | 0 |
| [TC-SIO-004](TC-SIO-004/report_TC-SIO-004.md) | Frontera exacta superior — value=100.0, NORMAL (operador estricto) | ✅ | 2 | 0 |
| [TC-SIO-005](TC-SIO-005/report_TC-SIO-005.md) | Ligeramente por encima del umbral inferior — value=10.1, NORMAL | ✅ | 2 | 0 |
| [TC-SIO-006](TC-SIO-006/report_TC-SIO-006.md) | Valor cero — alarm=true (por debajo del minimo) | ✅ | 2 | 0 |
| [TC-SIO-007](TC-SIO-007/report_TC-SIO-007.md) | Valor maximo practico — alarm=true, sin desbordamiento | ✅ | 3 | 0 |
| [TC-SIO-008](TC-SIO-008/report_TC-SIO-008.md) | Cambio de valor que cruza todas las fronteras | ✅ | 6 | 0 |
| [TC-SIO-009](TC-SIO-009/report_TC-SIO-009.md) | Estabilidad — alarm siempre correcta en simulacion larga | ✅ | 3 | 0 |
| [TC-SIO-010](TC-SIO-010/report_TC-SIO-010.md) | Valor negativo — alarm=true, scaled_value negativo | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `StringInputOutput` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 27 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
