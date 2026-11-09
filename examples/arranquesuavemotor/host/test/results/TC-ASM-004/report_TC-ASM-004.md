# TC-ASM-004 — Stop command — tension decae tras parada

## Descripcion del test

Motor arrancado de t=0 a t=10s, luego orden de parada. A t=13s (3s tras la parada = 1 tau_rampa) la tension debe haber caido significativamente. Verifica el arranque suave inverso (rampa de bajada).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 13.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`carga_motor=0.0`  
`orden_arranque`: t=0: 1, t=10.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 1302  |  Tiempo total: 13 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada`@t=10.0: esperado 0.964±0.05, obtenido 0.957191 |
| ✅ | `tension_aplicada`@t=13.0: esperado 0.35±0.12, obtenido 0.426675 |
| ✅ | `motor_en_marcha`@t=13.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0 | 1 | 0 | 0 | 0.0001313 |
| 6.51 | 1 | 0 | 1 | 0 | 0 | 0.863 |
| 13 | 0 | 0 | 0 | 0 | 0 | 0.4267 |
| 13 | 0 | 0 | 0 | 0 | 0 | 0.4267 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 0 | 1 | 0.7688 | 0.4218 | 1 | 0 | decreciente |
| `carga_motor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_rampa` | 0 | 1 | 0.573 | 0.4948 | 1 | 0 | decreciente |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 1 | 0.1959 | 0.397 | 0 | 0 | creciente |
| `tension_aplicada` | 0 | 0.9575 | 0.6709 | 0.2655 | 0 | 0.4267 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `orden_arranque`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `en_rampa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `motor_en_marcha`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `carga_motor`=0, `fallo_sobrecarga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `orden_arranque`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `en_rampa`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Al desactivar la orden a t=10s, la referencia pasa a 0 y la rampa decae con tau=3s. A t=13s han transcurrido 3s = 1 tau, por lo que la rampa habrá decaído en 1-e^-1=63%, quedando en ~36%. El filtro PT1 (tau=0.5s) sigue la rampa casi instantaneamente. Motor_en_marcha se desactiva inmediatamente al quitar la orden, confirmando la semantica booleana directa.
