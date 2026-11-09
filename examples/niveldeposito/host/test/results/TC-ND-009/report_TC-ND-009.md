# TC-ND-009 — Deposito lleno — bomba apagada

## Descripcion del test

nivel converge a 1.0 (cruzando 0.80 desde 0.5): alarma_maximo=true, bomba=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=1.0`  
`valvula_manual=0`

## Simulacion: ME-RK4

- Pasos simulados: 41  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarma_maximo` final: esperado 1±0, obtenido 1 |
| ✅ | `bomba` final: esperado 0.0±0.05, obtenido 0 |
| ✅ | `bomba_activa` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 0 | 0 | 1 | 0.5 |
| 0.5 | 0 | 1 | 0 | 0 | 1 | 0.2788 |
| 1 | 0 | 1 | 0 | 0 | 1 | 0.1065 |
| 10 | 0 | 1 | 1 | 0 | 0 | 0 |
| 19.5 | 0 | 1 | 1 | 0 | 0 | 0 |
| 20 | 0 | 1 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `alarma_maximo` | 0 | 1 | 0.9024 | 0.3004 | 0 | 1 | creciente |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 0 | 1 | 0.07317 | 0.2637 | 1 | 0 | decreciente |
| `bomba` | 0 | 0.5 | 0.02159 | 0.08944 | 0.5 | 0 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `alarma_maximo`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `bomba_activa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `bomba`: valor final = 0 (arranca en 0.5, delta = 0.5).
**Variables algebraicas constantes:** `valvula_manual`=0, `sensor_nivel`=1, `alarma_minimo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `sensor_nivel`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Deposito completamente lleno: nivel=1.0 (muy por encima de 0.80). La alarma maxima se activa y la bomba se apaga completamente. bomba_activa=false porque bomba=0.0<=0.05. Escenario de desbordamiento potencial que requiere abrir la valvula manual para drenar.
