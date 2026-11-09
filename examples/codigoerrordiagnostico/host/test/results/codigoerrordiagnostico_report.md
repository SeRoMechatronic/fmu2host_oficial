# Informe de test — CodigoErrorDiagnostico

Generado: 2026-05-21 13:27:31

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.1| Euler  |
| ME RK4    | 1.0    | 0.1| RK4    |
| CS        | 1.0    | 0.1| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 3 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 5 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| temperatura | 0.9 | 0.9 | 0.9 |
| tension | 0.8 | 0.8 | 0.8 |
| vibracion | 0.4 | 0.4 | 0.4 |
| factor_reduccion | 0 | 0 | 0 |
| codigo_error | 101 | 101 | 101 |
| parada_emergencia | 1 | 1 | 1 |
| nivel_prioridad | 3 | 3 | 3 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **nivel_prioridad no negativo Euler**: 11 filas OK

### Muestra de datos

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.9 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |

---

## Escenario: ME RK4

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| temperatura | 0.9 | 0.9 | 0.9 |
| tension | 0.8 | 0.8 | 0.8 |
| vibracion | 0.4 | 0.4 | 0.4 |
| factor_reduccion | 0 | 0 | 0 |
| codigo_error | 101 | 101 | 101 |
| parada_emergencia | 1 | 1 | 1 |
| nivel_prioridad | 3 | 3 | 3 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **nivel_prioridad=3 (sobre-temperatura) RK4**: 11 filas OK
- [PASS] **codigo_error=101 (temperatura) RK4**: 11 filas OK

### Muestra de datos

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.9 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `CodigoErrorDiagnostico_comparacion.png` — Comparacion de los 3 escenarios
- `CodigoErrorDiagnostico_me_euler.png` — ME con solver Euler
- `CodigoErrorDiagnostico_me_rk4.png` — ME con solver RK4
- `CodigoErrorDiagnostico_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*