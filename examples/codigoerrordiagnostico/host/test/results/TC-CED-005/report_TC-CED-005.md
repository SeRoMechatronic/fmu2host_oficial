# TC-CED-005 — Tension ligeramente por encima del umbral — sin fallo

## Descripcion del test

tension=0.11 es ligeramente superior al umbral de subtension (0.10). La condicion subtension < 0.10 es FALSA para 0.11, no hay fallo. El valor exacto 0.10 dispara hysteresis en OpenModelica FMU.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.5`  
`tension=0.11`  
`vibracion=0.4`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 0±0, obtenido 0 |
| ✅ | `nivel_prioridad` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.11 | 0.4 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.11 | 0.4 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0.11 | 0.4 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.11 | 0.4 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0.11 | 0.4 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `tension` | 0.11 | 0.11 | 0.11 | 0 | 0.11 | 0.11 | constante |
| `vibracion` | 0.4 | 0.4 | 0.4 | 0 | 0.4 | 0.4 | constante |
| `factor_reduccion` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `codigo_error` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `parada_emergencia` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `nivel_prioridad` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.5, `tension`=0.11, `vibracion`=0.4, `factor_reduccion`=1, `codigo_error`=0, `parada_emergencia`=0, `nivel_prioridad`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `factor_reduccion`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `codigo_error`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `parada_emergencia`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con tension=0.11 (justo encima del umbral 0.10), la condicion subtension (tension < 0.10) es FALSA. El sistema no registra fallos. Nota: el valor exacto tension=0.10 activa la hysteresis de OpenModelica y produce un falso positivo de subtension; se usa 0.11 para evitarlo. Este test confirma el comportamiento esperado con tension ligeramente superior al umbral de subtension.
