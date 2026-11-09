# TC-RB-007 — Anti-windup — desconexion y reconexion sin pico de corriente

## Descripcion del test

Tras carga prolongada, desconexion y reconexion: corriente acotada.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 8.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tension_bateria=0.3`  
`carga_conectada=1`  
`carga_conectada`: t=0: 1, t=5.0: 0, t=5.1: 1

## Simulacion: ME-RK4

- Pasos simulados: 802  |  Tiempo total: 8 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `corriente_carga` en [0, 1.1]: OK |
| ✅ | `corriente_carga` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | carga_conectada | tension_bateria | carga_completa | cargando | fallo_sobretension | corriente_carga |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.3 | 0 | 1 | 0 | 0 |
| 0.01 | 1 | 0.3 | 0 | 1 | 0 | 0.04407 |
| 0.02 | 1 | 0.3 | 0 | 1 | 0 | 0.08617 |
| 4.01 | 1 | 0.3 | 0 | 1 | 0 | 0.45 |
| 8 | 1 | 0.3 | 0 | 1 | 0 | 0.45 |
| 8 | 1 | 0.3 | 0 | 1 | 0 | 0.45 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `carga_conectada` | 0 | 1 | 0.9875 | 0.111 | 1 | 1 | estable |
| `tension_bateria` | 0.3 | 0.3 | 0.3 | 0 | 0.3 | 0.3 | constante |
| `carga_completa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `cargando` | 0 | 1 | 0.9875 | 0.111 | 1 | 1 | estable |
| `fallo_sobretension` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `corriente_carga` | 0 | 0.5006 | 0.4419 | 0.05014 | 0 | 0.45 | estable |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `carga_conectada`: valor final = 1 (arranca en 1, delta = 0).
**Convergencia** de `cargando`: valor final = 1 (arranca en 1, delta = 0).
**Convergencia** de `corriente_carga`: valor final = 0.45 (arranca en 0, delta = 0.45).
**Variables algebraicas constantes:** `tension_bateria`=0.3, `carga_completa`=0, `fallo_sobretension`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `carga_completa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `fallo_sobretension`:** estado final = inactivo (FALSE/0) (media = 0).
**Dinamica rapida** en `carga_conectada`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `cargando`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Tras 5 s de carga con bateria baja, los estados internos del regulador han acumulado energia. Al desconectar (t=5 s) y reconectar inmediatamente (t=5.1 s), el anti-windup debe evitar un pico de corriente superior a I_max=1.0. La corriente debe mantenerse en [0,1.1].
