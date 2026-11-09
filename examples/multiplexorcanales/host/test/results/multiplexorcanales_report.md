# Informe de test — MultiplexorCanales

Generado: 2026-05-21 13:29:33

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
| canal_0 | 0.5 | 0.5 | 0.5 |
| canal_1 | 0.75 | 0.75 | 0.75 |
| canal_seleccion | 0 | 0 | 0 |
| canal_2 | 0.25 | 0.25 | 0.25 |
| canal_3 | 1 | 1 | 1 |
| canal_activo | 0 | 0 | 0 |
| canal_valido | 1 | 1 | 1 |
| salida | 0.5 | 0.5 | 0.5 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa Euler**: t_final=1

### Muestra de datos

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0.5 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 1 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0.5 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 1 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| canal_0 | 0.5 | 0.5 | 0.5 |
| canal_1 | 0.75 | 0.75 | 0.75 |
| canal_seleccion | 0 | 0 | 0 |
| canal_2 | 0.25 | 0.25 | 0.25 |
| canal_3 | 1 | 1 | 1 |
| canal_activo | 0 | 0 | 0 |
| canal_valido | 1 | 1 | 1 |
| salida | 0.5 | 0.5 | 0.5 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **simulacion completa RK4**: t_final=1

### Muestra de datos

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0.5 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 1 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 0.5 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |
| 1 | 0.5 | 0.75 | 0 | 0.25 | 1 | 0 | 1 | 0.5 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `MultiplexorCanales_comparacion.png` — Comparacion de los 3 escenarios
- `MultiplexorCanales_me_euler.png` — ME con solver Euler
- `MultiplexorCanales_me_rk4.png` — ME con solver RK4
- `MultiplexorCanales_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*