# TC-ASM-008 — Overload justo por encima del umbral — acumulador sube

## Descripcion del test

carga_motor=0.91 supera el umbral por poco. Der(tiempo_sobrecarga)=1.0 y el acumulador debe crecer. Complementario al TC-007.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor=0.91`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobrecarga`@t=1.0: esperado 0±0, obtenido 0 |
| ✅ | `fallo_sobrecarga` == 0 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.91 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0.91 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0.91 | 1 | 0 | 0 | 0.0001313 |
| 0.5 | 1 | 0.91 | 1 | 0 | 0 | 0.0578 |
| 0.99 | 1 | 0.91 | 1 | 0 | 0 | 0.1649 |
| 1 | 1 | 0.91 | 1 | 0 | 0 | 0.1672 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `carga_motor` | 0.91 | 0.91 | 0.91 | 0 | 0.91 | 0.91 | constante |
| `en_rampa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_aplicada` | 0 | 0.1672 | 0.06616 | 0.05243 | 0 | 0.1672 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `orden_arranque`=1, `carga_motor`=0.91, `en_rampa`=1, `fallo_sobrecarga`=0, `motor_en_marcha`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `en_rampa`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con carga=0.91 > 0.9, la derivada del integrador es +1.0, por lo que tiempo_sobrecarga crece linealmente. A t=1s vale ~1s, por debajo del umbral de 2s. Si se mantuviera la sobrecarga hasta t=2s, dispararia. Este test contrasta con TC-007 para verificar la logica de borde.
