# TC-VE-003 — u=1.0 — valor nominal: todas las operaciones validas

## Descripcion del test

y_inv=1, y_sqrt=1, y_log=0, y_sat=1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `y_sqrt` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `y_log` final: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `y_sat` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `es_finito` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.1 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.2 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.1 | 1 | 1 | 1 | 0 | 1 | 1 |
| 0.2 | 1 | 1 | 1 | 0 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_log` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_sat` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_sqrt` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1, `es_finito`=1, `y_inv`=1, `y_log`=0, `y_sat`=1, `y_sqrt`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `y_inv`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Con u=1.0, todas las operaciones son bien definidas: 1/1=1, sqrt(1)=1, ln(1)=0. y_sat=1.0 (exactamente en el limite superior de saturacion). Este caso nominal verifica que las guardas no disparan falsamente para valores normales.
