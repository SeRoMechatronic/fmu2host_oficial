# TC-OA-008 — Velocidad maxima cerca del cero de posicion

## Descripcion del test

Cuando |posicion|<0.05, la velocidad debe ser ≈±6.283 rad/s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 5001  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia` en [19.5, 20]: OK |
| ✅ | `posicion` cambios de signo: 10 (minimo 8): OK |

### Muestra de datos (inicio / mitad / final)

| t | energia | posicion | velocidad |
| --- | --- | --- | --- |
| 0 | 19.74 | 1 | 0 |
| 0.001 | 19.74 | 1 | -0.03948 |
| 0.002 | 19.74 | 0.9999 | -0.07895 |
| 2.5 | 19.74 | -1 | -1.282e-09 |
| 4.999 | 19.74 | 1 | 0.03948 |
| 5 | 19.74 | 1 | 2.564e-09 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `energia` | 19.74 | 19.74 | 19.74 | 0 | 19.74 | 19.74 | constante |
| `posicion` | -1 | 1 | 0.0002 | 0.7072 | 1 | 1 | oscilante  (10 cruces cero, ~1 Hz) |
| `velocidad` | -6.283 | 6.283 | 1.894e-12 | 4.443 | 0 | 2.564e-09 | oscilante  (9 cruces cero, ~0.9 Hz) |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia`): valor medio = 19.74 J, deriva total = 0 J (0.00%) en 5 s — excelente.
**Oscilacion** de `posicion`: amplitud ~1, frecuencia estimada ~1 Hz (10 cruces de cero en 5 s).
**Oscilacion** de `velocidad`: amplitud ~6.283, frecuencia estimada ~0.9 Hz (9 cruces de cero en 5 s).
**Variables algebraicas constantes:** `energia`=19.74 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `velocidad`: tasa de cambio maxima = 39.48 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

En el cruce por cero (posicion≈0), toda la energia es cinetica: E=0.5*v^2, por lo que |v|=sqrt(2E)≈sqrt(2*19.739)≈6.28 rad/s. La posicion debe cruzar el cero mas de 8 veces en 5 s (T=1 s). Ambas verificaciones juntas confirman que el oscilador esta en regimen correcto.
