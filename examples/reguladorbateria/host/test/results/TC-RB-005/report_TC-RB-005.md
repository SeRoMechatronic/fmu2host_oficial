# TC-RB-005 — Limite exacto de sobretension — sin fallo

## Descripcion del test

tension=0.95 (exactamente V_max): fallo_sobretension=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tension_bateria=0.95`  
`carga_conectada=1`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobretension` final: esperado 0±0, obtenido 0 |
| ✅ | `cargando` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.95 | 0 | 1 | 0 | 0 |
| 0.1 | 1 | 0.95 | 0 | 1 | 0 | 0 |
| 0.2 | 1 | 0.95 | 0 | 1 | 0 | 0 |
| 0.4 | 1 | 0.95 | 0 | 1 | 0 | 0 |
| 0.5 | 1 | 0.95 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `carga_conectada` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `tension_bateria` | 0.95 | 0.95 | 0.95 | 0 | 0.95 | 0.95 | constante |
| `carga_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cargando` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_sobretension` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `corriente_carga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `carga_conectada`=1, `tension_bateria`=0.95, `carga_completa`=0, `cargando`=1, `fallo_sobretension`=0, `corriente_carga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_conectada`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `carga_completa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cargando`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El umbral de sobretension usa operador estricto >. Con tension=0.95 exacto, 0.95 NO > 0.95, por lo que no hay fallo. cargando=true porque la tension esta por debajo del umbral de carga completa (0.98). Verifica la boundary condition critica del sistema de proteccion.
