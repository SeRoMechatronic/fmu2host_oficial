# TC-OA-004 — Periodo completo — retorno a condicion inicial

## Descripcion del test

En t=1.0 s (un periodo), x≈1.0 y v≈0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.001 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 1.001 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` final: esperado 1.0±0.02, obtenido 0.99998 |
| ✅ | `velocidad` final: esperado 0.0±0.1, obtenido -0.039473 |
| ✅ | `energia` final: esperado 19.739±0.2, obtenido 19.7392 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 0.51 | 19.74 | -0.998 | 0.3945 |
| 1 | 19.74 | 1 | 5.12e-06 |
| 1.001 | 19.74 | 1 | -0.03947 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 4.985e-07 | 19.74 | 19.74 | decreciente |
| `posicion` | -1 | 1 | 0.01961 | 0.7173 | 1 | 1 | estable |
| `velocidad` | -6.283 | 6.283 | -0.000387 | 4.421 | 0 | -0.03947 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 1.68e-06 J (0.00%) en 1.001 s — excelente.
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.48 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Tras exactamente un periodo T=1.0 s, el sistema debe retornar a su estado inicial (x=1, v=0). Un error de >0.02 m indicaria que el periodo numerico del integrador difiere del periodo analitico, lo que sugiere un error en la fuerza restauradora o en el paso de integracion.
