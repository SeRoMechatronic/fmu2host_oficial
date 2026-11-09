# TC-CE-003 — Diez eventos — descomposicion BCD: decenas=1, unidades=0

## Descripcion del test

10 flancos ascendentes: cuenta=10, decenas=1, unidades=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 11.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`evento=0`  
`reset=0`  
`evento`: t=0: 0, t=0.5: 1, t=1.0: 0, t=1.5: 1, t=2.0: 0, t=2.5: 1, t=3.0: 0, t=3.5: 1, t=4.0: 0, t=4.5: 1, t=5.0: 0, t=5.5: 1, t=6.0: 0, t=6.5: 1, t=7.0: 0, t=7.5: 1, t=8.0: 0, t=8.5: 1, t=9.0: 0, t=9.5: 1, t=10.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 23  |  Tiempo total: 11 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `cuenta` final: esperado 10±0, obtenido 0 |
| ❌ | `decenas` final: esperado 1±0, obtenido 0 |
| ✅ | `unidades` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | evento | reset | cuenta | decenas | desbordamiento | unidades |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.5 | 1 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5.5 | 1 | 0 | 0 | 0 | 0 | 0 |
| 10.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 11 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `evento` | 0 | 1 | 0.4348 | 0.5069 | 0 | 0 | decreciente |
| `reset` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cuenta` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `decenas` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `desbordamiento` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `unidades` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 3:**
  - `cuenta` final: esperado 10±0, obtenido 0
  - `decenas` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `reset`=0, `cuenta`=0, `decenas`=0, `desbordamiento`=0, `unidades`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `reset`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `cuenta`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `decenas`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 2 FAIL)

10 flancos ascendentes generan cuenta=10. La descomposicion BCD: decenas=div(10,10)=1, unidades=mod(10,10)=0. Verifica la transicion de digito en la decena. Un error de off-by-one daria cuenta=9 o 11, y la descomposicion BCD seria incorrecta.
