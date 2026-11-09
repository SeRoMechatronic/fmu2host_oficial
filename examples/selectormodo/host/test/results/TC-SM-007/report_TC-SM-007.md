# TC-SM-007 — Modo Emergencia — salida forzada a cero

## Descripcion del test

modo_operacion=2: salida=0.0 independientemente de consigna.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=2`  
`consigna_manual=0.9`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 0.0±1e-09, obtenido 0 |
| ✅ | `codigo_estado` final: esperado 99±0, obtenido 99 |
| ✅ | `fallo_modo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 2 | 99 | 0 | 0 |
| 0.1 | 0.9 | 2 | 99 | 0 | 0 |
| 0.2 | 0.9 | 2 | 99 | 0 | 0 |
| 0.1 | 0.9 | 2 | 99 | 0 | 0 |
| 0.2 | 0.9 | 2 | 99 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `modo_operacion` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `codigo_estado` | 99 | 99 | 99 | 0 | 99 | 99 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0.9, `modo_operacion`=2, `codigo_estado`=99, `fallo_modo`=0, `salida_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fallo_modo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `salida_actuador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

El modo Emergencia (2) fuerza la salida a cero sin importar la consigna. codigo_estado=99 es un codigo especial que identifica inequivocamente la emergencia. Este mecanismo garantiza la parada segura del actuador en cualquier condicion de emergencia.
