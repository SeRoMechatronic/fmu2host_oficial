# Resumen de Test Battery — ArraysVectores

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 2 (20%) |
| Test cases FAIL | 8 |
| Checks individuales PASS | 6 |
| Checks individuales FAIL | 33 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-AV-001](TC-AV-001/report_TC-AV-001.md) | Todos ceros — suma e indices en cero | ✅ | 5 | 0 |
| [TC-AV-002](TC-AV-002/report_TC-AV-002.md) | Todos unos — suma=4, doble=[2,2,2,2], alguno=true | ❌ | 0 | 5 |
| [TC-AV-003](TC-AV-003/report_TC-AV-003.md) | Valores reales distintos — discriminador de indice | ❌ | 0 | 5 |
| [TC-AV-004](TC-AV-004/report_TC-AV-004.md) | Un solo TRUE en el OR — alguno_true activado | ❌ | 0 | 1 |
| [TC-AV-005](TC-AV-005/report_TC-AV-005.md) | Todos booleanos FALSE — alguno_true=false | ✅ | 1 | 0 |
| [TC-AV-006](TC-AV-006/report_TC-AV-006.md) | Reales con signos mixtos — suma y dobles con signos | ❌ | 0 | 5 |
| [TC-AV-007](TC-AV-007/report_TC-AV-007.md) | Enteros con signos mixtos — suma_int correcto | ❌ | 0 | 1 |
| [TC-AV-008](TC-AV-008/report_TC-AV-008.md) | Magnitudes grandes — sin perdida de precision en suma | ❌ | 0 | 5 |
| [TC-AV-009](TC-AV-009/report_TC-AV-009.md) | Cambio de un elemento en mitad de simulacion | ❌ | 0 | 4 |
| [TC-AV-010](TC-AV-010/report_TC-AV-010.md) | Independencia de los 4 elementos — sin escrituras cruzadas | ❌ | 0 | 7 |

## Analisis del modelo

**8 TEST(S) FALLAN (20% de tasa de exito).**

Test cases con fallos:
- **TC-AV-002** — Todos unos — suma=4, doble=[2,2,2,2], alguno=true (5 check(s) fallados)
- **TC-AV-003** — Valores reales distintos — discriminador de indice (5 check(s) fallados)
- **TC-AV-004** — Un solo TRUE en el OR — alguno_true activado (1 check(s) fallados)
- **TC-AV-006** — Reales con signos mixtos — suma y dobles con signos (5 check(s) fallados)
- **TC-AV-007** — Enteros con signos mixtos — suma_int correcto (1 check(s) fallados)
- **TC-AV-008** — Magnitudes grandes — sin perdida de precision en suma (5 check(s) fallados)
- **TC-AV-009** — Cambio de un elemento en mitad de simulacion (4 check(s) fallados)
- **TC-AV-010** — Independencia de los 4 elementos — sin escrituras cruzadas (7 check(s) fallados)

Se recomienda revisar el codegen para los escenarios indicados.
