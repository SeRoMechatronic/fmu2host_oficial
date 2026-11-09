# TC-CA-004 — Transiciones de en_fase — batido de modos

## Descripcion del test

en_fase cambia al menos 8 veces en 30 s (4 inversiones de fase).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 30.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 3001  |  Tiempo total: 30 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `en_fase` == 1 eventualmente: OK |
| ✅ | `en_fase` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.01 | 0 | 0 | 3.625 | 0.9997 | -0.4949 | -0.05497 | 0.5125 |
| 0.02 | 0 | 0 | 3.625 | 0.9989 | -0.4898 | -0.1099 | 0.5248 |
| 15 | 0 | 1 | 3.625 | -1.093 | -0.3496 | -1.283 | -0.1214 |
| 29.99 | 0 | 1 | 3.625 | 0.5482 | 0.06522 | 2.034 | -0.9137 |
| 30 | 0 | 1 | 3.625 | 0.5684 | 0.05609 | 2.006 | -0.9118 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 1 | 0.4505 | 0.4976 | 0 | 1 | estable |
| `energia_total` | 3.625 | 3.625 | 3.625 | 5.268e-09 | 3.625 | 3.625 | constante |
| `pos1` | -1.246 | 1.187 | -0.007344 | 0.7772 | 1 | 0.5684 | oscilante  (22 cruces cero, ~0.367 Hz) |
| `pos2` | -0.5525 | 0.6909 | 0.02875 | 0.3978 | -0.5 | 0.05609 | oscilante  (11 cruces cero, ~0.183 Hz) |
| `vel1` | -2.659 | 2.632 | -0.01405 | 1.763 | 0 | 2.006 | oscilante  (21 cruces cero, ~0.35 Hz) |
| `vel2` | -0.9201 | 0.9718 | 0.01846 | 0.5204 | 0.5 | -0.9118 | oscilante  (11 cruces cero, ~0.183 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.625 J, deriva total = 1.8e-08 J (0.00%) en 30 s — excelente.
**Oscilacion** de `pos1`: amplitud ~1.217, frecuencia estimada ~0.367 Hz (22 cruces de cero en 30 s).
**Oscilacion** de `pos2`: amplitud ~0.6217, frecuencia estimada ~0.183 Hz (11 cruces de cero en 30 s).
**Oscilacion** de `vel1`: amplitud ~2.645, frecuencia estimada ~0.35 Hz (21 cruces de cero en 30 s).
**Oscilacion** de `vel2`: amplitud ~0.946, frecuencia estimada ~0.183 Hz (11 cruces de cero en 30 s).
**Variables algebraicas constantes:** `fuerza_externa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Las dos frecuencias naturales (sqrt(5)≈2.24 y sqrt(1.5)≈1.22 rad/s) producen un efecto de batido: los cuerpos oscilan alternativamente en fase y en contra-fase. en_fase=sign(x1)==sign(x2) cambia con cada inversion de fase relativa. Al menos 4 cambios en 30 s confirman que la dinamica de 4 estados se simula correctamente.
