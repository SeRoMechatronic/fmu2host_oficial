# TC-RB-002 — Cargador conectado — bateria baja, demanda inicial

## Descripcion del test

Con tension=0.30 y carga=true: cargando=true, corriente crece.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tension_bateria=0.3`  
`carga_conectada=1`

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `cargando` final: esperado 1±0, obtenido 1 |
| ✅ | `corriente_carga` > 0.1 eventualmente: OK |
| ✅ | `fallo_sobretension` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.3 | 0 | 1 | 0 | 0 |
| 0.01 | 1 | 0.3 | 0 | 1 | 0 | 0.04407 |
| 0.02 | 1 | 0.3 | 0 | 1 | 0 | 0.08617 |
| 1 | 1 | 0.3 | 0 | 1 | 0 | 0.4499 |
| 1.99 | 1 | 0.3 | 0 | 1 | 0 | 0.45 |
| 2 | 1 | 0.3 | 0 | 1 | 0 | 0.45 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `carga_conectada` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `tension_bateria` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `carga_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cargando` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_sobretension` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `corriente_carga` | 0 | 0.5006 | 0.4399 | 0.06794 | 0 | 0.45 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `corriente_carga`: valor final = 0.45 (arranca en 0, delta = 0.45).
**Variables algebraicas constantes:** `carga_conectada`=1, `tension_bateria`=0.3, `carga_completa`=0, `cargando`=1, `fallo_sobretension`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_conectada`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_completa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cargando`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con bateria al 30% (muy por debajo de V_nominal=0.75), el regulador activa la carga. La corriente crece desde 0 (estados iniciales nulos) segun la dinamica del controlador de segundo orden. cargando=true y no hay fallo de sobretension.
