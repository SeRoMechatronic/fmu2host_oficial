# Resumen de Test Battery — BooleanLogica

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 4 (40%) |
| Test cases FAIL | 6 |
| Checks individuales PASS | 23 |
| Checks individuales FAIL | 14 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-BL-001](TC-BL-001/report_TC-BL-001.md) | Tabla de verdad AND/OR/XOR — caso a=F b=F | ✅ | 3 | 0 |
| [TC-BL-002](TC-BL-002/report_TC-BL-002.md) | XOR: a=TRUE b=TRUE → y_xor=FALSE | ✅ | 3 | 0 |
| [TC-BL-003](TC-BL-003/report_TC-BL-003.md) | XOR: a=FALSE b=TRUE → y_xor=TRUE | ✅ | 4 | 0 |
| [TC-BL-004](TC-BL-004/report_TC-BL-004.md) | above_threshold: umbral > 0.5 → TRUE, umbral <= 0.5 → FALSE | ✅ | 2 | 0 |
| [TC-BL-005](TC-BL-005/report_TC-BL-005.md) | D-latch: captura a=TRUE en flanco ascendente de clk | ❌ | 1 | 2 |
| [TC-BL-006](TC-BL-006/report_TC-BL-006.md) | D-latch: captura a=FALSE en flanco — latch no es level-triggered | ❌ | 2 | 1 |
| [TC-BL-007](TC-BL-007/report_TC-BL-007.md) | Contador de flancos — 3 flancos ascendentes | ❌ | 0 | 3 |
| [TC-BL-008](TC-BL-008/report_TC-BL-008.md) | Sin doble conteo — clk=TRUE mantenido no cuenta multiples flancos | ❌ | 0 | 4 |
| [TC-BL-009](TC-BL-009/report_TC-BL-009.md) | Todos los inputs activos simultaneamente — salidas combinadas | ❌ | 4 | 2 |
| [TC-BL-010](TC-BL-010/report_TC-BL-010.md) | Reset a cero — outputs combinacionales inmediatos, secuenciales retenidos | ❌ | 4 | 2 |

## Analisis del modelo

**6 TEST(S) FALLAN (40% de tasa de exito).**

Test cases con fallos:
- **TC-BL-005** — D-latch: captura a=TRUE en flanco ascendente de clk (2 check(s) fallados)
- **TC-BL-006** — D-latch: captura a=FALSE en flanco — latch no es level-triggered (1 check(s) fallados)
- **TC-BL-007** — Contador de flancos — 3 flancos ascendentes (3 check(s) fallados)
- **TC-BL-008** — Sin doble conteo — clk=TRUE mantenido no cuenta multiples flancos (4 check(s) fallados)
- **TC-BL-009** — Todos los inputs activos simultaneamente — salidas combinadas (2 check(s) fallados)
- **TC-BL-010** — Reset a cero — outputs combinacionales inmediatos, secuenciales retenidos (2 check(s) fallados)

Se recomienda revisar el codegen para los escenarios indicados.
