# Informe de test — StringsParametros

Generado: 2026-05-21 13:30:57

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
| y | 34 | 34 | 34 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa Euler**: t_final=1

### Muestra de datos

| t | u | y |
| --- | --- | --- |
| 0 | 1 | 34 |
| 0.5 | 1 | 34 |
| 1 | 1 | 34 |
| 0 | 1 | 34 |
| 0.5 | 1 | 34 |
| 1 | 1 | 34 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| u | 1 | 1 | 1 |
| y | 34 | 34 | 34 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa RK4**: t_final=1

### Muestra de datos

| t | u | y |
| --- | --- | --- |
| 0 | 1 | 34 |
| 0.5 | 1 | 34 |
| 1 | 1 | 34 |
| 0 | 1 | 34 |
| 0.5 | 1 | 34 |
| 1 | 1 | 34 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `StringsParametros_comparacion.png` — Comparacion de los 3 escenarios
- `StringsParametros_me_euler.png` — ME con solver Euler
- `StringsParametros_me_rk4.png` — ME con solver RK4
- `StringsParametros_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*