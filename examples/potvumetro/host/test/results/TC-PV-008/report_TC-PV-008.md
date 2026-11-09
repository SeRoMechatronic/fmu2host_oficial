# TC-PV-008 — Justo por debajo de escala completa — pot=0.999

## Descripcion del test

pot=0.999 activa LED1 a LED4, pero NO LED5.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=0.999`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led4` final: esperado 1±0, obtenido 1 |
| ✅ | `led5` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.999 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 0.999 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 0.999 | 1 | 1 | 1 | 1 | 0 |
| 0.1 | 0.999 | 1 | 1 | 1 | 1 | 0 |
| 0.2 | 0.999 | 1 | 1 | 1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 0.999 | 0.999 | 0.999 | 0 | 0.999 | 0.999 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led4` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=0.999, `led1`=1, `led2`=1, `led3`=1, `led4`=1, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led3`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Un valor casi a escala completa (0.999) aun no activa LED5, cuyo umbral es exactamente 1.0. Este test critico verifica que el LED de pico (rojo) no se activa prematuramente antes de que la senal llegue al maximo real.
