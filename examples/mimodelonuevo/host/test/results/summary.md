# Resumen de Test Battery — Mi_Modelo_Nuevo

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 20 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-MN-001](TC-MN-001/report_TC-MN-001.md) | Condiciones iniciales — filtro en reposo | ✅ | 2 | 0 |
| [TC-MN-002](TC-MN-002/report_TC-MN-002.md) | Respuesta al escalon — 63% en t=tau=1.0 s | ✅ | 2 | 0 |
| [TC-MN-003](TC-MN-003/report_TC-MN-003.md) | Respuesta al escalon — 99.3% en t=5·tau=5.0 s | ✅ | 2 | 0 |
| [TC-MN-004](TC-MN-004/report_TC-MN-004.md) | Cruce de umbral flag_salida en t≈0.693 s | ✅ | 2 | 0 |
| [TC-MN-005](TC-MN-005/report_TC-MN-005.md) | Desactivacion — decaimiento exponencial al desactivar filtro | ✅ | 3 | 0 |
| [TC-MN-006](TC-MN-006/report_TC-MN-006.md) | Escalon de entrada de 1.0 a 2.0 en t=5 s | ✅ | 2 | 0 |
| [TC-MN-007](TC-MN-007/report_TC-MN-007.md) | Entrada grande — sin saturacion | ✅ | 2 | 0 |
| [TC-MN-008](TC-MN-008/report_TC-MN-008.md) | Entrada negativa — filtro rastrea valores negativos | ✅ | 2 | 0 |
| [TC-MN-009](TC-MN-009/report_TC-MN-009.md) | Salida siempre positiva y creciente durante activacion | ✅ | 2 | 0 |
| [TC-MN-010](TC-MN-010/report_TC-MN-010.md) | Sin NaN ni Inf en simulacion completa | ✅ | 1 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `Mi_Modelo_Nuevo` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 20 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
