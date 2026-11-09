# TC-PV-006 — Justo encima umbral LED3 — pot=0.61

## Descripcion del test

pot=0.61 (por encima de 0.60) activa LED1, LED2 y LED3.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=0.61`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led1` final: esperado 1±0, obtenido 1 |
| ✅ | `led2` final: esperado 1±0, obtenido 1 |
| ✅ | `led3` final: esperado 1±0, obtenido 1 |
| ✅ | `led4` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.61 | 1 | 1 | 1 | 0 | 0 |
| 0.1 | 0.61 | 1 | 1 | 1 | 0 | 0 |
| 0.2 | 0.61 | 1 | 1 | 1 | 0 | 0 |
| 0.1 | 0.61 | 1 | 1 | 1 | 0 | 0 |
| 0.2 | 0.61 | 1 | 1 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 0.61 | 0.61 | 0.61 | 0 | 0.61 | 0.61 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led4` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `led5` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=0.61, `led1`=1, `led2`=1, `led3`=1, `led4`=0, `led5`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led3`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Tres LEDs encendidos con pot=0.61 (justo encima del umbral LED3=0.60). La barra gradual muestra nivel medio-alto. Cada umbral representa el 20% del rango total.
