# TC-LZ-002 — z siempre positivo con RK4 (30 s)

## Descripcion del test

El atractor de Lorenz existe completamente en z>0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 30.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 3001  |  Tiempo total: 30 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `z_out` > 0.0 siempre: OK |
| ✅ | `z_out` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.01 | 1 | 1.012 | 1.255 | 1.472 |
| 0.02 | 1 | 1.048 | 1.514 | 1.447 |
| 15 | 1 | 9.355 | 3.81 | 33.82 |
| 29.99 | 1 | -5.765 | -5.963 | 23.46 |
| 30 | 1 | -5.794 | -6.173 | 23.18 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `x_out` | -17.98 | 19.44 | -2.301 | 7.803 | 1 | -5.794 | oscilante  (9 cruces cero, ~0.15 Hz) |
| `y_out` | -24.14 | 26.91 | -2.324 | 8.555 | 1 | -6.173 | oscilante  (13 cruces cero, ~0.217 Hz) |
| `z_out` | 1.397 | 47.52 | 24.56 | 7.679 | 1.5 | 23.18 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Oscilacion** de `x_out`: amplitud ~18.71, frecuencia estimada ~0.15 Hz (9 cruces de cero en 30 s).
**Oscilacion** de `y_out`: amplitud ~25.53, frecuencia estimada ~0.217 Hz (13 cruces de cero en 30 s).
**Variables algebraicas constantes:** `on_attractor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `on_attractor`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 158.1 unidades/s.
**Dinamica rapida** en `y_out`: tasa de cambio maxima = 364.6 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Para los parametros estandar (sigma=10, rho=28, beta=8/3) y condiciones iniciales con z>0, la trayectoria permanece en el semiplano z>0 para siempre. Si z se vuelve negativo, la integracion ha fallado y el sistema ha abandonado el atractor.
