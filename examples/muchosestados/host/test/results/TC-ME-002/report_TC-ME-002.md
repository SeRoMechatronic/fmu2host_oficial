# TC-ME-002 — Propagacion de senal: y1 responde, y8 retrasado

## Descripcion del test

A t=0.1s: y1>0, y8≈0. A t=5s: y1≈1, y8>0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1`@t=0.1: esperado 0.09±0.02, obtenido 0.0951626 |
| ✅ | `y8`@t=0.1: esperado 0.0±0.001, obtenido 2.26043e-13 |
| ✅ | `y1`@t=5.0: esperado 0.993±0.01, obtenido 0.993262 |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.00995 | 4.967e-05 | 1.654e-07 | 4.167e-10 | 0 | 0 |
| 0.02 | 1 | 0 | 0.0198 | 0.0001974 | 1.313e-06 | 6.567e-09 | 2.465e-11 | 6.861e-14 |
| 2.51 | 1 | 0 | 0.9187 | 0.7147 | 0.4587 | 0.2446 | 0.1102 | 0.04269 |
| 5 | 1 | 1 | 0.9933 | 0.9596 | 0.8753 | 0.735 | 0.5595 | 0.384 |
| 5 | 1 | 1 | 0.9933 | 0.9596 | 0.8753 | 0.735 | 0.5595 | 0.384 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 1 | 0.4203 | 0.4941 | 0 | 1 | creciente |
| `y1` | 0 | 0.9933 | 0.8011 | 0.2473 | 0 | 0.9933 | creciente |
| `y2` | 0 | 0.9596 | 0.6099 | 0.3127 | 0 | 0.9596 | creciente |
| `y3` | 0 | 0.8753 | 0.4352 | 0.3016 | 0 | 0.8753 | creciente |
| `y4` | 0 | 0.735 | 0.2884 | 0.2486 | 0 | 0.735 | creciente |
| `y5` | 0 | 0.5595 | 0.1764 | 0.1805 | 0 | 0.5595 | creciente |
| `y6` | 0 | 0.384 | 0.09941 | 0.117 | 0 | 0.384 | creciente |
| `y7` | 0 | 0.2378 | 0.0516 | 0.0683 | 0 | 0.2378 | creciente |
| `y8` | 0 | 0.1334 | 0.02472 | 0.03619 | 0 | 0.1334 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `todos_activos`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y1`: valor final = 0.9933 (arranca en 0, delta = 0.9933).
**Convergencia** de `y2`: valor final = 0.9596 (arranca en 0, delta = 0.9596).
**Variables algebraicas constantes:** `u`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

La senal se propaga en cascada. y1 responde en t=0.1 s (≈0.095). y8 aun no ha recibido la senal (≈0). A t=5 s (5 tau), y1 esta casi convergido. y8 aun esta en transitorio. Verifica que los 8 estados son independientes y no comparten buffers.
