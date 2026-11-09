# Resumen de Test Battery — FrenadoABS

> Generado: 2026-11-09 17:22

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 28 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-FABS-001](TC-FABS-001/report_TC-FABS-001.md) | Sin frenado — estado estacionario, lambda=0, ABS inactivo | ✅ | 4 | 0 |
| [TC-FABS-002](TC-FABS-002/report_TC-FABS-002.md) | Frenado suave — ABS no activado, frenado_normal=true | ✅ | 4 | 0 |
| [TC-FABS-003](TC-FABS-003/report_TC-FABS-003.md) | Frenado de emergencia — ABS activa tras escalon de velocidad | ✅ | 2 | 0 |
| [TC-FABS-004](TC-FABS-004/report_TC-FABS-004.md) | Bloqueo de rueda — rueda_bloqueada=true con desaceleracion extrema | ✅ | 2 | 0 |
| [TC-FABS-005](TC-FABS-005/report_TC-FABS-005.md) | Vehiculo detenido — guarda de division por cero en lambda | ✅ | 3 | 0 |
| [TC-FABS-006](TC-FABS-006/report_TC-FABS-006.md) | presion_modulada acotada en [0,1] siempre | ✅ | 2 | 0 |
| [TC-FABS-007](TC-FABS-007/report_TC-FABS-007.md) | Oscilador interno — no produce NaN ni Inf durante 10 Hz | ✅ | 2 | 0 |
| [TC-FABS-008](TC-FABS-008/report_TC-FABS-008.md) | frenado_normal requiere pedal > 0.05 — frontera exacta | ✅ | 2 | 0 |
| [TC-FABS-009](TC-FABS-009/report_TC-FABS-009.md) | Buffer de 5 estados — no NaN en 2 segundos | ✅ | 5 | 0 |
| [TC-FABS-010](TC-FABS-010/report_TC-FABS-010.md) | Transitorio del filtro de velocidad tras escalon | ✅ | 2 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `FrenadoABS` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 28 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
