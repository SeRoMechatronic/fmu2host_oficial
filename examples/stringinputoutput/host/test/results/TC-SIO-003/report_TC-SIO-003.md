# TC-SIO-003 — Valor por debajo del limite inferior — alarm=true

## Descripcion del test

value=3.0: scaled_value=4.5, alarm=true (3 < 10).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=3.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 4.5±1e-09, obtenido 4.5 |
| ✅ | `alarm` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 3 |  |  | 4.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | 3 |  |  | 4.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0 | 3 |  |  | 4.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 0.1 | 3 |  |  | 4.5 | 1 | ALERT: value below lower limit (10.0) | LOW |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `scaled_value` | 4.5 | 4.5 | 4.5 | 0 | 4.5 | 4.5 | constante |
| `alarm` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=3, `scaled_value`=4.5, `alarm`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

value=3 < 10 (limite inferior): alarm=TRUE, status='LOW'. scaled_value=3*1.5=4.5. El alert_msg sera 'ALERT: value below lower limit (10.0)'. Verifica la rama LOW. Si el codegen invierte el orden de evaluacion if/else, LOW podria ser tratado como HIGH o NORMAL.
