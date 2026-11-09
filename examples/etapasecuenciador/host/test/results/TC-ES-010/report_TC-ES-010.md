# TC-ES-010 — Reinicio tras completion — nueva secuencia arranca correctamente

## Descripcion del test

Tras completion (etapa=0), nuevo flanco de arrancar: etapa=1 de nuevo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 65.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.5: 1, t=1.0: 0, t=54.0: 1, t=54.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 651  |  Tiempo total: 65 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual` == 1 eventualmente: nunca (max=0, min=0) |
| ❌ | `etapa_actual` final: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 32.5 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 64.9 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 65 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.0169 | 0.129 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 2:**
  - `etapa_actual` == 1 eventualmente: nunca (max=0, min=0)
  - `etapa_actual` final: esperado 1±0, obtenido 0
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `arrancar`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 2 FAIL)

Tras completar la primera secuencia (≈51 s), el secuenciador vuelve a etapa=0. Segundo flanco de arrancar en t=54 s: la condicion 'edge(arrancar) and etapa==0' se cumple de nuevo y la secuencia reinicia en etapa=1. Verifica que el secuenciador es reutilizable sin necesidad de reiniciar la FMU.
