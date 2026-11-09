# Informe de test — ArranqueSuaveMotor

Generado: 2026-05-21 13:29:15

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 12.0    | 0.01| Euler  |
| ME RK4    | 12.0    | 0.01| RK4    |
| CS        | 12.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 3 PASS / 0 FAIL
- **ME RK4**: ejecutado | 4 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 7 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 1201

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| orden_arranque | 1 | 1 | 1 |
| carga_motor | 0.5 | 0.5 | 0.5 |
| en_rampa | 0 | 1 | 0 |
| fallo_sobrecarga | 0 | 0 | 0 |
| motor_en_marcha | 0 | 1 | 1 |
| tension_aplicada | 0 | 0.97824 | 0.97824 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1201 filas OK
- [PASS] **tension no negativa Euler**: 1201 filas OK
- [PASS] **tension no mayor que 1 Euler**: 1201 filas OK

### Muestra de datos

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0.5 | 1 | 0 | 0 | 6.66667e-05 |
| 0.02 | 1 | 0.5 | 1 | 0 | 0 | 0.000198444 |
| ... | ... | ... | ... | ... | ... | ... |
| 11.98 | 1 | 0.5 | 0 | 0 | 1 | 0.978095 |
| 11.99 | 1 | 0.5 | 0 | 0 | 1 | 0.978168 |
| 12 | 1 | 0.5 | 0 | 0 | 1 | 0.97824 |

---

## Escenario: ME RK4

**Filas de datos:** 1201

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| orden_arranque | 1 | 1 | 1 |
| carga_motor | 0.5 | 0.5 | 0.5 |
| en_rampa | 0 | 1 | 0 |
| fallo_sobrecarga | 0 | 0 | 0 |
| motor_en_marcha | 0 | 1 | 1 |
| tension_aplicada | 3.30754e-05 | 0.978094 | 0.978094 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1201 filas OK
- [PASS] **tension no negativa RK4**: 1201 filas OK
- [PASS] **tension no excede 1.0 RK4**: 1201 filas OK
- [PASS] **rampa supera 50% en t=12s RK4**: t=2.62: 0.501637667

### Muestra de datos

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 1 | 0 | 0 | 3.30754e-05 |
| 0.01 | 1 | 0.5 | 1 | 0 | 0 | 0.00013128 |
| 0.02 | 1 | 0.5 | 1 | 0 | 0 | 0.000293106 |
| ... | ... | ... | ... | ... | ... | ... |
| 11.98 | 1 | 0.5 | 0 | 0 | 1 | 0.977948 |
| 11.99 | 1 | 0.5 | 0 | 0 | 1 | 0.978021 |
| 12 | 1 | 0.5 | 0 | 0 | 1 | 0.978094 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `ArranqueSuaveMotor_comparacion.png` — Comparacion de los 3 escenarios
- `ArranqueSuaveMotor_me_euler.png` — ME con solver Euler
- `ArranqueSuaveMotor_me_rk4.png` — ME con solver RK4
- `ArranqueSuaveMotor_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*