# TC-TM-009 — Cambios simultaneos de todos los tipos

## Descripcion del test

Cambios de r_in, i_in y b_in al mismo tiempo en cada paso.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`r_in=1.0`  
`i_in=0`  
`b_in=1`  
`r_in`: t=0: 1.0, t=1.0: -2.0, t=2.0: 0.0  
`i_in`: t=0: 0, t=1.0: 5, t=2.0: -1  
`b_in`: t=0: 1, t=1.0: 0, t=2.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 4  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `r_out`@t=0.5: esperado 2.0±1e-09, obtenido 2 |
| ✅ | `r_out`@t=1.5: esperado -4.0±1e-09, obtenido -4 |
| ✅ | `i_out`@t=1.5: esperado 6±0, obtenido 6 |
| ✅ | `b_out`@t=1.5: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | i_in | b_in | r_in | r_abs | i_out | b_out | r_out |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 1 | 1 | 1 | 0 | 2 |
| 1 | 5 | 0 | -2 | 2 | 6 | 1 | -4 |
| 2 | -1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 2 | -1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 3 | -1 | 1 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `i_in` | -1 | 5 | 0.75 | 2.872 | 0 | -1 | variable |
| `b_in` | 0 | 1 | 0.75 | 0.5 | 1 | 1 | variable |
| `r_in` | -2 | 1 | -0.25 | 1.258 | 1 | 0 | variable |
| `r_abs` | 0 | 2 | 0.75 | 0.9574 | 1 | 0 | variable |
| `i_out` | 0 | 6 | 1.75 | 2.872 | 1 | 0 | variable |
| `b_out` | 0 | 1 | 0.25 | 0.5 | 0 | 0 | variable |
| `r_out` | -4 | 2 | -0.5 | 2.517 | 2 | 0 | variable |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Los tres tipos cambian en el mismo paso de simulacion. Verifica que fmi2SetReal, fmi2SetInteger y fmi2SetBoolean se llaman todos antes de la evaluacion de los outputs. Un codegen que solo actualiza un tipo antes de cada paso produciria valores mezclados incorrectos.
