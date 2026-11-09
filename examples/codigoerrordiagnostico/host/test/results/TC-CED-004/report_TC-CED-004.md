# TC-CED-004 — Fallo de subtension — prioridad 2

## Descripcion del test

tension=0.05 esta por debajo del umbral de 0.10. Debe activarse codigo 202 con prioridad 2.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.5`  
`tension=0.05`  
`vibracion=0.4`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 202±0, obtenido 202 |
| ✅ | `nivel_prioridad` final: esperado 2±0, obtenido 2 |
| ✅ | `parada_emergencia` final: esperado 0±0, obtenido 0 |
| ✅ | `factor_reduccion` final: esperado 0.5±1e-09, obtenido 0.5 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.05 | 0.4 | 0.5 | 202 | 0 | 2 |
| 0.1 | 0.5 | 0.05 | 0.4 | 0.5 | 202 | 0 | 2 |
| 0.2 | 0.5 | 0.05 | 0.4 | 0.5 | 202 | 0 | 2 |
| 0.1 | 0.5 | 0.05 | 0.4 | 0.5 | 202 | 0 | 2 |
| 0.2 | 0.5 | 0.05 | 0.4 | 0.5 | 202 | 0 | 2 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `tension` | 0.05 | 0.05 | 0.05 | 0 | 0.05 | 0.05 | constante |
| `vibracion` | 0.4 | 0.4 | 0.4 | 0 | 0.4 | 0.4 | constante |
| `factor_reduccion` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `codigo_error` | 202 | 202 | 202 | 0 | 202 | 202 | constante |
| `parada_emergencia` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `nivel_prioridad` | 2 | 2 | 2 | 0 | 2 | 2 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.5, `tension`=0.05, `vibracion`=0.4, `factor_reduccion`=0.5, `codigo_error`=202, `parada_emergencia`=0, `nivel_prioridad`=2 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parada_emergencia`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

La subtension (0.05 < 0.10) activa el codigo 202. Con prioridad 2, el sistema no ordena parada de emergencia (nivel < 3), pero reduce el factor de operacion a 0.50, lo que implica una reduccion del 50% en la potencia disponible como medida preventiva ante la alimentacion deficiente.
