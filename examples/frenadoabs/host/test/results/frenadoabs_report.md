# Informe de test — FrenadoABS

Generado: 2026-05-21 13:28:57

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 20.0    | 0.01| Euler  |
| ME RK4    | 20.0    | 0.01| RK4    |
| CS        | 20.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| presion_pedal | 0.9 | 0.9 | 0.9 |
| velocidad_rueda | 0.9 | 0.9 | 0.9 |
| abs_activo | 0 | 0 | 0 |
| frenado_normal | 1 | 1 | 1 |
| rueda_bloqueada | 0 | 0 | 0 |
| presion_modulada | 0.1125 | 0.9 | 0.9 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **presion no negativa Euler**: 2000 filas OK

### Muestra de datos

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.9 | 0 | 1 | 0 | 0.1125 |
| 0.01 | 0.9 | 0.9 | 0 | 1 | 0 | 0.210938 |
| 0.02 | 0.9 | 0.9 | 0 | 1 | 0 | 0.29707 |
| ... | ... | ... | ... | ... | ... | ... |
| 19.97 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |
| 19.98 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |
| 19.99 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |

---

## Escenario: ME RK4

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| presion_pedal | 0.9 | 0.9 | 0.9 |
| velocidad_rueda | 0.9 | 0.9 | 0.9 |
| abs_activo | 0 | 0 | 0 |
| frenado_normal | 1 | 1 | 1 |
| rueda_bloqueada | 0 | 0 | 0 |
| presion_modulada | 0.105753 | 0.9 | 0.9 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **presion no negativa RK4**: 2000 filas OK

### Muestra de datos

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.9 | 0 | 1 | 0 | 0.105753 |
| 0.01 | 0.9 | 0.9 | 0 | 1 | 0 | 0.199079 |
| 0.02 | 0.9 | 0.9 | 0 | 1 | 0 | 0.281439 |
| ... | ... | ... | ... | ... | ... | ... |
| 19.97 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |
| 19.98 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |
| 19.99 | 0.9 | 0.9 | 0 | 1 | 0 | 0.9 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `FrenadoABS_comparacion.png` — Comparacion de los 3 escenarios
- `FrenadoABS_me_euler.png` — ME con solver Euler
- `FrenadoABS_me_rk4.png` — ME con solver RK4
- `FrenadoABS_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*