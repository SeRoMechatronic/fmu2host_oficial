# TC-PV-010 — Valor a mitad de rango — pot=0.50

## Descripcion del test

pot=0.50 activa LED1 y LED2, no LED3.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led1` final: esperado 1±0, obtenido 1 |
| ✅ | `led2` final: esperado 1±0, obtenido 1 |
| ✅ | `led3` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 1 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 1 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 1 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 1 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 1 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led4` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=0.5, `led1`=1, `led2`=1, `led3`=0, `led4`=0, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led3`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

A mitad del rango (0.50), el VUmetro muestra 2 de 5 LEDs. El tercer LED requiere >= 0.60, que no se alcanza con 0.50. Confirma el comportamiento esperado en el punto medio de la escala.
