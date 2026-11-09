# TC-SA-005 — Bache justo sobre el umbral — bache_detectado=true

## Descripcion del test

posicion_filtrada→0.31: bache=true, modo_confort bloqueado.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.31`  
`velocidad_vehiculo=0.2`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bache_detectado` final: esperado 1±0, obtenido 1 |
| ✅ | `modo_confort` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.31 | 0.2 | 0 | 0 | 1 | 0 |
| 0.01 | 0.31 | 0.2 | 0 | 0 | 1 | -0.3129 |
| 0.02 | 0.31 | 0.2 | 0 | 0 | 1 | -0.5747 |
| 0.5 | 0.31 | 0.2 | 1 | 1 | 0 | -1 |
| 0.99 | 0.31 | 0.2 | 0 | 1 | 0 | -0.9312 |
| 1 | 0.31 | 0.2 | 0 | 1 | 0 | -0.9311 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0.31 | 0.31 | 0.31 | 0 | 0.31 | 0.31 | constante |
| `velocidad_vehiculo` | 0.2 | 0.2 | 0.2 | 0 | 0.2 | 0.2 | constante |
| `actuador_saturado` | 0 | 1 | 0.4653 | 0.5013 | 0 | 0 | decreciente |
| `bache_detectado` | 0 | 1 | 0.6535 | 0.4782 | 0 | 1 | creciente |
| `modo_confort` | 0 | 1 | 0.3465 | 0.4782 | 1 | 0 | decreciente |
| `fuerza_actuador` | -1 | 0 | -0.9509 | 0.1268 | 0 | -0.9311 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `actuador_saturado`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `bache_detectado`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `fuerza_actuador`: valor final = -0.9311 (arranca en 0, delta = 0.9311).
**Variables algebraicas constantes:** `perfil_bache`=0.31, `velocidad_vehiculo`=0.2 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `actuador_saturado`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `bache_detectado`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con perfil=0.31, posicion_filtrada→0.31 > 0.30 → bache_detectado=TRUE. Aunque velocidad=0.2 < 0.3, modo_confort=FALSE porque la condicion es 'velocidad < 0.3 AND NOT bache'. El bache suprime el modo confort. Verifica el operador AND y la interaccion entre las dos condiciones.
