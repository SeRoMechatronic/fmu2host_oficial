# TC-PN-005 — Deriva energetica con Euler — discriminador

## Descripcion del test

Euler con h=0.05 debe mostrar deriva >0.5 J antes de t=10 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-EULER

- Pasos simulados: 201  |  Tiempo total: 10 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` > 9.0 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.05 | 0 | 2.618 | 8.526 | -0.2452 |
| 0.1 | 0 | 2.606 | 8.555 | -0.4905 |
| 5 | 0 | -20.49 | 21.63 | -6.468 |
| 9.95 | 0 | -54.52 | 29.94 | -7.16 |
| 10 | 0 | -54.88 | 29.83 | -7.6 |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.004975 | 0.07053 | 1 | 0 | estable |
| `angulo` | -54.88 | 2.618 | -22.14 | 17.22 | 2.618 | -54.88 | decreciente |
| `energia_total` | 8.496 | 32.75 | 20.01 | 6.856 | 8.496 | 29.83 | creciente |
| `velocidad_angular` | -8.963 | 0 | -5.759 | 1.914 | 0 | -7.6 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 20.01 J, deriva total = 24.25 J (121.16%) en 10 s — elevada.
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 20 unidades/s.
**Dinamica rapida** en `energia_total`: tasa de cambio maxima = 19.07 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Euler con h=0.05 acumula error en el termino no lineal sin(θ). La energia crece sistematicamente, superando 9 J (>6% de deriva). Si Euler tambien conserva la energia con h=0.05, usar h=0.1 s para ampliar la diferencia. Este es el discriminador RK4 vs Euler.
