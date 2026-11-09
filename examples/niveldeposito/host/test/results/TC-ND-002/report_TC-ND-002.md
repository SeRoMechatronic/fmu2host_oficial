# TC-ND-002 — Nivel exactamente en umbral minimo — sin alarma

## Descripcion del test

nivel_filtrado converge a 0.20: alarma_minimo=false (limite exclusivo).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.2`  
`valvula_manual=0`

## Simulacion: ME-RK4

- Pasos simulados: 41  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarma_minimo` final: esperado 0±0, obtenido 0 |
| ✅ | `bomba` final: esperado 1.0±0.05, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.2 | 0 | 0 | 1 | 0.5 |
| 0.5 | 0 | 0.2 | 0 | 0 | 1 | 0.6327 |
| 1 | 0 | 0.2 | 0 | 0 | 1 | 0.7361 |
| 10 | 0 | 0.2 | 0 | 0 | 1 | 1 |
| 19.5 | 0 | 0.2 | 0 | 0 | 1 | 1 |
| 20 | 0 | 0.2 | 0 | 0 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 0.2 | 0.2 | 0.2 | 0 | 0.2 | 0.2 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `bomba` | 0.5 | 1 | 0.9623 | 0.1062 | 0.5 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `bomba`: valor final = 1 (arranca en 0.5, delta = 0.5).
**Variables algebraicas constantes:** `valvula_manual`=0, `sensor_nivel`=0.2, `alarma_maximo`=0, `alarma_minimo`=0, `bomba_activa`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El umbral minimo usa operador estricto <. Con nivel=0.20 exacto, la condicion 0.20 < 0.20 es falsa: no hay alarma. La bomba opera al maximo (error=0.3, bomba=0.5+2*0.3=1.1 → clamped a 1.0). Boundary condition critica para el sistema de alarmas.
