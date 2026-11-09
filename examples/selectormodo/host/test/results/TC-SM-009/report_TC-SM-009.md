# TC-SM-009 — Modo invalido — por encima del rango

## Descripcion del test

modo_operacion=5 debe activar fallo_modo=true y salida=0.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`modo_operacion=5`  
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
| 0 | 0.5 | 5 | -1 | 1 | 0 |
| 0.1 | 0.5 | 5 | -1 | 1 | 0 |
| 0.2 | 0.5 | 5 | -1 | 1 | 0 |
| 0.1 | 0.5 | 5 | -1 | 1 | 0 |
| 0.2 | 0.5 | 5 | -1 | 1 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna_manual` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `modo_operacion` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `codigo_estado` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `fallo_modo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `salida_actuador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna_manual`=0.5, `modo_operacion`=5, `codigo_estado`=-1, `fallo_modo`=1, `salida_actuador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fallo_modo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `salida_actuador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Modo invalido por exceso (5, cuando el maximo es 2). El comportamiento es identico al modo invalido por defecto: salida segura a 0, codigo -1, y fallo_modo activado. Verifica que el rango valido [0,2] esta correctamente delimitado en ambos extremos.
