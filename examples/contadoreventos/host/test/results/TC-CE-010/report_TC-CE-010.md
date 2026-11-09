# TC-CE-010 — BCD en valor limite 99 — decenas=9, unidades=9

## Descripcion del test

Exactamente 99 eventos: cuenta=99, decenas=9, unidades=9, desbordamiento=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.9 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`  
`evento`: t=0: 0, t=0.1: 1, t=0.2: 0, t=0.3: 1, t=0.4: 0, t=0.5: 1, t=0.6: 0, t=0.7: 1, t=0.8: 0, t=0.9: 1, t=1.0: 0, t=1.1: 1, t=1.2: 0, t=1.3: 1, t=1.4: 0, t=1.5: 1, t=1.6: 0, t=1.7: 1, t=1.8: 0, t=1.9: 1, t=2.0: 0, t=2.1: 1, t=2.2: 0, t=2.3: 1, t=2.4: 0, t=2.5: 1, t=2.6: 0, t=2.7: 1, t=2.8: 0, t=2.9: 1, t=3.0: 0, t=3.1: 1, t=3.2: 0, t=3.3: 1, t=3.4: 0, t=3.5: 1, t=3.6: 0, t=3.7: 1, t=3.8: 0, t=3.9: 1, t=4.0: 0, t=4.1: 1, t=4.2: 0, t=4.3: 1, t=4.4: 0, t=4.5: 1, t=4.6: 0, t=4.7: 1, t=4.8: 0, t=4.9: 1, t=5.0: 0, t=5.1: 1, t=5.2: 0, t=5.3: 1, t=5.4: 0, t=5.5: 1, t=5.6: 0, t=5.7: 1, t=5.8: 0, t=5.9: 1, t=6.0: 0, t=6.1: 1, t=6.2: 0, t=6.3: 1, t=6.4: 0, t=6.5: 1, t=6.6: 0, t=6.7: 1, t=6.8: 0, t=6.9: 1, t=7.0: 0, t=7.1: 1, t=7.2: 0, t=7.3: 1, t=7.4: 0, t=7.5: 1, t=7.6: 0, t=7.7: 1, t=7.8: 0, t=7.9: 1, t=8.0: 0, t=8.1: 1, t=8.2: 0, t=8.3: 1, t=8.4: 0, t=8.5: 1, t=8.6: 0, t=8.7: 1, t=8.8: 0, t=8.9: 1, t=9.0: 0, t=9.1: 1, t=9.2: 0, t=9.3: 1, t=9.4: 0, t=9.5: 1, t=9.6: 0, t=9.7: 1, t=9.8: 0, t=9.9: 1, t=10.0: 0, t=10.1: 1, t=10.2: 0, t=10.3: 1, t=10.4: 0, t=10.5: 1, t=10.6: 0, t=10.7: 1, t=10.8: 0, t=10.9: 1, t=11.0: 0, t=11.1: 1, t=11.2: 0, t=11.3: 1, t=11.4: 0, t=11.5: 1, t=11.6: 0, t=11.7: 1, t=11.8: 0, t=11.9: 1, t=12.0: 0, t=12.1: 1, t=12.2: 0, t=12.3: 1, t=12.4: 0, t=12.5: 1, t=12.6: 0, t=12.7: 1, t=12.8: 0, t=12.9: 1, t=13.0: 0, t=13.1: 1, t=13.2: 0, t=13.3: 1, t=13.4: 0, t=13.5: 1, t=13.6: 0, t=13.7: 1, t=13.8: 0, t=13.9: 1, t=14.0: 0, t=14.1: 1, t=14.2: 0, t=14.3: 1, t=14.4: 0, t=14.5: 1, t=14.6: 0, t=14.7: 1, t=14.8: 0, t=14.9: 1, t=15.0: 0, t=15.1: 1, t=15.2: 0, t=15.3: 1, t=15.4: 0, t=15.5: 1, t=15.6: 0, t=15.7: 1, t=15.8: 0, t=15.9: 1, t=16.0: 0, t=16.1: 1, t=16.2: 0, t=16.3: 1, t=16.4: 0, t=16.5: 1, t=16.6: 0, t=16.7: 1, t=16.8: 0, t=16.9: 1, t=17.0: 0, t=17.1: 1, t=17.2: 0, t=17.3: 1, t=17.4: 0, t=17.5: 1, t=17.6: 0, t=17.7: 1, t=17.8: 0, t=17.9: 1, t=18.0: 0, t=18.1: 1, t=18.2: 0, t=18.3: 1, t=18.4: 0, t=18.5: 1, t=18.6: 0, t=18.7: 1, t=18.8: 0, t=18.9: 1, t=19.0: 0, t=19.1: 1, t=19.2: 0, t=19.3: 1, t=19.4: 0, t=19.5: 1, t=19.6: 0, t=19.7: 1, t=19.8: 0

## Simulacion: ME-RK4

- Pasos simulados: 210  |  Tiempo total: 20.9 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta` final: esperado 99±0, obtenido 0 |
| ❌ | `decenas` final: esperado 9±0, obtenido 0 |
| ❌ | `unidades` final: esperado 9±0, obtenido 0 |
| ❌ | `desbordamiento` final: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 20.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 20.9 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 1 | 0.4714 | 0.5004 | 0 | 0 | decreciente |
| `reset` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 4 check(s) fallados de 4:**
  - `cuenta` final: esperado 99±0, obtenido 0
  - `decenas` final: esperado 9±0, obtenido 0
  - `unidades` final: esperado 9±0, obtenido 0
  - `desbordamiento` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `reset`=0, `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `reset`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `evento`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 4 FAIL)

99 eventos llevan el contador exactamente a 99 (sin saturar en 98). decenas=div(99,10)=9, unidades=mod(99,10)=9. desbordamiento=TRUE (99 >= 99). Verifica el valor limite exacto: la condicion desbordamiento usa >= no >. Si usara >, no habria desbordamiento con 99.
