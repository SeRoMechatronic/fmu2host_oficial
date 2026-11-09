# TC-BL-006 — D-latch: captura a=FALSE en flanco — latch no es level-triggered

## Descripcion del test

a=FALSE en flanco, despues a→TRUE (sin flanco): y_latch permanece FALSE.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=0`  
`b=0`  
`clk=0`  
`umbral=0.0`  
`clk`: t=0: 0, t=1.0: 1, t=2.0: 1  
`a`: t=0: 0, t=2.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 4  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_latch`@t=1.5: esperado 0±0, obtenido 0 |
| ✅ | `y_latch`@t=2.5: esperado 0±0, obtenido 0 |
| ❌ | `cuenta_flancos` final: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
| 2 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |
| 3 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 0 | 1 | 0.5 | 0.5774 | 0 | 1 | variable |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 1 | 0.75 | 0.5 | 0 | 1 | variable |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 0 | 1 | 0.5 | 0.5774 | 0 | 1 | variable |
| `y_xor` | 0 | 1 | 0.5 | 0.5774 | 0 | 1 | variable |

#### Analisis contextual

**❌ 1 check(s) fallados de 3:**
  - `cuenta_flancos` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `umbral`=0, `b`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=0, `y_latch`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta_flancos`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (2 checks OK, 1 FAIL)

En t=1.0: flanco ascendente de clk, a=FALSE → y_latch captura FALSE. En t=2.0: a cambia a TRUE pero clk permanece TRUE (no hay flanco). La latch NO actualiza: y_latch=FALSE en t=2.5. Si y_latch fuera level-triggered, cambiaria cuando a=TRUE. cuenta_flancos=1 (solo un flanco ascendente total).
