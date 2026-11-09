# TC-CP-003 — Sobredisparo de Euler — discriminador de integrador

## Descripcion del test

Euler con h=1.0 (grande) debe causar superpoblacion (N>100) antes de t=3 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | ME |
| Solver | euler |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-EULER

- Pasos simulados: 4  |  Tiempo total: 3 s
- Grafica individual: [sim_me_euler.png](sim_me_euler.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `superpoblacion` == 1 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 1 | 0 | 0 | 8.86 | 0.0886 | 28.26 |
| 2 | 0 | 0 | 37.12 | 0.3712 | 81.7 |
| 2 | 0 | 0 | 37.12 | 0.3712 | 81.7 |
| 3 | 0 | 1 | 118.8 | 1.188 | -78.26 |

## Analisis de datos

### Simulacion: ME-EULER

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 1 | 0.25 | 0.5 | 0 | 1 | variable |
| `poblacion` | 2 | 118.8 | 41.7 | 53.61 | 2 | 118.8 | variable |
| `saturacion` | 0.02 | 1.188 | 0.417 | 0.5361 | 0.02 | 1.188 | variable |
| `tasa_crecimiento` | -78.26 | 81.7 | 9.64 | 66.52 | 6.86 | -78.26 | variable |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `tasa_entrada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `poblacion`: tasa de cambio maxima = 81.7 unidades/s.
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 160 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Con h=1.0 (paso grande), Euler acumula un error significativo en la region de maximo crecimiento logistico (N≈50, dN/dt_max≈87.5). El paso de 87.5 lleva N de ~37 a ~125 en un solo paso, activando superpoblacion. Con h=0.1 el error es insuficiente para superar K. Discriminador clave: RK4 con cualquier h razonable no sobrepasa.
