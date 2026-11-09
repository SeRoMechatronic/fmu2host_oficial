# TC-MC-009 — Cambio de canal — conmutacion instantanea

## Descripcion del test

Cambio de canal_seleccion=0 a canal_seleccion=2 a t=0.5. La salida debe cambiar instantaneamente (modelo algebraico).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`canal_0=0.3`  
`canal_2=0.8`  
`canal_seleccion=0`  
`canal_seleccion`: t=0: 0, t=0.5: 2

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida`@t=0.0: esperado 0.3±1e-09, obtenido 0.3 |
| ✅ | `salida`@t=1.0: esperado 0.8±1e-09, obtenido 0.8 |

### Muestra de datos (inicio / mitad / final)

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.3 | 0 | 0 | 0.8 | 0 | 0 | 1 | 0.3 |
| 0.5 | 0.3 | 0 | 2 | 0.8 | 0 | 2 | 1 | 0.8 |
| 1 | 0.3 | 0 | 2 | 0.8 | 0 | 2 | 1 | 0.8 |
| 0.5 | 0.3 | 0 | 2 | 0.8 | 0 | 2 | 1 | 0.8 |
| 1 | 0.3 | 0 | 2 | 0.8 | 0 | 2 | 1 | 0.8 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `canal_0` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `canal_1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_seleccion` | 0 | 2 | 1.333 | 1.155 | 0 | 2 | variable |
| `canal_2` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `canal_3` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_activo` | 0 | 2 | 1.333 | 1.155 | 0 | 2 | variable |
| `canal_valido` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida` | 0.3 | 0.8 | 0.6333 | 0.2887 | 0.3 | 0.8 | variable |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `canal_0`=0.3, `canal_1`=0, `canal_2`=0.8, `canal_3`=0, `canal_valido`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `canal_1`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_3`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_valido`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El multiplexor es puramente algebraico: no tiene memoria ni retardo. Al cambiar el selector de 0 a 2 en t=0.5s, la salida debe cambiar de 0.3 (canal_0) a 0.8 (canal_2) instantaneamente. Este test verifica la respuesta dinamica de un modelo sin estados.
