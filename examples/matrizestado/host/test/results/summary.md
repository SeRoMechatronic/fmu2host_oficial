# Resumen de Test Battery — MatrizEstado

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 6 (60%) |
| Test cases FAIL | 4 |
| Checks individuales PASS | 16 |
| Checks individuales FAIL | 11 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-MZ-001](TC-MZ-001/report_TC-MZ-001.md) | Condiciones iniciales — todos los estados en cero | ✅ | 5 | 0 |
| [TC-MZ-002](TC-MZ-002/report_TC-MZ-002.md) | Traza constante en todo momento | ✅ | 1 | 0 |
| [TC-MZ-003](TC-MZ-003/report_TC-MZ-003.md) | Ordenacion de estados: x3 > x2 > x1 para u>0 | ❌ | 0 | 3 |
| [TC-MZ-004](TC-MZ-004/report_TC-MZ-004.md) | Verificacion analitica en t=1.0 s | ❌ | 0 | 3 |
| [TC-MZ-005](TC-MZ-005/report_TC-MZ-005.md) | Norma creciente con u>0 | ✅ | 1 | 0 |
| [TC-MZ-006](TC-MZ-006/report_TC-MZ-006.md) | Entrada cero — estados permanecen en cero | ✅ | 4 | 0 |
| [TC-MZ-007](TC-MZ-007/report_TC-MZ-007.md) | Entrada negativa — estados negativos con mismo ordenamiento | ❌ | 0 | 3 |
| [TC-MZ-008](TC-MZ-008/report_TC-MZ-008.md) | Cambio de entrada en t=1 s — sistema inestable sigue creciendo | ❌ | 0 | 2 |
| [TC-MZ-009](TC-MZ-009/report_TC-MZ-009.md) | Traza no cambia con entrada | ✅ | 1 | 0 |
| [TC-MZ-010](TC-MZ-010/report_TC-MZ-010.md) | Sin NaN ni Inf en 2 segundos | ✅ | 4 | 0 |

## Analisis del modelo

**4 TEST(S) FALLAN (60% de tasa de exito).**

Test cases con fallos:
- **TC-MZ-003** — Ordenacion de estados: x3 > x2 > x1 para u>0 (3 check(s) fallados)
- **TC-MZ-004** — Verificacion analitica en t=1.0 s (3 check(s) fallados)
- **TC-MZ-007** — Entrada negativa — estados negativos con mismo ordenamiento (3 check(s) fallados)
- **TC-MZ-008** — Cambio de entrada en t=1 s — sistema inestable sigue creciendo (2 check(s) fallados)

Se recomienda revisar el codegen para los escenarios indicados.
