# Resumen de Test Battery — PenduloNoLineal

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 15 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-PN-001](TC-PN-001/report_TC-PN-001.md) | Condiciones iniciales — angulo=2.618, omega=0 | ✅ | 4 | 0 |
| [TC-PN-002](TC-PN-002/report_TC-PN-002.md) | Velocidad maxima en el fondo (theta≈0) | ✅ | 1 | 0 |
| [TC-PN-003](TC-PN-003/report_TC-PN-003.md) | Oscilacion simetrica — angulo minimo ≈ -2.618 | ✅ | 1 | 0 |
| [TC-PN-004](TC-PN-004/report_TC-PN-004.md) | Conservacion de energia con RK4 (h=0.05, 10 s) | ✅ | 1 | 0 |
| [TC-PN-005](TC-PN-005/report_TC-PN-005.md) | Deriva energetica con Euler — discriminador | ✅ | 1 | 0 |
| [TC-PN-006](TC-PN-006/report_TC-PN-006.md) | en_reposo activa al menos 4 veces en 15 s | ✅ | 1 | 0 |
| [TC-PN-007](TC-PN-007/report_TC-PN-007.md) | Angulo acotado dentro de [-3.2, 3.2] rad | ✅ | 1 | 0 |
| [TC-PN-008](TC-PN-008/report_TC-PN-008.md) | Estimacion del periodo de gran angulo | ✅ | 1 | 0 |
| [TC-PN-009](TC-PN-009/report_TC-PN-009.md) | Sin NaN ni Inf en 30 s | ✅ | 3 | 0 |
| [TC-PN-010](TC-PN-010/report_TC-PN-010.md) | Comparacion energetica RK4 vs Euler en t=5 s | ✅ | 1 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `PenduloNoLineal` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 15 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
