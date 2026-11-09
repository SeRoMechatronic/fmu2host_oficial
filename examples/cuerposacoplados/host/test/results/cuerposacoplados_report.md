# Informe de test — CuerposAcoplados

Generado: 2026-05-21 13:28:35

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 20.0    | 0.05| Euler  |
| ME RK4    | 20.0    | 0.05| RK4    |
| CS        | 20.0    | 0.05| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 5 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 400

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| fuerza_externa | 1 | 1 | 1 |
| en_fase | 0 | 1 | 0 |
| energia_total | 2.78051 | 370.082 | 370.082 |
| pos1 | -8.62428 | 11.1573 | 4.05727 |
| pos2 | -1.43687 | 2.44258 | -1.05766 |
| vel1 | -25.2249 | 22.4172 | -25.2249 |
| vel2 | -3.98542 | 3.68168 | 2.1935 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 400 filas OK
- [PASS] **energia total positiva Euler**: 400 filas OK

### Muestra de datos

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 3.65516 | 1 | -0.475 | -0.225 | 0.5625 |
| 0.05 | 1 | 0 | 3.67443 | 0.98875 | -0.446875 | -0.44875 | 0.623125 |
| 0.1 | 1 | 0 | 3.6829 | 0.966313 | -0.415719 | -0.668281 | 0.681359 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 19.85 | 1 | 0 | 363.203 | 6.36747 | -1.24259 | -22.3 | 1.72308 |
| 19.9 | 1 | 0 | 366.653 | 5.25247 | -1.15643 | -23.904 | 1.97546 |
| 19.95 | 1 | 0 | 370.082 | 4.05727 | -1.05766 | -25.2249 | 2.1935 |

---

## Escenario: ME RK4

**Filas de datos:** 400

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| fuerza_externa | 1 | 1 | 1 |
| en_fase | 0 | 1 | 0 |
| energia_total | 1.7717 | 3.86678 | 2.89712 |
| pos1 | -0.853275 | 1.24179 | 0.272148 |
| pos2 | -0.559807 | 0.796616 | -0.2554 |
| vel1 | -2.25726 | 2.15145 | -2.20641 |
| vel2 | -0.785178 | 0.992511 | -0.332381 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 400 filas OK
- [PASS] **energia total positiva RK4**: 400 filas OK
- [PASS] **energia inicial correcta**: t=0: 3.61939 ~= 3.625 (tol=0.1)

### Muestra de datos

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 3.61939 | 0.994392 | -0.473454 | -0.223881 | 0.561477 |
| 0.05 | 1 | 0 | 3.60268 | 0.977682 | -0.443892 | -0.443565 | 0.62057 |
| 0.1 | 1 | 0 | 3.57515 | 0.950153 | -0.411445 | -0.656161 | 0.676782 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 19.85 | 1 | 0 | 3.11292 | 0.487944 | -0.21947 | -2.09213 | -0.387115 |
| 19.9 | 1 | 0 | 3.00645 | 0.381476 | -0.238119 | -2.16232 | -0.359071 |
| 19.95 | 1 | 0 | 2.89712 | 0.272148 | -0.2554 | -2.20641 | -0.332381 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `CuerposAcoplados_comparacion.png` — Comparacion de los 3 escenarios
- `CuerposAcoplados_me_euler.png` — ME con solver Euler
- `CuerposAcoplados_me_rk4.png` — ME con solver RK4
- `CuerposAcoplados_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*