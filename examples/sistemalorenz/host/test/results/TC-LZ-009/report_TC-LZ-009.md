# TC-LZ-009 — Divergencia rapida con Euler y paso grande

## Descripcion del test

Euler con h=0.05 debe abandonar el atractor antes de t=3 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-EULER

- Pasos simulados: 102  |  Tiempo total: 5 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `on_attractor` es FALSE en algun punto: OK |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.05 | 1 | 1 | 2.275 | 1.35 |
| 0.1 | 1 | 1.637 | 3.494 | 1.284 |
| 2.55 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |
| 5 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |
| 5 | 0 | -nan(ind) | -nan(ind) | -nan(ind) |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 0 | 1 | 0.07843 | 0.2702 | 1 | 0 | decreciente |
| `x_out` ⚠️ | -1.764e+268 | 9.404e+63 | -6.534e+266 | 3.395e+267 | 1 | nan | INVALIDO (1 NaN/Inf) |
| `y_out` ⚠️ | -3.529e+268 | 1.881e+64 | -1.357e+267 | 6.92e+267 | 1 | nan | INVALIDO (1 NaN/Inf) |
| `z_out` ⚠️ | -2.576e+166 | 1.805e+268 | 6.942e+266 | 3.54e+267 | 1.5 | nan | INVALIDO (1 NaN/Inf) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `on_attractor`: valor final = 0 (arranca en 1, delta = 1).
**⚠️ CRITICO: `x_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**⚠️ CRITICO: `y_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**⚠️ CRITICO: `z_out` contiene 1 valor(es) NaN/Inf** — indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.
**Dinamica rapida** en `on_attractor`: tasa de cambio maxima = 20 unidades/s.
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 3.529e+269 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Con un paso Euler 5x mayor (h=0.05), la divergencia ocurre antes (tipicamente en t<3 s en lugar de t<8 s para h=0.01). Esto confirma que el test on_attractor es sensible al metodo de integracion y al paso de tiempo, no solo al modelo. Un codegen que generara Euler en lugar de RK4 seria detectado aqui.
