# TC-NI-007 — Sin NaN ni Inf en 20 segundos

## Descripcion del test

Simulacion larga: ningun output debe producir valores invalidos.

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
| ✅ | `posicion` sin NaN/Inf: OK |
| ✅ | `velocidad` sin NaN/Inf: OK |
| ✅ | `energia` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.01 | 5 | 0.9997 | -0.06659 |
| 0.02 | 5 | 0.9987 | -0.133 |
| 10 | 0.703 | 0.2977 | -0.5886 |
| 19.99 | 0.09379 | 0.04004 | -0.3382 |
| 20 | 0.09345 | 0.03665 | -0.3401 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 0.09345 | 5 | 1.232 | 1.282 | 5 | 0.09345 | decreciente |
| `posicion` | -0.8853 | 1 | 0.004252 | 0.3518 | 1 | 0.03665 | oscilante  (16 cruces cero, ~0.4 Hz) |
| `velocidad` | -2.433 | 2.154 | -0.04823 | 0.903 | 0 | -0.3401 | oscilante  (16 cruces cero, ~0.4 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 1.232 J, deriva total = 4.907 J (398.42%) en 20 s — elevada.
**Oscilacion** de `posicion`: amplitud ~0.9427, frecuencia estimada ~0.4 Hz (16 cruces de cero en 20 s).
**Oscilacion** de `velocidad`: amplitud ~2.294, frecuencia estimada ~0.4 Hz (16 cruces de cero en 20 s).
**Convergencia** de `energia`: valor final = 0.09345 (arranca en 5, delta = 4.907).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

20 segundos de simulacion sin entradas ni eventos. Si el codegen genera codigo de derivadas incorrecto o hay un error en la FMU, el integrador puede producir NaN/Inf. Este test verifica la estabilidad numerica basica del FMU de cero entradas.
