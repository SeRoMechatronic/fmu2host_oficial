# Informe de test — MatrizEstado

Generado: 2026-05-21 13:29:05

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 2.0    | 0.01| Euler  |
| ME RK4    | 2.0    | 0.01| RK4    |
| CS        | 2.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: ejecutado | 2 PASS / 0 FAIL

**Total: 7 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 200

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| traza | 6 | 6 | 6 |
| x[1] | 0 | 0 | 0 |
| x[2] | 0 | 0 | 0 |
| x[3] | 0 | 0 | 0 |
| y_norma | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **traza conservada Euler**: 200 filas OK

### Muestra de datos

| t | traza | x[1] | x[2] | x[3] | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |
| 0.02 | 6 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... |
| 1.97 | 6 | 0 | 0 | 0 | 0 |
| 1.98 | 6 | 0 | 0 | 0 | 0 |
| 1.99 | 6 | 0 | 0 | 0 | 0 |

---

## Escenario: ME RK4

**Filas de datos:** 200

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| traza | 6 | 6 | 6 |
| x[1] | 0 | 0 | 0 |
| x[2] | 0 | 0 | 0 |
| x[3] | 0 | 0 | 0 |
| y_norma | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **traza conservada (aprox 6)**: 200 filas OK
- [PASS] **traza exacta en t=1**: t=1: 6 ~= 6.0 (tol=0.01)

### Muestra de datos

| t | traza | x[1] | x[2] | x[3] | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |
| 0.02 | 6 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... |
| 1.97 | 6 | 0 | 0 | 0 | 0 |
| 1.98 | 6 | 0 | 0 | 0 | 0 |
| 1.99 | 6 | 0 | 0 | 0 | 0 |

---

## Escenario: CS

**Filas de datos:** 200

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| traza | 6 | 6 | 6 |
| x[1] | 0 | 0 | 0 |
| x[2] | 0 | 0 | 0 |
| x[3] | 0 | 0 | 0 |
| y_norma | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **traza conservada CS**: 200 filas OK

### Muestra de datos

| t | traza | x[1] | x[2] | x[3] | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |
| 0.02 | 6 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... |
| 1.97 | 6 | 0 | 0 | 0 | 0 |
| 1.98 | 6 | 0 | 0 | 0 | 0 |
| 1.99 | 6 | 0 | 0 | 0 | 0 |

---

## Graficas generadas

- `MatrizEstado_comparacion.png` — Comparacion de los 3 escenarios
- `MatrizEstado_me_euler.png` — ME con solver Euler
- `MatrizEstado_me_rk4.png` — ME con solver RK4
- `MatrizEstado_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*