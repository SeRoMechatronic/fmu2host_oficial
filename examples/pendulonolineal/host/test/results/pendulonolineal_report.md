# Informe de test — PenduloNoLineal

Generado: 2026-05-21 13:30:02

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 10.0    | 0.05| Euler  |
| ME RK4    | 10.0    | 0.05| RK4    |
| CS        | 10.0    | 0.05| interno|

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
| en_reposo | 0 | 0 | 0 |
| angulo | -54.8808 | 2.618 | -54.8808 |
| energia_total | 8.52581 | 32.7461 | 29.8313 |
| velocidad_angular | -8.96311 | -0.245247 | -7.6001 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **energia total positiva Euler**: 200 filas OK

### Muestra de datos

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 0 | 2.618 | 8.52581 | -0.245247 |
| 0.05 | 0 | 2.60574 | 8.55525 | -0.490495 |
| 0.1 | 0 | 2.58121 | 8.58408 | -0.740933 |
| ... | ... | ... | ... | ... |
| 9.85 | 0 | -54.182 | 30.2399 | -6.81631 |
| 9.9 | 0 | -54.5228 | 29.9406 | -7.15951 |
| 9.95 | 0 | -54.8808 | 29.8313 | -7.6001 |

---

## Escenario: ME RK4

**Filas de datos:** 200

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| en_reposo | 0 | 0 | 0 |
| angulo | -2.61795 | 2.61743 | 1.50362 |
| energia_total | 8.49535 | 8.49575 | 8.49535 |
| velocidad_angular | -6.05026 | 6.05068 | 4.27875 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **energia total positiva RK4**: 200 filas OK
- [PASS] **angulo acotado**: 200 filas OK

### Muestra de datos

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 0 | 2.61186 | 8.49574 | -0.246114 |
| 0.05 | 0 | 2.5933 | 8.49574 | -0.497437 |
| 0.1 | 0 | 2.56194 | 8.49574 | -0.759168 |
| ... | ... | ... | ... | ... |
| 9.85 | 0 | 1.02814 | 8.49536 | 5.20795 |
| 9.9 | 0 | 1.27756 | 8.49535 | 4.76045 |
| 9.95 | 0 | 1.50362 | 8.49535 | 4.27875 |

---

## Escenario: CS

**Filas de datos:** 200

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| en_reposo | 0 | 0 | 0 |
| angulo | -54.8808 | 2.618 | -54.8808 |
| energia_total | 8.52581 | 32.7461 | 29.8313 |
| velocidad_angular | -8.96311 | -0.245247 | -7.6001 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 200 filas OK
- [PASS] **energia total positiva CS**: 200 filas OK

### Muestra de datos

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 0 | 2.618 | 8.52581 | -0.245247 |
| 0.05 | 0 | 2.60574 | 8.55525 | -0.490495 |
| 0.1 | 0 | 2.58121 | 8.58408 | -0.740933 |
| ... | ... | ... | ... | ... |
| 9.85 | 0 | -54.182 | 30.2399 | -6.81631 |
| 9.9 | 0 | -54.5228 | 29.9406 | -7.15951 |
| 9.95 | 0 | -54.8808 | 29.8313 | -7.6001 |

---

## Graficas generadas

- `PenduloNoLineal_comparacion.png` — Comparacion de los 3 escenarios
- `PenduloNoLineal_me_euler.png` — ME con solver Euler
- `PenduloNoLineal_me_rk4.png` — ME con solver RK4
- `PenduloNoLineal_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*