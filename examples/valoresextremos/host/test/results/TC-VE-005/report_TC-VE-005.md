# TC-VE-005 — u=2.0 — por encima de saturacion

## Descripcion del test

y_sat=1.0 (saturado), y_sqrt≈1.414, y_log≈0.693.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=2.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sat` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `y_sqrt` final: esperado 1.4142±0.001, obtenido 1.41421 |
| ✅ | `y_log` final: esperado 0.6931±0.001, obtenido 0.693147 |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 2 | 1 | 0.5 | 0.6931 | 1 | 1.414 |
| 0.1 | 2 | 1 | 0.5 | 0.6931 | 1 | 1.414 |
| 0.2 | 2 | 1 | 0.5 | 0.6931 | 1 | 1.414 |
| 0.1 | 2 | 1 | 0.5 | 0.6931 | 1 | 1.414 |
| 0.2 | 2 | 1 | 0.5 | 0.6931 | 1 | 1.414 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `y_log` | 0.6931 | 0.6931 | 0.6931 | 0 | 0.6931 | 0.6931 | constante |
| `y_sat` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_sqrt` | 1.414 | 1.414 | 1.414 | 0 | 1.414 | 1.414 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=2, `es_finito`=1, `y_inv`=0.5, `y_log`=0.6931, `y_sat`=1, `y_sqrt`=1.414 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `y_sat`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

u=2.0 supera el limite superior de saturacion. y_sat=1.0 (recortado). y_sqrt=sqrt(2)≈1.414, y_log=ln(2)≈0.693 son valores estandar reconocibles. Verifica que la saturacion opera correctamente y que las operaciones no-saturadas dan resultados esperados.
