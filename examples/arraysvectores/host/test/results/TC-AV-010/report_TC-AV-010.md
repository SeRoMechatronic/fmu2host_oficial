# TC-AV-010 — Independencia de los 4 elementos — sin escrituras cruzadas

## Descripcion del test

Simulacion con distintos valores en todos los elementos: cada doble refleja su propio real.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`v_real_1_=10.0`  
`v_real_2_=20.0`  
`v_real_3_=30.0`  
`v_real_4_=40.0`  
`v_int_1_=1`  
`v_int_2_=2`  
`v_int_3_=3`  
`v_int_4_=4`  
`v_bool_1_=1`  
`v_bool_2_=0`  
`v_bool_3_=0`  
`v_bool_4_=0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `suma_real` == 100.0 siempre: 3/3 violaciones (ej: 0) |
| ❌ | `suma_int` final: esperado 10±0, obtenido 0 |
| ❌ | `alguno_true` == 1 siempre: 3/3 violaciones (ej: 0) |
| ❌ | `v_doble_1_` == 20.0 siempre: 3/3 violaciones (ej: 0) |
| ❌ | `v_doble_2_` == 40.0 siempre: 3/3 violaciones (ej: 0) |
| ❌ | `v_doble_3_` == 60.0 siempre: 3/3 violaciones (ej: 0) |
| ❌ | `v_doble_4_` == 80.0 siempre: 3/3 violaciones (ej: 0) |

### Muestra de datos (inicio / mitad / final)

| t | suma_real | suma_int | v_doble_1_ | v_doble_2_ | v_doble_3_ | v_doble_4_ | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

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

**❌ 7 check(s) fallados de 7:**
  - `suma_real` == 100.0 siempre: 3/3 violaciones (ej: 0)
  - `suma_int` final: esperado 10±0, obtenido 0
  - `alguno_true` == 1 siempre: 3/3 violaciones (ej: 0)
  - `v_doble_1_` == 20.0 siempre: 3/3 violaciones (ej: 0)
  - `v_doble_2_` == 40.0 siempre: 3/3 violaciones (ej: 0)
  - `v_doble_3_` == 60.0 siempre: 3/3 violaciones (ej: 0)
  - `v_doble_4_` == 80.0 siempre: 3/3 violaciones (ej: 0)
**Variables algebraicas constantes:** `suma_real`=0, `suma_int`=0, `v_doble_1_`=0, `v_doble_2_`=0, `v_doble_3_`=0, `v_doble_4_`=0, `alguno_true`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `suma_real`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `suma_int`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `v_doble_1_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 7 FAIL)

VERIFICACION DE INDEPENDENCIA COMPLETA. Entradas [10,20,30,40] producen dobles [20,40,60,80] exactamente. suma_real=100 en todos los pasos. Si cualquier v_doble difiere de su valor esperado, hay una escritura cruzada entre elementos del array. Este test cubre los 4 elementos de v_doble simultaneamente con valores que los hacen distinguibles entre si.
