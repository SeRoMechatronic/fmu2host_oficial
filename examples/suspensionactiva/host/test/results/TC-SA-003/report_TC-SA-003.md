# TC-SA-003 — Bache pequeno — por debajo del umbral de deteccion

## Descripcion del test

perfil=0.25 en estado estacionario: posicion_filtrada→0.25, bache=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.25`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bache_detectado` final: esperado 0±0, obtenido 0 |
| ✅ | `fuerza_actuador` final: esperado -0.75±0.01, obtenido -0.750874 |
| ✅ | `actuador_saturado` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.25 | 0.5 | 0 | 0 | 1 | 0 |
| 0.01 | 0.25 | 0.5 | 0 | 0 | 0 | -0.2523 |
| 0.02 | 0.25 | 0.5 | 0 | 0 | 0 | -0.4634 |
| 0.5 | 0.25 | 0.5 | 0 | 0 | 0 | -0.8123 |
| 0.99 | 0.25 | 0.5 | 0 | 0 | 0 | -0.751 |
| 1 | 0.25 | 0.5 | 0 | 0 | 0 | -0.7509 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0.25 | 0.25 | 0.25 | 0 | 0.25 | 0.25 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 1 | 0.2376 | 0.4278 | 0 | 0 | decreciente |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 0 | 1 | 0.009901 | 0.0995 | 1 | 0 | estable |
| `fuerza_actuador` | -1 | 0 | -0.8318 | 0.1509 | 0 | -0.7509 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = -0.7509 (arranca en 0, delta = 0.7509).
**Variables algebraicas constantes:** `perfil_bache`=0.25, `velocidad_vehiculo`=0.5, `bache_detectado`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `modo_confort`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con perfil=0.25 constante, tras convergencia (5*tau=0.5s): posicion_filtrada→0.25, velocidad_filtrada→0. fuerza_raw=-(3*0.25+0.8*0)=-0.75 (dentro de limites). bache_detectado=FALSE (0.25 < 0.30 — por debajo del umbral). actuador_saturado=FALSE (|fuerza_raw|=0.75 < 1.0).
