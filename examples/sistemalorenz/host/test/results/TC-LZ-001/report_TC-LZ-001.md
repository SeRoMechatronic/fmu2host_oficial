# TC-LZ-001 — Condiciones iniciales — t=0

## Descripcion del test

x=1, y=1, z=1.5, on_attractor=true en t=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `x_out`@t=0.0: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `y_out`@t=0.0: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `z_out`@t=0.0: esperado 1.5±1e-06, obtenido 1.5 |
| ✅ | `on_attractor`@t=0.0: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.001 | 1 | 1 | 1.025 | 1.497 |
| 0.002 | 1 | 1.001 | 1.051 | 1.494 |
| 0.005 | 1 | 1.003 | 1.127 | 1.485 |
| 0.009 | 1 | 1.01 | 1.229 | 1.474 |
| 0.01 | 1 | 1.012 | 1.255 | 1.472 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `x_out` | 1 | 1.012 | 1.004 | 0.004248 | 1 | 1.012 | creciente |
| `y_out` | 1 | 1.255 | 1.127 | 0.08454 | 1 | 1.255 | creciente |
| `z_out` | 1.472 | 1.5 | 1.486 | 0.009386 | 1.5 | 1.472 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `on_attractor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `on_attractor`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `y_out`: tasa de cambio maxima = 25.58 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El sistema Lorenz parte de (1, 1, 1.5), un punto en el interior del atractor. on_attractor=true porque z∈[0,60], |x|<30, |y|<35. Este test verifica la inicializacion correcta de los 3 estados del sistema caotico.
