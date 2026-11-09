# TC-BL-002 — XOR: a=TRUE b=TRUE → y_xor=FALSE

## Descripcion del test

Cuando a==b, XOR debe ser FALSE. Caso a=T, b=T.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=1`  
`b=1`  
`clk=0`  
`umbral=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_and` final: esperado 1±0, obtenido 1 |
| ✅ | `y_or` final: esperado 1±0, obtenido 1 |
| ✅ | `y_xor` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 |
| 0.1 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 |
| 0 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 |
| 0.1 | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `clk` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `umbral`=0, `a`=1, `b`=1, `clk`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=1, `y_latch`=0, `y_or`=1, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `a`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Fila (T,T) de la tabla de verdad. AND(T,T)=T, OR(T,T)=T, pero XOR(T,T)=FALSE (igual a distinto: no lo son). Un error comun de codegen es generar OR en lugar de XOR, lo que daria TRUE aqui. Este test es el discriminador directo de la implementacion XOR.
