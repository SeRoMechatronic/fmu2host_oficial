# Informe de test — SuspensionActiva

Generado: 2026-05-21 13:31:04

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
| perfil_bache | 0.5 | 0.5 | 0.5 |
| velocidad_vehiculo | 0.6 | 0.6 | 0.6 |
| actuador_saturado | 0 | 1 | 1 |
| bache_detectado | 0 | 1 | 1 |
| modo_confort | 0 | 0 | 0 |
| fuerza_actuador | -1 | -0.55 | -1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **fuerza acotada inferior Euler**: 1001 filas OK
- [PASS] **fuerza acotada superior Euler**: 1001 filas OK

### Muestra de datos

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.6 | 0 | 0 | 0 | -0.55 |
| 0.01 | 0.5 | 0.6 | 0 | 0 | 0 | -1 |
| 0.02 | 0.5 | 0.6 | 1 | 0 | 0 | -1 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |
| 9.99 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |
| 10 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |

---

## Escenario: ME RK4

**Filas de datos:** 1001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| perfil_bache | 0.5 | 0.5 | 0.5 |
| velocidad_vehiculo | 0.6 | 0.6 | 0.6 |
| actuador_saturado | 0 | 1 | 1 |
| bache_detectado | 0 | 1 | 1 |
| modo_confort | 0 | 0 | 0 |
| fuerza_actuador | -1 | -0.504677 | -1 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **fuerza acotada inferior RK4**: 1001 filas OK
- [PASS] **fuerza acotada [-1,1]**: 1001 filas OK

### Muestra de datos

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.6 | 0 | 0 | 0 | -0.504677 |
| 0.01 | 0.5 | 0.6 | 0 | 0 | 0 | -0.926885 |
| 0.02 | 0.5 | 0.6 | 0 | 0 | 0 | -1 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |
| 9.99 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |
| 10 | 0.5 | 0.6 | 1 | 1 | 0 | -1 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `SuspensionActiva_comparacion.png` — Comparacion de los 3 escenarios
- `SuspensionActiva_me_euler.png` — ME con solver Euler
- `SuspensionActiva_me_rk4.png` — ME con solver RK4
- `SuspensionActiva_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*