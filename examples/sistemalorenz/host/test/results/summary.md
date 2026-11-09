# Resumen de Test Battery — SistemaLorenz

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 19 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-LZ-001](TC-LZ-001/report_TC-LZ-001.md) | Condiciones iniciales — t=0 | ✅ | 4 | 0 |
| [TC-LZ-002](TC-LZ-002/report_TC-LZ-002.md) | z siempre positivo con RK4 (30 s) | ✅ | 2 | 0 |
| [TC-LZ-003](TC-LZ-003/report_TC-LZ-003.md) | on_attractor siempre TRUE con RK4 (30 s) — criterio principal | ✅ | 1 | 0 |
| [TC-LZ-004](TC-LZ-004/report_TC-LZ-004.md) | on_attractor FALSE con Euler h=0.04 — discriminador de integrador | ✅ | 1 | 0 |
| [TC-LZ-005](TC-LZ-005/report_TC-LZ-005.md) | x oscila entre positivo y negativo — estructura bilobulo | ✅ | 1 | 0 |
| [TC-LZ-006](TC-LZ-006/report_TC-LZ-006.md) | z acotado por debajo de 55 (RK4) | ✅ | 1 | 0 |
| [TC-LZ-007](TC-LZ-007/report_TC-LZ-007.md) | Limites de x e y con RK4 | ✅ | 2 | 0 |
| [TC-LZ-008](TC-LZ-008/report_TC-LZ-008.md) | Verificacion analitica en t=0.1 s | ✅ | 3 | 0 |
| [TC-LZ-009](TC-LZ-009/report_TC-LZ-009.md) | Divergencia rapida con Euler y paso grande | ✅ | 1 | 0 |
| [TC-LZ-010](TC-LZ-010/report_TC-LZ-010.md) | Sin NaN ni Inf con RK4 en 50 s | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `SistemaLorenz` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 19 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
