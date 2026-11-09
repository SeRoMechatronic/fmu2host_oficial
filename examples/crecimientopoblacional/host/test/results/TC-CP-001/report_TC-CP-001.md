# TC-CP-001 — Condiciones iniciales — N(0)=2

## Descripcion del test

En t=0: poblacion=2.0, saturacion=0.02, superpoblacion=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion`@t=0.0: esperado 2.0±0.01, obtenido 2 |
| ✅ | `saturacion`@t=0.0: esperado 0.02±0.001, obtenido 0.02 |
| ✅ | `superpoblacion`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `tasa_crecimiento`@t=0.0: esperado 6.86±0.1, obtenido 6.86 |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.001 | 0 | 0 | 2.007 | 0.02007 | 6.883 |
| 0.002 | 0 | 0 | 2.014 | 0.02014 | 6.906 |
| 0.005 | 0 | 0 | 2.035 | 0.02035 | 6.976 |
| 0.009 | 0 | 0 | 2.063 | 0.02063 | 7.07 |
| 0.01 | 0 | 0 | 2.07 | 0.0207 | 7.094 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `superpoblacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `poblacion` | 2 | 2.07 | 2.035 | 0.02314 | 2 | 2.07 | creciente |
| `saturacion` | 0.02 | 0.0207 | 0.02035 | 0.0002314 | 0.02 | 0.0207 | creciente |
| `tasa_crecimiento` | 6.86 | 7.094 | 6.977 | 0.07769 | 6.86 | 7.094 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `tasa_entrada`=0, `superpoblacion`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `tasa_entrada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `superpoblacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `tasa_crecimiento`: tasa de cambio maxima = 23.76 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

La poblacion empieza en N=2 individuos, muy lejos del equilibrio K=100. La tasa inicial de crecimiento es r*N*(1-N/K) = 3.5*2*(1-0.02) = 6.86 individuos/tiempo. La saturacion N/K=0.02 indica que el sistema esta muy lejos de la capacidad de carga.
