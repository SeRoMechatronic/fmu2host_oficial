# TC-FABS-003 — Frenado de emergencia — ABS activa tras escalon de velocidad

## Descripcion del test

velocidad_rueda: 0.8→0.0 (escalon). abs_activo eventually=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=0.9`  
`velocidad_rueda`: t=0: 0.8, t=0.1: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `abs_activo` == 1 eventualmente: OK |
| ✅ | `presion_modulada` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.8 | 0 | 0 | 0 | 0 |
| 0.005 | 0.9 | 0.8 | 0 | 1 | 0 | 0.05453 |
| 0.01 | 0.9 | 0.8 | 0 | 1 | 0 | 0.1058 |
| 0.25 | 0.9 | 0 | 1 | 0 | 1 | 0.4308 |
| 0.495 | 0.9 | 0 | 0 | 1 | 0 | 0.8982 |
| 0.5 | 0.9 | 0 | 0 | 1 | 0 | 0.8983 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `velocidad_rueda` | 0 | 0.8 | 0.1584 | 0.3204 | 0.8 | 0 | decreciente |
| `abs_activo` | 0 | 1 | 0.3663 | 0.4842 | 0 | 0 | decreciente |
| `frenado_normal` | 0 | 1 | 0.6238 | 0.4869 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 1 | 0.2871 | 0.4547 | 0 | 0 | estable |
| `presion_modulada` | 0 | 0.8983 | 0.5892 | 0.312 | 0 | 0.8983 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0 (arranca en 0.8, delta = 0.8).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `rueda_bloqueada`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `presion_modulada`: valor final = 0.8983 (arranca en 0, delta = 0.8983).
**Variables algebraicas constantes:** `presion_pedal`=0.9 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 160 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La velocidad cae abruptamente de 0.8 a 0.0 en t=0.1 s. El filtro de velocidad (tau=0.05 s) produce dv_filtrada fuertemente negativo, lo que genera lambda > 0.15. abs_activo=TRUE. Si el codegen no propaga correctamente los 5 estados del ABS, lambda no se calcula correctamente y abs_activo permanece FALSE.
