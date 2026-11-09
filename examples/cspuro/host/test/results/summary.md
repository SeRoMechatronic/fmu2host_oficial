# Resumen de Test Battery — CSPuro_SinME

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 30 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-CS-001](TC-CS-001/report_TC-CS-001.md) | Valores positivos basicos — u1 > u2 | ✅ | 3 | 0 |
| [TC-CS-002](TC-CS-002/report_TC-CS-002.md) | Valores iguales — limite estricto de active | ✅ | 3 | 0 |
| [TC-CS-003](TC-CS-003/report_TC-CS-003.md) | u1 menor que u2 | ✅ | 3 | 0 |
| [TC-CS-004](TC-CS-004/report_TC-CS-004.md) | Entradas negativas — producto positivo | ✅ | 3 | 0 |
| [TC-CS-005](TC-CS-005/report_TC-CS-005.md) | Entradas cero — sin division ni NaN | ✅ | 4 | 0 |
| [TC-CS-006](TC-CS-006/report_TC-CS-006.md) | Valores grandes — precision numerica | ✅ | 2 | 0 |
| [TC-CS-007](TC-CS-007/report_TC-CS-007.md) | Signo mixto — u1 negativo, u2 positivo | ✅ | 3 | 0 |
| [TC-CS-008](TC-CS-008/report_TC-CS-008.md) | Cambio de entrada a mitad — respuesta inmediata | ✅ | 3 | 0 |
| [TC-CS-009](TC-CS-009/report_TC-CS-009.md) | Valores muy pequeños — cerca de epsilon maquina | ✅ | 3 | 0 |
| [TC-CS-010](TC-CS-010/report_TC-CS-010.md) | Verificacion estructural — sin solver ODE en CS | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `CSPuro_SinME` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 30 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
