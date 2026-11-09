# TC-SIO-006 — Valor cero — alarm=true (por debajo del minimo)

## Descripcion del test

value=0.0: alarm=true (0 < 10), scaled_value=0.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `alarm` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 |  |  | 0 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | 0 |  |  | 0 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0 | 0 |  |  | 0 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | 0 |  |  | 0 | 1 | ALERT: value below lower limit (10.0) | LOW |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `scaled_value` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarm` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=0, `scaled_value`=0, `alarm`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `value`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `scaled_value`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarm`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

value=0: scaled_value=0*1.5=0.0. alarm=TRUE (0 < 10). Status='LOW'. Verifica que scaled_value maneja correctamente el cero (sin multiplicacion erronea). Las entradas String de modo e identificador tienen sus valores por defecto del modelo — el calculo solo depende de 'value'.
