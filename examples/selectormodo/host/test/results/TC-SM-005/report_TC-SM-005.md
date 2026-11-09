# TC-SM-005 — Modo Manual — consigna recortada por debajo de 0.0

## Descripcion del test

consigna_manual=-0.3 debe recortarse a 0.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=0`  
`consigna_manual=-0.3`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `fallo_modo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | -0.3 | 0 | 1 | 0 | 0 |
| 0.1 | -0.3 | 0 | 1 | 0 | 0 |
| 0.2 | -0.3 | 0 | 1 | 0 | 0 |
| 0.1 | -0.3 | 0 | 1 | 0 | 0 |
| 0.2 | -0.3 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | -0.3 | -0.3 | -0.3 | 0 | -0.3 | -0.3 | constante |
| `modo_operacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `codigo_estado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=-0.3, `modo_operacion`=0, `codigo_estado`=1, `fallo_modo`=0, `salida_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `modo_operacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `codigo_estado`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_modo`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Consigna negativa recortada a cero. En muchos sistemas de control, una consigna negativa de actuador no tiene sentido fisico (ej. bomba que no puede girar al reves). El recorte inferior protege el actuador de comandos fuera de su rango fisico de operacion.
