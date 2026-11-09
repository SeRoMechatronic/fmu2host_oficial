# TC-NI-008 — Posicion acotada durante oscilacion

## Descripcion del test

La amplitud amortiguada no debe exceder el valor inicial de 1.0 m.

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
| ✅ | `posicion` en [-1.01, 1.01]: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.01 | 5 | 0.9997 | -0.06659 |
| 0.02 | 5 | 0.9987 | -0.133 |
| 2.51 | 3.071 | 0.7694 | -0.3851 |
| 5 | 1.884 | 0.5807 | -0.5136 |
| 5 | 1.884 | 0.5807 | -0.5136 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 1.884 | 5 | 3.169 | 0.9322 | 5 | 1.884 | decreciente |
| `posicion` | -0.8853 | 1 | 0.02058 | 0.5687 | 1 | 0.5807 | oscilante  (4 cruces cero, ~0.4 Hz) |
| `velocidad` | -2.433 | 2.154 | -0.08505 | 1.438 | 0 | -0.5136 | oscilante  (4 cruces cero, ~0.4 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 3.169 J, deriva total = 3.116 J (98.34%) en 5 s — elevada.
**Oscilacion** de `posicion`: amplitud ~0.9427, frecuencia estimada ~0.4 Hz (4 cruces de cero en 5 s).
**Oscilacion** de `velocidad`: amplitud ~2.294, frecuencia estimada ~0.4 Hz (4 cruces de cero en 5 s).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Con amortiguamiento positivo, la amplitud nunca debe superar la amplitud inicial x0=1.0 m. El sistema oscila con amplitud decreciente. Si la posicion supera 1.01 m (con tolerancia del 1%), el integrador esta ganando energia artificialmente, lo que indica un error de implementacion del ODE solver.
