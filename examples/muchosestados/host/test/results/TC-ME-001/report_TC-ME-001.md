# TC-ME-001 — Condiciones iniciales — todos los estados en cero

## Descripcion del test

En t=0: y1=y2=...=y8=0, todos_activos=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `y8`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `todos_activos`@t=0.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.001 | 1 | 0 | 0.0009995 | 4.997e-07 | 1.665e-10 | 4.167e-14 | 0 | 0 |
| 0.002 | 1 | 0 | 0.001998 | 1.997e-06 | 1.331e-09 | 6.657e-13 | 2.497e-16 | 6.936e-20 |
| 0.005 | 1 | 0 | 0.004988 | 1.246e-05 | 2.076e-08 | 2.594e-11 | 2.589e-14 | 2.144e-17 |
| 0.009 | 1 | 0 | 0.00896 | 4.026e-05 | 1.207e-07 | 2.714e-10 | 4.883e-13 | 7.318e-16 |
| 0.01 | 1 | 0 | 0.00995 | 4.967e-05 | 1.654e-07 | 4.133e-10 | 8.263e-13 | 1.376e-15 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y1` | 0 | 0.00995 | 0.004983 | 0.0033 | 0 | 0.00995 | creciente |
| `y2` | 0 | 4.967e-05 | 1.741e-05 | 1.711e-05 | 0 | 4.967e-05 | creciente |
| `y3` | 0 | 1.654e-07 | 4.555e-08 | 5.603e-08 | 0 | 1.654e-07 | creciente |
| `y4` | 0 | 4.133e-10 | 9.529e-11 | 1.367e-10 | 0 | 4.133e-10 | constante |
| `y5` | 0 | 8.263e-13 | 1.66e-13 | 2.676e-13 | 0 | 8.263e-13 | constante |
| `y6` | 0 | 1.376e-15 | 2.476e-16 | 4.378e-16 | 0 | 1.376e-15 | constante |
| `y7` | 0 | 1.963e-18 | 3.226e-19 | 6.157e-19 | 0 | 1.963e-18 | constante |
| `y8` | 0 | 2.448e-21 | 3.727e-22 | 7.589e-22 | 0 | 2.448e-21 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1, `todos_activos`=0, `y5`=1.66e-13, `y6`=2.476e-16, `y7`=3.226e-19, `y8`=3.727e-22 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `todos_activos`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Los 8 filtros en cascada parten de estado cero. Con u=1.0 aplicado desde t=0, el primer filtro comienza a responder inmediatamente pero los filtros posteriores aun no tienen senal. todos_activos=false porque ninguna etapa ha superado el umbral de 0.01.
