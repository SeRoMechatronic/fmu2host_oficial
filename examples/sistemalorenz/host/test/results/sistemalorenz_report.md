# Informe de test — SistemaLorenz

Generado: 2026-05-21 13:30:39

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 30.0    | 0.01| Euler  |
| ME RK4    | 30.0    | 0.01| RK4    |
| CS        | 30.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 3 PASS / 0 FAIL
- **ME RK4**: ejecutado | 5 PASS / 0 FAIL
- **CS**: ejecutado | 3 PASS / 0 FAIL

**Total: 11 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 3000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| on_attractor | 1 | 1 | 1 |
| x_out | -18.5958 | 21.0884 | -1.50525 |
| y_out | -24.2139 | 28.6675 | -2.5388 |
| z_out | 1.37716 | 53.2664 | 15.6847 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3000 filas OK
- [PASS] **z positivo Euler**: 3000 filas OK
- [PASS] **x acotado Euler**: 3000 filas OK

### Muestra de datos

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1.255 | 1.47 |
| 0.01 | 1 | 1.0255 | 1.50775 | 1.44335 |
| 0.02 | 1 | 1.07373 | 1.76501 | 1.42032 |
| ... | ... | ... | ... | ... |
| 29.97 | 1 | -1.31076 | -2.26691 | 16.4898 |
| 29.98 | 1 | -1.40637 | -2.39511 | 16.0798 |
| 29.99 | 1 | -1.50525 | -2.5388 | 15.6847 |

---

## Escenario: ME RK4

**Filas de datos:** 3000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| on_attractor | 1 | 1 | 1 |
| x_out | -17.9846 | 19.4396 | -5.7939 |
| y_out | -24.1437 | 26.9105 | -6.17316 |
| z_out | 1.39723 | 47.5199 | 23.1842 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3000 filas OK
- [PASS] **siempre en el atractor**: 3000 filas OK
- [PASS] **z siempre positivo**: 3000 filas OK
- [PASS] **x acotado abs<25**: 3000 filas OK
- [PASS] **oscilacion caotica en x**: 9 cambios de signo

### Muestra de datos

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1.01233 | 1.25497 | 1.47171 |
| 0.01 | 1 | 1.04789 | 1.51403 | 1.44704 |
| 0.02 | 1 | 1.10517 | 1.78306 | 1.42645 |
| ... | ... | ... | ... | ... |
| 29.97 | 1 | -5.75434 | -5.76858 | 23.7471 |
| 29.98 | 1 | -5.76499 | -5.96331 | 23.4555 |
| 29.99 | 1 | -5.7939 | -6.17316 | 23.1842 |

---

## Escenario: CS

**Filas de datos:** 3000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| on_attractor | 1 | 1 | 1 |
| x_out | -18.5971 | 21.0884 | -1.44868 |
| y_out | -24.2167 | 28.6675 | -2.45117 |
| z_out | 1.37716 | 53.2664 | 15.618 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3000 filas OK
- [PASS] **siempre en el atractor CS**: 3000 filas OK
- [PASS] **z positivo CS**: 3000 filas OK

### Muestra de datos

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1.255 | 1.47 |
| 0.01 | 1 | 1.0255 | 1.50775 | 1.44335 |
| 0.02 | 1 | 1.07373 | 1.76501 | 1.42032 |
| ... | ... | ... | ... | ... |
| 29.97 | 1 | -1.25991 | -2.18819 | 16.4242 |
| 29.98 | 1 | -1.35274 | -2.31215 | 16.0138 |
| 29.99 | 1 | -1.44868 | -2.45117 | 15.618 |

---

## Graficas generadas

- `SistemaLorenz_comparacion.png` — Comparacion de los 3 escenarios
- `SistemaLorenz_me_euler.png` — ME con solver Euler
- `SistemaLorenz_me_rk4.png` — ME con solver RK4
- `SistemaLorenz_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*