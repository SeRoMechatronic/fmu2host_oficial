# TC-ME-006 — Ordenacion de salidas durante el transitorio

## Descripcion del test

A t=2 s: y1>y2>y3>y4>y5>y6>y7>y8 (cada etapa retrasada).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1`@t=2.0: esperado 0.865±0.02, obtenido 0.864665 |
| ✅ | `y2`@t=2.0: esperado 0.594±0.02, obtenido 0.593994 |
| ✅ | `y8`@t=2.0: esperado 0.0±0.01, obtenido 0.00109672 |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.00995 | 4.967e-05 | 1.654e-07 | 4.167e-10 | 0 | 0 |
| 0.02 | 1 | 0 | 0.0198 | 0.0001974 | 1.313e-06 | 6.567e-09 | 2.465e-11 | 6.861e-14 |
| 1 | 1 | 0 | 0.6321 | 0.2642 | 0.0803 | 0.01899 | 0.00366 | 0.0005942 |
| 1.99 | 1 | 0 | 0.8633 | 0.5913 | 0.3206 | 0.1411 | 0.05176 | 0.01621 |
| 2 | 1 | 0 | 0.8647 | 0.594 | 0.3233 | 0.1429 | 0.05265 | 0.01656 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y1` | 0 | 0.8647 | 0.567 | 0.244 | 0 | 0.8647 | creciente |
| `y2` | 0 | 0.594 | 0.2708 | 0.1905 | 0 | 0.594 | creciente |
| `y3` | 0 | 0.3233 | 0.1093 | 0.1015 | 0 | 0.3233 | creciente |
| `y4` | 0 | 0.1429 | 0.03774 | 0.04249 | 0 | 0.1429 | creciente |
| `y5` | 0 | 0.05265 | 0.01132 | 0.01475 | 0 | 0.05265 | creciente |
| `y6` | 0 | 0.01656 | 0.002989 | 0.004377 | 0 | 0.01656 | creciente |
| `y7` | 0 | 0.004534 | 0.0007032 | 0.001135 | 0 | 0.004534 | creciente |
| `y8` | 0 | 0.001097 | 0.0001489 | 0.000261 | 0 | 0.001097 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1, `todos_activos`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `todos_activos`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Durante el transitorio, cada etapa tiene menos senal que la anterior. A t=2 s: y1≈0.865 (casi convergida), y2≈0.4 (a mitad), y8≈0 (apenas llegando la senal). Este ordenamiento confirma que la cascada funciona correctamente: el buffer del estado i alimenta al estado i+1 y no hay escrituras cruzadas.
