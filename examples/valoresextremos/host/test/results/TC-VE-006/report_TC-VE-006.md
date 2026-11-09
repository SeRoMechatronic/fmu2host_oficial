# TC-VE-006 — u=-10.0 — saturacion profunda negativa

## Descripcion del test

y_sat=-1 (saturado abajo), y_inv=-0.1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=-10.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` final: esperado -0.1±1e-09, obtenido -0.1 |
| ✅ | `y_sqrt` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `y_sat` final: esperado -1.0±1e-09, obtenido -1 |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | -10 | 1 | -0.1 | -1e+30 | -1 | 0 |
| 0.1 | -10 | 1 | -0.1 | -1e+30 | -1 | 0 |
| 0.2 | -10 | 1 | -0.1 | -1e+30 | -1 | 0 |
| 0.1 | -10 | 1 | -0.1 | -1e+30 | -1 | 0 |
| 0.2 | -10 | 1 | -0.1 | -1e+30 | -1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | -10 | -10 | -10 | 0 | -10 | -10 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | -0.1 | -0.1 | -0.1 | 0 | -0.1 | -0.1 | constante |
| `y_log` | -1e+30 | -1e+30 | -1e+30 | 0 | -1e+30 | -1e+30 | constante |
| `y_sat` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `y_sqrt` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=-10, `es_finito`=1, `y_inv`=-0.1, `y_log`=-1e+30, `y_sat`=-1, `y_sqrt`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `y_sqrt`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Entrada muy negativa: saturacion al limite inferior. 1/(-10)=-0.1 sigue siendo valido (lejos de cero). sqrt y log protegidos. Verifica el comportamiento consistente para valores grandes negativos.
