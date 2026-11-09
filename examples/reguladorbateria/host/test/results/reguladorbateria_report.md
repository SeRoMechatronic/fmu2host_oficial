# Informe de test — ReguladorBateria

Generado: 2026-05-21 13:30:17

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
| carga_conectada | 1 | 1 | 1 |
| tension_bateria | 0.5 | 0.5 | 0.5 |
| carga_completa | 0 | 0 | 0 |
| cargando | 1 | 1 | 1 |
| fallo_sobretension | 0 | 0 | 0 |
| corriente_carga | 0.025 | 0.282418 | 0.25 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 501 filas OK
- [PASS] **corriente_carga no negativa Euler**: 501 filas OK

### Muestra de datos

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 0 | 1 | 0 | 0.025 |
| 0.01 | 1 | 0.5 | 0 | 1 | 0 | 0.049 |
| 0.02 | 1 | 0.5 | 0 | 1 | 0 | 0.07189 |
| ... | ... | ... | ... | ... | ... | ... |
| 4.98 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |
| 4.99 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |
| 5 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |

---

## Escenario: ME RK4

**Filas de datos:** 501

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| carga_conectada | 1 | 1 | 1 |
| tension_bateria | 0.5 | 0.5 | 0.5 |
| carga_completa | 0 | 0 | 0 |
| cargando | 1 | 1 | 1 |
| fallo_sobretension | 0 | 0 | 0 |
| corriente_carga | 0.0244827 | 0.278095 | 0.25 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 501 filas OK
- [PASS] **corriente_carga no negativa RK4**: 501 filas OK

### Muestra de datos

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 0 | 1 | 0 | 0.0244827 |
| 0.01 | 1 | 0.5 | 0 | 1 | 0 | 0.0478697 |
| 0.02 | 1 | 0.5 | 0 | 1 | 0 | 0.0700859 |
| ... | ... | ... | ... | ... | ... | ... |
| 4.98 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |
| 4.99 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |
| 5 | 1 | 0.5 | 0 | 1 | 0 | 0.25 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `ReguladorBateria_comparacion.png` — Comparacion de los 3 escenarios
- `ReguladorBateria_me_euler.png` — ME con solver Euler
- `ReguladorBateria_me_rk4.png` — ME con solver RK4
- `ReguladorBateria_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*