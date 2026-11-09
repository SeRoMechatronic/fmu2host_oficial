# Informe de test — CrecimientoPoblacional

Generado: 2026-05-21 13:27:59

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 5.0    | 0.1| Euler  |
| ME RK4    | 5.0    | 0.1| RK4    |
| CS        | 5.0    | 0.1| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 4 PASS / 0 FAIL
- **CS**: ejecutado | 3 PASS / 0 FAIL

**Total: 9 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 51

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| tasa_entrada | 0 | 0 | 0 |
| superpoblacion | 0 | 0 | 0 |
| poblacion | 2.686 | 100 | 100 |
| saturacion | 0.02686 | 1 | 1 |
| tasa_crecimiento | 2.92769e-05 | 87.1494 | 2.92769e-05 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 51 filas OK
- [PASS] **poblacion positiva Euler**: 51 filas OK

### Muestra de datos

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2.686 | 0.02686 | 9.14849 |
| 0.1 | 0 | 0 | 3.60085 | 0.0360085 | 12.1492 |
| 0.2 | 0 | 0 | 4.81576 | 0.0481576 | 16.0435 |
| ... | ... | ... | ... | ... | ... |
| 4.8 | 0 | 0 | 100 | 1 | 6.92944e-05 |
| 4.9 | 0 | 0 | 100 | 1 | 4.50414e-05 |
| 5 | 0 | 0 | 100 | 1 | 2.92769e-05 |

---

## Escenario: ME RK4

**Filas de datos:** 51

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| tasa_entrada | 0 | 0 | 0 |
| superpoblacion | 0 | 0 | 0 |
| poblacion | 2.81447 | 99.9999 | 99.9999 |
| saturacion | 0.0281447 | 0.999999 | 0.999999 |
| tasa_crecimiento | 0.00030412 | 87.4614 | 0.00030412 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 51 filas OK
- [PASS] **RK4 no sobrepasa K**: 51 filas OK
- [PASS] **poblacion siempre positiva**: 51 filas OK
- [PASS] **poblacion cerca de K en t=5**: t=5: 99.9999 ~= 95.0 (tol=5.0)

### Muestra de datos

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2.81447 | 0.0281447 | 9.57339 |
| 0.1 | 0 | 0 | 3.94725 | 0.0394725 | 13.2701 |
| 0.2 | 0 | 0 | 5.51013 | 0.0551013 | 18.2228 |
| ... | ... | ... | ... | ... | ... |
| 4.8 | 0 | 0 | 99.9998 | 0.999998 | 0.00061235 |
| 4.9 | 0 | 0 | 99.9999 | 0.999999 | 0.000431541 |
| 5 | 0 | 0 | 99.9999 | 0.999999 | 0.00030412 |

---

## Escenario: CS

**Filas de datos:** 51

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| tasa_entrada | 0 | 0 | 0 |
| superpoblacion | 0 | 0 | 0 |
| poblacion | 2.686 | 100 | 100 |
| saturacion | 0.02686 | 1 | 1 |
| tasa_crecimiento | 2.92769e-05 | 87.1494 | 2.92769e-05 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 51 filas OK
- [PASS] **poblacion positiva CS**: 51 filas OK
- [PASS] **poblacion cerca de K en t=5 CS**: t=5: 100 ~= 95.0 (tol=10.0)

### Muestra de datos

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2.686 | 0.02686 | 9.14849 |
| 0.1 | 0 | 0 | 3.60085 | 0.0360085 | 12.1492 |
| 0.2 | 0 | 0 | 4.81576 | 0.0481576 | 16.0435 |
| ... | ... | ... | ... | ... | ... |
| 4.8 | 0 | 0 | 100 | 1 | 6.92944e-05 |
| 4.9 | 0 | 0 | 100 | 1 | 4.50414e-05 |
| 5 | 0 | 0 | 100 | 1 | 2.92769e-05 |

---

## Graficas generadas

- `CrecimientoPoblacional_comparacion.png` — Comparacion de los 3 escenarios
- `CrecimientoPoblacional_me_euler.png` — ME con solver Euler
- `CrecimientoPoblacional_me_rk4.png` — ME con solver RK4
- `CrecimientoPoblacional_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*