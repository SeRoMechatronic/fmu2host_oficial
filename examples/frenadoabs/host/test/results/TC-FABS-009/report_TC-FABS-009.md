# TC-FABS-009 — Buffer de 5 estados — no NaN en 2 segundos

## Descripcion del test

2 s de simulacion con ABS activo: los 5 estados no producen NaN.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.005 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.8`  
`presion_pedal=0.9`  
`velocidad_rueda`: t=0: 0.8, t=0.1: 0.1

## Simulacion: ME-RK4

- Pasos simulados: 402  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `presion_modulada` sin NaN/Inf: OK |
| ✅ | `abs_activo` sin NaN/Inf: OK |
| ✅ | `rueda_bloqueada` sin NaN/Inf: OK |
| ✅ | `frenado_normal` sin NaN/Inf: OK |
| ✅ | `presion_modulada` en [0, 1]: OK |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.8 | 0 | 0 | 0 | 0 |
| 0.005 | 0.9 | 0.8 | 0 | 1 | 0 | 0.05453 |
| 0.01 | 0.9 | 0.8 | 0 | 1 | 0 | 0.1058 |
| 1.005 | 0.9 | 0.1 | 0 | 1 | 0 | 0.9 |
| 2 | 0.9 | 0.1 | 0 | 1 | 0 | 0.9 |
| 2 | 0.9 | 0.1 | 0 | 1 | 0 | 0.9 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `velocidad_rueda` | 0.1 | 0.8 | 0.1348 | 0.1524 | 0.8 | 0.1 | decreciente |
| `abs_activo` | 0 | 1 | 0.1169 | 0.3217 | 0 | 0 | decreciente |
| `frenado_normal` | 0 | 1 | 0.8806 | 0.3247 | 0 | 1 | creciente |
| `rueda_bloqueada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `presion_modulada` | 0 | 0.9 | 0.8138 | 0.2142 | 0 | 0.9 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `velocidad_rueda`: valor final = 0.1 (arranca en 0.8, delta = 0.7).
**Convergencia** de `abs_activo`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `frenado_normal`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `presion_modulada`: valor final = 0.9 (arranca en 0, delta = 0.9).
**Variables algebraicas constantes:** `presion_pedal`=0.9, `rueda_bloqueada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `rueda_bloqueada`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `velocidad_rueda`: tasa de cambio maxima = 140 unidades/s.
**Dinamica rapida** en `abs_activo`: tasa de cambio maxima = 200 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

TEST CRITICO DE BUFFER. FrenadoABS tiene 5 estados (mas que cualquier otro modelo de la suite excepto MuchosEstados). Si el codegen usa EULER_BUF_SIZE o RK4_BUF_SIZE < 5, hay desbordamiento de buffer. Los estados del oscilador (posicion/velocidad) son los que mas probablemente quedan fuera del buffer en un codegen con tamano fijo.
