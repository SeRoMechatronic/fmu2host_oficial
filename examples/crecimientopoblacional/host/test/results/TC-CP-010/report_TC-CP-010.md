# TC-CP-010 — Sin NaN ni Inf con RK4 en 10 s

## Descripcion del test

Simulacion completa de la curva logistica sin valores invalidos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 1002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion` sin NaN/Inf: OK |
| ✅ | `tasa_crecimiento` sin NaN/Inf: OK |
| ✅ | `saturacion` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.01 | 0 | 0 | 2.07 | 0.0207 | 7.094 |
| 0.02 | 0 | 0 | 2.142 | 0.02142 | 7.336 |
| 5.01 | 0 | 0 | 100 | 1 | 0.0004158 |
| 10 | 0 | 0 | 100 | 1 | 1.072e-11 |
| 10 | 0 | 0 | 100 | 1 | 1.072e-11 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 100 | 88.8 | 26.76 | 2 | 100 | creciente |
| `saturacion` | 0.02 | 1 | 0.888 | 0.2676 | 0.02 | 1 | creciente |
| `tasa_crecimiento` | 1.072e-11 | 87.5 | 9.784 | 22.05 | 6.86 | 1.072e-11 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `poblacion`: valor final = 100 (arranca en 2, delta = 98).
**Convergencia** de `saturacion`: valor final = 1 (arranca en 0.02, delta = 0.98).
**Convergencia** de `tasa_crecimiento`: valor final = 1.072e-11 (arranca en 6.86, delta = 6.86).
**Variables algebraicas constantes:** `tasa_entrada`=0, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 87.5 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 117.9 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

La ecuacion logistica tiene un termino N*(1-N/K) que puede producir problemas numericos si N diverge. Con RK4 y h=0.01, el sistema debe mantenerse sin valores invalidos durante la convergencia completa desde N=2 hasta N≈100.
