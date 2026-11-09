# TC-TM-007 — Entero cerca del maximo de int32

## Descripcion del test

i_in=2147483646: i_out=2147483647 (INT32_MAX).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=0.0`  
`i_in=2147483646`  
`b_in=0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `i_out` final: esperado 2147483647±0, obtenido 2.14748e+09 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 2.147e+09 | 0 | 0 | 0 | 2.147e+09 | 1 | 0 |
| 0.1 | 2.147e+09 | 0 | 0 | 0 | 2.147e+09 | 1 | 0 |
| 0.2 | 2.147e+09 | 0 | 0 | 0 | 2.147e+09 | 1 | 0 |
| 0.1 | 2.147e+09 | 0 | 0 | 0 | 2.147e+09 | 1 | 0 |
| 0.2 | 2.147e+09 | 0 | 0 | 0 | 2.147e+09 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 2.147e+09 | 2.147e+09 | 2.147e+09 | 0 | 2.147e+09 | 2.147e+09 | constante |
| `b_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_abs` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `i_out` | 2.147e+09 | 2.147e+09 | 2.147e+09 | 0 | 2.147e+09 | 2.147e+09 | constante |
| `b_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=2.147e+09, `b_in`=0, `r_in`=0, `r_abs`=0, `i_out`=2.147e+09, `b_out`=1, `r_out`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_abs`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

INT32_MAX - 1 + 1 = INT32_MAX. Un error de tipo (almacenar el entero en float) perderia precision: (float)2147483646 ≠ 2147483646. El resultado exacto 2147483647 solo es posible si el tipo es int32_t en todo el camino de datos.
