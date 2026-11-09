# Resumen de Test Battery — CrecimientoPoblacional

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 18 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-CP-001](TC-CP-001/report_TC-CP-001.md) | Condiciones iniciales — N(0)=2 | ✅ | 4 | 0 |
| [TC-CP-002](TC-CP-002/report_TC-CP-002.md) | Convergencia a K con RK4 (t=5 s) — sin sobredisparo | ✅ | 2 | 0 |
| [TC-CP-003](TC-CP-003/report_TC-CP-003.md) | Sobredisparo de Euler — discriminador de integrador | ✅ | 1 | 0 |
| [TC-CP-004](TC-CP-004/report_TC-CP-004.md) | Pico de tasa de crecimiento cerca de N=50 | ✅ | 1 | 0 |
| [TC-CP-005](TC-CP-005/report_TC-CP-005.md) | RK4 converge monotonamente — sin oscilacion alrededor de K | ✅ | 2 | 0 |
| [TC-CP-006](TC-CP-006/report_TC-CP-006.md) | Saturacion cerca de 1.0 a largo plazo | ✅ | 1 | 0 |
| [TC-CP-007](TC-CP-007/report_TC-CP-007.md) | Inmigracion positiva — equilibrio por encima de K | ✅ | 1 | 0 |
| [TC-CP-008](TC-CP-008/report_TC-CP-008.md) | Emigracion negativa — equilibrio por debajo de K | ✅ | 1 | 0 |
| [TC-CP-009](TC-CP-009/report_TC-CP-009.md) | Cambio de tasa de inmigracion en t=2 s | ✅ | 2 | 0 |
| [TC-CP-010](TC-CP-010/report_TC-CP-010.md) | Sin NaN ni Inf con RK4 en 10 s | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `CrecimientoPoblacional` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 18 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
