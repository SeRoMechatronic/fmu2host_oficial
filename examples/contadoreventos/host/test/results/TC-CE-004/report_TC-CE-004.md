# TC-CE-004 — 47 eventos — BCD arbitrario: decenas=4, unidades=7

## Descripcion del test

47 flancos ascendentes: cuenta=47, decenas=4, unidades=7.

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
`evento`: t=0: 0, t=0.1: 1, t=0.2: 0, t=0.3: 1, t=0.4: 0, t=0.5: 1, t=0.6: 0, t=0.7: 1, t=0.8: 0, t=0.9: 1, t=1.0: 0, t=1.1: 1, t=1.2: 0, t=1.3: 1, t=1.4: 0, t=1.5: 1, t=1.6: 0, t=1.7: 1, t=1.8: 0, t=1.9: 1, t=2.0: 0, t=2.1: 1, t=2.2: 0, t=2.3: 1, t=2.4: 0, t=2.5: 1, t=2.6: 0, t=2.7: 1, t=2.8: 0, t=2.9: 1, t=3.0: 0, t=3.1: 1, t=3.2: 0, t=3.3: 1, t=3.4: 0, t=3.5: 1, t=3.6: 0, t=3.7: 1, t=3.8: 0, t=3.9: 1, t=4.0: 0, t=4.1: 1, t=4.2: 0, t=4.3: 1, t=4.4: 0, t=4.5: 1, t=4.6: 0, t=4.7: 1, t=4.8: 0, t=4.9: 1, t=5.0: 0, t=5.1: 1, t=5.2: 0, t=5.3: 1, t=5.4: 0, t=5.5: 1, t=5.6: 0, t=5.7: 1, t=5.8: 0, t=5.9: 1, t=6.0: 0, t=6.1: 1, t=6.2: 0, t=6.3: 1, t=6.4: 0, t=6.5: 1, t=6.6: 0, t=6.7: 1, t=6.8: 0, t=6.9: 1, t=7.0: 0, t=7.1: 1, t=7.2: 0, t=7.3: 1, t=7.4: 0, t=7.5: 1, t=7.6: 0, t=7.7: 1, t=7.8: 0, t=7.9: 1, t=8.0: 0, t=8.1: 1, t=8.2: 0, t=8.3: 1, t=8.4: 0, t=8.5: 1, t=8.6: 0, t=8.7: 1, t=8.8: 0, t=8.9: 1, t=9.0: 0, t=9.1: 1, t=9.2: 0, t=9.3: 1, t=9.4: 0

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta` final: esperado 47±0, obtenido 0 |
| ❌ | `decenas` final: esperado 4±0, obtenido 0 |
| ❌ | `unidades` final: esperado 7±0, obtenido 0 |
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
| `evento` | 0 | 1 | 0.4608 | 0.5009 | 0 | 0 | decreciente |
| `reset` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 3 check(s) fallados de 4:**
  - `cuenta` final: esperado 47±0, obtenido 0
  - `decenas` final: esperado 4±0, obtenido 0
  - `unidades` final: esperado 7±0, obtenido 0
**Variables algebraicas constantes:** `reset`=0, `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `reset`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `evento`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 3 FAIL)

47 eventos: cuenta=47, decenas=div(47,10)=4, unidades=mod(47,10)=7. Valor arbitrario que verifica la descomposicion BCD en un rango intermedio. desbordamiento=FALSE (47 < 99). Confirma que la aritmetica de division y modulo es exacta para enteros no triviales.
