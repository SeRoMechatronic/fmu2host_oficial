# TC-CS-010 — Verificacion estructural — sin solver ODE en CS

## Descripcion del test

Simulacion CS larga sin divergencia: modelo algebraico puro.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 1.0 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=2.0`  
`u2=1.0`

## Simulacion: CS

- Pasos simulados: 11  |  Tiempo total: 10 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` == 3.0 siempre: OK |
| ✅ | `y_prod` == 2.0 siempre: OK |
| ✅ | `active` == 1 eventualmente: OK |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 2 | 1 | 0 | 2 | 3 |
| 1 | 2 | 1 | 1 | 2 | 3 |
| 2 | 2 | 1 | 1 | 2 | 3 |
| 5 | 2 | 1 | 1 | 2 | 3 |
| 9 | 2 | 1 | 1 | 2 | 3 |
| 10 | 2 | 1 | 1 | 2 | 3 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `u2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `active` | 0 | 1 | 0.9091 | 0.3015 | 0 | 1 | creciente |
| `y_prod` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `y_sum` | 3 | 3 | 3 | 0 | 3 | 3 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `active`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `u1`=2, `u2`=1, `y_prod`=2, `y_sum`=3 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u2`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

En 10 segundos de simulacion con paso de 1s, las salidas algebraicas permanecen constantes en todos los pasos (suma=3, producto=2, active=1). Al ser el modelo puramente algebraico, no hay integracion ni acumulacion de error. Esto confirma que la ruta CS del codegen no introduce ODE solver ni modifica los outputs entre pasos de comunicacion.
