# TC-FABS-004 — Bloqueo de rueda — rueda_bloqueada=true con desaceleracion extrema

## Descripcion del test

velocidad_rueda: 0.8→0.0 con pedal maximo. rueda_bloqueada eventually=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=1.0`  
`velocidad_rueda`: t=0: 0.8, t=0.05: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `rueda_bloqueada` == 1 eventualmente: OK |
| ✅ | `abs_activo` == 1 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.8 | 0 | 0 | 0 | 0 |
| 0.005 | 1 | 0.8 | 0 | 1 | 0 | 0.06059 |
| 0.01 | 1 | 0.8 | 0 | 1 | 0 | 0.1175 |
| 0.25 | 1 | 0 | 1 | 0 | 1 | 0.4786 |
| 0.495 | 1 | 0 | 0 | 1 | 0 | 0.9979 |
| 0.5 | 1 | 0 | 0 | 1 | 0 | 0.9981 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `velocidad_rueda` | 0 | 0.8 | 0.08713 | 0.2505 | 0.8 | 0 | decreciente |
| `abs_activo` | 0 | 1 | 0.3168 | 0.4676 | 0 | 0 | decreciente |
| `frenado_normal` | 0 | 1 | 0.6733 | 0.4714 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 1 | 0.2376 | 0.4278 | 0 | 0 | decreciente |
| `presion_modulada` | 0 | 0.9981 | 0.7252 | 0.3233 | 0 | 0.9981 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0 (arranca en 0.8, delta = 0.8).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `rueda_bloqueada`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `presion_modulada`: valor final = 0.9981 (arranca en 0, delta = 0.9981).
**Variables algebraicas constantes:** `presion_pedal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `presion_pedal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 160 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Desaceleracion extrema: velocidad cae en 0.05 s. El filtro produce dv_filtrada muy negativo. lambda = clamp(-dv_filt/(v_filt*20),0,1) puede alcanzar 1.0 (rueda totalmente bloqueada). rueda_bloqueada=TRUE (lambda > 0.90). Verifica que el buffer de 5 estados integra correctamente sin desbordamiento.
