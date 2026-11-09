# TC-OA-006 — Deriva de energia con Euler — debe ser peor que RK4

## Descripcion del test

Euler con h=0.01 debe mostrar deriva energetica mayor de 0.8 J en 20 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-EULER

- Pasos simulados: 2001  |  Tiempo total: 20 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia` > 20.5 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.82 | 1 | -0.3948 |
| 0.02 | 19.9 | 0.9961 | -0.7896 |
| 10 | 1015 | 7.147 | 3.712 |
| 19.99 | 5.199e+04 | 50 | 72.8 |
| 20 | 5.22e+04 | 50.72 | 53.06 |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 5.22e+04 | 6631 | 1.138e+04 | 19.74 | 5.22e+04 | creciente |
| `posicion` | -46.86 | 50.72 | -0.04182 | 12.92 | 1 | 50.72 | oscilante  (40 cruces cero, ~1 Hz) |
| `velocidad` | -280.2 | 309.3 | 2.511 | 81.71 | 0 | 53.06 | oscilante  (39 cruces cero, ~0.975 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 6631 J, deriva total = 5.218e+04 J (786.86%) en 20 s — elevada.
**Oscilacion** de `posicion`: amplitud ~48.79, frecuencia estimada ~1 Hz (40 cruces de cero en 20 s).
**Oscilacion** de `velocidad`: amplitud ~294.8, frecuencia estimada ~0.975 Hz (39 cruces de cero en 20 s).
**Dinamica rapida** en `energia`: tasa de cambio maxima = 2.052e+04 unidades/s.
**Dinamica rapida** en `posicion`: tasa de cambio maxima = 309.3 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Euler es un integrador de orden 1 que sistemáticamente gana energia en osciladores sin amortiguamiento. Con h=0.01 s sobre 20 ciclos, la energia del oscilador crece mas del 3% respecto al valor inicial de 19.739 J. Si Euler tambien conserva la energia, el paso h es demasiado pequeno o el test no es discriminante.
