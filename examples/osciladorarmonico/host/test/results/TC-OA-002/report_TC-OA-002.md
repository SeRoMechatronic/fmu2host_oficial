# TC-OA-002 — Posicion analitica en t=0.25 s (cuarto de periodo)

## Descripcion del test

x(0.25)=cos(π/2)≈0.0, v(0.25)=-2π≈-6.283.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.251 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 27  |  Tiempo total: 0.251 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` final: esperado 0.0±0.02, obtenido -0.00628294 |
| ✅ | `velocidad` final: esperado -6.283±0.05, obtenido -6.28306 |
| ✅ | `energia` final: esperado 19.739±0.1, obtenido 19.7392 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 0.13 | 19.74 | 0.6845 | -4.58 |
| 0.25 | 19.74 | 2.037e-07 | -6.283 |
| 0.251 | 19.74 | -0.006283 | -6.283 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 1.33e-07 | 19.74 | 19.74 | decreciente |
| `posicion` | -0.006283 | 1 | 0.6076 | 0.3416 | 1 | -0.006283 | decreciente |
| `velocidad` | -6.283 | 0 | -4.052 | 2.052 | 0 | -6.283 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 4.2e-07 J (0.00%) en 0.251 s — excelente.
**Convergencia** de `velocidad`: valor final = -6.283 (arranca en 0, delta = 6.283).
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.45 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

A un cuarto de periodo (T/4=0.25 s), la posicion pasa por cero y la velocidad alcanza su maximo negativo ω=2π≈6.283 rad/s. Toda la energia es cinetica en este punto (E=0.5*m*v^2). Este es el punto donde el codegen demuestra que integra correctamente el termino no-lineal omega^2*x.
