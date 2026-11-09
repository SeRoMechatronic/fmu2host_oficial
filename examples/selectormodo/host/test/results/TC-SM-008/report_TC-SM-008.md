# TC-SM-008 — Modo invalido — por debajo del rango

## Descripcion del test

modo_operacion=-1 debe activar fallo_modo=true y salida=0.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=-1`  
`consigna_manual=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `codigo_estado` final: esperado -1±0, obtenido -1 |
| ✅ | `fallo_modo` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | -1 | -1 | 1 | 0 |
| 0.1 | 0.5 | -1 | -1 | 1 | 0 |
| 0.2 | 0.5 | -1 | -1 | 1 | 0 |
| 0.1 | 0.5 | -1 | -1 | 1 | 0 |
| 0.2 | 0.5 | -1 | -1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `modo_operacion` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `codigo_estado` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `fallo_modo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0.5, `modo_operacion`=-1, `codigo_estado`=-1, `fallo_modo`=1, `salida_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fallo_modo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `salida_actuador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Un modo de operacion invalido (-1) activa fallo_modo y forza la salida a cero como medida de seguridad. codigo_estado=-1 es el codigo de fallo. Este comportamiento defensivo es esencial: ante un comando de modo no reconocido, el sistema debe fallar de forma segura en lugar de comportarse de forma impredecible.
