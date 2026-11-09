# Informe de test — SinInputs

Generado: 2026-05-21 13:30:32

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 20.0    | 0.01| Euler  |
| ME RK4    | 20.0    | 0.01| RK4    |
| CS        | 20.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 3 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: ejecutado | 3 PASS / 0 FAIL

**Total: 9 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 0.352915 | 5.03628 | 0.352915 |
| posicion | -0.922107 | 1 | 0.0610635 |
| velocidad | -2.48197 | 2.2883 | -0.667603 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **posicion acotada inferior Euler**: 2000 filas OK
- [PASS] **posicion acotada superior Euler**: 2000 filas OK

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5.00333 | 1 | -0.0666667 |
| 0.01 | 5.00664 | 0.999333 | -0.1332 |
| 0.02 | 5.0099 | 0.998001 | -0.199556 |
| ... | ... | ... | ... |
| 19.97 | 0.355092 | 0.0743156 | -0.660786 |
| 19.98 | 0.354011 | 0.0677077 | -0.664418 |
| 19.99 | 0.352915 | 0.0610635 | -0.667603 |

---

## Escenario: ME RK4

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 0.0934475 | 5 | 0.0934475 |
| posicion | -0.88534 | 0.999667 | 0.0366451 |
| velocidad | -2.43301 | 2.15417 | -0.340065 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **energia decreciente (amortiguamiento)**: 2000 puntos OK
- [PASS] **oscilacion subamortiguada**: 16 cambios de signo

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 0.999667 | -0.0665926 |
| 0.01 | 4.99996 | 0.998669 | -0.133008 |
| 0.02 | 4.99988 | 0.997007 | -0.199202 |
| ... | ... | ... | ... |
| 19.97 | 0.0941335 | 0.0434081 | -0.33608 |
| 19.98 | 0.0937925 | 0.0400366 | -0.338187 |
| 19.99 | 0.0934475 | 0.0366451 | -0.340065 |

---

## Escenario: CS

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 0.352915 | 5.03628 | 0.352915 |
| posicion | -0.922107 | 1 | 0.0610635 |
| velocidad | -2.48197 | 2.2883 | -0.667603 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **energia positiva CS**: 2000 filas OK
- [PASS] **oscilacion detectada en CS**: 16 cambios de signo

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5.00333 | 1 | -0.0666667 |
| 0.01 | 5.00664 | 0.999333 | -0.1332 |
| 0.02 | 5.0099 | 0.998001 | -0.199556 |
| ... | ... | ... | ... |
| 19.97 | 0.355092 | 0.0743156 | -0.660786 |
| 19.98 | 0.354011 | 0.0677077 | -0.664418 |
| 19.99 | 0.352915 | 0.0610635 | -0.667603 |

---

## Graficas generadas

- `SinInputs_comparacion.png` — Comparacion de los 3 escenarios
- `SinInputs_me_euler.png` — ME con solver Euler
- `SinInputs_me_rk4.png` — ME con solver RK4
- `SinInputs_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*