# TC-AV-006 — Reales con signos mixtos — suma y dobles con signos

## Descripcion del test

v_real=[-1,2,-3,4]: suma=2, v_doble=[-2,4,-6,8].

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`v_real_1_=-1.0`  
`v_real_2_=2.0`  
`v_real_3_=-3.0`  
`v_real_4_=4.0`  
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
| ❌ | `suma_real` final: esperado 2.0±1e-09, obtenido 0 |
| ❌ | `v_doble_1_` final: esperado -2.0±1e-09, obtenido 0 |
| ❌ | `v_doble_2_` final: esperado 4.0±1e-09, obtenido 0 |
| ❌ | `v_doble_3_` final: esperado -6.0±1e-09, obtenido 0 |
| ❌ | `v_doble_4_` final: esperado 8.0±1e-09, obtenido 0 |

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

**❌ 5 check(s) fallados de 5:**
  - `suma_real` final: esperado 2.0±1e-09, obtenido 0
  - `v_doble_1_` final: esperado -2.0±1e-09, obtenido 0
  - `v_doble_2_` final: esperado 4.0±1e-09, obtenido 0
  - `v_doble_3_` final: esperado -6.0±1e-09, obtenido 0
  - `v_doble_4_` final: esperado 8.0±1e-09, obtenido 0
**Variables algebraicas constantes:** `suma_real`=0, `suma_int`=0, `v_doble_1_`=0, `v_doble_2_`=0, `v_doble_3_`=0, `v_doble_4_`=0, `alguno_true`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `suma_real`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `suma_int`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `v_doble_1_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 5 FAIL)

Entradas con signos alternos [-1,2,-3,4]. suma=-1+2-3+4=2. v_doble[i]=2*v_real[i] conserva el signo: [-2,4,-6,8]. Verifica que la multiplicacion por 2 no aplica abs() ni truncamiento de signo. Un codegen que mezcle indices produciria sumas y dobles incorrectos.
