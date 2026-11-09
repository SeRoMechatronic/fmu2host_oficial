# TC-ASM-002 — Start command — en_rampa activa inmediatamente

## Descripcion del test

Al dar la orden de arranque, 'en_rampa' debe activarse y 'tension_aplicada' debe comenzar a crecer. A t=0.1s la tension ya es positiva, pero el motor no ha llegado aun al 90% necesario para declararse en marcha.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 51  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada` > 0.0 eventualmente: OK |
| ✅ | `motor_en_marcha` == 0 siempre: OK |
| ✅ | `fallo_sobrecarga` == 0 siempre: OK |
| ✅ | `tension_aplicada` >= 0.0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0 | 1 | 0 | 0 | 0.0001313 |
| 0.25 | 1 | 0 | 1 | 0 | 0 | 0.01725 |
| 0.49 | 1 | 0 | 1 | 0 | 0 | 0.05589 |
| 0.5 | 1 | 0 | 1 | 0 | 0 | 0.0578 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `carga_motor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_rampa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_aplicada` | 0 | 0.0578 | 0.02125 | 0.01811 | 0 | 0.0578 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `orden_arranque`=1, `carga_motor`=0, `en_rampa`=1, `fallo_sobrecarga`=0, `motor_en_marcha`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `en_rampa`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

En el instante del arranque, la rampa de tension comienza su ascenso exponencial con tau=3s. A t=0.1s la tension apenas alcanza ~3%, pero ya es positiva. La salida 'en_rampa' se activa (orden_arranque=true y tension<90%), mientras que 'motor_en_marcha' requiere al menos ~9s. Este test confirma la respuesta inmediata del actuador al comando.
