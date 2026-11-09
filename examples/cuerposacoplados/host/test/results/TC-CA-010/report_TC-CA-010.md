# TC-CA-010 — Independencia de fuerza cero y fuerza maxima

## Descripcion del test

Comparacion de energias: F=0 conserva, F=10 crece, sin NaN.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=10.0`

## Simulacion: ME-RK4

- Pasos simulados: 302  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` > 5.0 eventualmente: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |
| ✅ | `en_fase` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 10 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.01 | 10 | 0 | 3.627 | 1 | -0.4949 | 0.04502 | 0.5125 |
| 0.02 | 10 | 0 | 3.634 | 1.001 | -0.4898 | 0.09007 | 0.5249 |
| 1.51 | 10 | 1 | 24.51 | 3.089 | 1.266 | 0.02834 | 1.472 |
| 3 | 10 | 1 | 10.99 | 1.736 | 1.903 | 0.4842 | -1.099 |
| 3 | 10 | 1 | 10.99 | 1.736 | 1.903 | 0.4842 | -1.099 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 10 | 10 | 10 | 0 | 10 | 10 | constante |
| `en_fase` | 0 | 1 | 0.8013 | 0.3997 | 0 | 1 | creciente |
| `energia_total` | 3.625 | 24.51 | 15.43 | 6.51 | 3.625 | 10.99 | creciente |
| `pos1` | 1 | 3.089 | 2.18 | 0.651 | 1 | 1.736 | creciente |
| `pos2` | -0.5 | 2.177 | 1.085 | 0.9367 | -0.5 | 1.903 | creciente |
| `vel1` | -1.623 | 2.18 | 0.2462 | 1.31 | 0 | 0.4842 | decreciente |
| `vel2` | -1.099 | 1.502 | 0.7909 | 0.7216 | 0.5 | -1.099 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 15.43 J, deriva total = 20.89 J (135.40%) en 3 s — elevada.
**Convergencia** de `en_fase`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `fuerza_externa`=10 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `energia_total`: tasa de cambio maxima = 21.8 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con fuerza_externa=10 N (doble del caso TC-CA-006), la energia crece mas rapidamente. En 3 s con F=10 N, la energia supera facilmente 5 J (mas del 38% sobre la energia inicial). Verifica que fmi2SetReal transmite correctamente valores grandes y que la ODE los integra sin problemas numericos.
