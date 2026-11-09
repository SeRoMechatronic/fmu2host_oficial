# TC-NI-001 — Condiciones iniciales en t=0

## Descripcion del test

Verifica posicion=1.0, velocidad=0.0, energia=5.0 en t=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion`@t=0.0: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `velocidad`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `energia`@t=0.0: esperado 5.0±0.001, obtenido 5 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.001 | 5 | 1 | -0.006666 |
| 0.002 | 5 | 1 | -0.01333 |
| 0.005 | 5 | 0.9999 | -0.03332 |
| 0.009 | 5 | 0.9997 | -0.05994 |
| 0.01 | 5 | 0.9997 | -0.06659 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 5 | 5 | 5 | 1.503e-06 | 5 | 5 | decreciente |
| `posicion` | 0.9997 | 1 | 0.9999 | 0.0001147 | 1 | 0.9997 | decreciente |
| `velocidad` | -0.06659 | 0 | -0.03331 | 0.02209 | 0 | -0.06659 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 5 J, deriva total = 4.437e-06 J (0.00%) en 0.01 s — excelente.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El sistema arranca desde x0=1.0 m con velocidad nula. La energia inicial es 0.5*k*x0^2 = 0.5*10*1^2 = 5.0 J. Este test confirma que el codegen no necesita llamadas fmi2Set* para un FMU sin entradas y que las condiciones iniciales se leen correctamente de la FMU.
