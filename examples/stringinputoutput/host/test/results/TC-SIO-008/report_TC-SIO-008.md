# TC-SIO-008 — Cambio de valor que cruza todas las fronteras

## Descripcion del test

value: 55→120→5→55. alarm alterna false→true→true→false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 4.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`value=55.0`  
`value`: t=0: 55.0, t=1.0: 120.0, t=2.0: 5.0, t=3.0: 55.0

## Simulacion: ME-RK4

- Pasos simulados: 5  |  Tiempo total: 4 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarm`@t=0.5: esperado 0±0, obtenido 0 |
| ✅ | `alarm`@t=1.5: esperado 1±0, obtenido 1 |
| ✅ | `alarm`@t=2.5: esperado 1±0, obtenido 1 |
| ✅ | `alarm`@t=3.5: esperado 0±0, obtenido 0 |
| ✅ | `scaled_value`@t=1.5: esperado 180.0±1e-09, obtenido 180 |
| ✅ | `scaled_value`@t=2.5: esperado 7.5±1e-09, obtenido 7.5 |

### Muestra de datos (inicio / mitad / final)

| t | value | mode_operation | tag_sensor | scaled_value | alarm | alert_msg | status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 55 |  |  | 82.5 | 0 |  | NORMAL |
| 1 | 120 |  |  | 180 | 1 | ALERT: value above upper limit (100.0) | HIGH |
| 2 | 5 |  |  | 7.5 | 1 | ALERT: value below lower limit (10.0) | LOW |
| 3 | 55 |  |  | 82.5 | 0 |  | NORMAL |
| 4 | 55 |  |  | 82.5 | 0 |  | NORMAL |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `value` | 5 | 120 | 58 | 40.87 | 55 | 55 | decreciente |
| `scaled_value` | 7.5 | 180 | 87 | 61.3 | 82.5 | 82.5 | decreciente |
| `alarm` | 0 | 1 | 0.4 | 0.5477 | 0 | 0 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 6 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Dinamica rapida** en `value`: tasa de cambio maxima = 115 unidades/s.
**Dinamica rapida** en `scaled_value`: tasa de cambio maxima = 172.5 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (6 checks OK, 0 FAIL)

value cambia entre los tres estados: NORMAL (55), HIGH (120), LOW (5). alarm=F en t=0.5 (NORMAL), T en t=1.5 (HIGH), T en t=2.5 (LOW), F en t=3.5. scaled_value: 180 cuando HIGH, 7.5 cuando LOW. Verifica que las ramas condicionales se reevaluan en cada paso de simulacion, no solo en la inicializacion.
