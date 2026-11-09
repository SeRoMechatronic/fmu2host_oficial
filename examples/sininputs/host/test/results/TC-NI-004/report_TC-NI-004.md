# TC-NI-004 — Comprobacion analitica en t=1.0 s

## Descripcion del test

Solcion analitica: x(1)≈-0.728. Verifica precision del integrador RK4.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` final: esperado -0.728±0.05, obtenido -0.747212 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.01 | 5 | 0.9997 | -0.06659 |
| 0.02 | 5 | 0.9987 | -0.133 |
| 0.5 | 4.63 | 0.299 | -2.362 |
| 0.99 | 3.959 | -0.7345 | -1.297 |
| 1 | 3.954 | -0.7472 | -1.245 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 3.954 | 5 | 4.564 | 0.3726 | 5 | 3.954 | decreciente |
| `posicion` | -0.7472 | 1 | 0.238 | 0.5836 | 1 | -0.7472 | decreciente |
| `velocidad` | -2.433 | 0 | -1.736 | 0.6709 | 0 | -1.245 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 4.564 J, deriva total = 1.046 J (22.92%) en 1 s — elevada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La solucion analitica del oscilador subamortiguado a t=1s es x(1) ≈ e^(-0.1415) * cos(2.58) ≈ 0.868 * (-0.839) ≈ -0.728 m. RK4 con h=0.01 debe reproducir este valor con error menor a ±0.05 m. Si el resultado es muy diferente, el codegen ha generado coeficientes de ODE incorrectos para los parametros masa/amortiguacion/rigidez.
