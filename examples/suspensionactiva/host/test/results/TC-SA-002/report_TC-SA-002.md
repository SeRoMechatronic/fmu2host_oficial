# TC-SA-002 — Velocidad baja sin bache — modo_confort activo

## Descripcion del test

perfil=0, velocidad=0.2: modo_confort=true (0.2 < 0.3 y sin bache).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.0`  
`velocidad_vehiculo=0.2`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fuerza_actuador`@t=0.0: esperado 0.0±1e-06, obtenido -0 |
| ✅ | `bache_detectado`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `modo_confort`@t=0.0: esperado 1±0, obtenido 1 |
| ✅ | `actuador_saturado`@t=0.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.2 | 0 | 0 | 1 | 0 |
| 0.01 | 0 | 0.2 | 0 | 0 | 1 | 0 |
| 0.02 | 0 | 0.2 | 0 | 0 | 1 | 0 |
| 0.06 | 0 | 0.2 | 0 | 0 | 1 | 0 |
| 0.1 | 0 | 0.2 | 0 | 0 | 1 | 0 |
| 0.1 | 0 | 0.2 | 0 | 0 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `velocidad_vehiculo` | 0.2 | 0.2 | 0.2 | 0 | 0.2 | 0.2 | constante |
| `actuador_saturado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fuerza_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `perfil_bache`=0, `velocidad_vehiculo`=0.2, `actuador_saturado`=0, `bache_detectado`=0, `modo_confort`=1, `fuerza_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `perfil_bache`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `actuador_saturado`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con velocidad=0.2 < 0.3 (umbral de confort) y sin bache detectado: modo_confort=TRUE. La condicion es 'velocidad < 0.3 AND NOT bache'. fuerza_actuador=0 (estados en cero). Verifica la activacion de modo confort en ciudad (velocidad reducida, sin perturbaciones).
