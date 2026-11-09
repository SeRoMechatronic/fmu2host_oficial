# TC-ES-002 — Comando de arranque — entra en etapa 1

## Descripcion del test

Flanco ascendente en arrancar: etapa_actual pasa a 1.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 3.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.5: 1, t=1.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 31  |  Tiempo total: 3 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `etapa_actual`@t=0.3: esperado 0±0, obtenido 0 |
| ❌ | `etapa_actual` == 1 eventualmente: nunca (max=0, min=0) |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1.5 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2.9 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 3 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.1935 | 0.4016 | 0 | 0 | decreciente |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 1 check(s) fallados de 2:**
  - `etapa_actual` == 1 eventualmente: nunca (max=0, min=0)
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `arrancar`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (1 checks OK, 1 FAIL)

En t=0: etapa=0 (idle). Flanco ascendente de arrancar en t=0.5. La secuencia entra en etapa=1 (primera etapa activa). El temporizador comienza en 0. Verifica que edge(arrancar) with etapa==0 es la condicion correcta para iniciar la secuencia.
