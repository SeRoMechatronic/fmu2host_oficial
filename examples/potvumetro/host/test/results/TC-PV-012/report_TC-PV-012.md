# TC-PV-012 — Entrada fuera de rango — positiva alta

## Descripcion del test

pot=1.5 debe activar todos los LEDs ya que supera todos los umbrales.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`pot=1.5`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `led1` final: esperado 1±0, obtenido 1 |
| ✅ | `led5` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | pot | led1 | led2 | led3 | led4 | led5 |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1.5 | 1 | 1 | 1 | 1 | 1 |
| 0.1 | 1.5 | 1 | 1 | 1 | 1 | 1 |
| 0.2 | 1.5 | 1 | 1 | 1 | 1 | 1 |
| 0.1 | 1.5 | 1 | 1 | 1 | 1 | 1 |
| 0.2 | 1.5 | 1 | 1 | 1 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `pot` | 1.5 | 1.5 | 1.5 | 0 | 1.5 | 1.5 | constante |
| `led1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led2` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led3` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led4` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `led5` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `pot`=1.5, `led1`=1, `led2`=1, `led3`=1, `led4`=1, `led5`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `led1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led2`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `led3`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con pot=1.5, todos los umbrales (incluido 1.0) son superados por la condicion >=, por lo que todos los LEDs se encienden. Esto es diferente del caso negativo: aqui el valor es mayor que todos los umbrales en lugar de menor. Confirma el comportamiento de saturacion alta del VUmetro.
