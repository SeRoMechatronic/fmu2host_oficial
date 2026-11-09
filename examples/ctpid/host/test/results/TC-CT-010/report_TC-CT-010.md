# TC-CT-010 — Ambas entradas al maximo — ledAlcanzado, sin demanda

## Descripcion del test

temperatura=1.0, consigna=1.0: error=0, ventilador=0, ledAlcanzado=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=1.0`  
`consigna=1.0`

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
| ✅ | `ventilador` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 1 | 0 | 0 | 0 |
| 0.1 | 1 | 1 | 1 | 0 | 0 | 0 |
| 0 | 1 | 1 | 1 | 0 | 0 | 0 |
| 0.1 | 1 | 1 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `temperatura` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `ledAlcanzado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ventilador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 5 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=1, `temperatura`=1, `ledAlcanzado`=1, `ledPorDebajo`=0, `ledPorEncima`=0, `ventilador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `consigna`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `temperatura`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `ledAlcanzado`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (5 checks OK, 0 FAIL)

Limite superior: temperatura=consigna=1.0 → error=0. Simetrico a TC-CT-009 pero en el extremo superior. ventilador=0, ledAlcanzado=TRUE. Verifica que el calculo con T_max=100 no causa desbordamiento ni precision flotante que genere un error artificial de epsilon.
