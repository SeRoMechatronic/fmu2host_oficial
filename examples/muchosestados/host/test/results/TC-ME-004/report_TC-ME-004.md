# TC-ME-004 — Comprobacion analitica de y1 en t=1, 2, 3 s

## Descripcion del test

y1(t)=1-e^(-t/tau): y1(1)≈0.632, y1(2)≈0.865, y1(3)≈0.950.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 302  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y1`@t=1.0: esperado 0.632±0.01, obtenido 0.632121 |
| ✅ | `y1`@t=2.0: esperado 0.865±0.01, obtenido 0.864665 |
| ✅ | `y1`@t=3.0: esperado 0.95±0.01, obtenido 0.950213 |

### Muestra de datos (inicio / mitad / final)

| t | u | todos_activos | y1 | y2 | y3 | y4 | y5 | y6 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.01 | 1 | 0 | 0.00995 | 4.967e-05 | 1.654e-07 | 4.167e-10 | 0 | 0 |
| 0.02 | 1 | 0 | 0.0198 | 0.0001974 | 1.313e-06 | 6.567e-09 | 2.465e-11 | 6.861e-14 |
| 1.51 | 1 | 0 | 0.7791 | 0.4455 | 0.1937 | 0.0669 | 0.01905 | 0.004599 |
| 3 | 1 | 1 | 0.9502 | 0.8009 | 0.5768 | 0.3528 | 0.1847 | 0.08392 |
| 3 | 1 | 1 | 0.9502 | 0.8009 | 0.5768 | 0.3528 | 0.1847 | 0.08392 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `todos_activos` | 0 | 1 | 0.03642 | 0.1877 | 0 | 1 | creciente |
| `y1` | 0 | 0.9502 | 0.6835 | 0.2585 | 0 | 0.9502 | creciente |
| `y2` | 0 | 0.8009 | 0.4175 | 0.2614 | 0 | 0.8009 | creciente |
| `y3` | 0 | 0.5768 | 0.2254 | 0.1887 | 0 | 0.5768 | creciente |
| `y4` | 0 | 0.3528 | 0.1075 | 0.1104 | 0 | 0.3528 | creciente |
| `y5` | 0 | 0.1847 | 0.04549 | 0.05465 | 0 | 0.1847 | creciente |
| `y6` | 0 | 0.08392 | 0.01721 | 0.02344 | 0 | 0.08392 | creciente |
| `y7` | 0 | 0.03351 | 0.00586 | 0.00886 | 0 | 0.03351 | creciente |
| `y8` | 0 | 0.0119 | 0.001811 | 0.002992 | 0 | 0.0119 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `y1`: valor final = 0.9502 (arranca en 0, delta = 0.9502).
**Variables algebraicas constantes:** `u`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `todos_activos`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El primer filtro tiene solucion analitica exacta: y1(t)=1-e^(-t). Los valores en t=1,2,3 tau son el 63%, 86.5% y 95% del valor final. Este test verifica el primer slot del buffer de estados y que la ODE tau*dx/dt=u-x esta correctamente generada para la primera etapa.
