# TC-TM-001 — Valores nominales — todos los tipos activos

## Descripcion del test

r_in=3.0, i_in=5, b_in=true: r_out=6, i_out=6, b_out=false, r_abs=3.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=3.0`  
`i_in=5`  
`b_in=1`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado 6.0±1e-09, obtenido 6 |
| ✅ | `i_out` final: esperado 6±0, obtenido 6 |
| ✅ | `b_out` final: esperado 0±0, obtenido 0 |
| ✅ | `r_abs` final: esperado 3.0±1e-09, obtenido 3 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 1 | 3 | 3 | 6 | 0 | 6 |
| 0.1 | 5 | 1 | 3 | 3 | 6 | 0 | 6 |
| 0.2 | 5 | 1 | 3 | 3 | 6 | 0 | 6 |
| 0.1 | 5 | 1 | 3 | 3 | 6 | 0 | 6 |
| 0.2 | 5 | 1 | 3 | 3 | 6 | 0 | 6 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `b_in` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_in` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `r_abs` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `i_out` | 6 | 6 | 6 | 0 | 6 | 6 | constante |
| `b_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_out` | 6 | 6 | 6 | 0 | 6 | 6 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=5, `b_in`=1, `r_in`=3, `r_abs`=3, `i_out`=6, `b_out`=0, `r_out`=6 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b_out`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Caso nominal con los cuatro tipos de FMI 2.0 activos simultaneamente. r_out=r_in*2=6, i_out=i_in+1=6, b_out=NOT(TRUE)=FALSE, r_abs=|3|=3. Este test ejercita los cuatro caminos de fmi2Set*/fmi2Get* en un solo paso de simulacion.
