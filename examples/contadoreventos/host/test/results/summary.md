# Resumen de Test Battery — ContadorEventos

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 2 (20%) |
| Test cases FAIL | 8 |
| Checks individuales PASS | 15 |
| Checks individuales FAIL | 16 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-CE-001](TC-CE-001/report_TC-CE-001.md) | Estado inicial — contador en cero | ✅ | 4 | 0 |
| [TC-CE-002](TC-CE-002/report_TC-CE-002.md) | Un solo evento — contador pasa a 1 | ❌ | 2 | 2 |
| [TC-CE-003](TC-CE-003/report_TC-CE-003.md) | Diez eventos — descomposicion BCD: decenas=1, unidades=0 | ❌ | 1 | 2 |
| [TC-CE-004](TC-CE-004/report_TC-CE-004.md) | 47 eventos — BCD arbitrario: decenas=4, unidades=7 | ❌ | 1 | 3 |
| [TC-CE-005](TC-CE-005/report_TC-CE-005.md) | Reset borra el contador — cuenta vuelve a 0 | ❌ | 2 | 1 |
| [TC-CE-006](TC-CE-006/report_TC-CE-006.md) | Saturacion en 99 — 100 eventos, cuenta queda en 99 | ❌ | 0 | 2 |
| [TC-CE-007](TC-CE-007/report_TC-CE-007.md) | El contador permanece en 99 tras la saturacion | ❌ | 1 | 1 |
| [TC-CE-008](TC-CE-008/report_TC-CE-008.md) | Reset tras desbordamiento — contador vuelve a 0 | ❌ | 2 | 1 |
| [TC-CE-009](TC-CE-009/report_TC-CE-009.md) | Prioridad de reset sobre evento simultaneo | ✅ | 2 | 0 |
| [TC-CE-010](TC-CE-010/report_TC-CE-010.md) | BCD en valor limite 99 — decenas=9, unidades=9 | ❌ | 0 | 4 |

## Analisis del modelo

**8 TEST(S) FALLAN (20% de tasa de exito).**

Test cases con fallos:
- **TC-CE-002** — Un solo evento — contador pasa a 1 (2 check(s) fallados)
- **TC-CE-003** — Diez eventos — descomposicion BCD: decenas=1, unidades=0 (2 check(s) fallados)
- **TC-CE-004** — 47 eventos — BCD arbitrario: decenas=4, unidades=7 (3 check(s) fallados)
- **TC-CE-005** — Reset borra el contador — cuenta vuelve a 0 (1 check(s) fallados)
- **TC-CE-006** — Saturacion en 99 — 100 eventos, cuenta queda en 99 (2 check(s) fallados)
- **TC-CE-007** — El contador permanece en 99 tras la saturacion (1 check(s) fallados)
- **TC-CE-008** — Reset tras desbordamiento — contador vuelve a 0 (1 check(s) fallados)
- **TC-CE-010** — BCD en valor limite 99 — decenas=9, unidades=9 (4 check(s) fallados)

Se recomienda revisar el codegen para los escenarios indicados.
