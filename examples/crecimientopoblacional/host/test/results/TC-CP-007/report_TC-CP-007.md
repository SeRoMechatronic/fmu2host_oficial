# TC-CP-007 — Inmigracion positiva — equilibrio por encima de K

## Descripcion del test

Con tasa_entrada=5.0, la poblacion de equilibrio supera K=100.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=5.0`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion` final: esperado 103.0±5.0, obtenido 101.409 |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 5 | 0 | 2 | 0.02 | 6.86 |
| 0.01 | 5 | 0 | 2.121 | 0.02121 | 7.265 |
| 0.02 | 5 | 0 | 2.245 | 0.02245 | 7.682 |
| 2.51 | 5 | 1 | 101.1 | 1.011 | -3.72 |
| 5 | 5 | 1 | 101.4 | 1.014 | -5 |
| 5 | 5 | 1 | 101.4 | 1.014 | -5 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `superpoblacion` | 0 | 1 | 0.5757 | 0.4947 | 0 | 1 | creciente |
| `poblacion` | 2 | 101.4 | 81.92 | 32.56 | 2 | 101.4 | creciente |
| `saturacion` | 0.02 | 1.014 | 0.8192 | 0.3256 | 0.02 | 1.014 | creciente |
| `tasa_crecimiento` | -5 | 87.5 | 14.81 | 29.47 | 6.86 | -5 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `superpoblacion`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `poblacion`: valor final = 101.4 (arranca en 2, delta = 99.41).
**Convergencia** de `saturacion`: valor final = 1.014 (arranca en 0.02, delta = 0.9941).
**Convergencia** de `tasa_crecimiento`: valor final = -5 (arranca en 6.86, delta = 11.86).
**Variables algebraicas constantes:** `tasa_entrada`=5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `superpoblacion`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 92.5 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La inmigracion constante de 5 individuos/tiempo eleva el equilibrio por encima de K. En el equilibrio: 0 = r*N*(1-N/K)+u implica N*>100. El test verifica que la entrada u=5 se suma correctamente a la ODE y que el FMU responde al input en el bucle de simulacion.
