# TC-SIO-004 — Frontera exacta superior — value=100.0, NORMAL (operador estricto)

## Descripcion del test

value=100.0 exacto: alarm=false, scaled_value=150.0. No es HIGH (strict >).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=100.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `scaled_value` final: esperado 150.0±1e-09, obtenido 150 |
| ✅ | `alarm` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 100 |  |  | 150 | 0 |  | NORMAL |
| 0.1 | 100 |  |  | 150 | 0 |  | NORMAL |
| 0 | 100 |  |  | 150 | 0 |  | NORMAL |
| 0.1 | 100 |  |  | 150 | 0 |  | NORMAL |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 100 | 100 | 100 | 0 | 100 | 100 | constante |
| `scaled_value` | 150 | 150 | 150 | 0 | 150 | 150 | constante |
| `alarm` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=100, `scaled_value`=150, `alarm`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

value=100.0 exacto. La condicion HIGH es 'value > 100.0' (estricto). 100.0 NO es mayor que 100.0 → NORMAL, alarm=FALSE. scaled_value=150.0. Si el codegen genera >= en lugar de >, alarm=TRUE incorrectamente. Frontera critica del if/else chain.
