# TC-CT-001 — Setpoint = temperatura — ledAlcanzado activo, ventilador=0

## Descripcion del test

temperatura=0.50, consigna=0.50: error=0, ventilador=0, ledAlcanzado=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.5`  
`consigna=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `ledAlcanzado` final: esperado 1±0, obtenido 1 |
| ✅ | `ledPorEncima` final: esperado 0±0, obtenido 0 |
| ✅ | `ledPorDebajo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 0 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `ledAlcanzado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ventilador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=0.5, `temperatura`=0.5, `ledAlcanzado`=1, `ledPorDebajo`=0, `ledPorEncima`=0, `ventilador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledAlcanzado`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `ledPorDebajo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `ledPorEncima`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con consigna=temperatura=0.50, error=0. En t=0, integrador=0 y derivador=0, por lo que pid_raw=0 y ventilador=0. ledAlcanzado=TRUE porque |error|=0 <= epsilon=1.0. Ningun LED de encima o debajo activo. Verifica el punto de operacion nominal sin demanda inicial.
