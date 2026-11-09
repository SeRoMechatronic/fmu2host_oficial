# TC-VE-008 — u=1e30 — cerca de Inf, es_finito=false

## Descripcion del test

y_sat=1.0, es_finito=false (|u|>=1e29).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1e+30`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sat` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `es_finito` final: esperado 0±0, obtenido 0 |
| ✅ | `y_inv` sin NaN/Inf: OK |
| ✅ | `y_log` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1e+30 | 0 | 1e-30 | 69.08 | 1 | 1e+15 |
| 0.1 | 1e+30 | 0 | 1e-30 | 69.08 | 1 | 1e+15 |
| 0.2 | 1e+30 | 0 | 1e-30 | 69.08 | 1 | 1e+15 |
| 0.1 | 1e+30 | 0 | 1e-30 | 69.08 | 1 | 1e+15 |
| 0.2 | 1e+30 | 0 | 1e-30 | 69.08 | 1 | 1e+15 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1e+30 | 1e+30 | 1e+30 | 0 | 1e+30 | 1e+30 | constante |
| `es_finito` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_inv` | 1e-30 | 1e-30 | 1e-30 | 0 | 1e-30 | 1e-30 | constante |
| `y_log` | 69.08 | 69.08 | 69.08 | 0 | 69.08 | 69.08 | constante |
| `y_sat` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_sqrt` | 1e+15 | 1e+15 | 1e+15 | 0 | 1e+15 | 1e+15 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1e+30, `es_finito`=0, `y_inv`=1e-30, `y_log`=69.08, `y_sat`=1, `y_sqrt`=1e+15 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y_sat`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con u=1e30 (maximo double practico), es_finito=false porque |1e30|>=1e29. y_sat=1.0 (saturado). Las operaciones son validas: 1/1e30≈1e-30, sqrt(1e30)≈1e15, log(1e30)≈69.08. Ninguna debe producir NaN/Inf.
