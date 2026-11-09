# TC-LZ-008 — Verificacion analitica en t=0.1 s

## Descripcion del test

x(0.1)≈2.11, y(0.1)≈4.40, z(0.1)≈1.49 (RK4, IC: x=1,y=1,z=1.5).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.101 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 0.101 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `x_out` final: esperado 2.11±0.1, obtenido 2.13267 |
| ✅ | `y_out` final: esperado 4.4±0.2, obtenido 4.44714 |
| ✅ | `z_out` final: esperado 1.49±0.05, obtenido 1.49522 |

### Muestra de datos (inicio / mitad / final)

| t | on_attractor | x_out | y_out | z_out |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 1.5 |
| 0.01 | 1 | 1.012 | 1.255 | 1.472 |
| 0.02 | 1 | 1.048 | 1.514 | 1.447 |
| 0.06 | 1 | 1.402 | 2.704 | 1.397 |
| 0.1 | 1 | 2.11 | 4.395 | 1.49 |
| 0.101 | 1 | 2.133 | 4.447 | 1.495 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `on_attractor` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `x_out` | 1 | 2.133 | 1.452 | 0.421 | 1 | 2.133 | creciente |
| `y_out` | 1 | 4.447 | 2.665 | 1.199 | 1 | 4.447 | creciente |
| `z_out` | 1.397 | 1.5 | 1.442 | 0.03875 | 1.5 | 1.495 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `on_attractor`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `on_attractor`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `x_out`: tasa de cambio maxima = 23 unidades/s.
**Dinamica rapida** en `y_out`: tasa de cambio maxima = 51.81 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

A t=0.1 s, con IC (1,1,1.5) y parametros sigma=10, rho=28, beta=8/3: dy/dt(0)=25.5 domina el movimiento inicial, haciendo que y crezca rapidamente hasta ~4.4 en 0.1s. dx/dt(0)=0 pero x crece a ~2.1 por el acoplamiento. t_end=0.101 para capturar t=0.1 con h=0.01 (evita imprecision de punto flotante en 10*0.01=0.1).
