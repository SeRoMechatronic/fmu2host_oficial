# Resumen de Test Battery — SuspensionActiva

> Generado: 2026-11-09 17:23

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 31 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-SA-001](TC-SA-001/report_TC-SA-001.md) | Sin bache — todas las salidas en cero al inicio | ✅ | 4 | 0 |
| [TC-SA-002](TC-SA-002/report_TC-SA-002.md) | Velocidad baja sin bache — modo_confort activo | ✅ | 4 | 0 |
| [TC-SA-003](TC-SA-003/report_TC-SA-003.md) | Bache pequeno — por debajo del umbral de deteccion | ✅ | 3 | 0 |
| [TC-SA-004](TC-SA-004/report_TC-SA-004.md) | Bache exactamente en el umbral — bache_detectado=false (operador estricto) | ✅ | 3 | 0 |
| [TC-SA-005](TC-SA-005/report_TC-SA-005.md) | Bache justo sobre el umbral — bache_detectado=true | ✅ | 2 | 0 |
| [TC-SA-006](TC-SA-006/report_TC-SA-006.md) | Bache grande — actuador saturado en -1.0 | ✅ | 3 | 0 |
| [TC-SA-007](TC-SA-007/report_TC-SA-007.md) | Bache negativo (socavon) — fuerza positiva, saturacion hacia arriba | ✅ | 3 | 0 |
| [TC-SA-008](TC-SA-008/report_TC-SA-008.md) | Transitorio del filtro — bache_detectado activa a t≈0.1 s | ✅ | 3 | 0 |
| [TC-SA-009](TC-SA-009/report_TC-SA-009.md) | Frontera de velocidad para modo_confort — por encima y por debajo | ✅ | 2 | 0 |
| [TC-SA-010](TC-SA-010/report_TC-SA-010.md) | Interaccion P y D — fuerza con ambos terminos activos | ✅ | 4 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `SuspensionActiva` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 31 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
