# TC-CS-004 — Entradas negativas — producto positivo

## Descripcion del test

u1=-3.0, u2=-1.0: producto positivo, active=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=-3.0`  
`u2=-1.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado -4.0±1e-09, obtenido -4 |
| ✅ | `y_prod` final: esperado 3.0±1e-09, obtenido 3 |
| ✅ | `active` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | -3 | -1 | 0 | 3 | -4 |
| 0.1 | -3 | -1 | 0 | 3 | -4 |
| 0.2 | -3 | -1 | 0 | 3 | -4 |
| 0.4 | -3 | -1 | 0 | 3 | -4 |
| 0.5 | -3 | -1 | 0 | 3 | -4 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | -3 | -3 | -3 | 0 | -3 | -3 | constante |
| `u2` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `y_sum` | -4 | -4 | -4 | 0 | -4 | -4 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=-3, `u2`=-1, `active`=0, `y_prod`=3, `y_sum`=-4 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Entradas negativas: -3 + (-1) = -4 (suma negativa), (-3)*(-1) = 3 (producto positivo por regla de signos). active=false porque -3 < -1. Este test verifica el manejo correcto de signos en ambas operaciones.
