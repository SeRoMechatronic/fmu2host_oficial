# TC-VE-007 — u=1e-11 — por debajo del umbral de guarda

## Descripcion del test

y_inv=1e30 y y_log=-1e30 (guardas activas), y_sqrt≈3.16e-6.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1e-11`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_inv` final: esperado 1e+30±1e+20, obtenido 1e+30 |
| ✅ | `y_log` final: esperado -1e+30±1e+20, obtenido -1e+30 |
| ✅ | `y_sat` final: esperado 1e-11±1e-20, obtenido 1e-11 |
| ✅ | `es_finito` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | u | es_finito | y_inv | y_log | y_sat | y_sqrt |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |
| 0.1 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |
| 0.2 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |
| 0.1 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |
| 0.2 | 1e-11 | 1 | 1e+30 | -1e+30 | 1e-11 | 3.162e-06 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1e-11 | 1e-11 | 1e-11 | 0 | 1e-11 | 1e-11 | constante |
| `es_finito` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y_inv` | 1e+30 | 1e+30 | 1e+30 | 0 | 1e+30 | 1e+30 | constante |
| `y_log` | -1e+30 | -1e+30 | -1e+30 | 0 | -1e+30 | -1e+30 | constante |
| `y_sat` | 1e-11 | 1e-11 | 1e-11 | 0 | 1e-11 | 1e-11 | constante |
| `y_sqrt` | 3.162e-06 | 3.162e-06 | 3.162e-06 | 0 | 3.162e-06 | 3.162e-06 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1e-11, `es_finito`=1, `y_inv`=1e+30, `y_log`=-1e+30, `y_sat`=1e-11, `y_sqrt`=3.162e-06 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `es_finito`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

1e-11 esta por debajo del umbral de guarda 1e-10. Aunque u>0, las guardas de y_inv y y_log se activan (|u|<1e-10 y u<1e-10). y_sqrt=sqrt(1e-11)≈3.16e-6 es valido (u>=0). Verifica que las guardas tienen umbrales en 1e-10 y no en otros valores.
