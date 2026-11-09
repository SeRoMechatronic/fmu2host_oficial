# TC-ASM-005 — Brief overload (1s) — no dispara fallo

## Descripcion del test

Sobrecarga de 1s (carga_motor=0.95 durante t=10..11s). El integrador de sobrecarga apenas acumula 1s y luego decae. A t=12s fallo_sobrecarga debe ser FALSE (umbral es 2s).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 12.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor`: t=0: 0.0, t=10.0: 0.95, t=11.0: 0.0

## Simulacion: ME-RK4

- Pasos simulados: 1202  |  Tiempo total: 12 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobrecarga`@t=12.0: esperado 0±0, obtenido 0 |
| ✅ | `fallo_sobrecarga` == 0 siempre: OK |
| ✅ | `motor_en_marcha`@t=12.0: esperado 1±0, obtenido 1 |

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
| `carga_motor` | 0 | 0.95 | 0.07903 | 0.2625 | 0 | 0 | creciente |
| `en_rampa` | 0 | 1 | 0.6206 | 0.4854 | 1 | 0 | decreciente |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 1 | 0.3794 | 0.4854 | 0 | 1 | creciente |
| `tension_aplicada` | 0 | 0.978 | 0.7139 | 0.2863 | 0 | 0.978 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `en_rampa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `motor_en_marcha`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `tension_aplicada`: valor final = 0.978 (arranca en 0, delta = 0.978).
**Variables algebraicas constantes:** `orden_arranque`=1, `fallo_sobrecarga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `carga_motor`: tasa de cambio maxima = 95 unidades/s.
**Dinamica rapida** en `en_rampa`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con t_retardo=2s, una sobrecarga de 1s no alcanza el umbral de fallo. El integrador acumula 1s pero luego decae con tau=0.5s antes de llegar a 2. Este test valida la robustez del sistema: perturbaciones cortas no generan paradas innecesarias, lo que es critico en aplicaciones industriales donde picos transitorios de carga son frecuentes.
