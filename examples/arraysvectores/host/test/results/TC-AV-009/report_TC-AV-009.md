# TC-AV-009 — Cambio de un elemento en mitad de simulacion

## Descripcion del test

t=0: v_real=[1,1,1,1] → suma=4. t=1: v_real[4]→5 → suma=8, v_doble[4]=10.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`v_real_1_=1.0`  
`v_real_2_=1.0`  
`v_real_3_=1.0`  
`v_real_4_=1.0`  
`v_int_1_=0`  
`v_int_2_=0`  
`v_int_3_=0`  
`v_int_4_=0`  
`v_bool_1_=0`  
`v_bool_2_=0`  
`v_bool_3_=0`  
`v_bool_4_=0`  
`v_real_4_`: t=0: 1.0, t=1.0: 5.0

## Simulacion: ME-RK4

- Pasos simulados: 5  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `suma_real`@t=0.5: esperado 4.0±1e-09, obtenido 0 |
| ❌ | `suma_real`@t=1.5: esperado 8.0±1e-09, obtenido 0 |
| ❌ | `v_doble_4_`@t=0.5: esperado 2.0±1e-09, obtenido 0 |
| ❌ | `v_doble_4_`@t=1.5: esperado 10.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | suma_real | suma_int | v_doble_1_ | v_doble_2_ | v_doble_3_ | v_doble_4_ | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `suma_real` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `suma_int` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `v_doble_1_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `v_doble_2_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `v_doble_3_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `v_doble_4_` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alguno_true` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 4 check(s) fallados de 4:**
  - `suma_real`@t=0.5: esperado 4.0±1e-09, obtenido 0
  - `suma_real`@t=1.5: esperado 8.0±1e-09, obtenido 0
  - `v_doble_4_`@t=0.5: esperado 2.0±1e-09, obtenido 0
  - `v_doble_4_`@t=1.5: esperado 10.0±1e-09, obtenido 0
**Variables algebraicas constantes:** `suma_real`=0, `suma_int`=0, `v_doble_1_`=0, `v_doble_2_`=0, `v_doble_3_`=0, `v_doble_4_`=0, `alguno_true`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `suma_real`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `suma_int`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `v_doble_1_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 4 FAIL)

Solo v_real[4] cambia de 1.0 a 5.0 en t=1.0. Antes del cambio: suma=4, v_doble[4]=2. Despues: suma=1+1+1+5=8, v_doble[4]=10. v_doble[1,2,3] permanecen en 2. Verifica que cada elemento se lee independientemente: un codegen que lee solo [1] no detectaria el cambio en [4].
