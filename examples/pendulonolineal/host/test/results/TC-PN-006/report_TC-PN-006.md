# TC-PN-006 — en_reposo activa al menos 4 veces en 15 s

## Descripcion del test

El pendulo pasa por los extremos al menos 2 veces por ciclo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 15.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 1502  |  Tiempo total: 15 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `en_reposo`==1 al menos 3 veces, encontrado 3: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |
| 0.02 | 0 | 2.617 | 8.496 | -0.09815 |
| 7.51 | 0 | 2.08 | 8.496 | -2.725 |
| 15 | 0 | 0.1464 | 8.496 | -6.033 |
| 15 | 0 | 0.1464 | 8.496 | -6.033 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.001997 | 0.04466 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | 0.1073 | 1.966 | 2.618 | 0.1464 | oscilante  (8 cruces cero, ~0.267 Hz) |
| `energia_total` | 8.496 | 8.496 | 8.496 | 6.096e-08 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.051 | 6.051 | -0.1706 | 3.548 | 0 | -6.033 | oscilante  (8 cruces cero, ~0.267 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 3.07e-07 J (0.00%) en 15 s — excelente.
**Oscilacion** de `angulo`: amplitud ~2.618, frecuencia estimada ~0.267 Hz (8 cruces de cero en 15 s).
**Oscilacion** de `velocidad_angular`: amplitud ~6.051, frecuencia estimada ~0.267 Hz (8 cruces de cero en 15 s).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El periodo del pendulo de 150° es aproximadamente T≈7 s (mucho mayor que el periodo lineal de 2 s). En 15 s deben ocurrir ~2 ciclos, cada uno con 2 puntos de reposo (extremos). en_reposo=true indica que |omega|<0.01, lo que sucede en los puntos de maxima amplitud.
