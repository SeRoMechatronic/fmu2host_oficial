# TC-ME-007 — Entrada cero — todas las etapas permanecen en cero

## Descripcion del test

Con u=0: y1=...=y8=0, todos_activos=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1` == 0.0 siempre: OK |
| ✅ | `y8` == 0.0 siempre: OK |
| ✅ | `todos_activos` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.02 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5.01 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `todos_activos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y2` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y3` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y4` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y6` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y7` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y8` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=0, `todos_activos`=0, `y1`=0, `y2`=0, `y3`=0, `y4`=0, `y5`=0, `y6`=0, `y7`=0, `y8`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `todos_activos`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y1`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con entrada nula y estados iniciales cero, todas las etapas permanecen en cero. Verifica que no hay ruido numerico ni condiciones iniciales no nulas en ningun buffer de los 8 estados.
