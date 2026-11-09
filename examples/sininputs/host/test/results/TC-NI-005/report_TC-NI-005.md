# TC-NI-005 — Convergencia a cero a largo plazo

## Descripcion del test

A t=100s el sistema amortiguado debe estar cerca del reposo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 100.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 2002  |  Tiempo total: 100 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion`@t=100.0: esperado 0.0±0.01, obtenido 4.25996e-05 |
| ✅ | `velocidad`@t=100.0: esperado 0.0±0.01, obtenido -4.50329e-05 |
| ✅ | `energia`@t=100.0: esperado 0.0±0.001, obtenido 1.05946e-08 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.05 | 4.999 | 0.9917 | -0.3308 |
| 0.1 | 4.996 | 0.9671 | -0.6527 |
| 50.05 | 0.0002301 | -0.006435 | 0.005548 |
| 100 | 1.059e-08 | 4.26e-05 | -4.503e-05 |
| 100 | 1.059e-08 | 4.26e-05 | -4.503e-05 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 1.059e-08 | 5 | 0.2517 | 0.7574 | 5 | 1.059e-08 | decreciente |
| `posicion` | -0.8844 | 1 | 0.0005495 | 0.1593 | 1 | 4.26e-05 | oscilante  (82 cruces cero, ~0.41 Hz) |
| `velocidad` | -2.433 | 2.153 | -0.009976 | 0.408 | 0 | -4.503e-05 | oscilante  (82 cruces cero, ~0.41 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 0.2517 J, deriva total = 5 J (1986.10%) en 100 s — elevada.
**Oscilacion** de `posicion`: amplitud ~0.9422, frecuencia estimada ~0.41 Hz (82 cruces de cero en 100 s).
**Oscilacion** de `velocidad`: amplitud ~2.293, frecuencia estimada ~0.41 Hz (82 cruces de cero en 100 s).
**Convergencia** de `energia`: valor final = 1.059e-08 (arranca en 5, delta = 5).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Tras 100 segundos de amortiguamiento, el sistema converge al reposo. La constante de tiempo de decaimiento es τ=1/(ζ·ω0)≈7.07 s, por lo que a t=100s han transcurrido ~14 constantes de tiempo y la amplitud es e^(-14) ≈ 8e-7 m. La energia debe ser practicamente cero.
