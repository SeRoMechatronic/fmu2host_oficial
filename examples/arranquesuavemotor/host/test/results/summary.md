# Resumen de Test Battery — ArranqueSuaveMotor

> Generado: 2026-11-09 17:20

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 30 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-ASM-001](TC-ASM-001/report_TC-ASM-001.md) | No start command — estado en reposo | ✅ | 4 | 0 |
| [TC-ASM-002](TC-ASM-002/report_TC-ASM-002.md) | Start command — en_rampa activa inmediatamente | ✅ | 4 | 0 |
| [TC-ASM-003](TC-ASM-003/report_TC-ASM-003.md) | Motor fully started — umbral 90% superado | ✅ | 5 | 0 |
| [TC-ASM-004](TC-ASM-004/report_TC-ASM-004.md) | Stop command — tension decae tras parada | ✅ | 3 | 0 |
| [TC-ASM-005](TC-ASM-005/report_TC-ASM-005.md) | Brief overload (1s) — no dispara fallo | ✅ | 3 | 0 |
| [TC-ASM-006](TC-ASM-006/report_TC-ASM-006.md) | Sustained overload (2s) — fallo dispara | ✅ | 2 | 0 |
| [TC-ASM-007](TC-ASM-007/report_TC-ASM-007.md) | Overload exactamente en umbral — no fallo | ✅ | 1 | 0 |
| [TC-ASM-008](TC-ASM-008/report_TC-ASM-008.md) | Overload justo por encima del umbral — acumulador sube | ✅ | 2 | 0 |
| [TC-ASM-009](TC-ASM-009/report_TC-ASM-009.md) | Ramp timing — verificacion a 1 constante de tiempo | ✅ | 3 | 0 |
| [TC-ASM-010](TC-ASM-010/report_TC-ASM-010.md) | Stop during ramp — en_rampa desactiva inmediatamente | ✅ | 3 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `ArranqueSuaveMotor` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 30 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
