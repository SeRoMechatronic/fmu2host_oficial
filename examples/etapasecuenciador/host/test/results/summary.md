# Resumen de Test Battery — EtapaSecuenciador

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 12 |
| Test cases PASS | 1 (8%) |
| Test cases FAIL | 11 |
| Checks individuales PASS | 9 |
| Checks individuales FAIL | 19 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-ES-001](TC-ES-001/report_TC-ES-001.md) | Estado idle inicial | ✅ | 3 | 0 |
| [TC-ES-002](TC-ES-002/report_TC-ES-002.md) | Comando de arranque — entra en etapa 1 | ❌ | 1 | 1 |
| [TC-ES-003](TC-ES-003/report_TC-ES-003.md) | Progreso dentro de la etapa 1 en t=5 s | ❌ | 1 | 2 |
| [TC-ES-004](TC-ES-004/report_TC-ES-004.md) | Avance de etapa — etapa 1→2 tras 10 s con sensor confirmado | ❌ | 0 | 2 |
| [TC-ES-005](TC-ES-005/report_TC-ES-005.md) | Sin avance sin confirmacion del sensor | ❌ | 0 | 2 |
| [TC-ES-006](TC-ES-006/report_TC-ES-006.md) | Sensor exactamente en el umbral — sin avance (operador estricto) | ❌ | 0 | 1 |
| [TC-ES-007](TC-ES-007/report_TC-ES-007.md) | Parada durante secuencia — vuelta inmediata a idle | ❌ | 1 | 1 |
| [TC-ES-008](TC-ES-008/report_TC-ES-008.md) | Arrancar ignorado si ya en ejecucion | ❌ | 0 | 2 |
| [TC-ES-009](TC-ES-009/report_TC-ES-009.md) | Secuencia completa — secuencia_completa=true al finalizar | ❌ | 1 | 2 |
| [TC-ES-010](TC-ES-010/report_TC-ES-010.md) | Reinicio tras completion — nueva secuencia arranca correctamente | ❌ | 0 | 2 |
| [TC-ES-011](TC-ES-011/report_TC-ES-011.md) | Progreso clamped a 1.0 cuando sensor bloquea el avance | ❌ | 0 | 2 |
| [TC-ES-012](TC-ES-012/report_TC-ES-012.md) | Ciclo de parada y reinicio | ❌ | 2 | 2 |

## Analisis del modelo

**11 TEST(S) FALLAN (8% de tasa de exito).**

Test cases con fallos:
- **TC-ES-002** — Comando de arranque — entra en etapa 1 (1 check(s) fallados)
- **TC-ES-003** — Progreso dentro de la etapa 1 en t=5 s (2 check(s) fallados)
- **TC-ES-004** — Avance de etapa — etapa 1→2 tras 10 s con sensor confirmado (2 check(s) fallados)
- **TC-ES-005** — Sin avance sin confirmacion del sensor (2 check(s) fallados)
- **TC-ES-006** — Sensor exactamente en el umbral — sin avance (operador estricto) (1 check(s) fallados)
- **TC-ES-007** — Parada durante secuencia — vuelta inmediata a idle (1 check(s) fallados)
- **TC-ES-008** — Arrancar ignorado si ya en ejecucion (2 check(s) fallados)
- **TC-ES-009** — Secuencia completa — secuencia_completa=true al finalizar (2 check(s) fallados)
- **TC-ES-010** — Reinicio tras completion — nueva secuencia arranca correctamente (2 check(s) fallados)
- **TC-ES-011** — Progreso clamped a 1.0 cuando sensor bloquea el avance (2 check(s) fallados)
- **TC-ES-012** — Ciclo de parada y reinicio (2 check(s) fallados)

Se recomienda revisar el codegen para los escenarios indicados.
