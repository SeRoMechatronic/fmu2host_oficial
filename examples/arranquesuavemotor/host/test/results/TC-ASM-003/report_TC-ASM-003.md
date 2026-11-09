# TC-ASM-003 — Motor fully started — umbral 90% superado

## Descripcion del test

Corrida de 12s con orden de arranque continua. A t=12s la tension debe superar el 90% y el motor debe declararse en marcha. Verifica la dinamica completa del ciclo de arranque suave.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 12.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 1202  |  Tiempo total: 12 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tension_aplicada`@t=12.0: esperado 0.978±0.03, obtenido 0.978021 |
| ✅ | `motor_en_marcha` == 1 eventualmente: OK |
| ✅ | `en_rampa`@t=12.0: esperado 0±0, obtenido 0 |
| ✅ | `fallo_sobrecarga` == 0 siempre: OK |
| ✅ | `tension_aplicada` monotona creciente: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0 | 1 | 0 | 0 | 0.0001313 |
| 6.01 | 1 | 0 | 1 | 0 | 0 | 0.8381 |
| 12 | 1 | 0 | 0 | 0 | 1 | 0.978 |
| 12 | 1 | 0 | 0 | 0 | 1 | 0.978 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `carga_motor` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_rampa` | 0 | 1 | 0.6206 | 0.4854 | 1 | 0 | decreciente |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 1 | 0.3794 | 0.4854 | 0 | 1 | creciente |
| `tension_aplicada` | 0 | 0.978 | 0.7139 | 0.2863 | 0 | 0.978 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `en_rampa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `motor_en_marcha`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `tension_aplicada`: valor final = 0.978 (arranca en 0, delta = 0.978).
**Variables algebraicas constantes:** `orden_arranque`=1, `carga_motor`=0, `fallo_sobrecarga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_motor`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `en_rampa`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `motor_en_marcha`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Con tau_rampa=3s y tau_pt1=0.5s, a t=12s (4 constantes de tiempo) la rampa alcanza 1-e^-4=98.2%. El filtro PT1 la sigue de cerca. El motor se declara en marcha hacia t~9s cuando la tension_filtrada supera 0.90. La monotonia de la tension confirma la estabilidad del controlador de arranque suave bajo condiciones nominales sin sobrecarga.
