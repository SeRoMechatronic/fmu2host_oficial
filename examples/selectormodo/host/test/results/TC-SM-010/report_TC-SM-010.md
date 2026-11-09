# TC-SM-010 — Limite de modo — exactamente 2 es Emergencia valida

## Descripcion del test

modo_operacion=2 es el maximo valido: debe ser Emergencia, no fallo.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=2`  
`consigna_manual=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_modo` final: esperado 0±0, obtenido 0 |
| ✅ | `codigo_estado` final: esperado 99±0, obtenido 99 |
| ✅ | `salida_actuador` final: esperado 0.0±1e-09, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 2 | 99 | 0 | 0 |
| 0.1 | 0 | 2 | 99 | 0 | 0 |
| 0.2 | 0 | 2 | 99 | 0 | 0 |
| 0.1 | 0 | 2 | 99 | 0 | 0 |
| 0.2 | 0 | 2 | 99 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `modo_operacion` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `codigo_estado` | 99 | 99 | 99 | 0 | 99 | 99 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0, `modo_operacion`=2, `codigo_estado`=99, `fallo_modo`=0, `salida_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `consigna_manual`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `fallo_modo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `salida_actuador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El modo 2 (Emergencia) es el limite superior valido del rango [0,2]. fallo_modo=false confirma que el selector no lo interpreta como invalido. Este test hace de guardia contra errores off-by-one en la condicion de validacion: si el rango se implementara como [0,1] por error, el modo 2 se clasificaria como fallo en lugar de emergencia.
