# TC-ND-003 — Nivel por debajo del umbral minimo — alarma activa

## Descripcion del test

nivel_filtrado converge a 0.199 (cruzando 0.20 desde 0.5): alarma_minimo=true, bomba=1.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.199`  
`valvula_manual=0`

## Simulacion: ME-RK4

- Pasos simulados: 41  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarma_minimo` final: esperado 1±0, obtenido 1 |
| ✅ | `bomba` final: esperado 1.0±0.05, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.199 | 0 | 0 | 1 | 0.5 |
| 0.5 | 0 | 0.199 | 0 | 0 | 1 | 0.6332 |
| 1 | 0 | 0.199 | 0 | 0 | 1 | 0.7369 |
| 10 | 0 | 0.199 | 0 | 0 | 1 | 1 |
| 19.5 | 0 | 0.199 | 0 | 1 | 1 | 1 |
| 20 | 0 | 0.199 | 0 | 1 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 0.199 | 0.199 | 0.199 | 0 | 0.199 | 0.199 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 1 | 0.439 | 0.5024 | 0 | 1 | creciente |
| `bomba_activa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `bomba` | 0.5 | 1 | 0.9625 | 0.106 | 0.5 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `alarma_minimo`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `bomba`: valor final = 1 (arranca en 0.5, delta = 0.5).
**Variables algebraicas constantes:** `valvula_manual`=0, `sensor_nivel`=0.199, `alarma_maximo`=0, `bomba_activa`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `bomba_activa`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con nivel=0.199 (justo debajo del umbral 0.20), la alarma minima se activa. La bomba trabaja al maximo para recuperar el nivel. Este test verifica el comportamiento del sistema ante un nivel de liquido peligrosamente bajo.
