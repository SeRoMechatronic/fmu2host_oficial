# TC-SM-006 — Modo Automatico — salida fija al 50%

## Descripcion del test

modo_operacion=1: salida fija=0.5 independientemente de consigna.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=1`  
`consigna_manual=0.9`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 0.5±1e-09, obtenido 0.5 |
| ✅ | `codigo_estado` final: esperado 10±0, obtenido 10 |
| ✅ | `fallo_modo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 1 | 10 | 0 | 0.5 |
| 0.1 | 0.9 | 1 | 10 | 0 | 0.5 |
| 0.2 | 0.9 | 1 | 10 | 0 | 0.5 |
| 0.1 | 0.9 | 1 | 10 | 0 | 0.5 |
| 0.2 | 0.9 | 1 | 10 | 0 | 0.5 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `modo_operacion` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `codigo_estado` | 10 | 10 | 10 | 0 | 10 | 10 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0.9, `modo_operacion`=1, `codigo_estado`=10, `fallo_modo`=0, `salida_actuador`=0.5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `modo_operacion`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_modo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

En modo Automatico (1), el sistema ignora la consigna manual y aplica un setpoint interno fijo del 50%. Aunque consigna_manual=0.90, la salida es 0.5. El codigo_estado=10 identifica el modo Automatico. Este comportamiento modela un controlador autonomo que no acepta interferencia manual.
