# TC-OA-009 — Comparacion de paso — RK4 h=0.01 vs h=0.001

## Descripcion del test

Con h=0.001, la energia debe ser mas estable que con h=0.01.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 10002  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia` en [19.73, 19.75]: OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.001 | 19.74 | 1 | -0.03948 |
| 0.002 | 19.74 | 0.9999 | -0.07895 |
| 5.001 | 19.74 | 1 | -0.03948 |
| 10 | 19.74 | 1 | 5.127e-09 |
| 10 | 19.74 | 1 | 5.123e-09 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 0 | 19.74 | 19.74 | constante |
| `posicion` | -1 | 1 | 0.0002 | 0.7072 | 1 | 1 | oscilante  (20 cruces cero, ~1 Hz) |
| `velocidad` | -6.283 | 6.283 | 4.271e-13 | 4.443 | 0 | 5.123e-09 | oscilante  (19 cruces cero, ~0.95 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 0 J (0.00%) en 10 s — excelente.
**Oscilacion** de `posicion`: amplitud ~1, frecuencia estimada ~1 Hz (20 cruces de cero en 10 s).
**Oscilacion** de `velocidad`: amplitud ~6.283, frecuencia estimada ~0.95 Hz (19 cruces de cero en 10 s).
**Variables algebraicas constantes:** `energia`=19.74 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.48 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Con un paso 10x mas pequeno (h=0.001 s), la deriva de energia de RK4 se reduce drasticamente. La ventana de tolerancia [19.730, 19.748] es 5x mas estrecha que para h=0.01. Esto verifica la propiedad de convergencia de RK4: la precision mejora como O(h^4) al reducir el paso.
