# TC-PV-007 — Justo encima umbral LED4 — pot=0.81

## Descripcion del test

pot=0.81 (por encima de 0.80) activa LED1 a LED4.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=0.81`

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
| 0 | 0.81 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 0.81 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 0.81 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 0.81 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 0.81 | 1 | 1 | 1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 0.81 | 0.81 | 0.81 | 0 | 0.81 | 0.81 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led4` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=0.81, `led1`=1, `led2`=1, `led3`=1, `led4`=1, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led3`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Cuatro LEDs encendidos con pot=0.81 (justo encima del umbral LED4=0.80). El LED5 (rojo, pico) no se activa porque 0.81 < 1.0. Nivel maximo sin alarma de pico.
