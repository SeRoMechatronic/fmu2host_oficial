# TC-CT-009 — Ambas entradas en cero — ledAlcanzado, sin demanda

## Descripcion del test

temperatura=0.0, consigna=0.0: error=0, ventilador=0, ledAlcanzado=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.0`  
`consigna=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `ledAlcanzado` final: esperado 1±0, obtenido 1 |
| ✅ | `ledPorEncima` final: esperado 0±0, obtenido 0 |
| ✅ | `ledPorDebajo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 1 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 | 0 | 0 |
| 0.1 | 0 | 0 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `temperatura` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledAlcanzado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ventilador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=0, `temperatura`=0, `ledAlcanzado`=1, `ledPorDebajo`=0, `ledPorEncima`=0, `ventilador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `consigna`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `temperatura`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `ledAlcanzado`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Limite inferior: temperatura=consigna=0 → error=0. ventilador=0 (sin demanda). ledAlcanzado=TRUE. Verifica la estabilidad en el extremo inferior del rango [0,1]. No debe haber residuos de precision flotante que activen un LED equivocado con valores cero.
