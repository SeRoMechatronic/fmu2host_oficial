# TC-ME-008 — Eliminacion del escalon — decaimiento desde convergencia

## Descripcion del test

Despues de convergencia a t=20 s, u→0: todas las etapas decaen.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 30.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`  
`u`: t=0: 1.0, t=20.0: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 601  |  Tiempo total: 30 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1`@t=25.0: esperado 0.007±0.01, obtenido 0.00673795 |
| ✅ | `todos_activos` es FALSE en algun punto: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.05 | 1 | 0 | 0.04877 | 0.001209 | 2.005e-05 | 2.604e-07 | 0 | 0 |
| 0.1 | 1 | 0 | 0.09516 | 0.004679 | 0.0001546 | 3.865e-06 | 7.286e-08 | 1.021e-09 |
| 15 | 1 | 1 | 1 | 1 | 1 | 0.9998 | 0.9991 | 0.9972 |
| 29.95 | 0 | 0 | 4.773e-05 | 0.0005226 | 0.002885 | 0.01072 | 0.03021 | 0.069 |
| 30 | 0 | 0 | 4.54e-05 | 0.0004994 | 0.002769 | 0.01034 | 0.02925 | 0.06709 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 0 | 1 | 0.6656 | 0.4722 | 1 | 0 | decreciente |
| `todos_activos` | 0 | 1 | 0.7221 | 0.4483 | 0 | 0 | decreciente |
| `y1` | 0 | 1 | 0.6656 | 0.4355 | 0 | 4.54e-05 | decreciente |
| `y2` | 0 | 1 | 0.6655 | 0.4159 | 0 | 0.0004994 | decreciente |
| `y3` | 0 | 1 | 0.6654 | 0.4008 | 0 | 0.002769 | decreciente |
| `y4` | 0 | 1 | 0.6651 | 0.3881 | 0 | 0.01034 | decreciente |
| `y5` | 0 | 1 | 0.6642 | 0.3779 | 0 | 0.02925 | estable |
| `y6` | 0 | 0.9999 | 0.662 | 0.3707 | 0 | 0.06709 | creciente |
| `y7` | 0 | 0.9998 | 0.6577 | 0.3676 | 0 | 0.1301 | creciente |
| `y8` | 0 | 0.9996 | 0.6504 | 0.3694 | 0 | 0.2202 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `u`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `y1`: valor final = 4.54e-05 (arranca en 0, delta = 4.54e-05).
**Dinamica rapida** en `u`: tasa de cambio maxima = 20 unidades/s.
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

En t=20 s, todas las etapas han convergido a 1.0. Al eliminar la entrada, la primera etapa decae: y1(25)≈e^(-5)≈0.007 (5 tau despues). Las etapas posteriores decaen mas lentamente (sistema de orden superior). todos_activos vuelve a false cuando alguna etapa baja de 0.01.
