# TC-CED-002 — Fallo de sobretemperatura — prioridad maxima

## Descripcion del test

temperatura=0.90 supera el umbral de 0.85. Debe activarse codigo 101 con prioridad 3 y parada de emergencia.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.9`  
`tension=0.8`  
`vibracion=0.4`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 101±0, obtenido 101 |
| ✅ | `nivel_prioridad` final: esperado 3±0, obtenido 3 |
| ✅ | `parada_emergencia` final: esperado 1±0, obtenido 1 |
| ✅ | `factor_reduccion` final: esperado 0.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.8 | 0.4 | 0 | 101 | 1 | 3 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `tension` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `vibracion` | 0.4 | 0.4 | 0.4 | 0 | 0.4 | 0.4 | constante |
| `factor_reduccion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `codigo_error` | 101 | 101 | 101 | 0 | 101 | 101 | constante |
| `parada_emergencia` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `nivel_prioridad` | 3 | 3 | 3 | 0 | 3 | 3 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.9, `tension`=0.8, `vibracion`=0.4, `factor_reduccion`=0, `codigo_error`=101, `parada_emergencia`=1, `nivel_prioridad`=3 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `factor_reduccion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `parada_emergencia`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

La sobretemperatura (0.90 > 0.85) activa el fallo de maxima prioridad. El codigo 101 indica alarma termica, el nivel 3 es el mas alto posible, la parada de emergencia se activa inmediatamente, y el factor de reduccion cae a 0.0, cortando completamente la potencia. Este es el escenario mas critico del sistema de diagnostico.
