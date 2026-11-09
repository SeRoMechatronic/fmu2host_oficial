# Resumen de Test Battery — CodigoErrorDiagnostico

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 32 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-CED-001](TC-CED-001/report_TC-CED-001.md) | Todos los canales nominales — sin fallo | ✅ | 4 | 0 |
| [TC-CED-002](TC-CED-002/report_TC-CED-002.md) | Fallo de sobretemperatura — prioridad maxima | ✅ | 4 | 0 |
| [TC-CED-003](TC-CED-003/report_TC-CED-003.md) | Temperatura exactamente en umbral — sin fallo (limite estricto) | ✅ | 2 | 0 |
| [TC-CED-004](TC-CED-004/report_TC-CED-004.md) | Fallo de subtension — prioridad 2 | ✅ | 4 | 0 |
| [TC-CED-005](TC-CED-005/report_TC-CED-005.md) | Tension ligeramente por encima del umbral — sin fallo | ✅ | 2 | 0 |
| [TC-CED-006](TC-CED-006/report_TC-CED-006.md) | Fallo de sobrevidbracion — prioridad 1 | ✅ | 4 | 0 |
| [TC-CED-007](TC-CED-007/report_TC-CED-007.md) | Temperatura + tension — temperatura gana (prioridad 3 vs 2) | ✅ | 3 | 0 |
| [TC-CED-008](TC-CED-008/report_TC-CED-008.md) | Temperatura + vibracion — temperatura gana | ✅ | 2 | 0 |
| [TC-CED-009](TC-CED-009/report_TC-CED-009.md) | Tension + vibracion — tension gana (prioridad 2 vs 1) | ✅ | 3 | 0 |
| [TC-CED-010](TC-CED-010/report_TC-CED-010.md) | Tres fallos simultaneos — temperatura gana | ✅ | 4 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `CodigoErrorDiagnostico` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 32 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
