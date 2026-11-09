# TC-OA-005 — Conservacion de energia — RK4 sobre 20 ciclos

## Descripcion del test

Con RK4, la desviacion de energia debe ser menor de 0.05 J en 20 s.

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
| ✅ | `energia` en [19.69, 19.79]: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 10 | 19.74 | 1 | 5.12e-05 |
| 19.99 | 19.74 | 0.998 | 0.3946 |
| 20 | 19.74 | 1 | 0.0001024 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 9.742e-06 | 19.74 | 19.74 | decreciente |
| `posicion` | -1 | 1 | 0.0004996 | 0.7075 | 1 | 1 | oscilante  (40 cruces cero, ~1 Hz) |
| `velocidad` | -6.283 | 6.283 | -1.71e-08 | 4.443 | 0 | 0.0001024 | oscilante  (39 cruces cero, ~0.975 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 3.372e-05 J (0.00%) en 20 s — excelente.
**Oscilacion** de `posicion`: amplitud ~1, frecuencia estimada ~1 Hz (40 cruces de cero en 20 s).
**Oscilacion** de `velocidad`: amplitud ~6.283, frecuencia estimada ~0.975 Hz (39 cruces de cero en 20 s).
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.45 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Test principal de calidad del integrador. RK4 con h=0.01 s (100 pasos por ciclo) debe mantener la energia dentro de ±0.05 J (±0.25%) durante 20 ciclos completos. Este es el criterio de aceptacion primario: un integrador de orden inferior o con paso mayor fallaria este test acumulando error energetico.
