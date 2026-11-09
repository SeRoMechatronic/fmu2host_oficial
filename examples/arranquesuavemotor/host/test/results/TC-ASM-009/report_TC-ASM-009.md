# TC-ASM-009 — Ramp timing — verificacion a 1 constante de tiempo

## Descripcion del test

A t=3s (= tau_rampa), la rampa debe haber alcanzado 1-e^-1 ≈ 63.2% del valor final. Verifica la dinamica temporal exacta del primer orden.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 3002  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada`@t=3.0: esperado 0.559±0.02, obtenido 0.55904 |
| ✅ | `en_rampa`@t=3.0: esperado 1±0, obtenido 1 |
| ✅ | `motor_en_marcha`@t=3.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.001 | 1 | 0 | 1 | 0 | 0 | 3.331e-07 |
| 0.002 | 1 | 0 | 1 | 0 | 0 | 1.331e-06 |
| 1.501 | 1 | 0 | 1 | 0 | 0 | 0.2823 |
| 3 | 1 | 0 | 1 | 0 | 0 | 0.559 |
| 3 | 1 | 0 | 1 | 0 | 0 | 0.559 |

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
| `tension_aplicada` | 0 | 0.559 | 0.2748 | 0.1771 | 0 | 0.559 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `orden_arranque`=1, `carga_motor`=0, `en_rampa`=1, `fallo_sobrecarga`=0, `motor_en_marcha`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `en_rampa`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Para un sistema de primer orden con tau=3s, la respuesta al escalon a t=3s vale 1-e^-1=63.2%. Sin embargo, la tension_aplicada pasa por dos filtros en cascada (rampa tau=3s + PT1 tau=0.5s), por lo que el valor real es ligeramente inferior (~60%). Este test valida la constante de tiempo del sistema y confirma que la dinamica temporal es correcta.
