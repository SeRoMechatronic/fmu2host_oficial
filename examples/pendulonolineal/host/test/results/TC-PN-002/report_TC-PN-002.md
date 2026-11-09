# TC-PN-002 — Velocidad maxima en el fondo (theta≈0)

## Descripcion del test

max|velocidad_angular| ≈ 6.047 rad/s cuando el pendulo pasa por theta=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `velocidad_angular` > 5.5 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |
| 0.02 | 0 | 2.617 | 8.496 | -0.09815 |
| 2.51 | 0 | -0.8285 | 8.496 | 5.5 |
| 5 | 0 | -2.379 | 8.496 | -1.676 |
| 5 | 0 | -2.379 | 8.496 | -1.676 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.001992 | 0.04463 | 1 | 0 | estable |
| `angulo` | -2.618 | 2.618 | 0.1487 | 1.926 | 2.618 | -2.379 | estable |
| `energia_total` | 8.496 | 8.496 | 8.496 | 4.705e-08 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.051 | 6.051 | -1 | 3.51 | 0 | -1.676 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 2.17e-07 J (0.00%) en 5 s — excelente.
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Al pasar por el punto mas bajo (theta=0), toda la energia es cinetica. La velocidad maxima teorica es omega_max = sqrt(2*(E0 - PE_bottom)) = sqrt(2*(8.496 + 9.81)) ≈ 6.047 rad/s. El test verifica que el pendulo alcanza velocidades superiores a 5.5 rad/s, confirmando que la conversion de energia potencial a cinetica es correcta.
