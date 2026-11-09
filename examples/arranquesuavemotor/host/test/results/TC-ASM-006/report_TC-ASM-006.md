# TC-ASM-006 — Sustained overload (2s) — fallo dispara

## Descripcion del test

Sobrecarga sostenida desde t=10s con carga_motor=0.95. A t=12s (2s de sobrecarga continua) el integrador supera el umbral y fallo_sobrecarga debe activarse.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 12.5 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor`: t=0: 0.0, t=10.0: 0.95

## Simulacion: ME-RK4

- Pasos simulados: 1252  |  Tiempo total: 12.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobrecarga` == 1 eventualmente: OK |
| ✅ | `en_rampa`@t=12.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0 | 1 | 0 | 0 | 0.0001313 |
| 6.26 | 1 | 0 | 1 | 0 | 0 | 0.8511 |
| 12.5 | 1 | 0.95 | 0 | 1 | 1 | 0.9814 |
| 12.5 | 1 | 0.95 | 0 | 1 | 1 | 0.9814 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `carga_motor` | 0 | 0.95 | 0.1905 | 0.3805 | 0 | 0.95 | creciente |
| `en_rampa` | 0 | 1 | 0.5958 | 0.4909 | 1 | 0 | decreciente |
| `fallo_sobrecarga` | 0 | 1 | 0.03994 | 0.1959 | 0 | 1 | creciente |
| `motor_en_marcha` | 0 | 1 | 0.4042 | 0.4909 | 0 | 1 | creciente |
| `tension_aplicada` | 0 | 0.9814 | 0.7245 | 0.2853 | 0 | 0.9814 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `carga_motor`: valor final = 0.95 (arranca en 0, delta = 0.95).
**Convergencia** de `en_rampa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `motor_en_marcha`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `tension_aplicada`: valor final = 0.9814 (arranca en 0, delta = 0.9814).
**Variables algebraicas constantes:** `orden_arranque`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `carga_motor`: tasa de cambio maxima = 95 unidades/s.
**Dinamica rapida** en `en_rampa`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con sobrecarga continua desde t=10s, el integrador acumula a razon de 1 s/s (der=1.0 cuando carga>0.9). A t=12s el integrador llega a 2s (valor de t_retardo), disparando el fallo. Este test verifica la proteccion contra sobrecargas prolongadas, fundamental en motores electricos donde el sobrecalentamiento por exceso de corriente puede causar danos permanentes.
