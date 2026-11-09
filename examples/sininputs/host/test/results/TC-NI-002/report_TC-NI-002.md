# TC-NI-002 — Energia monotonamente decreciente

## Descripcion del test

Con amortiguacion positiva, la energia debe decrecer estrictamente.

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
| ✅ | `energia` monotona decreciente: OK |

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

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 1.232 J, deriva total = 4.907 J (398.42%) en 20 s — elevada.
**Oscilacion** de `posicion`: amplitud ~0.9427, frecuencia estimada ~0.4 Hz (16 cruces de cero en 20 s).
**Oscilacion** de `velocidad`: amplitud ~2.294, frecuencia estimada ~0.4 Hz (16 cruces de cero en 20 s).
**Convergencia** de `energia`: valor final = 0.09345 (arranca en 5, delta = 4.907).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El amortiguador disipa energia continuamente. Con c=0.3 N·s/m y ζ≈0.055, el sistema es subamortiguado y oscila mientras la energia decrece. Cualquier aumento de energia indicaria un error del integrador. RK4 con h=0.01 mantiene la monotonia energetica para este sistema.
