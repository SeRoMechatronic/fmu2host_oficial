# Informe de test — EtapaSecuenciador

Generado: 2026-05-21 13:28:47

## Parametros de simulacion

| Escenario | t_end (s) | h (s) | Solver |
|-----------|-----------|-------|--------|
| ME Euler  | 50.0    | 0.01| Euler  |
| ME RK4    | 50.0    | 0.01| RK4    |
| CS        | 50.0    | 0.01| interno|

## Resumen de resultados

- **ME Euler**: ejecutado | 2 PASS / 0 FAIL
- **ME RK4**: ejecutado | 4 PASS / 0 FAIL
- **CS**: **NO EJECUTADO** | 0 PASS / 0 FAIL

**Total: 6 PASS / 0 FAIL**

---

## Escenario: ME Euler

**Filas de datos:** 5001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| sensor_confirmacion | 0.8 | 0.8 | 0.8 |
| arrancar | 1 | 1 | 1 |
| parar | 0 | 0 | 0 |
| progreso_etapa | 0 | 0 | 0 |
| etapa_actual | 0 | 0 | 0 |
| etapa_previa | 0 | 0 | 0 |
| secuencia_completa | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 5001 filas OK
- [PASS] **etapa_actual no negativa Euler**: 5001 filas OK

### Muestra de datos

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.02 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 49.98 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 49.99 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 50 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: ME RK4

**Filas de datos:** 5001

### Estadisticas de variables de salida

| Variable | min | max | final |
|----------|-----|-----|-------|
| sensor_confirmacion | 0.8 | 0.8 | 0.8 |
| arrancar | 1 | 1 | 1 |
| parar | 0 | 0 | 0 |
| progreso_etapa | 0 | 0 | 0 |
| etapa_actual | 0 | 0 | 0 |
| etapa_previa | 0 | 0 | 0 |
| secuencia_completa | 0 | 0 | 0 |

### Verificaciones

- [PASS] **sin NaN/Inf**: 5001 filas OK
- [PASS] **etapa_actual no negativa RK4**: 5001 filas OK
- [PASS] **progreso no negativo RK4**: 5001 filas OK
- [PASS] **progreso no mayor que 1 RK4**: 5001 filas OK

### Muestra de datos

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.02 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| ... | ... | ... | ... | ... | ... | ... | ... |
| 49.98 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 49.99 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 50 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |

---

## Escenario: CS

> Ejecutable no encontrado o error al correr la simulacion.

---

## Graficas generadas

- `EtapaSecuenciador_comparacion.png` — Comparacion de los 3 escenarios
- `EtapaSecuenciador_me_euler.png` — ME con solver Euler
- `EtapaSecuenciador_me_rk4.png` — ME con solver RK4
- `EtapaSecuenciador_cs.png` — Co-Simulation

---

*Informe generado automaticamente por test_utils.py*