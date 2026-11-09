# TC-CA-005 — Ambas masas oscilan cruzando cero — resortes de pared activos

## Descripcion del test

pos1 y pos2 cambian de signo al menos 3 veces cada una en 10 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `pos1` cambios de signo: 7 (minimo 3): OK |
| ✅ | `pos2` cambios de signo: 4 (minimo 3): OK |
| ✅ | `pos1` sin NaN/Inf: OK |
| ✅ | `pos2` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.01 | 0 | 0 | 3.625 | 0.9997 | -0.4949 | -0.05497 | 0.5125 |
| 0.02 | 0 | 0 | 3.625 | 0.9989 | -0.4898 | -0.1099 | 0.5248 |
| 5.01 | 0 | 0 | 3.625 | 0.306 | -0.5514 | 2.351 | -0.04816 |
| 10 | 0 | 1 | 3.625 | -0.9679 | -0.4279 | 1.651 | -0.2434 |
| 10 | 0 | 1 | 3.625 | -0.9679 | -0.4279 | 1.651 | -0.2434 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 1 | 0.476 | 0.4997 | 0 | 1 | creciente |
| `energia_total` | 3.625 | 3.625 | 3.625 | 1.8e-09 | 3.625 | 3.625 | constante |
| `pos1` | -1.235 | 1.187 | -0.02566 | 0.7947 | 1 | -0.9679 | oscilante  (7 cruces cero, ~0.35 Hz) |
| `pos2` | -0.5525 | 0.6581 | 0.04034 | 0.3832 | -0.5 | -0.4279 | oscilante  (4 cruces cero, ~0.2 Hz) |
| `vel1` | -2.659 | 2.527 | -0.1939 | 1.73 | 0 | 1.651 | oscilante  (7 cruces cero, ~0.35 Hz) |
| `vel2` | -0.6576 | 0.9718 | 0.007075 | 0.5246 | 0.5 | -0.2434 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.625 J, deriva total = 6e-09 J (0.00%) en 10 s — excelente.
**Oscilacion** de `pos1`: amplitud ~1.211, frecuencia estimada ~0.35 Hz (7 cruces de cero en 10 s).
**Oscilacion** de `pos2`: amplitud ~0.6053, frecuencia estimada ~0.2 Hz (4 cruces de cero en 10 s).
**Oscilacion** de `vel1`: amplitud ~2.593, frecuencia estimada ~0.35 Hz (7 cruces de cero en 10 s).
**Variables algebraicas constantes:** `fuerza_externa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Los resortes de pared impiden que las masas se desplacen indefinidamente. Con las condiciones iniciales x1=1, x2=-0.5, ambas masas oscilan alrededor de cero y cruzan el eje varias veces. Si alguna masa no cruza el cero, la integracion de su estado tiene un offset incorrecto (buffer contaminado por otro estado).
