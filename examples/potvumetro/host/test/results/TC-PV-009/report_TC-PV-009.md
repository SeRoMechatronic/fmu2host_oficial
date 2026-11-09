# TC-PV-009 — Escala completa — LED1-LED4 encendidos, LED5 por hysteresis

## Descripcion del test

pot=1.0 enciende LED1-LED4; LED5 (umbral>=1.0) no dispara con input estatico.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led1` final: esperado 1±0, obtenido 1 |
| ✅ | `led2` final: esperado 1±0, obtenido 1 |
| ✅ | `led3` final: esperado 1±0, obtenido 1 |
| ✅ | `led4` final: esperado 1±0, obtenido 1 |
| ✅ | `led5` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 1 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 1 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 1 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 1 | 1 | 1 | 1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led4` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=1, `led1`=1, `led2`=1, `led3`=1, `led4`=1, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `pot`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Con pot=1.0 (maximo del rango declarado [0,1]), LED1-LED4 se activan. LED5 (umbral >= 1.0) NO se activa con input estatico exactamente en el umbral, por la implementacion de relationhysteresis del FMU: requiere cruzar el umbral desde abajo. Para activar LED5 usar pot > 1.0 (ver TC-PV-012 con pot=1.5).
