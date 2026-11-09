# TC-ND-010 — Transitorio del filtro — sensor baja de 0.5 a 0.2 en t=2 s

## Descripcion del test

Despues de un escalon del sensor, el nivel filtrado responde con tau=2 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 6.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.5`  
`valvula_manual=0`  
`sensor_nivel`: t=0: 0.5, t=2.0: 0.2

## Simulacion: ME-RK4

- Pasos simulados: 602  |  Tiempo total: 6 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bomba`@t=4.0: esperado 0.8±0.15, obtenido 0.879272 |
| ✅ | `bomba`@t=2.0: esperado 0.5±0.05, obtenido 0.5 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.01 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.02 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 3.01 | 0 | 0.2 | 0 | 0 | 1 | 0.7379 |
| 6 | 0 | 0.2 | 0 | 0 | 1 | 1 |
| 6 | 0 | 0.2 | 0 | 0 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 0.2 | 0.5 | 0.2997 | 0.1414 | 0.5 | 0.2 | decreciente |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `bomba` | 0.5 | 1 | 0.7269 | 0.199 | 0.5 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `sensor_nivel`: valor final = 0.2 (arranca en 0.5, delta = 0.3).
**Variables algebraicas constantes:** `valvula_manual`=0, `alarma_maximo`=0, `alarma_minimo`=0, `bomba_activa`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `sensor_nivel`: tasa de cambio maxima = 30 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Antes del escalon (t=2 s): nivel_filtrado≈0.5, bomba≈0.5. Despues del escalon, el sensor baja a 0.2 pero el filtro (tau=2 s) responde gradualmente: a t=4 s (1 tau despues del escalon), nivel_filtrado ≈ 0.5+(0.2-0.5)*(1-e^-1)≈0.31. bomba aumenta. Verifica la dinamica del filtro del sensor de nivel.
