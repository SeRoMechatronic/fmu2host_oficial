# TC-CS-005 — Entradas cero — sin division ni NaN

## Descripcion del test

u1=0.0, u2=0.0: suma=0, producto=0, active=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=0.0`  
`u2=0.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `y_prod` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `active` final: esperado 0±0, obtenido 0 |
| ✅ | `y_sum` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0 | 0 | 0 | 0 | 0 |
| 0.4 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `u2` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_sum` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=0, `u2`=0, `active`=0, `y_prod`=0, `y_sum`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u1`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `u2`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El caso de ceros verifica que no hay division por cero ni NaN. El modelo solo realiza suma y multiplicacion, operaciones seguras con cero. active=false porque 0 no es > 0.
