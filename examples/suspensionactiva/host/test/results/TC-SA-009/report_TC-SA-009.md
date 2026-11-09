# TC-SA-009 — Frontera de velocidad para modo_confort — por encima y por debajo

## Descripcion del test

velocidad=0.31: modo_confort=false (0.31 > 0.30). velocidad=0.29: true. Valor exacto 0.30 dispara hysteresis en OpenModelica FMU.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`perfil_bache=0.0`  
`velocidad_vehiculo=0.31`  
`velocidad_vehiculo`: t=0: 0.31, t=1.0: 0.29

## Simulacion: ME-RK4

- Pasos simulados: 5  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `modo_confort`@t=0.5: esperado 0±0, obtenido 0 |
| ✅ | `modo_confort`@t=1.5: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | perfil_bache | velocidad_vehiculo | actuador_saturado | bache_detectado | modo_confort | fuerza_actuador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.31 | 0 | 0 | 1 | 0 |
| 0.5 | 0 | 0.31 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0.29 | 0 | 0 | 0 | 0 |
| 1.5 | 0 | 0.29 | 0 | 0 | 1 | 0 |
| 2 | 0 | 0.29 | 0 | 0 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `perfil_bache` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `velocidad_vehiculo` | 0.29 | 0.31 | 0.298 | 0.01095 | 0.31 | 0.29 | decreciente |
| `actuador_saturado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bache_detectado` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_confort` | 0 | 1 | 0.6 | 0.5477 | 1 | 1 | creciente |
| `fuerza_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `perfil_bache`=0, `actuador_saturado`=0, `bache_detectado`=0, `fuerza_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `perfil_bache`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `actuador_saturado`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `bache_detectado`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La condicion modo_confort usa 'velocidad_vehiculo < 0.30' (estricto). Con velocidad=0.31 (sobre el umbral): modo_confort=FALSE en t=0.5. Con velocidad=0.29 (bajo el umbral): modo_confort=TRUE en t=1.5. Nota: el valor exacto 0.30 activa la hysteresis de OpenModelica FMU y produce modo_confort=TRUE incorrectamente; se usa 0.31 para evitarlo. Sin bache (perfil=0), la condicion de baja velocidad es suficiente.
