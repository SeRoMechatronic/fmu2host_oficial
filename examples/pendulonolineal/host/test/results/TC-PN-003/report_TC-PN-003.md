# TC-PN-003 — Oscilacion simetrica — angulo minimo ≈ -2.618

## Descripcion del test

Sin amortiguamiento, el pendulo debe alcanzar -2.618 rad.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `angulo` < -2.4 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |
| 0.02 | 0 | 2.617 | 8.496 | -0.09815 |
| 5.01 | 0 | -2.395 | 8.496 | -1.608 |
| 10 | 0 | 1.503 | 8.496 | 4.28 |
| 10 | 0 | 1.503 | 8.496 | 4.28 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.001996 | 0.04465 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | -0.1338 | 1.942 | 2.618 | 1.503 | oscilante  (6 cruces cero, ~0.3 Hz) |
| `energia_total` | 8.496 | 8.496 | 8.496 | 5.279e-08 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.051 | 6.051 | -0.1049 | 3.62 | 0 | 4.28 | oscilante  (5 cruces cero, ~0.25 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 2.7e-07 J (0.00%) en 10 s — excelente.
**Oscilacion** de `angulo`: amplitud ~2.618, frecuencia estimada ~0.3 Hz (6 cruces de cero en 10 s).
**Oscilacion** de `velocidad_angular`: amplitud ~6.051, frecuencia estimada ~0.25 Hz (5 cruces de cero en 10 s).
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Sin amortiguamiento (g, L y las condiciones iniciales son los unicos parametros), el pendulo oscila simetricamente. Desde 2.618 rad debe alcanzar aproximadamente -2.618 rad en el otro extremo. Si solo alcanza -2.0 rad, la energia no se conserva correctamente.
