# TC-CE-002 — Un solo evento — contador pasa a 1

## Descripcion del test

1 flanco ascendente en evento: cuenta=1, decenas=0, unidades=1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 2.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`  
`evento`: t=0: 0, t=0.5: 1, t=1.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 5  |  Tiempo total: 2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta` final: esperado 1±0, obtenido 0 |
| ✅ | `decenas` final: esperado 0±0, obtenido 0 |
| ❌ | `unidades` final: esperado 1±0, obtenido 0 |
| ✅ | `desbordamiento` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 1 | 0.2 | 0.4472 | 0 | 0 | decreciente |
| `reset` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 4:**
  - `cuenta` final: esperado 1±0, obtenido 0
  - `unidades` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `reset`=0, `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `reset`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (2 checks OK, 2 FAIL)

Un unico flanco ascendente (FALSE→TRUE en t=0.5). El contador pasa de 0 a 1. decenas=div(1,10)=0, unidades=mod(1,10)=1. desbordamiento=FALSE (1 < 99). Verifica el incremento minimo y que el flanco descendente (TRUE→FALSE en t=1.0) no cuenta.
