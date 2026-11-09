# TC-ASM-010 — Stop during ramp — en_rampa desactiva inmediatamente

## Descripcion del test

Motor arrancando (t=0..2s), luego parada a t=2s mientras la tension aun esta en rampa. En_rampa debe desactivarse inmediatamente al quitar la orden, aunque la tension tarde en decaer.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 4.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`carga_motor=0.0`  
`orden_arranque`: t=0: 1, t=2.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 402  |  Tiempo total: 4 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada`@t=2.0: esperado 0.388±0.04, obtenido 0.387563 |
| ✅ | `en_rampa`@t=2.1: esperado 0±0, obtenido 0 |
| ✅ | `tension_aplicada` > 0.0 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0 | 1 | 0 | 0 | 0.0001313 |
| 2.01 | 0 | 0 | 0 | 0 | 0 | 0.3895 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0.2962 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0.2962 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 0 | 1 | 0.4975 | 0.5006 | 1 | 0 | decreciente |
| `carga_motor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_rampa` | 0 | 1 | 0.4975 | 0.5006 | 1 | 0 | decreciente |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_aplicada` | 0 | 0.4229 | 0.2753 | 0.137 | 0 | 0.2962 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `orden_arranque`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `en_rampa`: valor final = 0 (arranca en 1, delta = 1).
**Variables algebraicas constantes:** `carga_motor`=0, `fallo_sobrecarga`=0, `motor_en_marcha`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `motor_en_marcha`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `orden_arranque`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `en_rampa`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

La salida en_rampa es una funcion logica directa de orden_arranque: se desactiva en el mismo ciclo en que la orden se retira. En cambio, la tension_aplicada tiene memoria (estados continuos) y continua decayendo durante varios segundos. Este test verifica la diferencia entre la respuesta instantanea de outputs discretos y la inercia de los estados continuos.
