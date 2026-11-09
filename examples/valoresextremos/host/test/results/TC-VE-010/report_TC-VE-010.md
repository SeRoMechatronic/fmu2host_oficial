# TC-VE-010 — Sin NaN ni Inf en todos los casos — barrido completo

## Descripcion del test

Simulacion con varios cambios de u: ningun output debe ser invalido.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`  
`u`: t=0: 0.0, t=0.5: -5.0, t=1.0: 1.0, t=1.5: -1.0, t=2.0: 2.0, t=2.5: 1e-11, t=3.0: 100.0, t=3.5: -10.0, t=4.0: 0.5

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` sin NaN/Inf: OK |
| ✅ | `y_sqrt` sin NaN/Inf: OK |
| ✅ | `y_log` sin NaN/Inf: OK |
| ✅ | `y_sat` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 1 | 1e+30 | -1e+30 | 0 | 0 |
| 0.5 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 1 | 1 |
| 2.5 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |
| 4.5 | 0.5 | 1 | 2 | -0.6931 | 0.5 | 0.7071 |
| 5 | 0.5 | 1 | 2 | -0.6931 | 0.5 | 0.7071 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | -10 | 100 | 8.045 | 30.69 | 0 | 0.5 | oscilante  (5 cruces cero, ~0.5 Hz) |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | -1 | 1e+30 | 1.818e+29 | 4.045e+29 | 1e+30 | 2 | oscilante  (6 cruces cero, ~0.6 Hz) |
| `y_log` | -1e+30 | 4.605 | -4.545e+29 | 5.222e+29 | -1e+30 | -0.6931 | oscilante  (4 cruces cero, ~0.4 Hz) |
| `y_sat` | -1 | 1 | 0.1364 | 0.809 | 0 | 0.5 | oscilante  (5 cruces cero, ~0.5 Hz) |
| `y_sqrt` | 0 | 10 | 1.321 | 2.92 | 0 | 0.7071 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Oscilacion** de `u`: amplitud ~55, frecuencia estimada ~0.5 Hz (5 cruces de cero en 5 s).
**Oscilacion** de `y_inv`: amplitud ~5e+29, frecuencia estimada ~0.6 Hz (6 cruces de cero en 5 s).
**Oscilacion** de `y_log`: amplitud ~5e+29, frecuencia estimada ~0.4 Hz (4 cruces de cero en 5 s).
**Oscilacion** de `y_sat`: amplitud ~1, frecuencia estimada ~0.5 Hz (5 cruces de cero en 5 s).
**Convergencia** de `y_sqrt`: valor final = 0.7071 (arranca en 0, delta = 0.7071).
**Variables algebraicas constantes:** `es_finito`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `u`: tasa de cambio maxima = 220 unidades/s.
**Dinamica rapida** en `y_inv`: tasa de cambio maxima = 2e+30 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Barrido de valores que cubren todos los casos: 0 (guarda inv/log), negativo (guarda sqrt/log), positivo nominal, limite saturacion, por encima de saturacion, muy pequeno (guarda inv/log), grande, etc. En ningun instante debe aparecer NaN o Inf. Este es el test de integridad de guardas mas completo de la bateria.
