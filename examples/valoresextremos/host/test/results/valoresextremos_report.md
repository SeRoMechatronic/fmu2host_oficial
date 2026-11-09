# Informe de test — ValoresExtremos

Generado: 2026-05-21 13:31:19

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.5| Euler  |
| ME RK4    | 1.0    | 0.5| RK4    |
| CS        | 1.0    | 0.5| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u | 1 | 1 | 1 |
| es_finito | 1 | 1 | 1 |
| y_inv | 1 | 1 | 1 |
| y_log | 0 | 0 | 0 |
| y_sat | 1 | 1 | 1 |
| y_sqrt | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa Euler**: t_final=1

### Muestra de datos

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.5 | 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.5 | 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 | 1 | 1 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u | 1 | 1 | 1 |
| es_finito | 1 | 1 | 1 |
| y_inv | 1 | 1 | 1 |
| y_log | 0 | 0 | 0 |
| y_sat | 1 | 1 | 1 |
| y_sqrt | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa RK4**: t_final=1

### Muestra de datos

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.5 | 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.5 | 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 | 1 | 1 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `ValoresExtremos_comparacion.png` — Comparacion de los 3 escenarios
- `ValoresExtremos_me_euler.png` — ME con solver Euler
- `ValoresExtremos_me_rk4.png` — ME con solver RK4
- `ValoresExtremos_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*