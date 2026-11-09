# TC-SA-001 — Sin bache — todas las salidas en cero al inicio

## Descripcion del test

perfil=0, velocidad=0.5: fuerza=0, bache=false, saturado=false, confort=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.0`  
`velocidad_vehiculo=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fuerza_actuador`@t=0.0: esperado 0.0±1e-06, obtenido -0 |
| ✅ | `bache_detectado`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `actuador_saturado`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `modo_confort`@t=0.01: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.5 | 0 | 0 | 1 | 0 |
| 0.01 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.02 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.06 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0.5 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `velocidad_vehiculo` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `actuador_saturado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 0 | 1 | 0.08333 | 0.2887 | 1 | 0 | decreciente |
| `fuerza_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `modo_confort`: valor final = 0 (arranca en 1, delta = 1).
**Variables algebraicas constantes:** `perfil_bache`=0, `velocidad_vehiculo`=0.5, `actuador_saturado`=0, `bache_detectado`=0, `fuerza_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `perfil_bache`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `actuador_saturado`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `modo_confort`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Estados iniciales: posicion_filtrada=0, velocidad_filtrada=0. Con perfil=0 y velocidad=0.5 en t=0: fuerza_raw=-(3*0+0.8*0)=0, fuerza_actuador=0. bache_detectado=FALSE (|0| < 0.30). modo_confort=FALSE (velocidad=0.5 >= 0.3). Se verifica en t=0.01 porque en t=0 la hysteresis inicializa con velocidad=0 (< 0.3) antes de aplicar el input, produciendo un transitorio de 1 paso. Linea base de carretera plana.
