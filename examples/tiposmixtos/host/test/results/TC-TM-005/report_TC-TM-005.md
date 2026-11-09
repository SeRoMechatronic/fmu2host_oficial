# TC-TM-005 — Real grande

## Descripcion del test

r_in=1e8: r_out=2e8, sin desbordamiento de double.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=100000000.0`  
`i_in=999`  
`b_in=1`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado 200000000.0±1.0, obtenido 2e+08 |
| ✅ | `i_out` final: esperado 1000±0, obtenido 1000 |
| ✅ | `r_abs` final: esperado 100000000.0±1.0, obtenido 1e+08 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 999 | 1 | 1e+08 | 1e+08 | 1000 | 0 | 2e+08 |
| 0.1 | 999 | 1 | 1e+08 | 1e+08 | 1000 | 0 | 2e+08 |
| 0.2 | 999 | 1 | 1e+08 | 1e+08 | 1000 | 0 | 2e+08 |
| 0.1 | 999 | 1 | 1e+08 | 1e+08 | 1000 | 0 | 2e+08 |
| 0.2 | 999 | 1 | 1e+08 | 1e+08 | 1000 | 0 | 2e+08 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 999 | 999 | 999 | 0 | 999 | 999 | constante |
| `b_in` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_in` | 1e+08 | 1e+08 | 1e+08 | 0 | 1e+08 | 1e+08 | constante |
| `r_abs` | 1e+08 | 1e+08 | 1e+08 | 0 | 1e+08 | 1e+08 | constante |
| `i_out` | 1000 | 1000 | 1000 | 0 | 1000 | 1000 | constante |
| `b_out` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_out` | 2e+08 | 2e+08 | 2e+08 | 0 | 2e+08 | 2e+08 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=999, `b_in`=1, `r_in`=1e+08, `r_abs`=1e+08, `i_out`=1000, `b_out`=0, `r_out`=2e+08 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `b_in`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b_out`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Magnitud grande (1e8): el double puede representar exactamente 2e8 sin perdida de precision. i_out=999+1=1000. Verifica que no hay truncamiento accidental de los tipos cuando los valores son grandes pero dentro del rango de double.
