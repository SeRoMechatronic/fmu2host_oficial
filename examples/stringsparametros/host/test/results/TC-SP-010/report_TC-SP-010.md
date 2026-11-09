# TC-SP-010 — Estabilidad numerica a pesar de la complejidad de Strings

## Descripcion del test

Simulacion larga: la complejidad de Strings no afecta el calculo numerico.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 21  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` == 34.0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 1 | 34 |
| 0.5 | 1 | 34 |
| 1 | 1 | 34 |
| 5 | 1 | 34 |
| 9.5 | 1 | 34 |
| 10 | 1 | 34 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y` | 34 | 34 | 34 | 0 | 34 | 34 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1, `y`=34 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El modelo algebraico puro y=u*34 debe producir exactamente 34.0 en todos los pasos de simulacion con u=1.0. La inicializacion de los 6 parametros String no debe dejar efectos residuales que modifiquen el calculo numerico en pasos posteriores. Confirmacion de la separacion entre parametros de inicializacion y el calculo de estado estacionario.
