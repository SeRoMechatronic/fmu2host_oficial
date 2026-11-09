# TC-BL-007 — Contador de flancos — 3 flancos ascendentes

## Descripcion del test

3 transiciones FALSE→TRUE en clk: cuenta_flancos=3 al final.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 6.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=0`  
`b=0`  
`clk=0`  
`umbral=0.0`  
`clk`: t=0: 0, t=1.0: 1, t=2.0: 0, t=3.0: 1, t=4.0: 0, t=5.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 7  |  Tiempo total: 6 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos`@t=3.5: esperado 2±0, obtenido 0 |
| ❌ | `cuenta_flancos` final: esperado 3±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 6 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 1 | 0.5714 | 0.5345 | 0 | 1 | creciente |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 3 check(s) fallados de 3:**
  - `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0
  - `cuenta_flancos`@t=3.5: esperado 2±0, obtenido 0
  - `cuenta_flancos` final: esperado 3±0, obtenido 0
**Variables algebraicas constantes:** `umbral`=0, `a`=0, `b`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=0, `y_latch`=0, `y_or`=0, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `a`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 3 FAIL)

Tres ciclos completos: 0→1 en t=1, 3, 5. Los flancos descendentes (1→0 en t=2, 4) no deben incrementar. cuenta_flancos debe ser exactamente 1, 2, 3 respectivamente. Si el contador incrementa en flancos descendentes, edge() fue sustituido por deteccion de nivel. Si se queda en 0, el when/edge no fue generado por el codegen.
