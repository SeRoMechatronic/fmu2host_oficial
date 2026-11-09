# TC-BL-005 — D-latch: captura a=TRUE en flanco ascendente de clk

## Descripcion del test

a=TRUE, clk: 0→1. y_latch pasa de FALSE a TRUE en el flanco.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=1`  
`b=0`  
`clk=0`  
`umbral=0.0`  
`clk`: t=0: 0, t=1.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_latch`@t=0.5: esperado 0±0, obtenido 0 |
| ❌ | `y_latch`@t=1.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
| 1 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 1 | 0.6667 | 0.5774 | 0 | 1 | variable |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_xor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 3:**
  - `y_latch`@t=1.5: esperado 1±0, obtenido 0
  - `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `umbral`=0, `a`=1, `b`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=0, `y_latch`=0, `y_or`=1, `y_xor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `a`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 2 FAIL)

clk permanece en FALSE hasta t=1.0 (sin flanco). y_latch=FALSE en t=0.5. En t=1.0, clk: FALSE→TRUE (flanco ascendente). La latch captura a=TRUE. En t=1.5: y_latch=TRUE, cuenta_flancos=1. Verifica que edge()/when se genera correctamente para capturar el valor de 'a' en el flanco.
