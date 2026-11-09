# TC-CS-001 — Valores positivos basicos — u1 > u2

## Descripcion del test

u1=3.0, u2=2.0: suma=5, producto=6, active=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=3.0`  
`u2=2.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 5.0±1e-09, obtenido 5 |
| ✅ | `y_prod` final: esperado 6.0±1e-09, obtenido 6 |
| ✅ | `active` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 3 | 2 | 0 | 6 | 5 |
| 0.1 | 3 | 2 | 1 | 6 | 5 |
| 0.2 | 3 | 2 | 1 | 6 | 5 |
| 0.4 | 3 | 2 | 1 | 6 | 5 |
| 0.5 | 3 | 2 | 1 | 6 | 5 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `u2` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `active` | 0 | 1 | 0.8333 | 0.4082 | 0 | 1 | creciente |
| `y_prod` | 6 | 6 | 6 | 0 | 6 | 6 | constante |
| `y_sum` | 5 | 5 | 5 | 0 | 5 | 5 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=3, `u2`=2, `y_prod`=6, `y_sum`=5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Caso nominal con u1 > u2. El modelo CoSimulation evalua suma y producto algebraicamente en cada paso de comunicacion. active=true porque u1=3.0 es estrictamente mayor que u2=2.0. Este test confirma que el doStep() del FMU CS funciona correctamente para el caso basico mas sencillo.
