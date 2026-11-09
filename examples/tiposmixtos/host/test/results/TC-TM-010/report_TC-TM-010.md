# TC-TM-010 — Sin NaN ni Inf en todos los tipos

## Descripcion del test

Simulacion con valores extremos: ningun output invalido.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=100000000.0`  
`i_in=1000000`  
`b_in=1`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` sin NaN/Inf: OK |
| ✅ | `r_abs` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1e+06 | 1 | 1e+08 | 1e+08 | 1e+06 | 0 | 2e+08 |
| 1 | 1e+06 | 1 | 1e+08 | 1e+08 | 1e+06 | 0 | 2e+08 |
| 2 | 1e+06 | 1 | 1e+08 | 1e+08 | 1e+06 | 0 | 2e+08 |
| 1 | 1e+06 | 1 | 1e+08 | 1e+08 | 1e+06 | 0 | 2e+08 |
| 2 | 1e+06 | 1 | 1e+08 | 1e+08 | 1e+06 | 0 | 2e+08 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 1e+06 | 1e+06 | 1e+06 | 0 | 1e+06 | 1e+06 | constante |
| `b_in` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_in` | 1e+08 | 1e+08 | 1e+08 | 0 | 1e+08 | 1e+08 | constante |
| `r_abs` | 1e+08 | 1e+08 | 1e+08 | 0 | 1e+08 | 1e+08 | constante |
| `i_out` | 1e+06 | 1e+06 | 1e+06 | 0 | 1e+06 | 1e+06 | constante |
| `b_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_out` | 2e+08 | 2e+08 | 2e+08 | 0 | 2e+08 | 2e+08 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=1e+06, `b_in`=1, `r_in`=1e+08, `r_abs`=1e+08, `i_out`=1e+06, `b_out`=0, `r_out`=2e+08 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b_out`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con valores grandes pero finitos de todos los tipos, ninguna salida debe producir NaN o Inf. r_out=2e8 y r_abs=1e8 son finitos. i_out=1000001 es un entero valido. b_out es 0 o 1. Verifica la integridad numerica del modelo algebraico completo.
