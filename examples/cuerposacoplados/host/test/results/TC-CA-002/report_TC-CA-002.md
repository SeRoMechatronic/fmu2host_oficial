# TC-CA-002 — Conservacion de energia con RK4 — 20 s

## Descripcion del test

Con F=0 y RK4, |energia - 3.625| < 0.05 J en todo momento.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 401  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` en [3.575, 3.675]: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.05 | 0 | 0 | 3.625 | 0.9931 | -0.4735 | -0.2738 | 0.5615 |
| 0.1 | 0 | 0 | 3.625 | 0.9727 | -0.4439 | -0.5427 | 0.6205 |
| 10 | 0 | 1 | 3.625 | -0.9679 | -0.4279 | 1.651 | -0.2434 |
| 19.95 | 0 | 0 | 3.625 | 0.2215 | -0.3444 | -2.534 | -0.1947 |
| 20 | 0 | 0 | 3.625 | 0.09328 | -0.3534 | -2.591 | -0.1645 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 1 | 0.4314 | 0.4959 | 0 | 0 | estable |
| `energia_total` | 3.625 | 3.625 | 3.625 | 1.096e-05 | 3.625 | 3.625 | decreciente |
| `pos1` | -1.242 | 1.186 | 0.03376 | 0.7775 | 1 | 0.09328 | oscilante  (14 cruces cero, ~0.35 Hz) |
| `pos2` | -0.5525 | 0.6897 | 0.03183 | 0.3949 | -0.5 | -0.3534 | oscilante  (8 cruces cero, ~0.2 Hz) |
| `vel1` | -2.658 | 2.584 | -0.0484 | 1.754 | 0 | -2.591 | oscilante  (14 cruces cero, ~0.35 Hz) |
| `vel2` | -0.8136 | 0.9718 | 0.007725 | 0.5306 | 0.5 | -0.1645 | oscilante  (7 cruces cero, ~0.175 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.625 J, deriva total = 3.783e-05 J (0.00%) en 20 s — excelente.
**Oscilacion** de `pos1`: amplitud ~1.214, frecuencia estimada ~0.35 Hz (14 cruces de cero en 20 s).
**Oscilacion** de `pos2`: amplitud ~0.6211, frecuencia estimada ~0.2 Hz (8 cruces de cero en 20 s).
**Oscilacion** de `vel1`: amplitud ~2.621, frecuencia estimada ~0.35 Hz (14 cruces de cero en 20 s).
**Oscilacion** de `vel2`: amplitud ~0.8927, frecuencia estimada ~0.175 Hz (7 cruces de cero en 20 s).
**Variables algebraicas constantes:** `fuerza_externa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

TEST PRIMARIO DE ENERGIA. El sistema conservativo sin disipacion ni fuerza externa debe conservar la energia mecanica total. RK4 con h=0.05 mantiene la energia en [3.575, 3.675] J durante 20 s. Si el buffer de estados tiene un tamano incorrecto (por ejemplo 2 en lugar de 4), los estados v1 o v2 se corrompen y la energia diverge.
