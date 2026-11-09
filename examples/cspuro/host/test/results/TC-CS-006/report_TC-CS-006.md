# TC-CS-006 — Valores grandes — precision numerica

## Descripcion del test

u1=1e6, u2=1e6: suma=2e6, producto=1e12.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=1000000.0`  
`u2=1000000.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 2000000.0±1.0, obtenido 2e+06 |
| ✅ | `y_prod` final: esperado 1000000000000.0±1000000.0, obtenido 1e+12 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1e+06 | 1e+06 | 0 | 1e+12 | 2e+06 |
| 0.1 | 1e+06 | 1e+06 | 0 | 1e+12 | 2e+06 |
| 0.2 | 1e+06 | 1e+06 | 0 | 1e+12 | 2e+06 |
| 0.4 | 1e+06 | 1e+06 | 0 | 1e+12 | 2e+06 |
| 0.5 | 1e+06 | 1e+06 | 0 | 1e+12 | 2e+06 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 1e+06 | 1e+06 | 1e+06 | 0 | 1e+06 | 1e+06 | constante |
| `u2` | 1e+06 | 1e+06 | 1e+06 | 0 | 1e+06 | 1e+06 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 1e+12 | 1e+12 | 1e+12 | 0 | 1e+12 | 1e+12 | constante |
| `y_sum` | 2e+06 | 2e+06 | 2e+06 | 0 | 2e+06 | 2e+06 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=1e+06, `u2`=1e+06, `active`=0, `y_prod`=1e+12, `y_sum`=2e+06 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Magnitudes grandes (1e6) verifican que no hay perdida de precision significativa en suma y multiplicacion de doubles. La tolerancia absoluta se escala al rango del resultado esperado.
