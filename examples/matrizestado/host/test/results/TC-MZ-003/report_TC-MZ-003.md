# TC-MZ-003 — Ordenacion de estados: x3 > x2 > x1 para u>0

## Descripcion del test

Con u=1, los estados crecen en orden inverso al indice.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u_1_=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `x_1_` > 0.0 siempre: 201/201 violaciones (ej: 0) |
| ❌ | `x_2_` > 0.0 siempre: 201/201 violaciones (ej: 0) |
| ❌ | `x_3_` > 0.0 siempre: 201/201 violaciones (ej: 0) |

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

**❌ 3 check(s) fallados de 3:**
  - `x_1_` > 0.0 siempre: 201/201 violaciones (ej: 0)
  - `x_2_` > 0.0 siempre: 201/201 violaciones (ej: 0)
  - `x_3_` > 0.0 siempre: 201/201 violaciones (ej: 0)
**Variables algebraicas constantes:** `traza`=6, `x_1_`=0, `x_2_`=0, `x_3_`=0, `y_norma`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `x_1_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_2_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_3_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 3 FAIL)

Para u=1, los tres estados crecen desde 0. El orden de crecimiento es x3 > x2 > x1 porque los autovalores son lambda_3=3 > lambda_2=2 > lambda_1=1 (crecimiento exponencial mas rapido para mayor autovalor). Una transposicion de la matriz A cambiaria este ordenamiento.
