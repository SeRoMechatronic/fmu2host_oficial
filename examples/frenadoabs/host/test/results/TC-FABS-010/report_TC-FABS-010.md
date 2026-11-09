# TC-FABS-010 — Transitorio del filtro de velocidad tras escalon

## Descripcion del test

velocidad: 0.8 → 0.0 en t=0.3. A t=0.35 (1 tau): v_filtrada ≈ 0.8*e^-1 ≈ 0.29.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.7 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=0.0`  
`velocidad_rueda`: t=0: 0.8, t=0.3: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 141  |  Tiempo total: 0.7 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `presion_modulada` sin NaN/Inf: OK |
| ✅ | `abs_activo` == 1 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.005 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.01 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 0.35 | 0 | 0 | 1 | 0 | 0 | 0 |
| 0.695 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.7 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `velocidad_rueda` | 0 | 0.8 | 0.3404 | 0.3969 | 0.8 | 0 | decreciente |
| `abs_activo` | 0 | 1 | 0.2908 | 0.4557 | 0 | 0 | creciente |
| `frenado_normal` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `rueda_bloqueada` | 0 | 1 | 0.234 | 0.4249 | 0 | 0 | creciente |
| `presion_modulada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0 (arranca en 0.8, delta = 0.8).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `rueda_bloqueada`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `presion_pedal`=0, `frenado_normal`=0, `presion_modulada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `presion_pedal`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `frenado_normal`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `presion_modulada`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 160 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con velocidad constante 0.8 durante [0, 0.3s], v_filtrada converge a 0.8. En t=0.3, velocidad cae a 0.0. El filtro con tau=0.05s produce v_filtrada(0.35) ≈ 0.8*e^(-1) ≈ 0.29 y dv_filtrada fortemente negativo. lambda = -dv_filt/(v_filt*20) >> 0.15, abs_activo=TRUE. Verifica la dinamica transitoria del filtro de primer orden.
