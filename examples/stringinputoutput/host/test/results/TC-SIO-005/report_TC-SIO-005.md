# TC-SIO-005 — Ligeramente por encima del umbral inferior — value=10.1, NORMAL

## Descripcion del test

value=10.1 > umbral inferior 10.0: alarm=false, scaled_value=15.15. El valor exacto 10.0 dispara hysteresis en OpenModelica FMU.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=10.1`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 15.15±0.01, obtenido 15.15 |
| ✅ | `alarm` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 10.1 |  |  | 15.15 | 0 |  | NORMAL |
| 0.1 | 10.1 |  |  | 15.15 | 0 |  | NORMAL |
| 0 | 10.1 |  |  | 15.15 | 0 |  | NORMAL |
| 0.1 | 10.1 |  |  | 15.15 | 0 |  | NORMAL |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 10.1 | 10.1 | 10.1 | 0 | 10.1 | 10.1 | constante |
| `scaled_value` | 15.15 | 15.15 | 15.15 | 0 | 15.15 | 15.15 | constante |
| `alarm` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=10.1, `scaled_value`=15.15, `alarm`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

value=10.0 exacto. La condicion LOW es 'value < 10.0' (estricto). 10.0 NO es menor que 10.0 → NORMAL, alarm=FALSE. scaled_value=15.0. Simetrico a TC-SIO-004. Verifica ambas fronteras de la zona NORMAL con operadores estrictos.
