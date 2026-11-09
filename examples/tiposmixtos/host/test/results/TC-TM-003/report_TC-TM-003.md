# TC-TM-003 — Real cero

## Descripcion del test

r_in=0.0: r_out=0, r_abs=0 (cero como valor absoluto).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=0.0`  
`i_in=10`  
`b_in=1`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `i_out` final: esperado 11±0, obtenido 11 |
| ✅ | `b_out` final: esperado 0±0, obtenido 0 |
| ✅ | `r_abs` final: esperado 0.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 10 | 1 | 0 | 0 | 11 | 0 | 0 |
| 0.1 | 10 | 1 | 0 | 0 | 11 | 0 | 0 |
| 0.2 | 10 | 1 | 0 | 0 | 11 | 0 | 0 |
| 0.1 | 10 | 1 | 0 | 0 | 11 | 0 | 0 |
| 0.2 | 10 | 1 | 0 | 0 | 11 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 10 | 10 | 10 | 0 | 10 | 10 | constante |
| `b_in` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_abs` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `i_out` | 11 | 11 | 11 | 0 | 11 | 11 | constante |
| `b_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=10, `b_in`=1, `r_in`=0, `r_abs`=0, `i_out`=11, `b_out`=0, `r_out`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `r_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_abs`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El valor absoluto del cero es cero. r_out=0*2=0 y r_abs=|0|=0. i_out=10+1=11. b_out=NOT(TRUE)=FALSE. El cero como entrada real no debe causar comportamientos especiales en ninguno de los tipos.
