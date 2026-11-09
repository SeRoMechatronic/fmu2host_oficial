# TC-MZ-004 — Verificacion analitica en t=1.0 s

## Descripcion del test

x1(1)≈1.718, x2(1)≈3.195, x3(1)≈6.029 con u=1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u_1_=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `x_1_` final: esperado 1.718±0.05, obtenido 0 |
| ❌ | `x_2_` final: esperado 3.195±0.05, obtenido 0 |
| ❌ | `x_3_` final: esperado 6.029±0.05, obtenido 0 |

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
  - `x_1_` final: esperado 1.718±0.05, obtenido 0
  - `x_2_` final: esperado 3.195±0.05, obtenido 0
  - `x_3_` final: esperado 6.029±0.05, obtenido 0
**Variables algebraicas constantes:** `traza`=6, `x_1_`=0, `x_2_`=0, `x_3_`=0, `y_norma`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `x_1_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_2_`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `x_3_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 3 FAIL)

Solucion analitica exacta: xi(1)=(exp(lambda_i)-1)/lambda_i. x1=(e^1-1)/1≈1.718, x2=(e^2-1)/2≈3.195, x3=(e^3-1)/3≈6.029. Este es el test de referencia mas preciso: detecta errores en los coeficientes de la matriz A (autovalores equivocados) y en el indexado de la matriz (transposicion de filas/columnas).
