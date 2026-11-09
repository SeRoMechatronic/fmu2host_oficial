# TC-CP-004 — Pico de tasa de crecimiento cerca de N=50

## Descripcion del test

max(tasa_crecimiento) ≈ 87.5 ind/tiempo (r*K/4).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `tasa_crecimiento` > 80.0 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.01 | 0 | 0 | 2.07 | 0.0207 | 7.094 |
| 0.02 | 0 | 0 | 2.142 | 0.02142 | 7.336 |
| 2.51 | 0 | 0 | 99.26 | 0.9926 | 2.585 |
| 5 | 0 | 0 | 100 | 1 | 0.0004306 |
| 5 | 0 | 0 | 100 | 1 | 0.0004306 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 100 | 77.64 | 34.36 | 2 | 100 | creciente |
| `saturacion` | 0.02 | 1 | 0.7764 | 0.3436 | 0.02 | 1 | creciente |
| `tasa_crecimiento` | 0.0004306 | 87.5 | 19.53 | 27.94 | 6.86 | 0.0004306 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `poblacion`: valor final = 100 (arranca en 2, delta = 98).
**Convergencia** de `saturacion`: valor final = 1 (arranca en 0.02, delta = 0.98).
**Convergencia** de `tasa_crecimiento`: valor final = 0.0004306 (arranca en 6.86, delta = 6.86).
**Variables algebraicas constantes:** `tasa_entrada`=0, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 87.5 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 117.9 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El punto de inflexion de la curva logistica es N*=K/2=50, donde la tasa de crecimiento alcanza su maximo: r*K/4=3.5*100/4=87.5. El test verifica que la trayectoria pasa por esta region y que el codegen genera correctamente el termino r*N*(1-N/K).
