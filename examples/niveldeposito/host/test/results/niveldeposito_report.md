# Informe de test — NivelDeposito

Generado: 2026-05-21 13:29:41

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 10.0    | 0.01| Euler  |
| ME RK4    | 10.0    | 0.01| RK4    |
| CS        | 10.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 5 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 1001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| valvula_manual | 0 | 0 | 0 |
| sensor_nivel | 0.8 | 0.8 | 0.8 |
| alarma_maximo | 0 | 0 | 0 |
| alarma_minimo | 0 | 0 | 0 |
| bomba_activa | 0 | 1 | 0 |
| bomba | 0 | 0.497 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **bomba no negativa Euler**: 1001 filas OK

### Muestra de datos

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.8 | 0 | 0 | 1 | 0.497 |
| 0.01 | 0 | 0.8 | 0 | 0 | 1 | 0.494015 |
| 0.02 | 0 | 0.8 | 0 | 0 | 1 | 0.491045 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 9.99 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0.8 | 0 | 0 | 0 | 0 |

---

## Escenario: ME RK4

**Filas de datos:** 1001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| valvula_manual | 0 | 0 | 0 |
| sensor_nivel | 0.8 | 0.8 | 0.8 |
| alarma_maximo | 0 | 0 | 0 |
| alarma_minimo | 0 | 0 | 0 |
| bomba_activa | 0 | 1 | 0 |
| bomba | 0 | 0.497007 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 1001 filas OK
- [PASS] **bomba no negativa RK4**: 1001 filas OK
- [PASS] **bomba no mayor que 1 RK4**: 1001 filas OK

### Muestra de datos

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.8 | 0 | 0 | 1 | 0.497007 |
| 0.01 | 0 | 0.8 | 0 | 0 | 1 | 0.49403 |
| 0.02 | 0 | 0.8 | 0 | 0 | 1 | 0.491067 |
| ... | ... | ... | ... | ... | ... | ... |
| 9.98 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 9.99 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0.8 | 0 | 0 | 0 | 0 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `NivelDeposito_comparacion.png` — Comparacion de los 3 escenarios
- `NivelDeposito_me_euler.png` — ME con solver Euler
- `NivelDeposito_me_rk4.png` — ME con solver RK4
- `NivelDeposito_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*