# TC-ES-006 — Sensor exactamente en el umbral — sin avance (operador estricto)

## Descripcion del test

sensor=0.5 exacto: NO avanza (> es estricto, 0.5 no > 0.5).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 15.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.5`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0

## Simulacion: ME-RK4

- Pasos simulados: 152  |  Tiempo total: 15 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=13.0: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.5 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 7.6 | 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 15 | 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |
| 15 | 0.5 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `arrancar` | 0 | 1 | 0.006579 | 0.08111 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 1 check(s) fallados de 1:**
  - `etapa_actual`@t=13.0: esperado 1±0, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.5, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 1 FAIL)

sensor_confirmacion=0.5 exacto. La condicion de avance es 'sensor > 0.5' con operador estricto. 0.5 NO es mayor que 0.5, por lo que el secuenciador NO avanza aunque hayan pasado mas de 10 s. Si la condicion fuera >=, habria avance. Verifica la frontera critica del umbral de confirmacion.
