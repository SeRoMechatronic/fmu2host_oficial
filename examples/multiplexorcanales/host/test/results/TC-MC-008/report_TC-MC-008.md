# TC-MC-008 — Canal 3 a escala completa

## Descripcion del test

canal_seleccion=3 con canal_3=1.0. Verifica valor maximo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`canal_seleccion=3`  
`canal_3=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `canal_activo` final: esperado 3±0, obtenido 3 |
| ✅ | `canal_valido` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3 | 0 | 1 | 3 | 1 | 1 |
| 0.1 | 0 | 0 | 3 | 0 | 1 | 3 | 1 | 1 |
| 0.2 | 0 | 0 | 3 | 0 | 1 | 3 | 1 | 1 |
| 0.1 | 0 | 0 | 3 | 0 | 1 | 3 | 1 | 1 |
| 0.2 | 0 | 0 | 3 | 0 | 1 | 3 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `canal_0` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_seleccion` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `canal_2` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `canal_activo` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `canal_valido` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `canal_0`=0, `canal_1`=0, `canal_seleccion`=3, `canal_2`=0, `canal_3`=1, `canal_activo`=3, `canal_valido`=1, `salida`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `canal_0`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_1`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_2`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El valor maximo de escala (1.0) en canal_3 se transmite sin modificacion a la salida. Confirma que no hay saturacion o recorte involuntario en el camino de datos del multiplexor.
