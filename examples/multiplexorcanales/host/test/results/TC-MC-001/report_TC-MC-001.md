# TC-MC-001 — Seleccion canal 0

## Descripcion del test

canal_seleccion=0 debe enrutar canal_0 a la salida.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`canal_seleccion=0`  
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
| ✅ | `salida` final: esperado 0.25±1e-09, obtenido 0.25 |
| ✅ | `canal_activo` final: esperado 0±0, obtenido 0 |
| ✅ | `canal_valido` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.25 | 0.5 | 0 | 0.75 | 1 | 0 | 1 | 0.25 |
| 0.1 | 0.25 | 0.5 | 0 | 0.75 | 1 | 0 | 1 | 0.25 |
| 0.2 | 0.25 | 0.5 | 0 | 0.75 | 1 | 0 | 1 | 0.25 |
| 0.1 | 0.25 | 0.5 | 0 | 0.75 | 1 | 0 | 1 | 0.25 |
| 0.2 | 0.25 | 0.5 | 0 | 0.75 | 1 | 0 | 1 | 0.25 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `canal_0` | 0.25 | 0.25 | 0.25 | 0 | 0.25 | 0.25 | constante |
| `canal_1` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `canal_seleccion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_2` | 0.75 | 0.75 | 0.75 | 0 | 0.75 | 0.75 | constante |
| `canal_3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `canal_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_valido` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida` | 0.25 | 0.25 | 0.25 | 0 | 0.25 | 0.25 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `canal_0`=0.25, `canal_1`=0.5, `canal_seleccion`=0, `canal_2`=0.75, `canal_3`=1, `canal_activo`=0, `canal_valido`=1, `salida`=0.25 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `canal_seleccion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_3`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `canal_activo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con selector=0, la salida debe reflejar exactamente canal_0=0.25. canal_activo confirma que el canal 0 esta enrutado. La seleccion es instantanea (modelo algebraico) sin retardo alguno.
