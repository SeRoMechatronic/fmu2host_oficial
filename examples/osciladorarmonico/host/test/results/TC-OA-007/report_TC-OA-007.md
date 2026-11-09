# TC-OA-007 — Posicion acotada con RK4 en 50 ciclos

## Descripcion del test

Con RK4, |posicion| debe mantenerse <= 1.5 m durante 50 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 50.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 5002  |  Tiempo total: 50 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` en [-1.5, 1.5]: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 25.01 | 19.74 | 0.998 | -0.3944 |
| 50 | 19.74 | 1 | 0.000256 |
| 50 | 19.74 | 1 | 0.000256 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 2.435e-05 | 19.74 | 19.74 | decreciente |
| `posicion` | -1 | 1 | 0.0003997 | 0.7073 | 1 | 1 | oscilante  (100 cruces cero, ~1 Hz) |
| `velocidad` | -6.283 | 6.283 | 3.407e-08 | 4.442 | 0 | 0.000256 | oscilante  (99 cruces cero, ~0.99 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 8.43e-05 J (0.00%) en 50 s — excelente.
**Oscilacion** de `posicion`: amplitud ~1, frecuencia estimada ~1 Hz (100 cruces de cero en 50 s).
**Oscilacion** de `velocidad`: amplitud ~6.283, frecuencia estimada ~0.99 Hz (99 cruces de cero en 50 s).
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.45 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Durante 50 ciclos, RK4 no debe permitir un crecimiento de amplitud mayor al 50% de la amplitud inicial (1.0 m). Un integrador simpletico ideal conservaria exactamente 1.0 m, pero RK4 permite una pequena deriva aceptable. Si la amplitud supera 1.5 m, el integrador esta inyectando energia artificialmente.
