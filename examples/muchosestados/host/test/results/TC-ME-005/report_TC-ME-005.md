# TC-ME-005 — Convergencia de todas las etapas a 1.0 en t=30 s

## Descripcion del test

A t=30 s, todas las etapas deben converger a >0.999.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 30.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 601  |  Tiempo total: 30 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1` final: esperado 1.0±0.001, obtenido 1 |
| ✅ | `y4` final: esperado 1.0±0.001, obtenido 1 |
| ✅ | `y8` final: esperado 1.0±0.01, obtenido 0.999999 |
| ✅ | `todos_activos` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.05 | 1 | 0 | 0.04877 | 0.001209 | 2.005e-05 | 2.604e-07 | 0 | 0 |
| 0.1 | 1 | 0 | 0.09516 | 0.004679 | 0.0001546 | 3.865e-06 | 7.286e-08 | 1.021e-09 |
| 15 | 1 | 1 | 1 | 1 | 1 | 0.9998 | 0.9991 | 0.9972 |
| 29.95 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| 30 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 1 | 0.9018 | 0.2978 | 0 | 1 | creciente |
| `y1` | 0 | 1 | 0.9659 | 0.1279 | 0 | 1 | creciente |
| `y2` | 0 | 1 | 0.9326 | 0.1948 | 0 | 1 | creciente |
| `y3` | 0 | 1 | 0.8993 | 0.2438 | 0 | 1 | creciente |
| `y4` | 0 | 1 | 0.8661 | 0.2824 | 0 | 1 | creciente |
| `y5` | 0 | 1 | 0.8328 | 0.3138 | 0 | 1 | creciente |
| `y6` | 0 | 1 | 0.7995 | 0.3398 | 0 | 1 | creciente |
| `y7` | 0 | 1 | 0.7662 | 0.3613 | 0 | 1 | creciente |
| `y8` | 0 | 1 | 0.7329 | 0.3791 | 0 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `todos_activos`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y1`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y2`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y3`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y4`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y5`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y6`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y7`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y8`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `u`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

CRITERIO PRIMARIO. A t=30 s (muy lejos del transitorio), todas las etapas deben haber convergido al valor de la entrada (u=1). Si alguna etapa no converge, su buffer de estado esta mal dimensionado o hay un error en la conexion en cascada entre etapas.
