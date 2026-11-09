# TC-LZ-010 — Sin NaN ni Inf con RK4 en 50 s

## Descripcion del test

Simulacion larga del sistema caotico sin valores invalidos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 50.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 5002  |  Tiempo total: 50 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `x_out` sin NaN/Inf: OK |
| ✅ | `y_out` sin NaN/Inf: OK |
| ✅ | `z_out` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.01 | 1 | 1.012 | 1.255 | 1.472 |
| 0.02 | 1 | 1.048 | 1.514 | 1.447 |
| 25.01 | 1 | -0.01313 | 0.01837 | 11.83 |
| 50 | 1 | 16.04 | 14.95 | 38.42 |
| 50 | 1 | 16.04 | 14.95 | 38.42 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `x_out` | -17.98 | 19.44 | -2.437 | 7.716 | 1 | 16.04 | oscilante  (16 cruces cero, ~0.16 Hz) |
| `y_out` | -24.14 | 26.91 | -2.407 | 8.586 | 1 | 14.95 | oscilante  (28 cruces cero, ~0.28 Hz) |
| `z_out` | 1.397 | 47.52 | 24.35 | 7.786 | 1.5 | 38.42 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Oscilacion** de `x_out`: amplitud ~18.71, frecuencia estimada ~0.16 Hz (16 cruces de cero en 50 s).
**Oscilacion** de `y_out`: amplitud ~25.53, frecuencia estimada ~0.28 Hz (28 cruces de cero en 50 s).
**Variables algebraicas constantes:** `on_attractor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `on_attractor`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 158.1 unidades/s.
**Dinamica rapida** en `y_out`: tasa de cambio maxima = 364.6 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

50 segundos de sistema caotico sin NaN ni Inf. Aunque la trayectoria no es periodica ni predecible a largo plazo, debe mantenerse dentro de los limites del atractor. NaN/Inf indicarian una divergencia catastrofica del integrador, no el caos normal del sistema Lorenz.
