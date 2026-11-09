# TC-FABS-005 — Vehiculo detenido — guarda de division por cero en lambda

## Descripcion del test

velocidad_rueda=0: v_filtrada → 0 → guarda activa, lambda=0, abs=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.0`  
`presion_pedal=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 51  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `abs_activo` == 0 siempre: OK |
| ✅ | `rueda_bloqueada` == 0 siempre: OK |
| ✅ | `presion_modulada` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0 | 1 | 0 | 0.1175 |
| 0.02 | 1 | 0 | 0 | 1 | 0 | 0.2212 |
| 0.25 | 1 | 0 | 0 | 1 | 0 | 0.9561 |
| 0.49 | 1 | 0 | 0 | 1 | 0 | 0.9978 |
| 0.5 | 1 | 0 | 0 | 1 | 0 | 0.9981 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `velocidad_rueda` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `abs_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `frenado_normal` | 0 | 1 | 0.9804 | 0.14 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `presion_modulada` | 0 | 0.9981 | 0.8334 | 0.2492 | 0 | 0.9981 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `presion_modulada`: valor final = 0.9981 (arranca en 0, delta = 0.9981).
**Variables algebraicas constantes:** `presion_pedal`=1, `velocidad_rueda`=0, `abs_activo`=0, `rueda_bloqueada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `presion_pedal`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `velocidad_rueda`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `abs_activo`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `frenado_normal`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `presion_modulada`: tasa de cambio maxima = 11.75 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con velocidad=0, v_filtrada → 0 (rapidamente, tau=0.05s). La guarda activa: if v_filtrada > 0.01 then lambda = ... else lambda = 0. Esto previene division por cero: 1/(v_filtrada*20). abs_activo=FALSE (lambda=0 < 0.15) en todo momento. Si aparece NaN en presion_modulada, la guarda no fue generada.
