# TC-ES-001 — Estado idle inicial

## Descripcion del test

Sin arrancar: etapa_actual=0, progreso=0, secuencia_completa=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.5 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`arrancar=0`  
`parar=0`  
`sensor_confirmacion=0.8`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `etapa_actual`@t=0.0: esperado 0±0, obtenido 0 |
| ✅ | `progreso_etapa`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `secuencia_completa` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | sensor_confirmacion | arrancar | parar | progreso_etapa | etapa_actual | etapa_previa | secuencia_completa |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.2 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0.6 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0.8 | 0 | 0 | 0 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `sensor_confirmacion` | 0.8 | 0.8 | 0.8 | 0 | 0.8 | 0.8 | constante |
| `arrancar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `parar` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `progreso_etapa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_actual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `etapa_previa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `secuencia_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `sensor_confirmacion`=0.8, `arrancar`=0, `parar`=0, `progreso_etapa`=0, `etapa_actual`=0, `etapa_previa`=0, `secuencia_completa`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `arrancar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `parar`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `progreso_etapa`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Estado inicial: etapa=0 (idle), temporizador=0. Sin flanco ascendente en arrancar, el secuenciador no entra en ninguna etapa. progreso=temporizador/duracion=0/10=0. secuencia_completa=FALSE siempre. Verifica que el estado discreto se inicializa en idle.
