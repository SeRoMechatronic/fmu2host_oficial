# TC-ES-011 — Progreso clamped a 1.0 cuando sensor bloquea el avance

## Descripcion del test

Con sensor < 0.5 y temporizador > duracion: progreso = 1.0 (clamped).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 20.0 s |
| Paso de integracion | 0.2 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.3`  
`arrancar`: t=0: 0, t=0.2: 1, t=0.4: 0

## Simulacion: ME-RK4

- Pasos simulados: 201  |  Tiempo total: 20 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=15.0: esperado 1±0, obtenido 0 |
| ❌ | `progreso_etapa`@t=15.0: esperado 1.0±0.01, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.3 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.3 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.3 | 1 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0.3 | 0 | 0 | 0 | 0 | 0 | 0 |
| 19.9 | 0.3 | 0 | 0 | 0 | 0 | 0 | 0 |
| 20 | 0.3 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `arrancar` | 0 | 1 | 0.00995 | 0.0995 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 2:**
  - `etapa_actual`@t=15.0: esperado 1±0, obtenido 0
  - `progreso_etapa`@t=15.0: esperado 1.0±0.01, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.3, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 2 FAIL)

Con sensor=0.3 < 0.5, el secuenciador no puede avanzar. El temporizador crece mas alla de duracion_etapa=10. progreso=min(1.0, timer/10): cuando timer>10, progreso se clampea a 1.0. Verifica que el clamp de progreso funciona correctamente y que la variable no supera 1.0.
