# TC-CS-002 — Valores iguales — limite estricto de active

## Descripcion del test

u1=5.0, u2=5.0: active=false (> es estricto).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=5.0`  
`u2=5.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 10.0±1e-09, obtenido 10 |
| ✅ | `y_prod` final: esperado 25.0±1e-09, obtenido 25 |
| ✅ | `active` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 5 | 5 | 0 | 25 | 10 |
| 0.1 | 5 | 5 | 0 | 25 | 10 |
| 0.2 | 5 | 5 | 0 | 25 | 10 |
| 0.4 | 5 | 5 | 0 | 25 | 10 |
| 0.5 | 5 | 5 | 0 | 25 | 10 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `u2` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 25 | 25 | 25 | 0 | 25 | 25 | constante |
| `y_sum` | 10 | 10 | 10 | 0 | 10 | 10 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=5, `u2`=5, `active`=0, `y_prod`=25, `y_sum`=10 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con entradas iguales, la condicion u1 > u2 es falsa (0 > 0), por lo que active=false. La suma y el producto son correctos (10 y 25). Este caso limite verifica que el operador de comparacion es estrictamente mayor (>) y no mayor o igual (>=).
