# Resumen de Test Battery — PotVumetro

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 12 |
| Test cases PASS | 12 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 41 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-PV-001](TC-PV-001/report_TC-PV-001.md) | Todos los LEDs apagados — por debajo del primer umbral | ✅ | 5 | 0 |
| [TC-PV-002](TC-PV-002/report_TC-PV-002.md) | Justo encima umbral LED1 — pot=0.21 | ✅ | 5 | 0 |
| [TC-PV-003](TC-PV-003/report_TC-PV-003.md) | Justo debajo del umbral de LED1 — pot=0.199 | ✅ | 2 | 0 |
| [TC-PV-004](TC-PV-004/report_TC-PV-004.md) | Entre LED1 y LED2 — pot=0.30 | ✅ | 3 | 0 |
| [TC-PV-005](TC-PV-005/report_TC-PV-005.md) | Justo encima umbral LED2 — pot=0.41 | ✅ | 3 | 0 |
| [TC-PV-006](TC-PV-006/report_TC-PV-006.md) | Justo encima umbral LED3 — pot=0.61 | ✅ | 4 | 0 |
| [TC-PV-007](TC-PV-007/report_TC-PV-007.md) | Justo encima umbral LED4 — pot=0.81 | ✅ | 5 | 0 |
| [TC-PV-008](TC-PV-008/report_TC-PV-008.md) | Justo por debajo de escala completa — pot=0.999 | ✅ | 2 | 0 |
| [TC-PV-009](TC-PV-009/report_TC-PV-009.md) | Escala completa — LED1-LED4 encendidos, LED5 por hysteresis | ✅ | 5 | 0 |
| [TC-PV-010](TC-PV-010/report_TC-PV-010.md) | Valor a mitad de rango — pot=0.50 | ✅ | 3 | 0 |
| [TC-PV-011](TC-PV-011/report_TC-PV-011.md) | Entrada fuera de rango — negativa | ✅ | 2 | 0 |
| [TC-PV-012](TC-PV-012/report_TC-PV-012.md) | Entrada fuera de rango — positiva alta | ✅ | 2 | 0 |

## Analisis del modelo

**TODOS LOS 12 TESTS PASAN (100%).**

El modelo `PotVumetro` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 41 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
