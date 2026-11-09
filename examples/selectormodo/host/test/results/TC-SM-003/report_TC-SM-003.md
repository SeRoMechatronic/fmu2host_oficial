# TC-SM-003 — Modo Manual — consigna maxima

## Descripcion del test

modo_operacion=0 con consigna_manual=1.0: salida=1.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=0`  
`consigna_manual=1.0`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_actuador` final: esperado 1.0±1e-09, obtenido 1 |
| ✅ | `codigo_estado` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | consigna_manual | modo_operacion | codigo_estado | fallo_modo | salida_actuador |
| --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0 | 1 | 0 | 1 |
| 0.1 | 1 | 0 | 1 | 0 | 1 |
| 0.2 | 1 | 0 | 1 | 0 | 1 |
| 0.1 | 1 | 0 | 1 | 0 | 1 |
| 0.2 | 1 | 0 | 1 | 0 | 1 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `modo_operacion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `codigo_estado` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_modo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_actuador` | 1 | 1 | 1 | 0 | 1 | 1 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=1, `modo_operacion`=0, `codigo_estado`=1, `fallo_modo`=0, `salida_actuador`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `consigna_manual`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `modo_operacion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `codigo_estado`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Consigna a escala completa en modo Manual. Confirma que el rango normalizado [0,1] se transmite sin recorte cuando la consigna esta exactamente en el limite superior.
