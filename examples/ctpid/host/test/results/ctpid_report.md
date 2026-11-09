# Informe de test — CTPID

Generado: 2026-05-21 13:28:25

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 10.0    | 0.01| Euler  |
| ME RK4    | 10.0    | 0.01| RK4    |
| CS        | 10.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 3 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 6 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 1001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| consigna | 0.8 | 0.8 | 0.8 |
| temperatura | 0.2 | 0.2 | 0.2 |
| ledAlcanzado | 0 | 0 | 0 |
| ledPorDebajo | 0 | 0 | 0 |
| ledPorEncima | 1 | 1 | 1 |
| ventilador | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **ventilador no negativo Euler**: 1001 filas OK
- [PASS] **ventilador no mayor que 1 Euler**: 1001 filas OK

### Muestra de datos

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 0.01 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 0.02 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 9.99 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 10 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |

---

## Escenario: ME RK4

**Filas de datos:** 1001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| consigna | 0.8 | 0.8 | 0.8 |
| temperatura | 0.2 | 0.2 | 0.2 |
| ledAlcanzado | 0 | 0 | 0 |
| ledPorDebajo | 0 | 0 | 0 |
| ledPorEncima | 1 | 1 | 1 |
| ventilador | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **ventilador no negativo RK4**: 1001 filas OK
- [PASS] **ventilador no mayor que 1 RK4**: 1001 filas OK

### Muestra de datos

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 0.01 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 0.02 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 9.99 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |
| 10 | 0.8 | 0.2 | 0 | 0 | 1 | 1 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `CTPID_comparacion.png` — Comparacion de los 3 escenarios
- `CTPID_me_euler.png` — ME con solver Euler
- `CTPID_me_rk4.png` — ME con solver RK4
- `CTPID_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*