# Informe de test — SelectorModo

Generado: 2026-05-21 13:30:24

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.5| Euler  |
| ME RK4    | 1.0    | 0.5| RK4    |
| CS        | 1.0    | 0.5| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 5 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| consigna_manual | 0.7 | 0.7 | 0.7 |
| modo_operacion | 0 | 0 | 0 |
| codigo_estado | 1 | 1 | 1 |
| fallo_modo | 0 | 0 | 0 |
| salida_actuador | 0.7 | 0.7 | 0.7 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **salida_actuador no negativa Euler**: 3 filas OK

### Muestra de datos

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.5 | 0.7 | 0 | 1 | 0 | 0.7 |
| 1 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.5 | 0.7 | 0 | 1 | 0 | 0.7 |
| 1 | 0.7 | 0 | 1 | 0 | 0.7 |

---

## Escenario: ME RK4

**Filas de datos:** 3

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| consigna_manual | 0.7 | 0.7 | 0.7 |
| modo_operacion | 0 | 0 | 0 |
| codigo_estado | 1 | 1 | 1 |
| fallo_modo | 0 | 0 | 0 |
| salida_actuador | 0.7 | 0.7 | 0.7 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 3 filas OK
- [PASS] **salida_actuador no negativa RK4**: 3 filas OK
- [PASS] **salida_actuador no mayor que 1 RK4**: 3 filas OK

### Muestra de datos

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.5 | 0.7 | 0 | 1 | 0 | 0.7 |
| 1 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.5 | 0.7 | 0 | 1 | 0 | 0.7 |
| 1 | 0.7 | 0 | 1 | 0 | 0.7 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `SelectorModo_comparacion.png` — Comparacion de los 3 escenarios
- `SelectorModo_me_euler.png` — ME con solver Euler
- `SelectorModo_me_rk4.png` — ME con solver RK4
- `SelectorModo_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*