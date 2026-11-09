# TC-RB-003 — Tension alta — fallo sobretension prevalece sobre carga_completa

## Descripcion del test

tension=0.98 > V_max=0.95: fallo_sobretension=true, cargando=false. carga_completa no alcanza (V_carga_completa=0.98 > V_max=0.95 por diseno del modelo).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tension_bateria=0.98`  
`carga_conectada=1`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobretension` final: esperado 1±0, obtenido 1 |
| ✅ | `cargando` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.98 | 0 | 1 | 0 | 0 |
| 0.1 | 1 | 0.98 | 0 | 0 | 1 | 0 |
| 0.2 | 1 | 0.98 | 0 | 0 | 1 | 0 |
| 0.4 | 1 | 0.98 | 0 | 0 | 1 | 0 |
| 0.5 | 1 | 0.98 | 0 | 0 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `carga_conectada` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `tension_bateria` | 0.98 | 0.98 | 0.98 | 0 | 0.98 | 0.98 | constante |
| `carga_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cargando` | 0 | 1 | 0.1667 | 0.4082 | 1 | 0 | decreciente |
| `fallo_sobretension` | 0 | 1 | 0.8333 | 0.4082 | 0 | 1 | creciente |
| `corriente_carga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `carga_conectada`=1, `tension_bateria`=0.98, `carga_completa`=0, `corriente_carga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_conectada`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_completa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `corriente_carga`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El modelo tiene V_max=0.95 < V_carga_completa=0.98, por lo que cualquier tension >= V_carga_completa tambien supera V_max y activa fallo_sobretension. Con tension=0.98: la proteccion de sobretension se activa (0.98 > 0.95) y cargando=false. En este diseno, la 'bateria llena' siempre co-ocurre con el fallo de sobretension por los parametros del modelo.
