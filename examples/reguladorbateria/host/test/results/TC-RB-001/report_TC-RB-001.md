# TC-RB-001 — Cargador desconectado — sin corriente

## Descripcion del test

Con carga_conectada=false: corriente=0, cargando=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tension_bateria=0.5`  
`carga_conectada=0`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `corriente_carga` == 0.0 siempre: OK |
| ✅ | `cargando` == 0 siempre: OK |
| ✅ | `carga_completa` final: esperado 0±0, obtenido 0 |
| ✅ | `fallo_sobretension` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.01 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.02 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 0.99 | 0 | 0.5 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0.5 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `carga_conectada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_bateria` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `carga_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cargando` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `fallo_sobretension` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `corriente_carga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `carga_conectada`=0, `tension_bateria`=0.5, `carga_completa`=0, `cargando`=0, `fallo_sobretension`=0, `corriente_carga`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_conectada`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `carga_completa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cargando`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Sin conexion del cargador, no debe fluir corriente de carga. La tension de la bateria es monitoreada pero el regulador no actua. Este estado representa la bateria en uso (sin carga conectada).
