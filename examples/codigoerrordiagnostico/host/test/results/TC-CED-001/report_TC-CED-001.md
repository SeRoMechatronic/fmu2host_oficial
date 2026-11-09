# TC-CED-001 — Todos los canales nominales — sin fallo

## Descripcion del test

Con todos los canales dentro de sus rangos normales, el sistema no debe reportar ningun error. codigo_error=0 y nivel_prioridad=0.

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
`vibracion=0.4`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 0±0, obtenido 0 |
| ✅ | `nivel_prioridad` final: esperado 0±0, obtenido 0 |
| ✅ | `parada_emergencia` final: esperado 0±0, obtenido 0 |
| ✅ | `factor_reduccion` final: esperado 1.0±1e-09, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.8 | 0.4 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.8 | 0.4 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0.8 | 0.4 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.8 | 0.4 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0.8 | 0.4 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `tension` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `vibracion` | 0.4 | 0.4 | 0.4 | 0 | 0.4 | 0.4 | constante |
| `factor_reduccion` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `codigo_error` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `parada_emergencia` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `nivel_prioridad` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.5, `tension`=0.8, `vibracion`=0.4, `factor_reduccion`=1, `codigo_error`=0, `parada_emergencia`=0, `nivel_prioridad`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `factor_reduccion`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `codigo_error`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `parada_emergencia`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El sistema opera en condicion nominal. Temperatura (0.50) esta bien por debajo del umbral de 0.85, la tension (0.80) supera el minimo de 0.10, y la vibracion (0.40) no supera 0.75. El resultado es codigo 0 con factor de reduccion 1.0, confirmando que el cascade de prioridades funciona correctamente cuando no hay ningun fallo activo.
