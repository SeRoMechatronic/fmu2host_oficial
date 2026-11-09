# TC-ASM-001 — No start command — estado en reposo

## Descripcion del test

Verifica que con orden_arranque=false y carga_motor=0, todos los outputs permanecen inactivos en t=0. Confirma que no hay activacion espontanea sin comandar el arranque.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=0`  
`carga_motor=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 51  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada` == 0.0 siempre: OK |
| ✅ | `motor_en_marcha` == 0 siempre: OK |
| ✅ | `fallo_sobrecarga` == 0 siempre: OK |
| ✅ | `en_rampa` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.02 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.25 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.49 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `carga_motor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_rampa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_aplicada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `orden_arranque`=0, `carga_motor`=0, `en_rampa`=0, `fallo_sobrecarga`=0, `motor_en_marcha`=0, `tension_aplicada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `en_rampa`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con la orden de arranque desactivada, el modelo permanece en estado de reposo. La rampa de tension no evoluciona (referencia=0), y ninguna salida booleana se activa. Este test verifica que la condicion inicial es correcta y que no existe activacion espontanea del sistema.
