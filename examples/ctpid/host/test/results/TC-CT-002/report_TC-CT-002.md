# TC-CT-002 — Setpoint por encima — demanda de calefaccion, ledPorEncima=true

## Descripcion del test

temperatura=0.30, consigna=0.50: error=20deg, ventilador=0.40 en t=0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.3`  
`consigna=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 0.4±0.01, obtenido 0.41 |
| ✅ | `ledPorEncima` final: esperado 1±0, obtenido 1 |
| ✅ | `ledPorDebajo` final: esperado 0±0, obtenido 0 |
| ✅ | `ledAlcanzado` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.3 | 1 | 0 | 0 | 0.4 |
| 0.1 | 0.5 | 0.3 | 0 | 0 | 1 | 0.41 |
| 0 | 0.5 | 0.3 | 1 | 0 | 0 | 0.4 |
| 0.1 | 0.5 | 0.3 | 0 | 0 | 1 | 0.41 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `temperatura` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `ledAlcanzado` | 0 | 1 | 0.5 | 0.7071 | 1 | 0 | variable |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 1 | 0.5 | 0.7071 | 0 | 1 | variable |
| `ventilador` | 0.4 | 0.41 | 0.405 | 0.007071 | 0.4 | 0.41 | variable |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=0.5, `temperatura`=0.3, `ledPorDebajo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledPorDebajo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

error = (0.50-0.30)*100 = 20 grados. En t=0 (integrador=0, der=0): pid_raw = Kp*20 = 2.0*20 = 40. ventilador = clamp(40/100,0,1) = 0.40. ledPorEncima=TRUE (50 > 30+1). Verifica la rampa proporcional inicial y que el ventilador activa con error positivo.
