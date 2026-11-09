# TC-CE-005 — Reset borra el contador — cuenta vuelve a 0

## Descripcion del test

30 eventos, luego flanco ascendente en reset: cuenta=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`  
`evento`: t=0: 0, t=0.1: 1, t=0.2: 0, t=0.3: 1, t=0.4: 0, t=0.5: 1, t=0.6: 0, t=0.7: 1, t=0.8: 0, t=0.9: 1, t=1.0: 0, t=1.1: 1, t=1.2: 0, t=1.3: 1, t=1.4: 0, t=1.5: 1, t=1.6: 0, t=1.7: 1, t=1.8: 0, t=1.9: 1, t=2.0: 0, t=2.1: 1, t=2.2: 0, t=2.3: 1, t=2.4: 0, t=2.5: 1, t=2.6: 0, t=2.7: 1, t=2.8: 0, t=2.9: 1, t=3.0: 0, t=3.1: 1, t=3.2: 0, t=3.3: 1, t=3.4: 0, t=3.5: 1, t=3.6: 0, t=3.7: 1, t=3.8: 0, t=3.9: 1, t=4.0: 0, t=4.1: 1, t=4.2: 0, t=4.3: 1, t=4.4: 0, t=4.5: 1, t=4.6: 0, t=4.7: 1, t=4.8: 0, t=4.9: 1, t=5.0: 0, t=5.1: 1, t=5.2: 0, t=5.3: 1, t=5.4: 0, t=5.5: 1, t=5.6: 0, t=5.7: 1, t=5.8: 0, t=5.9: 1, t=6.0: 0  
`reset`: t=0: 0, t=7.0: 1, t=7.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta`@t=5.9: esperado 30±0, obtenido 0 |
| ✅ | `cuenta` final: esperado 0±0, obtenido 0 |
| ✅ | `desbordamiento` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5.1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 1 | 0.2941 | 0.4579 | 0 | 0 | decreciente |
| `reset` | 0 | 1 | 0.04902 | 0.217 | 0 | 0 | creciente |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 1 check(s) fallados de 3:**
  - `cuenta`@t=5.9: esperado 30±0, obtenido 0
**Convergencia** de `evento`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `reset`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `desbordamiento`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `evento`: tasa de cambio maxima = 10 unidades/s.
**Dinamica rapida** en `reset`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (2 checks OK, 1 FAIL)

30 eventos llevan el contador a 30 (verificado en t≈6). Luego un flanco ascendente en reset (t=7.0) borra el contador a 0. desbordamiento=FALSE tras el reset. Verifica que el flanco de reset tiene efecto inmediato y que el contador no vuelve al valor previo al siguiente pulso de evento.
