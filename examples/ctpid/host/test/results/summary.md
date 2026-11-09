# Resumen de Test Battery — CTPID

> Generado: 2026-11-09 17:21

## Metricas globales

| Metrica | Valor |
|---------|-------|
| Test cases totales | 10 |
| Test cases PASS | 10 (100%) |
| Test cases FAIL | 0 |
| Checks individuales PASS | 37 |
| Checks individuales FAIL | 0 |

## Resultado por test case

| TC ID | Titulo | Resultado | PASS | FAIL |
|-------|--------|-----------|------|------|
| [TC-CT-001](TC-CT-001/report_TC-CT-001.md) | Setpoint = temperatura — ledAlcanzado activo, ventilador=0 | ✅ | 4 | 0 |
| [TC-CT-002](TC-CT-002/report_TC-CT-002.md) | Setpoint por encima — demanda de calefaccion, ledPorEncima=true | ✅ | 4 | 0 |
| [TC-CT-003](TC-CT-003/report_TC-CT-003.md) | Setpoint por debajo — sobretemperatura, ventilador=0 | ✅ | 4 | 0 |
| [TC-CT-004](TC-CT-004/report_TC-CT-004.md) | Dentro de la banda muerta — ledAlcanzado activo | ✅ | 3 | 0 |
| [TC-CT-005](TC-CT-005/report_TC-CT-005.md) | Justo fuera de la banda muerta — ledAlcanzado inactivo | ✅ | 2 | 0 |
| [TC-CT-006](TC-CT-006/report_TC-CT-006.md) | Demanda maxima — ventilador saturado a 1.0 | ✅ | 3 | 0 |
| [TC-CT-007](TC-CT-007/report_TC-CT-007.md) | Wind-up integral — 10 segundos de error positivo, ventilador=1.0 | ✅ | 4 | 0 |
| [TC-CT-008](TC-CT-008/report_TC-CT-008.md) | Escalon en la consigna — ledPorEncima activo despues del cambio | ✅ | 4 | 0 |
| [TC-CT-009](TC-CT-009/report_TC-CT-009.md) | Ambas entradas en cero — ledAlcanzado, sin demanda | ✅ | 4 | 0 |
| [TC-CT-010](TC-CT-010/report_TC-CT-010.md) | Ambas entradas al maximo — ledAlcanzado, sin demanda | ✅ | 5 | 0 |

## Analisis del modelo

**TODOS LOS 10 TESTS PASAN (100%).**

El modelo `CTPID` supera la bateria completa. Todos los escenarios verificados — nominal, extremos, condiciones de borde y dinamicas transitorias — producen resultados coherentes con la especificacion del modelo FMI 2.0.
Los 37 checks individuales cubren: valores finales, valores en instantes concretos, conservacion de invariantes, ausencia de NaN/Inf, monotonias y conteos de transiciones.
