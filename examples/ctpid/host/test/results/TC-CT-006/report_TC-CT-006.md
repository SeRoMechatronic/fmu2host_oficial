# TC-CT-006 — Demanda maxima — ventilador saturado a 1.0

## Descripcion del test

temperatura=0.0, consigna=1.0: error=100deg, pid_raw=200, ventilador=1.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.0`  
`consigna=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `ledPorEncima` final: esperado 1±0, obtenido 1 |
| ✅ | `ledAlcanzado` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 0 | 1 |
| 0.1 | 1 | 0 | 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 1 | 0 | 0 | 1 |
| 0.1 | 1 | 0 | 0 | 0 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `temperatura` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledAlcanzado` | 0 | 1 | 0.5 | 0.7071 | 1 | 0 | variable |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 1 | 0.5 | 0.7071 | 0 | 1 | variable |
| `ventilador` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=1, `temperatura`=0, `ledPorDebajo`=0, `ventilador`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `consigna`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `temperatura`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `ledPorDebajo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

error = (1.0-0.0)*100 = 100 grados. pid_raw = 2.0*100 = 200. ventilador = clamp(200/100, 0, 1) = clamp(2.0, 0, 1) = 1.0. El ventilador satura al maximo. ledPorEncima=TRUE (100 > 0+1). Verifica que el clamp es hacia arriba (1.0) correctamente.
