# TC-AV-001 — Todos ceros — suma e indices en cero

## Descripcion del test

v_real=[0,0,0,0], v_int=[0,0,0,0], v_bool=[F,F,F,F]: suma=0, doble=[0,0,0,0], alguno=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`v_real_1_=0.0`  
`v_real_2_=0.0`  
`v_real_3_=0.0`  
`v_real_4_=0.0`  
`v_int_1_=0`  
`v_int_2_=0`  
`v_int_3_=0`  
`v_int_4_=0`  
`v_bool_1_=0`  
`v_bool_2_=0`  
`v_bool_3_=0`  
`v_bool_4_=0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `suma_real` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `suma_int` final: esperado 0±0, obtenido 0 |
| ✅ | `alguno_true` final: esperado 0±0, obtenido 0 |
| ✅ | `v_doble_1_` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `v_doble_4_` final: esperado 0.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | suma_real | suma_int | v_doble_1_ | v_doble_2_ | v_doble_3_ | v_doble_4_ | alguno_true |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

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

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `suma_real`=0, `suma_int`=0, `v_doble_1_`=0, `v_doble_2_`=0, `v_doble_3_`=0, `v_doble_4_`=0, `alguno_true`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `suma_real`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `suma_int`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `v_doble_1_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Linea base de ceros. suma_real=0, suma_int=0, alguno_true=FALSE, todos los v_doble[i]=0. Confirma la inicializacion sin efectos laterales: ninguna variable comparte memoria con otra. Si algun doble es distinto de cero con entradas cero, hay un error de inicializacion del buffer.
