# Resumen de Test Battery — CuerposAcoplados

> Generado: 2026-11-09 17:21

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
| [TC-CA-001](TC-CA-001/report_TC-CA-001.md) | Condiciones iniciales en t=0 | ✅ | 6 | 0 |
| [TC-CA-002](TC-CA-002/report_TC-CA-002.md) | Conservacion de energia con RK4 — 20 s | ✅ | 2 | 0 |
| [TC-CA-003](TC-CA-003/report_TC-CA-003.md) | Deriva de energia con Euler — discriminador de integrador | ✅ | 2 | 0 |
| [TC-CA-004](TC-CA-004/report_TC-CA-004.md) | Transiciones de en_fase — batido de modos | ✅ | 2 | 0 |
| [TC-CA-005](TC-CA-005/report_TC-CA-005.md) | Ambas masas oscilan cruzando cero — resortes de pared activos | ✅ | 4 | 0 |
| [TC-CA-006](TC-CA-006/report_TC-CA-006.md) | Fuerza externa aumenta energia — F=5 N durante 5 s | ✅ | 2 | 0 |
| [TC-CA-007](TC-CA-007/report_TC-CA-007.md) | Fuerza → 0 conserva energia tras la actuacion | ✅ | 3 | 0 |
| [TC-CA-008](TC-CA-008/report_TC-CA-008.md) | Buffer de 4 estados — ausencia de NaN/Inf en toda la simulacion | ✅ | 5 | 0 |
| [TC-CA-009](TC-CA-009/report_TC-CA-009.md) | Amplitudes acotadas — estabilidad a largo plazo | ✅ | 2 | 0 |
| [TC-CA-010](TC-CA-010/report_TC-CA-010.md) | Independencia de fuerza cero y fuerza maxima | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `CuerposAcoplados` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 31 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
