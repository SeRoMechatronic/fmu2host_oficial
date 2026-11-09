# TC-SM-001 — Modo Manual — consigna pasada directamente

## Descripcion del test

modo_operacion=0 pasa consigna_manual=0.70 a la salida.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=0`  
`consigna_manual=0.7`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 0.7±1e-09, obtenido 0.7 |
| ✅ | `codigo_estado` final: esperado 1±0, obtenido 1 |
| ✅ | `fallo_modo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.1 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.2 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.1 | 0.7 | 0 | 1 | 0 | 0.7 |
| 0.2 | 0.7 | 0 | 1 | 0 | 0.7 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0.7 | 0.7 | 0.7 | 0 | 0.7 | 0.7 | constante |
| `modo_operacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `codigo_estado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 0.7 | 0.7 | 0.7 | 0 | 0.7 | 0.7 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0.7, `modo_operacion`=0, `codigo_estado`=1, `fallo_modo`=0, `salida_actuador`=0.7 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `modo_operacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `codigo_estado`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_modo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

En modo Manual (0), la consigna del operador se transfiere directamente al actuador. El codigo de estado 1 confirma que el modo es Manual, y fallo_modo=false indica seleccion valida. El valor exacto 0.70 confirma que no hay modificacion de la consigna en este modo.
