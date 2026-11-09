# TC-FABS-007 — Oscilador interno — no produce NaN ni Inf durante 10 Hz

## Descripcion del test

Oscilador en 10 Hz: presion_modulada estable, sin valores invalidos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.5`  
`presion_pedal=0.8`  
`velocidad_rueda`: t=0: 0.5, t=0.1: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 1001  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `presion_modulada` sin NaN/Inf: OK |
| ✅ | `abs_activo` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0.5 | 0 | 0 | 0 | 0 |
| 0.001 | 0.8 | 0.5 | 0 | 1 | 0 | 0.009938 |
| 0.002 | 0.8 | 0.5 | 0 | 1 | 0 | 0.01975 |
| 0.5 | 0.8 | 0 | 0 | 1 | 0 | 0.7985 |
| 0.999 | 0.8 | 0 | 0 | 1 | 0 | 0.8 |
| 1 | 0.8 | 0 | 0 | 1 | 0 | 0.8 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `velocidad_rueda` | 0 | 0.5 | 0.04995 | 0.15 | 0.5 | 0 | decreciente |
| `abs_activo` | 0 | 1 | 0.1638 | 0.3703 | 0 | 0 | decreciente |
| `frenado_normal` | 0 | 1 | 0.8352 | 0.3712 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 1 | 0.1269 | 0.333 | 0 | 0 | decreciente |
| `presion_modulada` | 0 | 0.8 | 0.6712 | 0.2338 | 0 | 0.8 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0 (arranca en 0.5, delta = 0.5).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `rueda_bloqueada`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `presion_modulada`: valor final = 0.8 (arranca en 0, delta = 0.8).
**Variables algebraicas constantes:** `presion_pedal`=0.8 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 500 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 1000 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El oscilador armonico interno (f=10 Hz, oscilador=sin, d_oscilador=cos) modula la presion. Los estados del oscilador tienen condiciones iniciales oscilador=0, d_oscilador=1. La integracion RK4 debe mantener la amplitud del oscilador acotada. Si los k-vectores del RK4 tienen tamanyo < 5, la integracion del oscilador puede corromperse.
