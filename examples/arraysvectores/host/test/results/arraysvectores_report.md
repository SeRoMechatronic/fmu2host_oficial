# Informe de test — ArraysVectores

Generado: 2026-05-21 13:26:57

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.5| Euler  |
| ME RK4    | 1.0    | 0.5| RK4    |
| CS        | 1.0    | 0.5| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: ejecutado | 2 PASS / 0 FAIL

**Total: 6 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| suma_real | 0 | 0 | 0 |
| suma_int | 0 | 0 | 0 |
| v_doble[1] | 0 | 0 | 0 |
| v_doble[2] | 0 | 0 | 0 |
| v_doble[3] | 0 | 0 | 0 |
| v_doble[4] | 0 | 0 | 0 |
| alguno_true | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa Euler**: t_final=1

### Muestra de datos

| t | suma_real | suma_int | v_doble[1] | v_doble[2] | v_doble[3] | v_doble[4] | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| suma_real | 0 | 0 | 0 |
| suma_int | 0 | 0 | 0 |
| v_doble[1] | 0 | 0 | 0 |
| v_doble[2] | 0 | 0 | 0 |
| v_doble[3] | 0 | 0 | 0 |
| v_doble[4] | 0 | 0 | 0 |
| alguno_true | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa RK4**: t_final=1

### Muestra de datos

| t | suma_real | suma_int | v_doble[1] | v_doble[2] | v_doble[3] | v_doble[4] | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: CS

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| suma_real | 0 | 0 | 0 |
| suma_int | 0 | 0 | 0 |
| v_doble[1] | 0 | 0 | 0 |
| v_doble[2] | 0 | 0 | 0 |
| v_doble[3] | 0 | 0 | 0 |
| v_doble[4] | 0 | 0 | 0 |
| alguno_true | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa CS**: t_final=1

### Muestra de datos

| t | suma_real | suma_int | v_doble[1] | v_doble[2] | v_doble[3] | v_doble[4] | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

---

## Graficas generadas

- `ArraysVectores_comparacion.png` — Comparacion de los 3 escenarios
- `ArraysVectores_me_euler.png` — ME con solver Euler
- `ArraysVectores_me_rk4.png` — ME con solver RK4
- `ArraysVectores_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*