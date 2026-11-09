# TC-CED-006 — Fallo de sobrevidbracion — prioridad 1

## Descripcion del test

vibracion=0.80 supera el umbral de 0.75. Debe activarse codigo 303 con prioridad 1 (la mas baja).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.5`  
`tension=0.8`  
`vibracion=0.8`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 303±0, obtenido 303 |
| ✅ | `nivel_prioridad` final: esperado 1±0, obtenido 1 |
| ✅ | `parada_emergencia` final: esperado 0±0, obtenido 0 |
| ✅ | `factor_reduccion` final: esperado 0.75±1e-09, obtenido 0.75 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.8 | 0.8 | 0.75 | 303 | 0 | 1 |
| 0.1 | 0.5 | 0.8 | 0.8 | 0.75 | 303 | 0 | 1 |
| 0.2 | 0.5 | 0.8 | 0.8 | 0.75 | 303 | 0 | 1 |
| 0.1 | 0.5 | 0.8 | 0.8 | 0.75 | 303 | 0 | 1 |
| 0.2 | 0.5 | 0.8 | 0.8 | 0.75 | 303 | 0 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `tension` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `vibracion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `factor_reduccion` | 0.75 | 0.75 | 0.75 | 0 | 0.75 | 0.75 | constante |
| `codigo_error` | 303 | 303 | 303 | 0 | 303 | 303 | constante |
| `parada_emergencia` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `nivel_prioridad` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.5, `tension`=0.8, `vibracion`=0.8, `factor_reduccion`=0.75, `codigo_error`=303, `parada_emergencia`=0, `nivel_prioridad`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parada_emergencia`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `nivel_prioridad`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

La sobrevidbracion activa el codigo 303 con la prioridad mas baja del sistema (nivel 1). No se activa parada de emergencia y el factor de reduccion es 0.75, indicando una reduccion moderada del 25%. Esto refleja que la vibracion es un indicador menos critico que la temperatura o la tension.
