# TC-TM-004 — Entero negativo

## Descripcion del test

i_in=-7: i_out=-7+1=-6. Incremento correcto para negativos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=1.0`  
`i_in=-7`  
`b_in=0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado 2.0±1e-09, obtenido 2 |
| ✅ | `i_out` final: esperado -6±0, obtenido -6 |
| ✅ | `b_out` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | -7 | 0 | 1 | 1 | -6 | 1 | 2 |
| 0.1 | -7 | 0 | 1 | 1 | -6 | 1 | 2 |
| 0.2 | -7 | 0 | 1 | 1 | -6 | 1 | 2 |
| 0.1 | -7 | 0 | 1 | 1 | -6 | 1 | 2 |
| 0.2 | -7 | 0 | 1 | 1 | -6 | 1 | 2 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | -7 | -7 | -7 | 0 | -7 | -7 | constante |
| `b_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_in` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_abs` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `i_out` | -6 | -6 | -6 | 0 | -6 | -6 | constante |
| `b_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_out` | 2 | 2 | 2 | 0 | 2 | 2 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=-7, `b_in`=0, `r_in`=1, `r_abs`=1, `i_out`=-6, `b_out`=1, `r_out`=2 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_in`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `r_abs`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El incremento i_in+1 funciona correctamente para enteros negativos: -7+1=-6. Un error de implementacion comun es usar abs() antes de incrementar, lo que daria 7+1=8 en lugar de -6. b_out=NOT(FALSE)=TRUE.
