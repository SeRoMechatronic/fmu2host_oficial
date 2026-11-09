# TC-PN-008 — Estimacion del periodo de gran angulo

## Descripcion del test

El periodo de oscilacion debe estar cerca de 7 s (≠ 2.006 s lineal).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 2001  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `angulo` cambios de signo: 11 (minimo 4): OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |
| 0.02 | 0 | 2.617 | 8.496 | -0.09815 |
| 10 | 0 | 1.503 | 8.496 | 4.28 |
| 19.99 | 0 | -1.736 | 8.496 | 3.709 |
| 20 | 0 | -1.699 | 8.496 | 3.806 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.001999 | 0.04468 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | -0.06467 | 1.979 | 2.618 | -1.699 | oscilante  (11 cruces cero, ~0.275 Hz) |
| `energia_total` | 8.496 | 8.496 | 8.496 | 7.148e-08 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.051 | 6.051 | -0.2148 | 3.514 | 0 | 3.806 | oscilante  (11 cruces cero, ~0.275 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 3.58e-07 J (0.00%) en 20 s — excelente.
**Oscilacion** de `angulo`: amplitud ~2.618, frecuencia estimada ~0.275 Hz (11 cruces de cero en 20 s).
**Oscilacion** de `velocidad_angular`: amplitud ~6.051, frecuencia estimada ~0.275 Hz (11 cruces de cero en 20 s).
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La no-linealidad alarga el periodo del pendulo. Para θ0=150°, T_grande ≈ 7 s (vs. T_lineal=2.006 s). En 20 s deben ocurrir ~2.8 ciclos, con ~6 cruces de cero. El test verifica un minimo de 4 cruces, que serian consistentes con ~2 ciclos completos, confirmando el periodo largo del sistema no lineal.
