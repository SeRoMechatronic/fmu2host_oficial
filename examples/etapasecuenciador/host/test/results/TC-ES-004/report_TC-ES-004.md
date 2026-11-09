# TC-ES-004 — Avance de etapa — etapa 1→2 tras 10 s con sensor confirmado

## Descripcion del test

Despues de 10 s en etapa 1 con sensor=0.8: etapa pasa a 2.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 13.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0

## Simulacion: ME-RK4

- Pasos simulados: 132  |  Tiempo total: 13 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=12.0: esperado 2±0, obtenido 0 |
| ❌ | `etapa_previa`@t=12.0: esperado 1±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 6.6 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 13 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 13 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.007576 | 0.08704 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 2:**
  - `etapa_actual`@t=12.0: esperado 2±0, obtenido 0
  - `etapa_previa`@t=12.0: esperado 1±0, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 2 FAIL)

Tras ~10 s en etapa=1 con sensor_confirmacion=0.8>0.5, la condicion de avance se cumple: temporizador>=10 AND sensor>0.5. El secuenciador pasa a etapa=2 y resetea el temporizador. etapa_previa=1 registra la etapa anterior. Verifica la logica de avance de estado.
