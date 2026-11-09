# TC-SA-007 — Bache negativo (socavon) — fuerza positiva, saturacion hacia arriba

## Descripcion del test

perfil=-0.40: posicion→-0.40, fuerza_raw=+1.2, fuerza_actuador=+1.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=-0.4`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fuerza_actuador` final: esperado 1.0±0.02, obtenido 1 |
| ✅ | `actuador_saturado` final: esperado 1±0, obtenido 1 |
| ✅ | `bache_detectado` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | -0.4 | 0.5 | 0 | 0 | 1 | 0 |
| 0.01 | -0.4 | 0.5 | 0 | 0 | 0 | 0.4037 |
| 0.02 | -0.4 | 0.5 | 0 | 0 | 0 | 0.7415 |
| 0.5 | -0.4 | 0.5 | 1 | 1 | 0 | 1 |
| 0.99 | -0.4 | 0.5 | 1 | 1 | 0 | 1 |
| 1 | -0.4 | 0.5 | 1 | 1 | 0 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | -0.4 | -0.4 | -0.4 | 0 | -0.4 | -0.4 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 1 | 0.9604 | 0.196 | 0 | 1 | creciente |
| `bache_detectado` | 0 | 1 | 0.8614 | 0.3473 | 0 | 1 | creciente |
| `modo_confort` | 0 | 1 | 0.009901 | 0.0995 | 1 | 0 | estable |
| `fuerza_actuador` | 0 | 1 | 0.9816 | 0.1178 | 0 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `bache_detectado`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `perfil_bache`=-0.4, `velocidad_vehiculo`=0.5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `bache_detectado`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Socavon (bache negativo): posicion_filtrada→-0.40. fuerza_raw=-(3*(-0.40))=+1.20 (fuerza hacia arriba). fuerza_actuador=clamp(+1.20,-1,1)=+1.0. actuador_saturado=TRUE. bache_detectado=TRUE (|-0.40|=0.40 > 0.30). Verifica que el actuador puede ejercer fuerza positiva (levantamiento de suspension).
