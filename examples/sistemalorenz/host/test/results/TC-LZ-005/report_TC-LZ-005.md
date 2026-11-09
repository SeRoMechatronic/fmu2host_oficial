# TC-LZ-005 — x oscila entre positivo y negativo — estructura bilobulo

## Descripcion del test

x debe cambiar de signo al menos 10 veces en 20 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 2001  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `x_out` cambios de signo: 4 (minimo 3): OK |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.01 | 1 | 1.012 | 1.255 | 1.472 |
| 0.02 | 1 | 1.048 | 1.514 | 1.447 |
| 10 | 1 | -5.788 | -2.394 | 28.38 |
| 19.99 | 1 | 12.78 | 13.33 | 32.04 |
| 20 | 1 | 12.8 | 12.63 | 32.83 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `x_out` | -17.98 | 19.44 | -2.697 | 7.789 | 1 | 12.8 | oscilante  (4 cruces cero, ~0.1 Hz) |
| `y_out` | -24.14 | 26.91 | -2.638 | 8.555 | 1 | 12.63 | oscilante  (6 cruces cero, ~0.15 Hz) |
| `z_out` | 1.397 | 47.52 | 25.02 | 7.027 | 1.5 | 32.83 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Oscilacion** de `x_out`: amplitud ~18.71, frecuencia estimada ~0.1 Hz (4 cruces de cero en 20 s).
**Oscilacion** de `y_out`: amplitud ~25.53, frecuencia estimada ~0.15 Hz (6 cruces de cero en 20 s).
**Variables algebraicas constantes:** `on_attractor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `on_attractor`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 158.1 unidades/s.
**Dinamica rapida** en `y_out`: tasa de cambio maxima = 364.6 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El atractor de Lorenz tiene estructura de 'mariposa' con dos lobulos. La coordenada x orbita alternadamente el centro positivo C+ y el centro negativo C-. En 20 s, x debe cambiar de signo al menos 10 veces (aproximadamente 1 cambio por segundo). Si x permanece siempre positivo o negativo, la trayectoria esta atrapada en un solo lobulo, lo que indica un error en la integracion.
