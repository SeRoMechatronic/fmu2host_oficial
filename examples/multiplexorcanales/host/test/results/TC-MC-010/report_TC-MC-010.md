# TC-MC-010 — Valores limite del selector: 0 y 3 son validos

## Descripcion del test

Verificacion de que ambos extremos del rango [0,3] son validos.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`canal_seleccion=0`  
`canal_0=0.5`  
`canal_3=0.9`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `canal_valido` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | canal_0 | canal_1 | canal_seleccion | canal_2 | canal_3 | canal_activo | canal_valido | salida |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0 | 0 | 0 | 0.9 | 0 | 1 | 0.5 |
| 0.1 | 0.5 | 0 | 0 | 0 | 0.9 | 0 | 1 | 0.5 |
| 0.2 | 0.5 | 0 | 0 | 0 | 0.9 | 0 | 1 | 0.5 |
| 0.1 | 0.5 | 0 | 0 | 0 | 0.9 | 0 | 1 | 0.5 |
| 0.2 | 0.5 | 0 | 0 | 0 | 0.9 | 0 | 1 | 0.5 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `canal_0` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `canal_1` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_seleccion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_2` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_3` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `canal_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `canal_valido` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `canal_0`=0.5, `canal_1`=0, `canal_seleccion`=0, `canal_2`=0, `canal_3`=0.9, `canal_activo`=0, `canal_valido`=1, `salida`=0.5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `canal_1`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_seleccion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `canal_2`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El selector 0 es el limite inferior valido. Un test simetrico con selector=3 (TC-MC-004) verifica el limite superior. Juntos confirman que el rango de validez [0,3] esta correctamente implementado en la logica del multiplexor.
