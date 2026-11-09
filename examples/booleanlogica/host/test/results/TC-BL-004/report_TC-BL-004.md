# TC-BL-004 — above_threshold: umbral > 0.5 → TRUE, umbral <= 0.5 → FALSE

## Descripcion del test

Boundary condition: umbral=0.5001 → TRUE, umbral=0.5 → FALSE.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=1`  
`b=0`  
`clk=0`  
`umbral=0.5001`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_xor` final: esperado 1±0, obtenido 1 |
| ✅ | `above_threshold` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5001 | 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 0.1 | 0.5001 | 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 0 | 0.5001 | 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 0.1 | 0.5001 | 1 | 0 | 0 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0.5001 | 0.5001 | 0.5001 | 0 | 0.5001 | 0.5001 | constante |
| `a` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_xor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `umbral`=0.5001, `a`=1, `b`=0, `clk`=0, `cuenta_flancos`=0, `above_threshold`=1, `y_and`=0, `y_latch`=0, `y_or`=1, `y_xor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `a`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `clk`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con umbral=0.5001 > 0.5, above_threshold=TRUE. La diferencia con TC-BL-003 (umbral=0.5 → FALSE) confirma el operador estricto >. Tambien: a=T,b=F → XOR(T,F)=T. AND(T,F)=F, OR(T,F)=T. Verifica la conversion fmi2SetReal → Boolean en la misma iteracion.
