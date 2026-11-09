# TC-BL-001 — Tabla de verdad AND/OR/XOR — caso a=F b=F

## Descripcion del test

a=FALSE, b=FALSE: y_and=FALSE, y_or=FALSE, y_xor=FALSE.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`a=0`  
`b=0`  
`clk=0`  
`umbral=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_and` final: esperado 0±0, obtenido 0 |
| ✅ | `y_or` final: esperado 0±0, obtenido 0 |
| ✅ | `y_xor` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | umbral | a | b | clk | cuenta_flancos | above_threshold | y_and | y_latch |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `umbral` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `a` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `b` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `clk` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta_flancos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `above_threshold` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_and` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_latch` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_or` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_xor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `umbral`=0, `a`=0, `b`=0, `clk`=0, `cuenta_flancos`=0, `above_threshold`=0, `y_and`=0, `y_latch`=0, `y_or`=0, `y_xor`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `umbral`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `a`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `b`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Fila (F,F) de la tabla de verdad. Todos los outputs combinacionales son FALSE: AND(F,F)=F, OR(F,F)=F, XOR(F,F)=F. Si alguno devuelve TRUE con ambas entradas a FALSE, hay un error en la generacion de la expresion logica combinacional. clk=FALSE evita disparos de flanco.
