# TC-CA-009 — Amplitudes acotadas — estabilidad a largo plazo

## Descripcion del test

En 50 s: |pos1|, |pos2| < 3.0 m. No hay crecimiento de amplitud.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 50.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 50 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `pos1` en [-3, 3]: OK |
| ✅ | `pos2` en [-3, 3]: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.05 | 0 | 0 | 3.625 | 0.9931 | -0.4735 | -0.2738 | 0.5615 |
| 0.1 | 0 | 0 | 3.625 | 0.9727 | -0.4439 | -0.5427 | 0.6205 |
| 25.05 | 0 | 0 | 3.625 | 1.015 | -0.2858 | -0.8616 | -0.514 |
| 50 | 0 | 1 | 3.625 | 1.186 | 0.3403 | -0.6242 | 0.3754 |
| 50 | 0 | 1 | 3.625 | 1.186 | 0.3403 | -0.6242 | 0.3754 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 1 | 0.4711 | 0.4994 | 0 | 1 | creciente |
| `energia_total` | 3.625 | 3.625 | 3.625 | 2.737e-05 | 3.625 | 3.625 | decreciente |
| `pos1` | -1.245 | 1.22 | 0.005298 | 0.7854 | 1 | 1.186 | oscilante  (36 cruces cero, ~0.36 Hz) |
| `pos2` | -0.6255 | 0.6908 | 0.002926 | 0.3941 | -0.5 | 0.3403 | oscilante  (19 cruces cero, ~0.19 Hz) |
| `vel1` | -2.658 | 2.66 | 0.002787 | 1.761 | 0 | -0.6242 | oscilante  (36 cruces cero, ~0.36 Hz) |
| `vel2` | -0.9722 | 0.9718 | 0.01758 | 0.5112 | 0.5 | 0.3754 | oscilante  (18 cruces cero, ~0.18 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.625 J, deriva total = 9.458e-05 J (0.00%) en 50 s — excelente.
**Oscilacion** de `pos1`: amplitud ~1.233, frecuencia estimada ~0.36 Hz (36 cruces de cero en 50 s).
**Oscilacion** de `pos2`: amplitud ~0.6582, frecuencia estimada ~0.19 Hz (19 cruces de cero en 50 s).
**Oscilacion** de `vel1`: amplitud ~2.659, frecuencia estimada ~0.36 Hz (36 cruces de cero en 50 s).
**Oscilacion** de `vel2`: amplitud ~0.972, frecuencia estimada ~0.18 Hz (18 cruces de cero en 50 s).
**Variables algebraicas constantes:** `fuerza_externa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Los resortes garantizan que las amplitudes son acotadas (eigenvalores imaginarios puros). Con RK4 y h=0.05, no debe haber crecimiento esponencial de amplitud. Si las posiciones superan 3.0 m, hay inestabilidad numerica (h demasiado grande) o un error en las ecuaciones de movimiento (acoplamiento k_c incorrecto).
