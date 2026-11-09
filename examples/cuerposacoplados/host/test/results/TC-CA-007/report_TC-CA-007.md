# TC-CA-007 — Fuerza → 0 conserva energia tras la actuacion

## Descripcion del test

F=5 N hasta t=2, luego F=0: energia conservada a partir de t=2.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=5.0`  
`fuerza_externa`: t=0: 5.0, t=2.0: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total`@t=1.9: esperado 5.0±0.2, obtenido 5.08315 |
| ✅ | `energia_total` en [3, 10]: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.01 | 5 | 0 | 3.625 | 1 | -0.4949 | -0.004974 | 0.5125 |
| 0.02 | 5 | 0 | 3.625 | 0.9999 | -0.4898 | -0.009895 | 0.5248 |
| 5.01 | 0 | 0 | 5.333 | 0.5346 | -1.51 | -0.7387 | 0.3424 |
| 10 | 0 | 0 | 5.333 | 0.2545 | -1.415 | 1.585 | -0.744 |
| 10 | 0 | 0 | 5.333 | 0.2545 | -1.415 | 1.585 | -0.744 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 5 | 0.998 | 1.999 | 5 | 0 | decreciente |
| `en_fase` | 0 | 1 | 0.6138 | 0.4871 | 0 | 0 | estable |
| `energia_total` | 3.279 | 5.333 | 5.024 | 0.6688 | 3.625 | 5.333 | creciente |
| `pos1` | -1.037 | 1.365 | 0.1986 | 0.8028 | 1 | 0.2545 | oscilante  (6 cruces cero, ~0.3 Hz) |
| `pos2` | -1.533 | 1.272 | 0.1463 | 0.9183 | -0.5 | -1.415 | oscilante  (4 cruces cero, ~0.2 Hz) |
| `vel1` | -2.568 | 2.54 | -0.07203 | 1.454 | 0 | 1.585 | oscilante  (7 cruces cero, ~0.35 Hz) |
| `vel2` | -1.772 | 1.728 | -0.09214 | 1.123 | 0.5 | -0.744 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 5.024 J, deriva total = 2.053 J (40.87%) en 10 s — elevada.
**Oscilacion** de `pos1`: amplitud ~1.201, frecuencia estimada ~0.3 Hz (6 cruces de cero en 10 s).
**Oscilacion** de `pos2`: amplitud ~1.402, frecuencia estimada ~0.2 Hz (4 cruces de cero en 10 s).
**Oscilacion** de `vel1`: amplitud ~2.554, frecuencia estimada ~0.35 Hz (7 cruces de cero en 10 s).
**Convergencia** de `fuerza_externa`: valor final = 0 (arranca en 5, delta = 5).
**Convergencia** de `energia_total`: valor final = 5.333 (arranca en 3.625, delta = 1.708).
**Dinamica rapida** en `fuerza_externa`: tasa de cambio maxima = 500 unidades/s.
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Durante t=[0,2] la fuerza inyecta energia. En t=2, se retira la fuerza. A partir de t=2, el sistema conserva la energia ganada (libre, sin disipacion). La energia en t≈2 es mayor que 4 J (F ha trabajado sobre la masa). Despues de t=2, la energia oscila entre [E_min, E_max] con RK4 manteniendo la conservacion.
