# TC-ES-009 — Secuencia completa — secuencia_completa=true al finalizar

## Descripcion del test

5 etapas x 10 s = ~50 s: secuencia_completa=true, etapa vuelve a 0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 55.0 s |
| Paso de integracion | 0.2 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.2: 1, t=0.4: 0

## Simulacion: ME-RK4

- Pasos simulados: 551  |  Tiempo total: 55 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `secuencia_completa` == 1 eventualmente: nunca (max=0, min=0) |
| ✅ | `etapa_actual` final: esperado 0±0, obtenido 0 |
| ❌ | `etapa_previa` == 5 eventualmente: nunca (max=0, min=0) |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 27.5 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 54.9 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 55 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.00363 | 0.06019 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 3:**
  - `secuencia_completa` == 1 eventualmente: nunca (max=0, min=0)
  - `etapa_previa` == 5 eventualmente: nunca (max=0, min=0)
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 2 FAIL)

La secuencia completa pasa por 5 etapas de 10 s cada una (con sensor=0.8). Duracion total ≈50 s + tiempo de transicion. Al completar la etapa 5, secuencia_completa=TRUE (pulso de 1 paso) y etapa_actual vuelve a 0. etapa_previa=5 registra que la ultima etapa completada fue la 5.
