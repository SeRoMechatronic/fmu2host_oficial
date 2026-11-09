# Informe de test — OsciladorArmonico

Generado: 2026-05-21 13:29:50

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 20.0    | 0.01| Euler  |
| ME RK4    | 20.0    | 0.01| RK4    |
| CS        | 20.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 3 PASS / 0 FAIL
- **ME RK4**: ejecutado | 4 PASS / 0 FAIL
- **CS**: ejecutado | 2 PASS / 0 FAIL

**Total: 9 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 19.8171 | 52195.2 | 52195.2 |
| posicion | -46.8571 | 50.724 | 50.724 |
| velocidad | -280.247 | 309.292 | 53.0615 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **energia positiva Euler**: 2000 filas OK
- [PASS] **oscilacion detectada Euler**: 40 cambios de signo

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.8171 | 1 | -0.394784 |
| 0.01 | 19.8954 | 0.996052 | -0.789568 |
| 0.02 | 19.9739 | 0.988156 | -1.18279 |
| ... | ... | ... | ... |
| 19.97 | 51785.5 | 49.0743 | 92.1729 |
| 19.98 | 51990 | 49.996 | 72.7992 |
| 19.99 | 52195.2 | 50.724 | 53.0615 |

---

## Escenario: ME RK4

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 19.7392 | 19.7392 | 19.7392 |
| posicion | -1 | 1 | 0.999999 |
| velocidad | -6.28319 | 6.28319 | 0.000102404 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **energia positiva RK4**: 2000 filas OK
- [PASS] **oscilacion detectada (RK4)**: 40 cambios de signo
- [PASS] **energia conservada RK4**: t=19.99: 19.7392 ~= 19.739 (tol=0.2)

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.7392 | 0.998027 | -0.394524 |
| 0.01 | 19.7392 | 0.992115 | -0.787492 |
| 0.02 | 19.7392 | 0.982287 | -1.17735 |
| ... | ... | ... | ... |
| 19.97 | 19.7392 | 0.992112 | 0.787593 |
| 19.98 | 19.7392 | 0.998025 | 0.394626 |
| 19.99 | 19.7392 | 0.999999 | 0.000102404 |

---

## Escenario: CS

**Filas de datos:** 2000

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| energia | 19.8171 | 52195.2 | 52195.2 |
| posicion | -46.8571 | 50.724 | 50.724 |
| velocidad | -280.247 | 309.292 | 53.0615 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 2000 filas OK
- [PASS] **energia positiva CS**: 2000 filas OK

### Muestra de datos

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.8171 | 1 | -0.394784 |
| 0.01 | 19.8954 | 0.996052 | -0.789568 |
| 0.02 | 19.9739 | 0.988156 | -1.18279 |
| ... | ... | ... | ... |
| 19.97 | 51785.5 | 49.0743 | 92.1729 |
| 19.98 | 51990 | 49.996 | 72.7992 |
| 19.99 | 52195.2 | 50.724 | 53.0615 |

---

## Graficas generadas

- `OsciladorArmonico_comparacion.png` — Comparacion de los 3 escenarios
- `OsciladorArmonico_me_euler.png` — ME con solver Euler
- `OsciladorArmonico_me_rk4.png` — ME con solver RK4
- `OsciladorArmonico_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*