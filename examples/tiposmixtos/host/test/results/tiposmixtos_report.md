# Informe de test — TiposMixtos

Generado: 2026-05-21 13:31:12

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
| i_in | 5 | 5 | 5 |
| b_in | 1 | 1 | 1 |
| r_in | 3.14 | 3.14 | 3.14 |
| r_abs | 3.14 | 3.14 | 3.14 |
| i_out | 6 | 6 | 6 |
| b_out | 0 | 0 | 0 |
| r_out | 6.28 | 6.28 | 6.28 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **r_abs siempre no negativo Euler**: 3 filas OK

### Muestra de datos

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0.5 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 1 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0.5 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 1 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| i_in | 5 | 5 | 5 |
| b_in | 1 | 1 | 1 |
| r_in | 3.14 | 3.14 | 3.14 |
| r_abs | 3.14 | 3.14 | 3.14 |
| i_out | 6 | 6 | 6 |
| b_out | 0 | 0 | 0 |
| r_out | 6.28 | 6.28 | 6.28 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **r_abs siempre no negativo**: 3 filas OK

### Muestra de datos

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0.5 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 1 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 0.5 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |
| 1 | 5 | 1 | 3.14 | 3.14 | 6 | 0 | 6.28 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `TiposMixtos_comparacion.png` — Comparacion de los 3 escenarios
- `TiposMixtos_me_euler.png` — ME con solver Euler
- `TiposMixtos_me_rk4.png` — ME con solver RK4
- `TiposMixtos_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*