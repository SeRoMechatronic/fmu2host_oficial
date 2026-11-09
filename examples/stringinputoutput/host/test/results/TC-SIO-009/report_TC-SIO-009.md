# TC-SIO-009 — Estabilidad — alarm siempre correcta en simulacion larga

## Descripcion del test

value=50.0 constante durante 10 s: alarm=false siempre, scaled_value=75.0 siempre.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=50.0`

## Simulacion: ME-RK4

- Pasos simulados: 21  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarm` == 0 siempre: OK |
| ✅ | `scaled_value` == 75.0 siempre: OK |
| ✅ | `scaled_value` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 50 |  |  | 75 | 0 |  | NORMAL |
| 0.5 | 50 |  |  | 75 | 0 |  | NORMAL |
| 1 | 50 |  |  | 75 | 0 |  | NORMAL |
| 5 | 50 |  |  | 75 | 0 |  | NORMAL |
| 9.5 | 50 |  |  | 75 | 0 |  | NORMAL |
| 10 | 50 |  |  | 75 | 0 |  | NORMAL |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 50 | 50 | 50 | 0 | 50 | 50 | constante |
| `scaled_value` | 75 | 75 | 75 | 0 | 75 | 75 | constante |
| `alarm` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `value`=50, `scaled_value`=75, `alarm`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `alarm`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El modelo algebraico puro (sin estados) debe producir los mismos outputs en todos los pasos con la misma entrada. scaled_value=50*1.5=75.0 exacto en todos los pasos. alarm=FALSE siempre. Verifica la estabilidad algebraica y que los String inputs/outputs no introducen efectos residuales entre pasos.
