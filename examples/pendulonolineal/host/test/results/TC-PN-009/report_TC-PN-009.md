# TC-PN-009 — Sin NaN ni Inf en 30 s

## Descripcion del test

Pendulo caotico-cercano sin valores invalidos en 30 s.

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
| ✅ | `angulo` sin NaN/Inf: OK |
| ✅ | `velocidad_angular` sin NaN/Inf: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |
| 0.02 | 0 | 2.617 | 8.496 | -0.09815 |
| 15 | 0 | 0.1464 | 8.496 | -6.033 |
| 29.99 | 0 | -2.61 | 8.496 | -0.2881 |
| 30 | 0 | -2.612 | 8.496 | -0.2384 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.002333 | 0.04825 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | 0.004225 | 1.967 | 2.618 | -2.612 | oscilante  (17 cruces cero, ~0.283 Hz) |
| `energia_total` | 8.496 | 8.496 | 8.496 | 9.699e-08 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.051 | 6.051 | -0.1743 | 3.553 | 0 | -0.2384 | oscilante  (16 cruces cero, ~0.267 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 4.65e-07 J (0.00%) en 30 s — excelente.
**Oscilacion** de `angulo`: amplitud ~2.618, frecuencia estimada ~0.283 Hz (17 cruces de cero en 30 s).
**Oscilacion** de `velocidad_angular`: amplitud ~6.051, frecuencia estimada ~0.267 Hz (16 cruces de cero en 30 s).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

30 segundos de pendulo no lineal de gran angulo. La proximidad a la posicion inestable (θ=π) hace este sistema numericamente sensible. Cualquier NaN/Inf indica que el integrador ha divergido. RK4 con h=0.01 debe mantenerse estable para estos parametros.
