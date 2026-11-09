# TC-TM-002 — Real negativo, entero cero, booleano false

## Descripcion del test

r_in=-4.5, i_in=0, b_in=false: r_out=-9, i_out=1, b_out=true, r_abs=4.5.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=-4.5`  
`i_in=0`  
`b_in=0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado -9.0±1e-09, obtenido -9 |
| ✅ | `i_out` final: esperado 1±0, obtenido 1 |
| ✅ | `b_out` final: esperado 1±0, obtenido 1 |
| ✅ | `r_abs` final: esperado 4.5±1e-09, obtenido 4.5 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | -4.5 | 4.5 | 1 | 1 | -9 |
| 0.1 | 0 | 0 | -4.5 | 4.5 | 1 | 1 | -9 |
| 0.2 | 0 | 0 | -4.5 | 4.5 | 1 | 1 | -9 |
| 0.1 | 0 | 0 | -4.5 | 4.5 | 1 | 1 | -9 |
| 0.2 | 0 | 0 | -4.5 | 4.5 | 1 | 1 | -9 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_in` | -4.5 | -4.5 | -4.5 | 0 | -4.5 | -4.5 | constante |
| `r_abs` | 4.5 | 4.5 | 4.5 | 0 | 4.5 | 4.5 | constante |
| `i_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_out` | -9 | -9 | -9 | 0 | -9 | -9 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=0, `b_in`=0, `r_in`=-4.5, `r_abs`=4.5, `i_out`=1, `b_out`=1, `r_out`=-9 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `i_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `i_out`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Real negativo: r_out=-9 (negativo) pero r_abs=4.5 (positivo). Entero cero: i_out=0+1=1. Booleano false negado: b_out=TRUE. Verifica que r_abs no confunde el signo con el resultado de r_out y que el tipo Boolean se niega correctamente para FALSE.
