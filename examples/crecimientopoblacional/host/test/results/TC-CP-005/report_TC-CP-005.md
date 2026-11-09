# TC-CP-005 — RK4 converge monotonamente — sin oscilacion alrededor de K

## Descripcion del test

Con RK4, poblacion es estrictamente creciente.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion` monotona creciente: OK |
| ✅ | `poblacion` en [0, 101]: OK |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.1 | 0 | 0 | 2.814 | 0.02814 | 9.573 |
| 0.2 | 0 | 0 | 3.947 | 0.03947 | 13.27 |
| 5.1 | 0 | 0 | 100 | 1 | 0.0003041 |
| 10 | 0 | 0 | 100 | 1 | 1.084e-11 |
| 10 | 0 | 0 | 100 | 1 | 1.084e-11 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 100 | 88.56 | 27.29 | 2 | 100 | creciente |
| `saturacion` | 0.02 | 1 | 0.8856 | 0.2729 | 0.02 | 1 | creciente |
| `tasa_crecimiento` | 1.084e-11 | 87.46 | 9.64 | 21.98 | 6.86 | 1.084e-11 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `poblacion`: valor final = 100 (arranca en 2, delta = 98).
**Convergencia** de `saturacion`: valor final = 1 (arranca en 0.02, delta = 0.98).
**Convergencia** de `tasa_crecimiento`: valor final = 1.084e-11 (arranca en 6.86, delta = 6.86).
**Variables algebraicas constantes:** `tasa_entrada`=0, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 86.89 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 117.1 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La ecuacion logistica con condiciones iniciales N(0)=2 < K=100 produce una trayectoria monotonamente creciente hacia K. RK4 debe reproducir esta propiedad sin oscilaciones. Euler puede oscilar alrededor de K, pero RK4 con h=0.1 no deberia.
