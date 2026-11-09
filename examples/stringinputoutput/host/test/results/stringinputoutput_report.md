# Informe de test — StringInputOutput

Generado: 2026-05-21 13:30:49

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 4.0    | 1.0| Euler  |
| ME RK4    | 4.0    | 1.0| RK4    |
| CS        | 4.0    | 1.0| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 5

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| value | 1 | 1 | 1 |
| mode_operation | — | — |  |
| tag_sensor | — | — |  |
| scaled_value | 1.5 | 1.5 | 1.5 |
| alarm | 1 | 1 | 1 |
| alert_msg | — | — | ALERT: value below lower limit (10.0) |
| status | — | — | LOW |

### Verificaciones

- [PASS] **sin NaN/Inf**: 5 filas OK
- [PASS] **simulacion completa Euler**: t_final=4

### Muestra de datos

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 1 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 2 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 2 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 3 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 4 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |

---

## Escenario: ME RK4

**Filas de datos:** 5

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| value | 1 | 1 | 1 |
| mode_operation | — | — |  |
| tag_sensor | — | — |  |
| scaled_value | 1.5 | 1.5 | 1.5 |
| alarm | 1 | 1 | 1 |
| alert_msg | — | — | ALERT: value below lower limit (10.0) |
| status | — | — | LOW |

### Verificaciones

- [PASS] **sin NaN/Inf**: 5 filas OK
- [PASS] **simulacion completa RK4**: t_final=4

### Muestra de datos

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 1 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 2 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 2 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 3 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 4 | 1 |  |  | 1.5 | 1 | ALERT: value below lower limit (10.0) | LOW |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `StringInputOutput_comparacion.png` — Comparacion de los 3 escenarios
- `StringInputOutput_me_euler.png` — ME con solver Euler
- `StringInputOutput_me_rk4.png` — ME con solver RK4
- `StringInputOutput_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*