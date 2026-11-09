# TC-OA-001 — Condiciones iniciales — t=0

## Descripcion del test

posicion=1.0, velocidad=0.0, energia≈19.739 en t=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion`@t=0.0: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `velocidad`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `energia`@t=0.0: esperado 19.739±0.01, obtenido 19.7392 |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.001 | 19.74 | 1 | -0.03948 |
| 0.002 | 19.74 | 0.9999 | -0.07895 |
| 0.005 | 19.74 | 0.9995 | -0.1974 |
| 0.009 | 19.74 | 0.9984 | -0.3551 |
| 0.01 | 19.74 | 0.998 | -0.3945 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 0 | 19.74 | 19.74 | constante |
| `posicion` | 0.998 | 1 | 0.9993 | 0.0006795 | 1 | 0.998 | decreciente |
| `velocidad` | -0.3945 | 0 | -0.1973 | 0.1309 | 0 | -0.3945 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 0 J (0.00%) en 0.01 s — excelente.
**Variables algebraicas constantes:** `energia`=19.74 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.48 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El oscilador empieza en x=1.0 m con v=0. La energia inicial es E0 = 0.5*omega^2*1^2 = 0.5*(2π)^2 ≈ 19.739 J. Este test verifica las condiciones iniciales antes de cualquier integracion, confirmando que la FMU esta correctamente inicializada.
