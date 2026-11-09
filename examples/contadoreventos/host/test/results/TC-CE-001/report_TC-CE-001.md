# TC-CE-001 — Estado inicial — contador en cero

## Descripcion del test

Sin eventos ni reset: cuenta=0, decenas=0, unidades=0, desbordamiento=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `cuenta`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `decenas`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `unidades`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `desbordamiento`@t=0.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `reset` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `evento`=0, `reset`=0, `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `evento`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `reset`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El modelo arranca con contador=0. Con evento=FALSE y reset=FALSE, no se producen flancos y el contador permanece en cero. decenas=0, unidades=0 (div y mod de 0). desbordamiento=FALSE (0 < 99). Verifica que el estado discreto se inicializa correctamente.
