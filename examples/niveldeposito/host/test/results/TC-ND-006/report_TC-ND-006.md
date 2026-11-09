# TC-ND-006 — Valvula manual abierta — compensacion feedforward

## Descripcion del test

Con valvula=true en setpoint: feedforward reduce la bomba.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.5`  
`valvula_manual=1`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bomba` final: esperado 0.0±0.05, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.5 | 0 | 0 | 0 | 0 |
| 0.1 | 1 | 0.5 | 0 | 0 | 0 | 0 |
| 0.2 | 1 | 0.5 | 0 | 0 | 0 | 0 |
| 0.4 | 1 | 0.5 | 0 | 0 | 0 | 0 |
| 0.5 | 1 | 0.5 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `sensor_nivel` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `valvula_manual`=1, `sensor_nivel`=0.5, `alarma_maximo`=0, `alarma_minimo`=0, `bomba_activa`=0, `bomba`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Al abrir la valvula manual, se activa el termino feedforward Q_salida/Q_bomba_max=0.3/0.5=0.6. En el setpoint: bomba=0.5+0-0.6=-0.1 → clamped a 0.0. El feedforward compensa el caudal de salida, pero en este caso domina y apaga la bomba. Verifica que fmi2SetBoolean afecta la logica de control.
