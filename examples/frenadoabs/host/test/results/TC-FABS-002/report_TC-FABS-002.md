# TC-FABS-002 — Frenado suave — ABS no activado, frenado_normal=true

## Descripcion del test

velocidad=0.6, pedal=0.3 en estado estacionario: frenado_normal=true, abs=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.6`  
`presion_pedal=0.3`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `abs_activo` final: esperado 0±0, obtenido 0 |
| ✅ | `rueda_bloqueada` final: esperado 0±0, obtenido 0 |
| ✅ | `frenado_normal` final: esperado 1±0, obtenido 1 |
| ✅ | `presion_modulada` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.3 | 0.6 | 0 | 0 | 0 | 0 |
| 0.01 | 0.3 | 0.6 | 0 | 1 | 0 | 0.03525 |
| 0.02 | 0.3 | 0.6 | 0 | 1 | 0 | 0.06636 |
| 0.5 | 0.3 | 0.6 | 0 | 1 | 0 | 0.2994 |
| 0.99 | 0.3 | 0.6 | 0 | 1 | 0 | 0.3 |
| 1 | 0.3 | 0.6 | 0 | 1 | 0 | 0.3 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `velocidad_rueda` | 0.6 | 0.6 | 0.6 | 0 | 0.6 | 0.6 | constante |
| `abs_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `frenado_normal` | 0 | 1 | 0.9901 | 0.0995 | 0 | 1 | estable |
| `rueda_bloqueada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `presion_modulada` | 0 | 0.3 | 0.2747 | 0.05851 | 0 | 0.3 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `presion_modulada`: valor final = 0.3 (arranca en 0, delta = 0.3).
**Variables algebraicas constantes:** `presion_pedal`=0.3, `velocidad_rueda`=0.6, `abs_activo`=0, `rueda_bloqueada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `abs_activo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `rueda_bloqueada`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `frenado_normal`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con velocidad constante y pedal=0.3, en estado estacionario: dv_filtrada→0, lambda→0. abs_activo=FALSE (lambda=0 < 0.15). frenado_normal=TRUE (lambda<=0.15 AND pedal=0.3 > 0.05). presion_modulada=p_filtrada (sin modulacion ABS). Verifica el modo de frenado normal sin intervencion del ABS.
