# TC-CT-003 — Setpoint por debajo — sobretemperatura, ventilador=0

## Descripcion del test

temperatura=0.70, consigna=0.50: error=-20deg, ventilador=0 (clamped), ledPorDebajo=true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.7`  
`consigna=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `ledPorDebajo` final: esperado 1±0, obtenido 1 |
| ✅ | `ledPorEncima` final: esperado 0±0, obtenido 0 |
| ✅ | `ledAlcanzado` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.7 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.7 | 0 | 1 | 0 | 0 |
| 0 | 0.5 | 0.7 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.7 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `temperatura` | 0.7 | 0.7 | 0.7 | 0 | 0.7 | 0.7 | constante |
| `ledAlcanzado` | 0 | 1 | 0.5 | 0.7071 | 1 | 0 | variable |
| `ledPorDebajo` | 0 | 1 | 0.5 | 0.7071 | 0 | 1 | variable |
| `ledPorEncima` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ventilador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=0.5, `temperatura`=0.7, `ledPorEncima`=0, `ventilador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledPorEncima`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `ventilador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

error = (0.50-0.70)*100 = -20 grados. pid_raw = Kp*(-20) = -40. ventilador = clamp(-40/100, 0, 1) = 0 (el ventilador no puede enfriar). ledPorDebajo=TRUE (50 < 70-1). Verifica que el ventilador se clampea a cero con error negativo (sobretemperatura).
