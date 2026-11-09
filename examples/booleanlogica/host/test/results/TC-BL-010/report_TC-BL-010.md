# TC-BL-010 — Reset a cero — outputs combinacionales inmediatos, secuenciales retenidos

## Descripcion del test

Tras flancos previos: a=F, b=F, clk=F → combinacional=F, latch y contador retenidos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 4.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=1`  
`b=1`  
`clk=0`  
`umbral=1.0`  
`clk`: t=0: 0, t=1.0: 1, t=2.0: 0  
`a`: t=0: 1, t=3.0: 0  
`b`: t=0: 1, t=3.0: 0  
`umbral`: t=0: 1.0, t=3.0: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 5  |  Tiempo total: 4 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_and` final: esperado 0±0, obtenido 0 |
| ✅ | `y_or` final: esperado 0±0, obtenido 0 |
| ✅ | `y_xor` final: esperado 0±0, obtenido 0 |
| ✅ | `above_threshold` final: esperado 0±0, obtenido 0 |
| ❌ | `y_latch` final: esperado 1±0, obtenido 0 |
| ❌ | `cuenta_flancos` final: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |
| 2 | 1 | 1 | 1 | 0 | 0 | 1 | 1 | 0 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `a` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `b` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `clk` | 0 | 1 | 0.2 | 0.4472 | 0 | 0 | decreciente |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `y_and` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 0 | 1 | 0.6 | 0.5477 | 1 | 0 | decreciente |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 6:**
  - `y_latch` final: esperado 1±0, obtenido 0
  - `cuenta_flancos` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `cuenta_flancos`=0, `y_latch`=0, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `cuenta_flancos`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y_latch`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y_xor`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (4 checks OK, 2 FAIL)

En t=3: a=F, b=F, clk=F, umbral=0. Los outputs combinacionales (y_and, y_or, y_xor, above_threshold) cambian a FALSE inmediatamente. Pero y_latch=TRUE (capturada en el flanco de t=1 con a=TRUE) y cuenta_flancos=1 se retienen sin nuevos flancos. Confirma que combinacional e secuencial se comportan de manera diferente.
