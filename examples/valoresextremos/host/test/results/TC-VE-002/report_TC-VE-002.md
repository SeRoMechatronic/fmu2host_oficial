# TC-VE-002 — u=-5.0 — negativo: sqrt y log protegidos

## Descripcion del test

y_inv=-0.2, y_sqrt=0, y_log=-1e30, y_sat=-1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=-5.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` final: esperado -0.2±1e-09, obtenido -0.2 |
| ✅ | `y_sqrt` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `y_log` final: esperado -1e+30±1e+20, obtenido -1e+30 |
| ✅ | `y_sat` final: esperado -1.0±1e-09, obtenido -1 |
| ✅ | `y_inv` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |
| 0.1 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |
| 0.2 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |
| 0.1 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |
| 0.2 | -5 | 1 | -0.2 | -1e+30 | -1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | -5 | -5 | -5 | 0 | -5 | -5 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | -0.2 | -0.2 | -0.2 | 0 | -0.2 | -0.2 | constante |
| `y_log` | -1e+30 | -1e+30 | -1e+30 | 0 | -1e+30 | -1e+30 | constante |
| `y_sat` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `y_sqrt` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=-5, `es_finito`=1, `y_inv`=-0.2, `y_log`=-1e+30, `y_sat`=-1, `y_sqrt`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `y_sqrt`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Entrada negativa: 1/(-5)=-0.2 (valido), sqrt(-5) indefinido → guarda devuelve 0, log(-5) indefinido → guarda devuelve -1e30. y_sat=clamp(-5,-1,1)=-1 (saturacion maxima negativa). Verifica las tres guardas protectoras simultaneamente.
