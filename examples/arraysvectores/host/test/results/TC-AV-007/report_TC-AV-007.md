# TC-AV-007 — Enteros con signos mixtos — suma_int correcto

## Descripcion del test

v_int=[-5,10,-3,2]: suma_int=4 (-5+10-3+2).

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
`v_int_1_=-5`  
`v_int_2_=10`  
`v_int_3_=-3`  
`v_int_4_=2`  
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
| ❌ | `suma_int` final: esperado 4±0, obtenido 0 |

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

**❌ 1 check(s) fallados de 1:**
  - `suma_int` final: esperado 4±0, obtenido 0
**Variables algebraicas constantes:** `suma_real`=0, `suma_int`=0, `v_doble_1_`=0, `v_doble_2_`=0, `v_doble_3_`=0, `v_doble_4_`=0, `alguno_true`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `suma_real`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `suma_int`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `v_doble_1_`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 1 FAIL)

Suma de enteros con signos mixtos: -5+10-3+2=4. El tipo fmi2Integer debe manejar negativos correctamente en el unrolling. Si el codegen convierte a unsigned o aplica abs(), la suma seria 20 en lugar de 4. Exact match required (tol=0).
