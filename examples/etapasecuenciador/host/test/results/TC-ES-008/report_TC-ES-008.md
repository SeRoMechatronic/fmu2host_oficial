# TC-ES-008 — Arrancar ignorado si ya en ejecucion

## Descripcion del test

Flanco de arrancar mientras en etapa 2: etapa_actual permanece en 2.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 25.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`  
`arrancar`: t=0: 0, t=0.1: 1, t=0.2: 0, t=13.0: 1, t=13.5: 0

## Simulacion: ME-RK4

- Pasos simulados: 251  |  Tiempo total: 25 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ❌ | `etapa_actual`@t=12.5: esperado 2±0, obtenido 0 |
| ❌ | `etapa_actual`@t=14.0: esperado 2±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 1 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 12.5 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 24.9 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 25 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 1 | 0.0239 | 0.1531 | 0 | 0 | estable |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**❌ 2 check(s) fallados de 2:**
  - `etapa_actual`@t=12.5: esperado 2±0, obtenido 0
  - `etapa_actual`@t=14.0: esperado 2±0, obtenido 0
**Convergencia** de `arrancar`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `etapa_actual`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `arrancar`: tasa de cambio maxima = 10 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ❌ FAIL** (0 checks OK, 2 FAIL)

En t≈12.5 la secuencia esta en etapa=2. Segundo flanco de arrancar en t=13: como la condicion es 'when edge(arrancar) and etapa==0', el flanco se ignora porque etapa!=0. La secuencia permanece en etapa=2 sin reiniciarse. Verifica la condicion de guarda del arranque.
