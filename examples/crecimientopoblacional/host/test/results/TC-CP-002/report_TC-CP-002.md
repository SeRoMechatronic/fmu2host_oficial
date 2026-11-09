# TC-CP-002 — Convergencia a K con RK4 (t=5 s) — sin sobredisparo

## Descripcion del test

poblacion > 95 a t=5 s, superpoblacion=false con RK4.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 52  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion` final: esperado 97.0±3.0, obtenido 99.9999 |
| ✅ | `superpoblacion` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.1 | 0 | 0 | 2.814 | 0.02814 | 9.573 |
| 0.2 | 0 | 0 | 3.947 | 0.03947 | 13.27 |
| 2.6 | 0 | 0 | 99.46 | 0.9946 | 1.896 |
| 5 | 0 | 0 | 100 | 1 | 0.0004315 |
| 5 | 0 | 0 | 100 | 1 | 0.0004315 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 100 | 77.56 | 34.98 | 2 | 100 | creciente |
| `saturacion` | 0.02 | 1 | 0.7756 | 0.3498 | 0.02 | 1 | creciente |
| `tasa_crecimiento` | 0.0004315 | 87.46 | 18.91 | 27.9 | 6.86 | 0.0004315 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `poblacion`: valor final = 100 (arranca en 2, delta = 98).
**Convergencia** de `saturacion`: valor final = 1 (arranca en 0.02, delta = 0.98).
**Convergencia** de `tasa_crecimiento`: valor final = 0.0004315 (arranca en 6.86, delta = 6.86).
**Variables algebraicas constantes:** `tasa_entrada`=0, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 86.89 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 117.1 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

CRITERIO PRIMARIO RK4. La ecuacion logistica con r=3.5, K=100 converge a K sin sobredisparo con RK4 y h=0.1. La poblacion debe superar 95 individuos a t=5 s y nunca exceder 100 (superpoblacion=false en todo momento). RK4 sigue la curva sigmoidal correctamente.
