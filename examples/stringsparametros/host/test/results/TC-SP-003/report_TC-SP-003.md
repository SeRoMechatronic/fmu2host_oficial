# TC-SP-003 — Salida numerica con entrada cero

## Descripcion del test

u=0.0: y = 0.0 * 34 = 0.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 0.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0.1 | 0 | 0 |
| 0.2 | 0 | 0 |
| 0.6 | 0 | 0 |
| 1 | 0 | 0 |
| 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `y` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=0, `y`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `u`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `y`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Entrada cero produce salida cero. El modelo no tiene estados ni integracion, es puramente algebraico (y=u*34). Con u=0, y=0 exactamente, sin residuos de los parametros String.
