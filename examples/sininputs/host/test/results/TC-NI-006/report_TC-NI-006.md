# TC-NI-006 — Energia inicial correcta

## Descripcion del test

Verifica E(0)=5.0 J = 0.5*k*x0^2 con k=10, x0=1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.001 s |
| Paso de integracion | 0.0001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.001 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia`@t=0.0: esperado 5.0±1e-06, obtenido 5 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 5 | 1 | 0 |
| 0.0001 | 5 | 1 | -0.0006667 |
| 0.0002 | 5 | 1 | -0.001333 |
| 0.0005 | 5 | 1 | -0.003333 |
| 0.0009 | 5 | 1 | -0.005999 |
| 0.001 | 5 | 1 | -0.006666 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 5 | 5 | 5 | 1.401e-09 | 5 | 5 | constante |
| `posicion` | 1 | 1 | 1 | 1.148e-06 | 1 | 1 | decreciente |
| `velocidad` | -0.006666 | 0 | -0.003333 | 0.002211 | 0 | -0.006666 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 5 J, deriva total = 4e-09 J (0.00%) en 0.001 s — excelente.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La energia inicial E0 = 0.5*k*x0^2 + 0.5*m*v0^2 = 0.5*10*1 + 0 = 5 J. Este test de precision alta verifica que la formula de energia esta implementada correctamente en la FMU desde el primer instante.
