# TC-VE-009 — u=100 — valor tipico positivo con resultados conocidos

## Descripcion del test

y_inv=0.01, y_sqrt=10, y_log≈4.605, y_sat=1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=100.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` final: esperado 0.01±1e-09, obtenido 0.01 |
| ✅ | `y_sqrt` final: esperado 10.0±1e-06, obtenido 10 |
| ✅ | `y_log` final: esperado 4.6052±0.001, obtenido 4.60517 |
| ✅ | `y_sat` final: esperado 1.0±1e-09, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 100 | 1 | 0.01 | 4.605 | 1 | 10 |
| 0.1 | 100 | 1 | 0.01 | 4.605 | 1 | 10 |
| 0.2 | 100 | 1 | 0.01 | 4.605 | 1 | 10 |
| 0.1 | 100 | 1 | 0.01 | 4.605 | 1 | 10 |
| 0.2 | 100 | 1 | 0.01 | 4.605 | 1 | 10 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 100 | 100 | 100 | 0 | 100 | 100 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | 0.01 | 0.01 | 0.01 | 0 | 0.01 | 0.01 | constante |
| `y_log` | 4.605 | 4.605 | 4.605 | 0 | 4.605 | 4.605 | constante |
| `y_sat` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_sqrt` | 10 | 10 | 10 | 0 | 10 | 10 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=100, `es_finito`=1, `y_inv`=0.01, `y_log`=4.605, `y_sat`=1, `y_sqrt`=10 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `y_sat`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Valores reconocibles con u=100: 1/100=0.01, sqrt(100)=10, ln(100)=2*ln(10)≈4.6052. y_sat=1.0 (saturado, 100>>1). Este test con valores exactos reconocibles detecta errores de implementacion (ej. log base 10 en lugar de natural, o sqrt(u^2) en lugar de sqrt(u)).
