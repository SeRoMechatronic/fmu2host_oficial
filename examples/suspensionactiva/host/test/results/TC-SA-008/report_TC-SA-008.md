# TC-SA-008 — Transitorio del filtro — bache_detectado activa a t≈0.1 s

## Descripcion del test

Escalon de perfil=0.5 en t=0: bache_detectado eventually=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.5`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bache_detectado`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `bache_detectado` == 1 eventualmente: OK |
| ✅ | `fuerza_actuador` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.5 | 0 | 0 | 1 | 0 |
| 0.005 | 0.5 | 0.5 | 0 | 0 | 0 | -0.2634 |
| 0.01 | 0.5 | 0.5 | 0 | 0 | 0 | -0.5047 |
| 0.25 | 0.5 | 0.5 | 1 | 1 | 0 | -1 |
| 0.495 | 0.5 | 0.5 | 1 | 1 | 0 | -1 |
| 0.5 | 0.5 | 0.5 | 1 | 1 | 0 | -1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 1 | 0.9406 | 0.2376 | 0 | 1 | creciente |
| `bache_detectado` | 0 | 1 | 0.8119 | 0.3928 | 0 | 1 | creciente |
| `modo_confort` | 0 | 1 | 0.009901 | 0.0995 | 1 | 0 | estable |
| `fuerza_actuador` | -1 | 0 | -0.9745 | 0.1343 | 0 | -1 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `bache_detectado`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = -1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `perfil_bache`=0.5, `velocidad_vehiculo`=0.5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 200 unidades/s.
**Dinamica rapida** en `bache_detectado`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

En t=0: posicion_filtrada=0 (estado inicial). bache_detectado=FALSE. Con perfil=0.5 aplicado desde t=0, el filtro de primer orden con tau=0.1 s tiene respuesta: posicion(t)=0.5*(1-e^(-t/0.1)). En t=0.1: pos=0.5*(1-e^-1)≈0.316 > 0.30 → bache_detectado=TRUE. Verifica la dinamica de deteccion del primer orden.
