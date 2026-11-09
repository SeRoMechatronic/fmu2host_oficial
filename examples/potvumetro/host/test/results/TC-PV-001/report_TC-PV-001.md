# TC-PV-001 — Todos los LEDs apagados — por debajo del primer umbral

## Descripcion del test

pot=0.0: ningun LED debe activarse.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led1` final: esperado 0±0, obtenido 0 |
| ✅ | `led2` final: esperado 0±0, obtenido 0 |
| ✅ | `led3` final: esperado 0±0, obtenido 0 |
| ✅ | `led4` final: esperado 0±0, obtenido 0 |
| ✅ | `led5` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led2` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led3` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led4` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=0, `led1`=0, `led2`=0, `led3`=0, `led4`=0, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `pot`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `led1`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `led2`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Con el potenciometro en posicion minima (0.0), ningun LED debe encenderse. Todos los umbrales (0.2, 0.4, 0.6, 0.8, 1.0) son mayores que 0.0. Este es el estado de reposo del vumeter: barra vacia.
