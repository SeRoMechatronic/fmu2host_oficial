# TC-ES-003 — Progreso dentro de la etapa 1 en t=5 s

## Descripcion del test

Tras arrancar, a t=5s: etapa_actual=1, progreso≈0.50.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 7.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0

## Simulacion: ME-RK4

- Pasos simulados: 72  |  Tiempo total: 7 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=5.1: esperado 1±0, obtenido 0 |
| ❌ | `progreso_etapa`@t=5.1: esperado 0.5±0.05, obtenido 0 |
| ✅ | `secuencia_completa`@t=5.1: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 3.6 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 7 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 7 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.01389 | 0.1179 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 3:**
  - `etapa_actual`@t=5.1: esperado 1±0, obtenido 0
  - `progreso_etapa`@t=5.1: esperado 0.5±0.05, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 2 FAIL)

Tras el flanco de arrancar (t≈0.1), la secuencia entra en etapa=1. El temporizador crece a razon de 1 s/s. En t≈5.1 s (5 s despues): temporizador≈5.0, progreso=min(1.0, 5/10)=0.50. La etapa no avanza hasta que temporizador>=10 Y sensor>0.5.
