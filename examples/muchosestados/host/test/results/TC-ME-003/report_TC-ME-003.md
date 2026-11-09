# TC-ME-003 — todos_activos=true después de propagacion completa

## Descripcion del test

todos_activos cambia a true aproximadamente en t≈8 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 2001  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `todos_activos` == 1 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.00995 | 4.967e-05 | 1.654e-07 | 4.167e-10 | 0 | 0 |
| 0.02 | 1 | 0 | 0.0198 | 0.0001974 | 1.313e-06 | 6.567e-09 | 2.465e-11 | 6.861e-14 |
| 10 | 1 | 1 | 1 | 0.9995 | 0.9972 | 0.9897 | 0.9707 | 0.9329 |
| 19.99 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0.9999 |
| 20 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0.9999 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 1 | 0.8546 | 0.3526 | 0 | 1 | creciente |
| `y1` | 0 | 1 | 0.9498 | 0.1508 | 0 | 1 | creciente |
| `y2` | 0 | 1 | 0.8998 | 0.2296 | 0 | 1 | creciente |
| `y3` | 0 | 1 | 0.8498 | 0.2843 | 0 | 1 | creciente |
| `y4` | 0 | 1 | 0.7999 | 0.3248 | 0 | 1 | creciente |
| `y5` | 0 | 1 | 0.7499 | 0.3552 | 0 | 1 | creciente |
| `y6` | 0 | 0.9999 | 0.6999 | 0.3775 | 0 | 0.9999 | creciente |
| `y7` | 0 | 0.9997 | 0.6499 | 0.3929 | 0 | 0.9997 | creciente |
| `y8` | 0 | 0.9992 | 0.6 | 0.402 | 0 | 0.9992 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `todos_activos`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y1`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y2`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y3`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y4`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y5`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y6`: valor final = 0.9999 (arranca en 0, delta = 0.9999).
**Convergencia** de `y7`: valor final = 0.9997 (arranca en 0, delta = 0.9997).
**Convergencia** de `y8`: valor final = 0.9992 (arranca en 0, delta = 0.9992).
**Variables algebraicas constantes:** `u`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La senal tarda ~8 veces el tiempo de transito individual (tau=1 s) en propagarse por las 8 etapas. todos_activos=true requiere que todos los yi > 0.01. Si este flag nunca se activa, alguno de los 8 estados tiene un buffer incorrecto y siempre es cero.
