# TC-SIO-002 — Valor por encima del limite superior — alarm=true

## Descripcion del test

value=150.0: scaled_value=225.0, alarm=true (150 > 100).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=150.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 225.0±1e-09, obtenido 225 |
| ✅ | `alarm` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 150 |  |  | 225 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0.1 | 150 |  |  | 225 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0 | 150 |  |  | 225 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 0.1 | 150 |  |  | 225 | 1 | ALERT: value above upper limit (100.0) | HIGH |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 150 | 150 | 150 | 0 | 150 | 150 | constante |
| `scaled_value` | 225 | 225 | 225 | 0 | 225 | 225 | constante |
| `alarm` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=150, `scaled_value`=225, `alarm`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

value=150 > 100 (limite superior): alarm=TRUE, status='HIGH'. scaled_value=150*1.5=225.0. El String alert_msg sera 'ALERT: value above upper limit (100.0)'. Verifica la rama HIGH de la logica condicional y que la alarma se activa con valor supraumbral.
