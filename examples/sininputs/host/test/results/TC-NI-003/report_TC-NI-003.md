# TC-NI-003 — Posicion cruza el cero al menos 4 veces (oscilacion subamortiguada)

## Descripcion del test

ζ≈0.055 implica oscilacion. La posicion debe cambiar de signo varias veces.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` cambios de signo: 8 (minimo 4): OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.01 | 5 | 0.9997 | -0.06659 |
| 0.02 | 5 | 0.9987 | -0.133 |
| 5.01 | 1.883 | 0.5754 | -0.5511 |
| 10 | 0.703 | 0.2977 | -0.5886 |
| 10 | 0.703 | 0.2977 | -0.5886 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 0.703 | 5 | 2.168 | 1.224 | 5 | 0.703 | decreciente |
| `posicion` | -0.8853 | 1 | 0.01186 | 0.4681 | 1 | 0.2977 | oscilante  (8 cruces cero, ~0.4 Hz) |
| `velocidad` | -2.433 | 2.154 | -0.07097 | 1.194 | 0 | -0.5886 | oscilante  (8 cruces cero, ~0.4 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 2.168 J, deriva total = 4.297 J (198.23%) en 10 s — elevada.
**Oscilacion** de `posicion`: amplitud ~0.9427, frecuencia estimada ~0.4 Hz (8 cruces de cero en 10 s).
**Oscilacion** de `velocidad`: amplitud ~2.294, frecuencia estimada ~0.4 Hz (8 cruces de cero en 10 s).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Con razon de amortiguacion ζ≈0.055, el sistema es claramente subamortiguado. El periodo amortiguado es T≈2.43 s, por lo que en 10 s deben ocurrir al menos 4 cruces por cero. Si el sistema fuera criticamente amortiguado (por error de parametros), no oscilaria y este test fallaria.
