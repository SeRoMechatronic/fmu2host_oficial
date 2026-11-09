# Informe de test — MuchosEstados

Generado: 2026-05-21 13:29:24

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 30.0    | 0.01| Euler  |
| ME RK4    | 30.0    | 0.01| RK4    |
| CS        | 30.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 4 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 6 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 3000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u | 1 | 1 | 1 |
| todos_activos | 0 | 1 | 1 |
| y1 | 0.01 | 1 | 1 |
| y2 | 0 | 1 | 1 |
| y3 | 0 | 1 | 1 |
| y4 | 0 | 1 | 1 |
| y5 | 0 | 1 | 1 |
| y6 | 0 | 1 | 1 |
| y7 | 0 | 1 | 1 |
| y8 | 0 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3000 filas OK
- [PASS] **y1 no negativo Euler**: 3000 filas OK

### Muestra de datos

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 | y7 | y8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0.01 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.0199 | 0.0001 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.02 | 1 | 0 | 0.029701 | 0.000298 | 1e-06 | 0 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 29.97 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| 29.98 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| 29.99 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

---

## Escenario: ME RK4

**Filas de datos:** 3000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u | 1 | 1 | 1 |
| todos_activos | 0 | 1 | 1 |
| y1 | 0.00995017 | 1 | 1 |
| y2 | 4.96679e-05 | 1 | 1 |
| y3 | 1.65417e-07 | 1 | 1 |
| y4 | 4.16667e-10 | 1 | 1 |
| y5 | 0 | 1 | 1 |
| y6 | 0 | 1 | 1 |
| y7 | 0 | 1 | 1 |
| y8 | 0 | 0.999999 | 0.999999 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3000 filas OK
- [PASS] **y1 no negativo RK4**: 3000 filas OK
- [PASS] **y8 no negativo RK4**: 3000 filas OK
- [PASS] **y8 no negativo RK4 (convergencia)**: 3000 filas OK

### Muestra de datos

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 | y7 | y8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0.00995017 | 4.96679e-05 | 1.65417e-07 | 4.16667e-10 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.0198013 | 0.000197353 | 1.31348e-06 | 6.56736e-09 | 2.46549e-11 | 6.86148e-14 | 1.37674e-16 | 1.73611e-19 |
| 0.02 | 1 | 0 | 0.0295545 | 0.0004411 | 4.39994e-06 | 3.29595e-08 | 1.95264e-10 | 9.36083e-13 | 3.667e-15 | 1.1736e-17 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 29.97 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0.999999 |
| 29.98 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0.999999 |
| 29.99 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0.999999 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `MuchosEstados_comparacion.png` — Comparacion de los 3 escenarios
- `MuchosEstados_me_euler.png` — ME con solver Euler
- `MuchosEstados_me_rk4.png` — ME con solver RK4
- `MuchosEstados_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*