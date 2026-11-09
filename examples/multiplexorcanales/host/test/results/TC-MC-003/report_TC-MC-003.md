# TC-MC-003 — Seleccion canal 2

## Descripcion del test

canal_seleccion=2 debe enrutar canal_2 a la salida.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`canal_seleccion=2`  
`canal_0=0.25`  
`canal_1=0.5`  
`canal_2=0.75`  
`canal_3=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida` final: esperado 0.75±1e-09, obtenido 0.75 |
| ✅ | `canal_activo` final: esperado 2±0, obtenido 2 |

### Muestra de datos (inicio / mitad / final)

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.25 | 0.5 | 2 | 0.75 | 1 | 2 | 1 | 0.75 |
| 0.1 | 0.25 | 0.5 | 2 | 0.75 | 1 | 2 | 1 | 0.75 |
| 0.2 | 0.25 | 0.5 | 2 | 0.75 | 1 | 2 | 1 | 0.75 |
| 0.1 | 0.25 | 0.5 | 2 | 0.75 | 1 | 2 | 1 | 0.75 |
| 0.2 | 0.25 | 0.5 | 2 | 0.75 | 1 | 2 | 1 | 0.75 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `canal_0` | 0.25 | 0.25 | 0.25 | 0 | 0.25 | 0.25 | constante |
| `canal_1` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `canal_seleccion` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `canal_2` | 0.75 | 0.75 | 0.75 | 0 | 0.75 | 0.75 | constante |
| `canal_3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `canal_activo` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `canal_valido` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida` | 0.75 | 0.75 | 0.75 | 0 | 0.75 | 0.75 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `canal_0`=0.25, `canal_1`=0.5, `canal_seleccion`=2, `canal_2`=0.75, `canal_3`=1, `canal_activo`=2, `canal_valido`=1, `salida`=0.75 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `canal_3`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `canal_valido`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Canal 2 enrutado correctamente. El valor 0.75 es univoco para canal_2 en este conjunto de entradas, por lo que cualquier error de indice en el multiplexor seria detectable inmediatamente.
