# TC-CS-008 — Cambio de entrada a mitad — respuesta inmediata

## Descripcion del test

u1 cambia de 1 a 5 en t=0.5s. Respuesta algebraica inmediata.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=1.0`  
`u2=2.0`  
`u1`: t=0: 1.0, t=0.5: 5.0

## Simulacion: CS

- Pasos simulados: 12  |  Tiempo total: 1 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum`@t=0.4: esperado 3.0±1e-09, obtenido 3 |
| ✅ | `y_sum`@t=1.0: esperado 7.0±1e-09, obtenido 7 |
| ✅ | `active`@t=1.0: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 2 | 0 | 2 | 3 |
| 0.1 | 1 | 2 | 0 | 2 | 3 |
| 0.2 | 1 | 2 | 0 | 2 | 3 |
| 0.6 | 5 | 2 | 1 | 10 | 7 |
| 1 | 5 | 2 | 1 | 10 | 7 |
| 1 | 5 | 2 | 1 | 10 | 7 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 1 | 5 | 3.333 | 2.06 | 1 | 5 | creciente |
| `u2` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `active` | 0 | 1 | 0.5 | 0.5222 | 0 | 1 | creciente |
| `y_prod` | 2 | 10 | 6.667 | 4.119 | 2 | 10 | creciente |
| `y_sum` | 3 | 7 | 5.333 | 2.06 | 3 | 7 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `u1`: valor final = 5 (arranca en 1, delta = 4).
**Convergencia** de `active`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `y_prod`: valor final = 10 (arranca en 2, delta = 8).
**Convergencia** de `y_sum`: valor final = 7 (arranca en 3, delta = 4).
**Variables algebraicas constantes:** `u2`=2 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `u1`: tasa de cambio maxima = 40 unidades/s.
**Dinamica rapida** en `active`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El modelo CS algebraico responde instantaneamente al cambio de entrada. Antes del cambio (t=0.4s): u1=1+u2=2, suma=3. Despues (t=1s): u1=5+u2=2, suma=7. Ademas active cambia de false a true. Esto confirma que fmi2SetReal es llamado en cada paso de comunicacion y no solo en la inicializacion.
