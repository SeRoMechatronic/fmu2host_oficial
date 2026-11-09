# TC-CS-003 — u1 menor que u2

## Descripcion del test

u1=1.0, u2=4.0: active=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=1.0`  
`u2=4.0`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 5.0±1e-09, obtenido 5 |
| ✅ | `y_prod` final: esperado 4.0±1e-09, obtenido 4 |
| ✅ | `active` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 4 | 0 | 4 | 5 |
| 0.1 | 1 | 4 | 0 | 4 | 5 |
| 0.2 | 1 | 4 | 0 | 4 | 5 |
| 0.4 | 1 | 4 | 0 | 4 | 5 |
| 0.5 | 1 | 4 | 0 | 4 | 5 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `u2` | 4 | 4 | 4 | 0 | 4 | 4 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 4 | 4 | 4 | 0 | 4 | 4 | constante |
| `y_sum` | 5 | 5 | 5 | 0 | 5 | 5 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=1, `u2`=4, `active`=0, `y_prod`=4, `y_sum`=5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u1`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Cuando u2 domina (4.0 > 1.0), active permanece false. La suma da 5.0 y el producto 4.0. Verifica que la comparacion es correcta cuando los roles se invierten respecto al caso TC-CS-001.
