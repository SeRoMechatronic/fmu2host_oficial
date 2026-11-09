# TC-CT-007 — Wind-up integral — 10 segundos de error positivo, ventilador=1.0

## Descripcion del test

temperatura=0.30, consigna=0.50 durante 10s: integrador≈200, ventilador=1.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 10.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.3`  
`consigna=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 102  |  Tiempo total: 10 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ventilador` final: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `ledPorEncima` final: esperado 1±0, obtenido 1 |
| ✅ | `ledAlcanzado` final: esperado 0±0, obtenido 0 |
| ✅ | `ventilador` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.3 | 1 | 0 | 0 | 0.4 |
| 0.1 | 0.5 | 0.3 | 0 | 0 | 1 | 0.41 |
| 0.2 | 0.5 | 0.3 | 0 | 0 | 1 | 0.42 |
| 5.1 | 0.5 | 0.3 | 0 | 0 | 1 | 0.91 |
| 10 | 0.5 | 0.3 | 0 | 0 | 1 | 1 |
| 10 | 0.5 | 0.3 | 0 | 0 | 1 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `temperatura` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `ledAlcanzado` | 0 | 1 | 0.009804 | 0.09901 | 1 | 0 | estable |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 1 | 0.9902 | 0.09901 | 0 | 1 | estable |
| `ventilador` | 0.4 | 1 | 0.8206 | 0.2014 | 0.4 | 1 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `ledAlcanzado`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `ledPorEncima`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `ventilador`: valor final = 1 (arranca en 0.4, delta = 0.6).
**Variables algebraicas constantes:** `consigna`=0.5, `temperatura`=0.3, `ledPorDebajo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledPorDebajo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Con error=20 grados constante durante 10s, der(integrador)=20 siempre. integrador(10) = 20*10 = 200. pid_raw = 2*20 + 0.5*200 + ... >> 100. ventilador = 1.0 (saturado). Verifica que la integracion acumulada de error satura el actuador — el wind-up del integrador es intencional en este modelo (sin anti-windup).
