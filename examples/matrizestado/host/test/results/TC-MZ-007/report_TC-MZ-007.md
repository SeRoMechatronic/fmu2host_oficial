# TC-MZ-007 — Entrada negativa — estados negativos con mismo ordenamiento

## Descripcion del test

Con u=-1: x1,x2,x3 < 0 con |x3|>|x2|>|x1|.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u_1_=-1.0`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `x_1_` < 0.0 siempre: 101/101 violaciones (ej: 0) |
| ❌ | `x_2_` < 0.0 siempre: 101/101 violaciones (ej: 0) |
| ❌ | `x_3_` < 0.0 siempre: 101/101 violaciones (ej: 0) |

### Muestra de datos (inicio / mitad / final)

| t | traza | x_1_ | x_2_ | x_3_ | y_norma |
| --- | --- | --- | --- | --- | --- |
| 0 | 6 | 0 | 0 | 0 | 0 |
| 0.01 | 6 | 0 | 0 | 0 | 0 |
| 0.02 | 6 | 0 | 0 | 0 | 0 |
| 0.5 | 6 | 0 | 0 | 0 | 0 |
| 0.99 | 6 | 0 | 0 | 0 | 0 |
| 1 | 6 | 0 | 0 | 0 | 0 |

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
  - `x_1_` < 0.0 siempre: 101/101 violaciones (ej: 0)
  - `x_2_` < 0.0 siempre: 101/101 violaciones (ej: 0)
  - `x_3_` < 0.0 siempre: 101/101 violaciones (ej: 0)
**Variables algebraicas constantes:** `traza`=6, `x_1_`=0, `x_2_`=0, `x_3_`=0, `y_norma`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `x_1_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_2_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_3_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 3 FAIL)

Con u=-1, la solucion es xi(t)=-(e^(lambda_i*t)-1)/lambda_i < 0. Los estados crecen en valor absoluto en la direccion negativa. El orden de crecimiento absoluto sigue siendo |x3|>|x2|>|x1|. Verifica el manejo de signos en fmi2SetReal.
