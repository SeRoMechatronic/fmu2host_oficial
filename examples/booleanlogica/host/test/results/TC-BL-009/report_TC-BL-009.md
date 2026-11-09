# TC-BL-009 — Todos los inputs activos simultaneamente — salidas combinadas

## Descripcion del test

a=T, b=T, clk: 0→1 (flanco), umbral=1.0: todos outputs activos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=1`  
`b=1`  
`clk=0`  
`umbral=1.0`  
`clk`: t=0: 0, t=1.0: 1

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_and`@t=1.5: esperado 1±0, obtenido 1 |
| ✅ | `y_or`@t=1.5: esperado 1±0, obtenido 1 |
| ✅ | `y_xor`@t=1.5: esperado 0±0, obtenido 0 |
| ❌ | `y_latch`@t=1.5: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0 |
| ✅ | `above_threshold`@t=1.5: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |
| 2 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |
| 2 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `a` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `clk` | 0 | 1 | 0.6667 | 0.5774 | 0 | 1 | variable |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_and` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 6:**
  - `y_latch`@t=1.5: esperado 1±0, obtenido 0
  - `cuenta_flancos`@t=1.5: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `umbral`=1, `a`=1, `b`=1, `cuenta_flancos`=0, `above_threshold`=1, `y_and`=1, `y_latch`=0, `y_or`=1, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `a`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (4 checks OK, 2 FAIL)

Con a=T, b=T, clk: 0→1 y umbral=1.0, todos los outputs deben activarse (excepto y_xor=FALSE porque a==b). Verifica el orden de lectura de todos los tipos: fmi2SetBoolean(a,b,clk), fmi2SetReal(umbral) antes del paso; luego fmi2GetBoolean(y_and,...), fmi2GetInteger(cuenta_flancos). Si algun get se ejecuta fuera de orden, los outputs seran inconsistentes.
