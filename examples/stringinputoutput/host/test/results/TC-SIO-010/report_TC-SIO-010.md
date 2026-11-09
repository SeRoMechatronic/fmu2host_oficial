# TC-SIO-010 — Valor negativo — alarm=true, scaled_value negativo

## Descripcion del test

value=-5.0: alarm=true (-5 < 10), scaled_value=-7.5.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=-5.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado -7.5±1e-09, obtenido -7.5 |
| ✅ | `alarm` final: esperado 1±0, obtenido 1 |
| ✅ | `scaled_value` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | -5 |  |  | -7.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | -5 |  |  | -7.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0 | -5 |  |  | -7.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | -5 |  |  | -7.5 | 1 | ALERT: value below lower limit (10.0) | LOW |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | -5 | -5 | -5 | 0 | -5 | -5 | constante |
| `scaled_value` | -7.5 | -7.5 | -7.5 | 0 | -7.5 | -7.5 | constante |
| `alarm` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=-5, `scaled_value`=-7.5, `alarm`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

value=-5 (fuera del rango documentado por abajo): scaled_value=-5*1.5=-7.5. alarm=TRUE (-5 < 10). Verifica que scaled_value maneja valores negativos correctamente (sin aplicar abs()). Status='LOW'. Un codegen que trunca scaled_value a [0, inf) daria 0 en lugar de -7.5.
