# TC-TM-006 — Real muy pequeño

## Descripcion del test

r_in=1e-15: r_out≈2e-15, sin truncamiento a cero.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=1e-15`  
`i_in=0`  
`b_in=0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out` final: esperado 2e-15±1e-25, obtenido 2e-15 |
| ✅ | `r_abs` final: esperado 1e-15±1e-25, obtenido 1e-15 |
| ✅ | `r_out` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1e-15 | 1e-15 | 1 | 1 | 2e-15 |
| 0.1 | 0 | 0 | 1e-15 | 1e-15 | 1 | 1 | 2e-15 |
| 0.2 | 0 | 0 | 1e-15 | 1e-15 | 1 | 1 | 2e-15 |
| 0.1 | 0 | 0 | 1e-15 | 1e-15 | 1 | 1 | 2e-15 |
| 0.2 | 0 | 0 | 1e-15 | 1e-15 | 1 | 1 | 2e-15 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b_in` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `r_in` | 1e-15 | 1e-15 | 1e-15 | 0 | 1e-15 | 1e-15 | constante |
| `r_abs` | 1e-15 | 1e-15 | 1e-15 | 0 | 1e-15 | 1e-15 | constante |
| `i_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b_out` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `r_out` | 2e-15 | 2e-15 | 2e-15 | 0 | 2e-15 | 2e-15 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `i_in`=0, `b_in`=0, `r_in`=1e-15, `r_abs`=1e-15, `i_out`=1, `b_out`=1, `r_out`=2e-15 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `i_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b_in`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `i_out`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Valor real cerca del epsilon de maquina (1e-15 >> DBL_EPSILON≈2.2e-16). r_out=2e-15 no debe ser truncado a cero. Verifica que fmi2SetReal transmite valores muy pequenos sin perdida de precision.
