# TC-ES-007 — Parada durante secuencia — vuelta inmediata a idle

## Descripcion del test

Flanco en parar durante etapa 3: etapa_actual=0 inmediatamente.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 35.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0  
`parar`: t=0: 0, t=25.0: 1, t=25.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 351  |  Tiempo total: 35 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=24.0: esperado 3±0, obtenido 0 |
| ✅ | `etapa_actual`@t=25.5: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 17.5 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 34.9 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 35 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.002849 | 0.05338 | 0 | 0 | estable |
| `parar` | 0 | 1 | 0.01425 | 0.1187 | 0 | 0 | estable |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 1 check(s) fallados de 2:**
  - `etapa_actual`@t=24.0: esperado 3±0, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `parar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_previa`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 1 FAIL)

En t≈24s la secuencia esta en etapa=3 (0→1→2→3, cada una 10s). Flanco ascendente en parar a t=25: el secuenciador vuelve a etapa=0 inmediatamente, reseteando temporizador. Verifica que el reset de parada tiene prioridad y que edge(parar) funciona desde cualquier etapa activa (no solo desde idle).
