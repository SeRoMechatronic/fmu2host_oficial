# TC-CP-008 — Emigracion negativa — equilibrio por debajo de K

## Descripcion del test

Con tasa_entrada=-1.0, la poblacion converge a N*<100.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=-1.0`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion` final: esperado 97.0±4.0, obtenido 99.7133 |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | -1 | 0 | 2 | 0.02 | 6.86 |
| 0.01 | -1 | 0 | 2.06 | 0.0206 | 7.06 |
| 0.02 | -1 | 0 | 2.121 | 0.02121 | 7.267 |
| 2.51 | -1 | 0 | 98.81 | 0.9881 | 4.118 |
| 5 | -1 | 0 | 99.71 | 0.9971 | 1.001 |
| 5 | -1 | 0 | 99.71 | 0.9971 | 1.001 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 99.71 | 76.5 | 34.86 | 2 | 99.71 | creciente |
| `saturacion` | 0.02 | 0.9971 | 0.765 | 0.3486 | 0.02 | 0.9971 | creciente |
| `tasa_crecimiento` | 1.001 | 87.5 | 20.47 | 27.63 | 6.86 | 1.001 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `poblacion`: valor final = 99.71 (arranca en 2, delta = 97.71).
**Convergencia** de `saturacion`: valor final = 0.9971 (arranca en 0.02, delta = 0.9771).
**Convergencia** de `tasa_crecimiento`: valor final = 1.001 (arranca en 6.86, delta = 5.859).
**Variables algebraicas constantes:** `tasa_entrada`=-1, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 86.5 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 115.9 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La emigracion reduce la poblacion de equilibrio por debajo de K. Con u=-1, el equilibrio se mueve a N*<100. El test verifica que fmi2SetReal maneja correctamente valores negativos del input, modificando la ODE en la direccion correcta.
