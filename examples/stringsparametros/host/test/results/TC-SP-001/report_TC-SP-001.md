# TC-SP-001 — Salida numerica basica — u=1.0

## Descripcion del test

y = u * len_nombre = 1.0 * 34 = 34.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 34.0±1e-09, obtenido 34 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 1 | 34 |
| 0.1 | 1 | 34 |
| 0.2 | 1 | 34 |
| 0.6 | 1 | 34 |
| 1 | 1 | 34 |
| 1 | 1 | 34 |

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

El modelo tiene un path numerico simple: y = u * len_nombre = u * 34. Con u=1.0, y=34.0. Este test verifica que la parte numerica del modelo funciona aunque los parametros String sean complejos. La lectura de parametros String no debe interferir con el calculo numerico.
