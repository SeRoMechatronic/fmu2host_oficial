# TC-ES-012 — Ciclo de parada y reinicio

## Descripcion del test

Arrancar→etapa1, luego parar→idle, luego arrancar→etapa1 fresco.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0, t=6.1: 1, t=6.2: 0  
`parar`: t=0: 0, t=5.0: 1, t=5.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=3.0: esperado 1±0, obtenido 0 |
| ✅ | `etapa_actual`@t=5.5: esperado 0±0, obtenido 0 |
| ❌ | `etapa_actual`@t=7.0: esperado 1±0, obtenido 0 |
| ✅ | `progreso_etapa`@t=6.5: esperado 0.0±0.15, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 5.1 | 0.8 | 0 | 1 | 0 | 0 | 0 | 0 |
| 10 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.01961 | 0.1393 | 0 | 0 | estable |
| `parar` | 0 | 1 | 0.04902 | 0.217 | 0 | 0 | estable |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 4:**
  - `etapa_actual`@t=3.0: esperado 1±0, obtenido 0
  - `etapa_actual`@t=7.0: esperado 1±0, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Convergencia** de `parar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_previa`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `arrancar`: tasa de cambio maxima = 10 unidades/s.
**Dinamica rapida** en `parar`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (2 checks OK, 2 FAIL)

Ciclo completo: arrancar en t=0.1 → etapa=1 en t=3. Parar en t=5 → idle (etapa=0) en t=5.5. Segundo arrancar en t=6.1 → etapa=1 fresca con temporizador≈0 en t=6.5 (progreso≈0). Verifica que tras parar el temporizador se resetea y el reinicio parte de cero.
