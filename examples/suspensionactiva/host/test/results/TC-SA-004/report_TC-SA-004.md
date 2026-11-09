# TC-SA-004 — Bache exactamente en el umbral — bache_detectado=false (operador estricto)

## Descripcion del test

posicion_filtrada→0.30 exacto: bache=false (>: 0.30 NO > 0.30).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.3`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bache_detectado` final: esperado 0±0, obtenido 0 |
| ✅ | `fuerza_actuador` final: esperado -0.9±0.02, obtenido -0.901049 |
| ✅ | `actuador_saturado` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.3 | 0.5 | 0 | 0 | 1 | 0 |
| 0.01 | 0.3 | 0.5 | 0 | 0 | 0 | -0.3028 |
| 0.02 | 0.3 | 0.5 | 0 | 0 | 0 | -0.5561 |
| 0.5 | 0.3 | 0.5 | 0 | 0 | 0 | -0.9748 |
| 0.99 | 0.3 | 0.5 | 0 | 0 | 0 | -0.9011 |
| 1 | 0.3 | 0.5 | 0 | 0 | 0 | -0.901 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 1 | 0.4158 | 0.4953 | 0 | 0 | decreciente |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 0 | 1 | 0.009901 | 0.0995 | 1 | 0 | estable |
| `fuerza_actuador` | -1 | 0 | -0.9343 | 0.1291 | 0 | -0.901 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = -0.901 (arranca en 0, delta = 0.901).
**Variables algebraicas constantes:** `perfil_bache`=0.3, `velocidad_vehiculo`=0.5, `bache_detectado`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `modo_confort`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con perfil=0.30, tras convergencia posicion_filtrada→0.30. bache_detectado = |posicion_filtrada| > 0.30 (estricto). 0.30 NO es mayor que 0.30 → bache=FALSE. fuerza_actuador=-(3*0.30)=-0.90 (sin saturar). Verifica la frontera critica del detector de bache.
