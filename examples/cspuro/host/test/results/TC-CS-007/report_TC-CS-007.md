# TC-CS-007 — Signo mixto — u1 negativo, u2 positivo

## Descripcion del test

u1=-2.0, u2=3.0: producto=-6, active=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=-2.0`  
`u2=3.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `y_prod` final: esperado -6.0±1e-09, obtenido -6 |
| ✅ | `active` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | -2 | 3 | 0 | -6 | 1 |
| 0.1 | -2 | 3 | 0 | -6 | 1 |
| 0.2 | -2 | 3 | 0 | -6 | 1 |
| 0.4 | -2 | 3 | 0 | -6 | 1 |
| 0.5 | -2 | 3 | 0 | -6 | 1 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | -2 | -2 | -2 | 0 | -2 | -2 | constante |
| `u2` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | -6 | -6 | -6 | 0 | -6 | -6 | constante |
| `y_sum` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=-2, `u2`=3, `active`=0, `y_prod`=-6, `y_sum`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y_sum`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Operandos de signo opuesto. El producto es negativo (-2 * 3 = -6), la suma es positiva (-2 + 3 = 1). active=false porque -2 < 3. Verifica el camino de datos con producto negativo en fmi2GetReal.
