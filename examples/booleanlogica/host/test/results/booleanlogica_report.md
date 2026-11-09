# Informe de test — BooleanLogica

Generado: 2026-05-21 13:27:14

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.1| Euler  |
| ME RK4    | 1.0    | 0.1| RK4    |
| CS        | 1.0    | 0.1| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| umbral | 0.5 | 0.5 | 0.5 |
| a | 1 | 1 | 1 |
| b | 0 | 0 | 0 |
| clk | 0 | 0 | 0 |
| cuenta_flancos | 0 | 0 | 0 |
| above_threshold | 0 | 0 | 0 |
| y_and | 0 | 0 | 0 |
| y_latch | 0 | 0 | 0 |
| y_or | 1 | 1 | 1 |
| y_xor | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **simulacion completa Euler**: t_final=1

### Muestra de datos

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch | y_or | y_xor |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.1 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.2 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.9 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 1 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |

---

## Escenario: ME RK4

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| umbral | 0.5 | 0.5 | 0.5 |
| a | 1 | 1 | 1 |
| b | 0 | 0 | 0 |
| clk | 0 | 0 | 0 |
| cuenta_flancos | 0 | 0 | 0 |
| above_threshold | 0 | 0 | 0 |
| y_and | 0 | 0 | 0 |
| y_latch | 0 | 0 | 0 |
| y_or | 1 | 1 | 1 |
| y_xor | 1 | 1 | 1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **simulacion completa RK4**: t_final=1

### Muestra de datos

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch | y_or | y_xor |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.1 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.2 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 0.9 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| 1 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 1 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `BooleanLogica_comparacion.png` — Comparacion de los 3 escenarios
- `BooleanLogica_me_euler.png` — ME con solver Euler
- `BooleanLogica_me_rk4.png` — ME con solver RK4
- `BooleanLogica_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*