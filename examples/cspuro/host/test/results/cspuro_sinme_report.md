# Informe de test — CSPuro_SinME

Generado: 2026-05-21 13:28:12

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.1| Euler  |
| ME RK4    | 1.0    | 0.1| RK4    |
| CS        | 1.0    | 0.1| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 1 PASS / 0 FAIL
- **ME RK4**: ejecutado | 1 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 2 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u1 | 1 | 1 | 1 |
| u2 | 0.5 | 0.5 | 0.5 |
| active | 1 | 1 | 1 |
| y_prod | 0.5 | 0.5 | 0.5 |
| y_sum | 1.5 | 1.5 | 1.5 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK

### Muestra de datos

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.1 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.2 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| ... | ... | ... | ... | ... | ... |
| 0.8 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.9 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 1 | 1 | 0.5 | 1 | 0.5 | 1.5 |

---

## Escenario: ME RK4

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u1 | 1 | 1 | 1 |
| u2 | 0.5 | 0.5 | 0.5 |
| active | 1 | 1 | 1 |
| y_prod | 0.5 | 0.5 | 0.5 |
| y_sum | 1.5 | 1.5 | 1.5 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK

### Muestra de datos

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.1 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.2 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| ... | ... | ... | ... | ... | ... |
| 0.8 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 0.9 | 1 | 0.5 | 1 | 0.5 | 1.5 |
| 1 | 1 | 0.5 | 1 | 0.5 | 1.5 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `CSPuro_SinME_comparacion.png` — Comparacion de los 3 escenarios
- `CSPuro_SinME_me_euler.png` — ME con solver Euler
- `CSPuro_SinME_me_rk4.png` — ME con solver RK4
- `CSPuro_SinME_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*