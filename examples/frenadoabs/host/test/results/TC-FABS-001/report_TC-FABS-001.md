# TC-FABS-001 — Sin frenado — estado estacionario, lambda=0, ABS inactivo

## Descripcion del test

velocidad=0.8 constante, pedal=0: lambda→0, abs_activo=false siempre.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `abs_activo` final: esperado 0±0, obtenido 0 |
| ✅ | `rueda_bloqueada` final: esperado 0±0, obtenido 0 |
| ✅ | `frenado_normal` final: esperado 0±0, obtenido 0 |
| ✅ | `presion_modulada` final: esperado 0.0±0.01, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.01 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.02 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.99 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0.8 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `velocidad_rueda` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `abs_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `frenado_normal` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `rueda_bloqueada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `presion_modulada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `presion_pedal`=0, `velocidad_rueda`=0.8, `abs_activo`=0, `frenado_normal`=0, `rueda_bloqueada`=0, `presion_modulada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `presion_pedal`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `abs_activo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `frenado_normal`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con velocidad constante y presion=0, tras convergencia de filtros (5*tau_v=0.25s, 5*tau_p=0.4s): v_filtrada→0.8, p_filtrada→0, dv_filtrada→0 (velocidad constante). lambda=clamp(0/(0.8*20),0,1)=0. abs_activo=FALSE (0 <= 0.15). frenado_normal=FALSE (pedal < 0.05). presion_modulada=0 (sin presion de pedal).
