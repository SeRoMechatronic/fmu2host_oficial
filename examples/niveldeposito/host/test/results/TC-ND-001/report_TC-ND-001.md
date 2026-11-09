# TC-ND-001 — Estado estacionario en setpoint — valvula cerrada

## Descripcion del test

nivel_filtrado=0.5 en setpoint: bomba=0.5, sin alarmas.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.5`  
`valvula_manual=0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bomba` final: esperado 0.5±0.02, obtenido 0.5 |
| ✅ | `alarma_minimo` final: esperado 0±0, obtenido 0 |
| ✅ | `alarma_maximo` final: esperado 0±0, obtenido 0 |
| ✅ | `bomba_activa` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.1 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.2 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.4 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |
| 0.5 | 0 | 0.5 | 0 | 0 | 1 | 0.5 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `bomba` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `valvula_manual`=0, `sensor_nivel`=0.5, `alarma_maximo`=0, `alarma_minimo`=0, `bomba_activa`=1, `bomba`=0.5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con nivel en el setpoint (0.5=50%), el error es cero y la bomba opera al 50% de su capacidad (bomba=0.5). Ninguna alarma activa. bomba_activa=true porque 0.5>0.05. Este es el punto de operacion nominal del controlador proporcional del deposito.
