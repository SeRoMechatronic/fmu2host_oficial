# Informe de test — Mi_Modelo_Nuevo

Generado: 2026-05-21 13:29:14

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 5.0    | 0.01| Euler  |
| ME RK4    | 5.0    | 0.01| RK4    |
| CS        | 5.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 2 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 4 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 501

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| flag_activo | 1 | 1 | 1 |
| entrada_principal | 1 | 1 | 1 |
| flag_salida | 0 | 1 | 1 |
| salida_filtrada | 0.01 | 0.993495 | 0.993495 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 501 filas OK
- [PASS] **salida_filtrada no negativa Euler**: 501 filas OK

### Muestra de datos

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0.01 |
| 0.01 | 1 | 1 | 0 | 0.0199 |
| 0.02 | 1 | 1 | 0 | 0.029701 |
| ... | ... | ... | ... | ... |
| 4.98 | 1 | 1 | 1 | 0.993363 |
| 4.99 | 1 | 1 | 1 | 0.99343 |
| 5 | 1 | 1 | 1 | 0.993495 |

---

## Escenario: ME RK4

**Filas de datos:** 501

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| flag_activo | 1 | 1 | 1 |
| entrada_principal | 1 | 1 | 1 |
| flag_salida | 0 | 1 | 1 |
| salida_filtrada | 0.00995017 | 0.993329 | 0.993329 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 501 filas OK
- [PASS] **salida_filtrada no negativa RK4**: 501 filas OK

### Muestra de datos

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0.00995017 |
| 0.01 | 1 | 1 | 0 | 0.0198013 |
| 0.02 | 1 | 1 | 0 | 0.0295545 |
| ... | ... | ... | ... | ... |
| 4.98 | 1 | 1 | 1 | 0.993194 |
| 4.99 | 1 | 1 | 1 | 0.993262 |
| 5 | 1 | 1 | 1 | 0.993329 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `Mi_Modelo_Nuevo_comparacion.png` — Comparacion de los 3 escenarios
- `Mi_Modelo_Nuevo_me_euler.png` — ME con solver Euler
- `Mi_Modelo_Nuevo_me_rk4.png` — ME con solver RK4
- `Mi_Modelo_Nuevo_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*