# TC-ND-004 — Nivel exactamente en umbral maximo — sin alarma

## Descripcion del test

nivel_filtrado converge a 0.80 (desde 0.5): alarma_maximo=false, bomba=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`sensor_nivel=0.8`  
`valvula_manual=0`

## Simulacion: ME-RK4

- Pasos simulados: 41  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `alarma_maximo` final: esperado 0±0, obtenido 0 |
| ✅ | `bomba` final: esperado 0.0±0.05, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | valvula_manual | sensor_nivel | alarma_maximo | alarma_minimo | bomba_activa | bomba |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0.8 | 0 | 0 | 1 | 0.5 |
| 0.5 | 0 | 0.8 | 0 | 0 | 1 | 0.3673 |
| 1 | 0 | 0.8 | 0 | 0 | 1 | 0.2639 |
| 10 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 19.5 | 0 | 0.8 | 0 | 0 | 0 | 0 |
| 20 | 0 | 0.8 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `valvula_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `sensor_nivel` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `alarma_maximo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `alarma_minimo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `bomba_activa` | 0 | 1 | 0.1463 | 0.3578 | 1 | 0 | decreciente |
| `bomba` | 0 | 0.5 | 0.03769 | 0.1062 | 0.5 | 0 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `bomba_activa`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `bomba`: valor final = 0 (arranca en 0.5, delta = 0.5).
**Variables algebraicas constantes:** `valvula_manual`=0, `sensor_nivel`=0.8, `alarma_maximo`=0, `alarma_minimo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `valvula_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_maximo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `alarma_minimo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El umbral maximo usa operador estricto >. Con nivel=0.80 exacto, no hay alarma. La bomba se desactiva (error negativo: 0.5-0.8=-0.3, bomba=0.5+2*(-0.3)=-0.1 → clamped a 0.0). Simetrico al TC-ND-002 para el limite superior.
