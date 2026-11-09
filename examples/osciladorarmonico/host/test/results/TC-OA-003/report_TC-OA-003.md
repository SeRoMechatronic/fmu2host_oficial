# TC-OA-003 — Posicion analitica en t=0.5 s (medio periodo)

## Descripcion del test

x(0.5)=cos(π)=-1.0, v≈0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.501 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 52  |  Tiempo total: 0.501 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` final: esperado -1.0±0.02, obtenido -0.99998 |
| ✅ | `velocidad` final: esperado 0.0±0.1, obtenido 0.0394756 |
| ✅ | `energia` final: esperado 19.739±0.1, obtenido 19.7392 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 0.26 | 19.74 | -0.06279 | -6.271 |
| 0.5 | 19.74 | -1 | -2.56e-06 |
| 0.501 | 19.74 | -1 | 0.03948 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 2.548e-07 | 19.74 | 19.74 | decreciente |
| `posicion` | -1 | 1 | -0.01923 | 0.7273 | 1 | -1 | decreciente |
| `velocidad` | -6.283 | 0.03948 | -3.844 | 2.07 | 0 | 0.03948 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 8.4e-07 J (0.00%) en 0.501 s — excelente.
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.48 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

A medio periodo (T/2=0.5 s) la posicion vuelve a la amplitud pero con signo opuesto: x=-1.0 m, v≈0. Toda la energia es potencial nuevamente. La simetria del resultado confirma que el codegen maneja correctamente los dos estados (posicion y velocidad) del oscilador.
