# TC-OA-010 — Sin NaN ni Inf en 100 ciclos con RK4

## Descripcion del test

100 segundos de simulacion autonoma sin valores invalidos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 100.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 10001  |  Tiempo total: 100 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `posicion` sin NaN/Inf: OK |
| ✅ | `velocidad` sin NaN/Inf: OK |
| ✅ | `energia` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.01 | 19.74 | 0.998 | -0.3945 |
| 0.02 | 19.74 | 0.9921 | -0.7875 |
| 50 | 19.74 | 1 | 0.000256 |
| 99.99 | 19.74 | 0.998 | 0.395 |
| 100 | 19.74 | 1 | 0.000512 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 4.868e-05 | 19.74 | 19.74 | decreciente |
| `posicion` | -1 | 1 | 9.986e-05 | 0.7072 | 1 | 1 | oscilante  (200 cruces cero, ~1 Hz) |
| `velocidad` | -6.283 | 6.283 | -1.713e-08 | 4.443 | 0 | 0.000512 | oscilante  (199 cruces cero, ~0.995 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 0.0001686 J (0.00%) en 100 s — excelente.
**Oscilacion** de `posicion`: amplitud ~1, frecuencia estimada ~1 Hz (200 cruces de cero en 100 s).
**Oscilacion** de `velocidad`: amplitud ~6.283, frecuencia estimada ~0.995 Hz (199 cruces de cero en 100 s).
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.45 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

100 segundos equivalen a 100 ciclos completos del oscilador. Un codegen que genera codigo de derivadas correcto y un integrador estable no producen NaN ni Inf en este tiempo. Si aparecen valores invalidos, el integrador ha divergido catastroficamente, lo que indica un error grave en el codigo generado.
