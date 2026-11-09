# TC-MN-006 — Escalon de entrada de 1.0 a 2.0 en t=5 s

## Descripcion del test

Tras convergencia a 1.0, un nuevo escalon a 2.0 inicia nuevo transitorio.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 6.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=1.0`  
`flag_activo=1`  
`entrada_principal`: t=0: 1.0, t=5.0: 2.0

## Simulacion: ME-RK4

- Pasos simulados: 602  |  Tiempo total: 6 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada`@t=5.0: esperado 0.993±0.01, obtenido 0.993262 |
| ✅ | `salida_filtrada`@t=6.0: esperado 1.632±0.03, obtenido 1.62594 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.01 | 1 | 1 | 0 | 0.00995 |
| 0.02 | 1 | 1 | 0 | 0.0198 |
| 3.01 | 1 | 1 | 1 | 0.9507 |
| 6 | 1 | 2 | 1 | 1.626 |
| 6 | 1 | 2 | 1 | 1.626 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 1 | 2 | 1.168 | 0.374 | 1 | 2 | creciente |
| `flag_salida` | 0 | 1 | 0.8837 | 0.3208 | 0 | 1 | creciente |
| `salida_filtrada` | 0 | 1.626 | 0.8951 | 0.3176 | 0 | 1.626 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `flag_activo`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `entrada_principal`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Despues de 5 tau la salida ha convergido a ≈1.0. Al aplicar el nuevo escalon a 2.0, en t=6 s (1 tau despues del escalon) la salida sera 1.0 + 1.0*(1-e^-1) ≈ 1.632. Verifica que fmi2SetReal actualiza la entrada en cada paso de simulacion correctamente.
