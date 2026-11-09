# TC-PN-004 — Conservacion de energia con RK4 (h=0.05, 10 s)

## Descripcion del test

|energia - 8.496| < 0.1 J en todo momento con RK4.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` en [8.396, 8.596]: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.05 | 0 | 2.612 | 8.496 | -0.2461 |
| 0.1 | 0 | 2.593 | 8.496 | -0.4974 |
| 5 | 0 | -2.379 | 8.496 | -1.675 |
| 9.95 | 0 | 1.278 | 8.495 | 4.76 |
| 10 | 0 | 1.504 | 8.495 | 4.279 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.004975 | 0.07053 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | -0.1266 | 1.948 | 2.618 | 1.504 | oscilante  (6 cruces cero, ~0.3 Hz) |
| `energia_total` | 8.495 | 8.496 | 8.496 | 9.565e-05 | 8.496 | 8.495 | decreciente |
| `velocidad_angular` | -6.05 | 6.051 | -0.1003 | 3.624 | 0 | 4.279 | oscilante  (5 cruces cero, ~0.25 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 0.0004049 J (0.00%) en 10 s — excelente.
**Oscilacion** de `angulo`: amplitud ~2.618, frecuencia estimada ~0.3 Hz (6 cruces de cero en 10 s).
**Oscilacion** de `velocidad_angular`: amplitud ~6.05, frecuencia estimada ~0.25 Hz (5 cruces de cero en 10 s).
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

TEST DE CALIDAD PRIMARIO para RK4. Con paso moderado h=0.05 s, la energia del pendulo no lineal debe conservarse dentro de ±0.1 J (±1.2%) durante 10 segundos. El pendulo de gran angulo es mas dificil de integrar que el oscilador armonico por el termino sin(θ), que varia mas rapidamente cerca de θ=±π.
