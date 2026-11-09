# TC-SP-007 — Parametro String 'vacio' — string vacio sin null pointer

## Descripcion del test

vacio='': el modelo no debe crashear con String de longitud 0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 34.0±1e-09, obtenido 34 |
| ✅ | `y` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 1 | 34 |
| 0.1 | 1 | 34 |
| 0.2 | 1 | 34 |
| 0.4 | 1 | 34 |
| 0.5 | 1 | 34 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `y` | 34 | 34 | 34 | 0 | 34 | 34 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=1, `y`=34 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

TEST CRITICO. El String vacio es el caso mas comun de crash en codegen de FMU: fmi2GetString devuelve '' y el codegen llama strlen(NULL) o strcpy desde NULL. Si el modelo produce y=34 sin crash, el String vacio se maneja correctamente. Un crash aqui indica un null pointer dereference en la inicializacion.
