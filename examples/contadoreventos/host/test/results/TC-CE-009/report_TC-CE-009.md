# TC-CE-009 — Prioridad de reset sobre evento simultaneo

## Descripcion del test

Flanco de reset y evento en el mismo paso: reset gana, cuenta=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`  
`evento`: t=0: 0, t=1.0: 1, t=1.5: 0  
`reset`: t=0: 0, t=1.0: 1, t=1.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 7  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `cuenta`@t=0.5: esperado 0±0, obtenido 0 |
| ✅ | `cuenta` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 1 | 1 | 0 | 0 | 0 | 0 |
| 1.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 1 | 0.1429 | 0.378 | 0 | 0 | decreciente |
| `reset` | 0 | 1 | 0.1429 | 0.378 | 0 | 0 | decreciente |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `desbordamiento`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

En t=1.0, ambos evento y reset tienen flanco ascendente simultaneamente. Segun Modelica when/elsewhen, la clausula reset (elsewhen) tiene prioridad sobre evento (when). El resultado debe ser cuenta=0, no 1. Si el codegen invierte la prioridad, cuenta=1. Despues de t=1.5 (ambos bajan), no hay mas flancos: cuenta=0 al final.
