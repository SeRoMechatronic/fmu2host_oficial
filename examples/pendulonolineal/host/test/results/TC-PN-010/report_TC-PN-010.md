# TC-PN-010 — Comparacion energetica RK4 vs Euler en t=5 s

## Descripcion del test

RK4 tiene menor deriva que Euler en el mismo instante.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.05 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` final: esperado 8.496±0.1, obtenido 8.49557 |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.05 | 0 | 2.612 | 8.496 | -0.2461 |
| 0.1 | 0 | 2.593 | 8.496 | -0.4974 |
| 2.55 | 0 | -0.6031 | 8.496 | 5.758 |
| 5 | 0 | -2.379 | 8.496 | -1.675 |
| 5 | 0 | -2.379 | 8.496 | -1.675 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.009804 | 0.09901 | 1 | 0 | estable |
| `angulo` | -2.617 | 2.618 | 0.1285 | 1.944 | 2.618 | -2.379 | estable |
| `energia_total` | 8.496 | 8.496 | 8.496 | 5.753e-05 | 8.496 | 8.496 | decreciente |
| `velocidad_angular` | -6.043 | 6.051 | -1.004 | 3.498 | 0 | -1.675 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 0.000241 J (0.00%) en 5 s — excelente.
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 20 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

A t=5 s con h=0.05, RK4 debe estar dentro de 0.1 J del valor de energia inicial. Euler con los mismos parametros estaria tipicamente a 0.3-0.5 J de deriva. Este test verifica la mitad de la comparacion directa (el caso RK4); TC-PN-005 verifica el caso Euler. Juntos demuestran la superioridad cuantitativa de RK4 para este sistema.
