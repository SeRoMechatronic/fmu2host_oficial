# TC-SA-010 — Interaccion P y D — fuerza con ambos terminos activos

## Descripcion del test

Tras convergencia completa: verificar fuerza_actuador estable y sin NaN.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.2`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fuerza_actuador` final: esperado -0.6±0.05, obtenido -0.6 |
| ✅ | `actuador_saturado` final: esperado 0±0, obtenido 0 |
| ✅ | `fuerza_actuador` sin NaN/Inf: OK |
| ✅ | `fuerza_actuador` en [-1, 1]: OK |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.2 | 0.5 | 0 | 0 | 1 | 0 |
| 0.01 | 0.2 | 0.5 | 0 | 0 | 0 | -0.2019 |
| 0.02 | 0.2 | 0.5 | 0 | 0 | 0 | -0.3708 |
| 1 | 0.2 | 0.5 | 0 | 0 | 0 | -0.6007 |
| 1.99 | 0.2 | 0.5 | 0 | 0 | 0 | -0.6 |
| 2 | 0.2 | 0.5 | 0 | 0 | 0 | -0.6 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0.2 | 0.2 | 0.2 | 0 | 0.2 | 0.2 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 1 | 0.01493 | 0.1216 | 0 | 0 | estable |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 0 | 1 | 0.004975 | 0.07053 | 1 | 0 | estable |
| `fuerza_actuador` | -1 | 0 | -0.6481 | 0.1251 | 0 | -0.6 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = -0.6 (arranca en 0, delta = 0.6).
**Variables algebraicas constantes:** `perfil_bache`=0.2, `velocidad_vehiculo`=0.5, `bache_detectado`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `modo_confort`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con perfil=0.20 constante, tras convergencia completa (t=2s >> 5*tau): posicion_filtrada→0.20, velocidad_filtrada→0. fuerza_raw=-(3*0.20+0.8*0)=-0.60. fuerza_actuador=-0.60 (sin saturar). Verifica que en estado estacionario ambos estados del filtro convergen y que fuerza_actuador es estable y acotada en [-1.0, 1.0].
