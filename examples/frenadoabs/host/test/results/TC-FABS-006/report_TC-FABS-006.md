# TC-FABS-006 — presion_modulada acotada en [0,1] siempre

## Descripcion del test

Con pedal=1.0 y ABS activo: presion_modulada en [0,1] sin excederse.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=1.0`  
`velocidad_rueda`: t=0: 0.8, t=0.1: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `presion_modulada` en [0, 1]: OK |
| ✅ | `presion_modulada` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.8 | 0 | 0 | 0 | 0 |
| 0.005 | 1 | 0.8 | 0 | 1 | 0 | 0.06059 |
| 0.01 | 1 | 0.8 | 0 | 1 | 0 | 0.1175 |
| 0.5 | 1 | 0 | 0 | 1 | 0 | 0.9981 |
| 0.995 | 1 | 0 | 0 | 1 | 0 | 1 |
| 1 | 1 | 0 | 0 | 1 | 0 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `velocidad_rueda` | 0 | 0.8 | 0.0796 | 0.2401 | 0.8 | 0 | decreciente |
| `abs_activo` | 0 | 1 | 0.1841 | 0.3885 | 0 | 0 | decreciente |
| `frenado_normal` | 0 | 1 | 0.8109 | 0.3925 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 1 | 0.1443 | 0.3522 | 0 | 0 | decreciente |
| `presion_modulada` | 0 | 1 | 0.8263 | 0.3 | 0 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0 (arranca en 0.8, delta = 0.8).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `rueda_bloqueada`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `presion_modulada`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `presion_pedal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `presion_pedal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 160 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La presion modulada ABS es presion_pedal * factor de modulacion, donde el factor oscila entre 0 y 1 (segun el oscilador interno). presion_modulada = p_filtrada * (0.5 + 0.5*oscilador) ∈ [0, p_filtrada]. Con p_filtrada → 1.0, presion_modulada ∈ [0, 1.0]. Nunca debe exceder 1.0 ni ser negativa.
