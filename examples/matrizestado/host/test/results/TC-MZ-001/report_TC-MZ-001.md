# TC-MZ-001 — Condiciones iniciales — todos los estados en cero

## Descripcion del test

En t=0 con u=1: x[1]=x[2]=x[3]=0, norma=0, traza=6.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u_1_=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `x_1_`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `x_2_`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `x_3_`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `y_norma`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `traza`@t=0.0: esperado 6.0±1e-09, obtenido 6 |

### Muestra de datos (inicio / mitad / final)

| t | traza | x_1_ | x_2_ | x_3_ | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.001 | 6 | 0 | 0 | 0 | 0 |
| 0.002 | 6 | 0 | 0 | 0 | 0 |
| 0.005 | 6 | 0 | 0 | 0 | 0 |
| 0.009 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `traza` | 6 | 6 | 6 | 0 | 6 | 6 | constante |
| `x_1_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `x_2_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `x_3_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_norma` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `traza`=6, `x_1_`=0, `x_2_`=0, `x_3_`=0, `y_norma`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `x_1_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_2_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_3_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

El sistema empieza en x(0)=[0,0,0]. La traza A[1,1]+A[2,2]+A[3,3]=1+2+3=6.0 es constante e independiente del estado. Este test verifica que la FMU se inicializa correctamente y que los parametros de la matriz A se leen bien en la inicializacion.
