# TC-CT-008 — Escalon en la consigna — ledPorEncima activo despues del cambio

## Descripcion del test

t=5: consigna 0.50→0.70 (escalon +20 grados). ledPorEncima cambia a true.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 7.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.5`  
`consigna=0.5`  
`consigna`: t=0: 0.5, t=5.0: 0.7

## Simulacion: ME-RK4

- Pasos simulados: 72  |  Tiempo total: 7 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ledAlcanzado`@t=4.9: esperado 1±0, obtenido 1 |
| ✅ | `ledPorEncima` == 1 eventualmente: OK |
| ✅ | `ledAlcanzado`@t=7.0: esperado 0±0, obtenido 0 |
| ✅ | `ventilador`@t=5.1: esperado 0.4±0.05, obtenido 0.4 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 0.2 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 3.6 | 0.5 | 0.5 | 1 | 0 | 0 | 0 |
| 7 | 0.7 | 0.5 | 0 | 0 | 1 | 0.59 |
| 7 | 0.7 | 0.5 | 0 | 0 | 1 | 0.59 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.7 | 0.5583 | 0.09154 | 0.5 | 0.7 | creciente |
| `temperatura` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `ledAlcanzado` | 0 | 1 | 0.7222 | 0.451 | 1 | 0 | decreciente |
| `ledPorDebajo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ledPorEncima` | 0 | 1 | 0.2778 | 0.451 | 0 | 1 | creciente |
| `ventilador` | 0 | 0.59 | 0.1457 | 0.2309 | 0 | 0.59 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `consigna`: valor final = 0.7 (arranca en 0.5, delta = 0.2).
**Convergencia** de `ledAlcanzado`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `ledPorEncima`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `temperatura`=0.5, `ledPorDebajo`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledPorDebajo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

Antes del escalon (t<5): error=0, ledAlcanzado=TRUE. Inmediatamente despues (t=5.1): consigna=0.70, temperatura=0.50, error=(0.70-0.50)*100=20 grados. ledPorEncima=TRUE, ledAlcanzado=FALSE. ventilador ≈ Kp*20/100 = 0.40 (componente proporcional dominante justo despues del escalon). Verifica la respuesta transitoria al escalon.
