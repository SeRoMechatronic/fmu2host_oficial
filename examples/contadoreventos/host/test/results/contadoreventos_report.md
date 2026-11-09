# Informe de test — ContadorEventos

Generado: 2026-05-21 13:27:45

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 1.0    | 0.1| Euler  |
| ME RK4    | 1.0    | 0.1| RK4    |
| CS        | 1.0    | 0.1| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| evento | 1 | 1 | 1 |
| reset | 0 | 0 | 0 |
| cuenta | 0 | 0 | 0 |
| decenas | 0 | 0 | 0 |
| desbordamiento | 0 | 0 | 0 |
| unidades | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **cuenta no negativa Euler**: 11 filas OK

### Muestra de datos

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 1 | 0 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.9 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 | 1 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: ME RK4

**Filas de datos:** 11

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| evento | 1 | 1 | 1 |
| reset | 0 | 0 | 0 |
| cuenta | 0 | 0 | 0 |
| decenas | 0 | 0 | 0 |
| desbordamiento | 0 | 0 | 0 |
| unidades | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 11 filas OK
- [PASS] **cuenta no negativa RK4**: 11 filas OK

### Muestra de datos

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 1 | 0 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... | ... |
| 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.9 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 | 1 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `ContadorEventos_comparacion.png` — Comparacion de los 3 escenarios
- `ContadorEventos_me_euler.png` — ME con solver Euler
- `ContadorEventos_me_rk4.png` — ME con solver RK4
- `ContadorEventos_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*