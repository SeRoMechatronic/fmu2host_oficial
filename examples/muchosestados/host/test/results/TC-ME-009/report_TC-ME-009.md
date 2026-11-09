# TC-ME-009 — Verificacion de buffer — todas las 8 etapas son independientes

## Descripcion del test

Cada etapa tiene un valor diferente durante el transitorio.

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
| ✅ | `y1` en [0, 1.01]: OK |
| ✅ | `y8` en [0, 1.01]: OK |
| ✅ | `y1` sin NaN/Inf: OK |
| ✅ | `y8` sin NaN/Inf: OK |

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

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `todos_activos`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y1`: valor final = 0.9933 (arranca en 0, delta = 0.9933).
**Convergencia** de `y2`: valor final = 0.9596 (arranca en 0, delta = 0.9596).
**Variables algebraicas constantes:** `u`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Las 8 etapas son acotadas en [0,1] con entrada u=1. Un buffer mal dimensionado podria causar escrituras fuera de rango que producen valores invalidos en otras etapas. Este test verifica que y1 e y8 (los extremos de la cadena) son siempre finitos y acotados.
