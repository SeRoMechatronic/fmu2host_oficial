# TC-CA-003 — Deriva de energia con Euler — discriminador de integrador

## Descripcion del test

Con Euler, energia_total debe desviarse mas de 0.2 J antes de t=20 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-EULER

- Pasos simulados: 401  |  Tiempo total: 20 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` > 3.825 eventualmente: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.05 | 0 | 0 | 3.668 | 1 | -0.475 | -0.275 | 0.5625 |
| 0.1 | 0 | 0 | 3.711 | 0.9862 | -0.4469 | -0.5487 | 0.6231 |
| 10 | 0 | 1 | 42.04 | -3.382 | -0.323 | 5.255 | -0.7577 |
| 19.95 | 0 | 0 | 524.2 | 6.225 | -1.45 | -28.53 | 2.833 |
| 20 | 0 | 0 | 530.9 | 4.798 | -1.308 | -30.16 | 3.098 |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 1 | 0.3117 | 0.4638 | 0 | 0 | decreciente |
| `energia_total` | 3.625 | 530.9 | 104.3 | 130.9 | 3.625 | 530.9 | creciente |
| `pos1` | -10.76 | 13.16 | 0.3158 | 4.449 | 1 | 4.798 | oscilante  (14 cruces cero, ~0.35 Hz) |
| `pos2` | -1.921 | 2.517 | 0.01164 | 0.8701 | -0.5 | -1.308 | oscilante  (10 cruces cero, ~0.25 Hz) |
| `vel1` | -30.16 | 27.09 | 0.1142 | 9.832 | 0 | -30.16 | oscilante  (14 cruces cero, ~0.35 Hz) |
| `vel2` | -4.63 | 4.012 | -0.03259 | 1.561 | 0.5 | 3.098 | oscilante  (12 cruces cero, ~0.3 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 104.3 J, deriva total = 527.3 J (505.32%) en 20 s — elevada.
**Oscilacion** de `pos1`: amplitud ~11.96, frecuencia estimada ~0.35 Hz (14 cruces de cero en 20 s).
**Oscilacion** de `pos2`: amplitud ~2.219, frecuencia estimada ~0.25 Hz (10 cruces de cero en 20 s).
**Oscilacion** de `vel1`: amplitud ~28.63, frecuencia estimada ~0.35 Hz (14 cruces de cero en 20 s).
**Oscilacion** de `vel2`: amplitud ~4.321, frecuencia estimada ~0.3 Hz (12 cruces de cero en 20 s).
**Variables algebraicas constantes:** `fuerza_externa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 20 unidades/s.
**Dinamica rapida** en `energia_total`: tasa de cambio maxima = 134.3 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Euler es un metodo de primer orden que introduce disipacion artificial en sistemas hamiltonianos. Con h=0.05 y 4 estados, la energia debe subir o bajar mas de 0.2 J antes de t=20 s. Si la energia se conserva igual que con RK4, el codegen no esta usando correctamente el buffer de k-vectores del integrador RK4 y esta degradando a Euler.
