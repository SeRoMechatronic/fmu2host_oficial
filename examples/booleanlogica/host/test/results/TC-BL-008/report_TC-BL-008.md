# TC-BL-008 — Sin doble conteo — clk=TRUE mantenido no cuenta multiples flancos

## Descripcion del test

clk=TRUE por 3 pasos seguidos: cuenta_flancos=1 (solo el primer flanco).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=0`  
`b=0`  
`clk=0`  
`umbral=0.0`  
`clk`: t=0: 0, t=1.0: 1, t=2.0: 1, t=3.0: 1, t=4.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos`@t=2.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos`@t=3.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos` final: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 1 | 0.5 | 0.5477 | 0 | 0 | decreciente |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 4 check(s) fallados de 4:**
  - `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0
  - `cuenta_flancos`@t=2.5: esperado 1±0, obtenido 0
  - `cuenta_flancos`@t=3.5: esperado 1±0, obtenido 0
  - `cuenta_flancos` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `umbral`=0, `a`=0, `b`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=0, `y_latch`=0, `y_or`=0, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `a`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 4 FAIL)

TEST CRITICO DE DOBLE CONTEO. clk permanece TRUE durante t=1,2,3 s. Solo hay UN flanco ascendente (0→1 en t=1). El contador debe mantenerse en 1 mientras clk=TRUE, no incrementar a 2, 3... Si el codegen genera 'if clk' en lugar de 'if edge(clk)', el contador incrementaria en cada paso con clk=TRUE.
