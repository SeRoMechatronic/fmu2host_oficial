# TC-MZ-008 — Cambio de entrada en t=1 s — sistema inestable sigue creciendo

## Descripcion del test

Al poner u=0 en t=1s, el sistema inestable sigue creciendo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u_1_=1.0`  
`u_1_`: t=0: 1.0, t=1.0: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `x_1_`@t=2.0: esperado 2.0±1.0, obtenido 0 |
| ❌ | `x_3_`@t=2.0: esperado 30.0±15.0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | traza | x_1_ | x_2_ | x_3_ | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |
| 0.02 | 6 | 0 | 0 | 0 | 0 |
| 1 | 6 | 0 | 0 | 0 | 0 |
| 1.99 | 6 | 0 | 0 | 0 | 0 |
| 2 | 6 | 0 | 0 | 0 | 0 |

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

**❌ 2 check(s) fallados de 2:**
  - `x_1_`@t=2.0: esperado 2.0±1.0, obtenido 0
  - `x_3_`@t=2.0: esperado 30.0±15.0, obtenido 0
**Variables algebraicas constantes:** `traza`=6, `x_1_`=0, `x_2_`=0, `x_3_`=0, `y_norma`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `x_1_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_2_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_3_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 2 FAIL)

El sistema con A diagonal positiva es inestable: los estados crecen exponencialmente incluso sin entrada (u=0). En t=1 s, x3≈6. Despues de cambiar u=0, x3 sigue creciendo (sistema homogeneo inestable). A t=2 s, x3≈6*exp(3*1)≈120. Este test verifica que el cambio de entrada se aplica correctamente en el bucle.
