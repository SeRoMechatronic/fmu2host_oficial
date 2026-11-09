# TC-SIO-007 — Valor maximo practico — alarm=true, sin desbordamiento

## Descripcion del test

value=200.0 (maximo del rango): alarm=true, scaled_value=300.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=200.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 300.0±1e-09, obtenido 300 |
| ✅ | `alarm` final: esperado 1±0, obtenido 1 |
| ✅ | `scaled_value` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 200 |  |  | 300 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0.1 | 200 |  |  | 300 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0 | 200 |  |  | 300 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0.1 | 200 |  |  | 300 | 1 | ALERT: value above upper limit (100.0) | HIGH |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 200 | 200 | 200 | 0 | 200 | 200 | constante |
| `scaled_value` | 300 | 300 | 300 | 0 | 300 | 300 | constante |
| `alarm` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=200, `scaled_value`=300, `alarm`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

value=200 (maximo del rango documentado). scaled_value=300.0, que es exactamente representable en double. alarm=TRUE (200 > 100). Verifica que la escala 1.5x no desborda para valores grandes dentro del rango de operacion. scaled_value no debe ser NaN ni Inf.
