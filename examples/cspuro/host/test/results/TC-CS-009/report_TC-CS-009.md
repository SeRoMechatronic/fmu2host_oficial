# TC-CS-009 — Valores muy pequeños — cerca de epsilon maquina

## Descripcion del test

u1=u2=1e-15: suma=2e-15, producto=1e-30.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | CS |
| Solver | rk4 |

**Entradas:**  
`u1=1e-15`  
`u2=1e-15`

## Simulacion: CS

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_cs.png](sim_cs.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y_sum` final: esperado 2e-15±1e-25, obtenido 2e-15 |
| ✅ | `y_prod` sin NaN/Inf: OK |
| ✅ | `active` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u1 | u2 | active | y_prod | y_sum |
| --- | --- | --- | --- | --- | --- |
| 0 | 1e-15 | 1e-15 | 0 | 1e-30 | 2e-15 |
| 0.1 | 1e-15 | 1e-15 | 0 | 1e-30 | 2e-15 |
| 0.2 | 1e-15 | 1e-15 | 0 | 1e-30 | 2e-15 |
| 0.4 | 1e-15 | 1e-15 | 0 | 1e-30 | 2e-15 |
| 0.5 | 1e-15 | 1e-15 | 0 | 1e-30 | 2e-15 |

## Analisis de datos

### Simulacion: CS

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u1` | 1e-15 | 1e-15 | 1e-15 | 0 | 1e-15 | 1e-15 | constante |
| `u2` | 1e-15 | 1e-15 | 1e-15 | 0 | 1e-15 | 1e-15 | constante |
| `active` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y_prod` | 1e-30 | 1e-30 | 1e-30 | 0 | 1e-30 | 1e-30 | constante |
| `y_sum` | 2e-15 | 2e-15 | 2e-15 | 0 | 2e-15 | 2e-15 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u1`=1e-15, `u2`=1e-15, `active`=0, `y_prod`=1e-30, `y_sum`=2e-15 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `active`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Valores cerca del epsilon de maquina (1e-15). El producto (1e-30) esta cerca del subdesbordamiento de double. Se verifica que no hay NaN ni Inf y que la comparacion active da correctamente false para valores iguales muy pequenos.
