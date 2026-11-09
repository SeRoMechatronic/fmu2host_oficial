# TC-LZ-004 — on_attractor FALSE con Euler h=0.04 — discriminador de integrador

## Descripcion del test

Euler con h=0.04 debe abandonar el atractor antes de t=10 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.04 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-EULER

- Pasos simulados: 252  |  Tiempo total: 10 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `on_attractor` es FALSE en algun punto: OK |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.04 | 1 | 1 | 2.02 | 1.38 |
| 0.08 | 1 | 1.408 | 3.004 | 1.314 |
| 5.04 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |
| 10 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |
| 10 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 0 | 1 | 0.04365 | 0.2047 | 1 | 0 | decreciente |
| `x_out` ⚠️ | -1.324e+114 | 4.366e+296 | 1.408e+295 | 7.842e+295 | 1 | nan | INVALIDO (1 NaN/Inf) |
| `y_out` ⚠️ | -3.309e+114 | 1.092e+297 | 3.638e+295 | 1.993e+296 | 1 | nan | INVALIDO (1 NaN/Inf) |
| `z_out` ⚠️ | -1.313e+297 | 2.062e+184 | -4.376e+295 | 2.397e+296 | 1.5 | nan | INVALIDO (1 NaN/Inf) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `on_attractor`: valor final = 0 (arranca en 1, delta = 1).
**⚠️ CRITICO: `x_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**⚠️ CRITICO: `y_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**⚠️ CRITICO: `z_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**Dinamica rapida** en `on_attractor`: tasa de cambio maxima = 25 unidades/s.
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 1.092e+298 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El exponente de Lyapunov positivo del sistema Lorenz amplifica cualquier error numerico exponencialmente. Euler de orden 1 con h=0.04 acumula suficiente error para que la trayectoria escape del atractor antes de t=10 s. Nota: h=0.01 no es suficiente para divergencia en 10s; h>=0.04 es necesario. Este es el test discriminador: SOLO RK4 pasa, Euler falla.
