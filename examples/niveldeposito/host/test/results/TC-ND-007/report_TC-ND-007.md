# TC-ND-007 — Nivel bajo con valvula abierta — demanda combinada

## Descripcion del test

nivel converge a 0.30, valvula=true: bomba=0.30 (P-control + feedforward) en estado estacionario.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.3`  
`valvula_manual=1`

## Simulacion: ME-RK4

- Pasos simulados: 41  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `bomba` final: esperado 0.3±0.05, obtenido 0.299982 |
| ✅ | `alarma_minimo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.3 | 0 | 0 | 0 | 0 |
| 0.5 | 1 | 0.3 | 0 | 0 | 0 | 0 |
| 1 | 1 | 0.3 | 0 | 0 | 1 | 0.05738 |
| 10 | 1 | 0.3 | 0 | 0 | 1 | 0.2973 |
| 19.5 | 1 | 0.3 | 0 | 0 | 1 | 0.3 |
| 20 | 1 | 0.3 | 0 | 0 | 1 | 0.3 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `sensor_nivel` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 0 | 1 | 0.9512 | 0.2181 | 0 | 1 | creciente |
| `bomba` | 0 | 0.3 | 0.2586 | 0.08053 | 0 | 0.3 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `bomba_activa`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `bomba`: valor final = 0.3 (arranca en 0, delta = 0.3).
**Variables algebraicas constantes:** `valvula_manual`=1, `sensor_nivel`=0.3, `alarma_maximo`=0, `alarma_minimo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con nivel=0.30 (por encima del umbral 0.20) y valvula abierta: error=0.5-0.3=0.2, bomba=0.5+2*0.2-0.6=0.3. La combinacion de control proporcional y compensacion feedforward da 0.30. Este caso ejercita ambos terminos de la ecuacion de control.
