# TC-TM-008 — Bascule booleano — tres pasos

## Descripcion del test

Tres pasos alternando b_in=true/false: b_out siempre niega.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=0.0`  
`i_in=0`  
`b_in=1`  
`b_in`: t=0: 1, t=1.0: 0, t=2.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 4  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `b_out`@t=0.5: esperado 0±0, obtenido 0 |
| ✅ | `b_out`@t=1.5: esperado 1±0, obtenido 1 |
| ✅ | `b_out`@t=2.5: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 1 | 1 | 0 |
| 2 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |
| 2 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |
| 3 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b_in` | 0 | 1 | 0.75 | 0.5 | 1 | 1 | variable |
| `r_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_abs` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `i_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b_out` | 0 | 1 | 0.25 | 0.5 | 0 | 0 | variable |
| `r_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=0, `r_in`=0, `r_abs`=0, `i_out`=1, `r_out`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `i_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `r_abs`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

La negacion booleana es combinacional: b_out=NOT(b_in) en todo momento. Al cambiar b_in con el scheduler, b_out debe invertirse inmediatamente. Verifica que b_out no es latched ni tiene memoria: responde instantaneamente a cada cambio de b_in.
