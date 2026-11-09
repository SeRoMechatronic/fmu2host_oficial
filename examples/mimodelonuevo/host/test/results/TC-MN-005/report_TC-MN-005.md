# TC-MN-005 — Desactivacion — decaimiento exponencial al desactivar filtro

## Descripcion del test

Al poner flag_activo=false en t=3 s, la salida decae.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=1.0`  
`flag_activo=1`  
`flag_activo`: t=0: 1, t=3.0: 0

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada`@t=3.0: esperado 0.95±0.02, obtenido 0.950213 |
| ✅ | `salida_filtrada`@t=4.0: esperado 0.35±0.03, obtenido 0.353261 |
| ✅ | `salida_filtrada`@t=5.0: esperado 0.128±0.03, obtenido 0.129957 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.01 | 1 | 1 | 0 | 0.00995 |
| 0.02 | 1 | 1 | 0 | 0.0198 |
| 2.51 | 1 | 1 | 1 | 0.9187 |
| 5 | 0 | 1 | 0 | 0.13 |
| 5 | 0 | 1 | 0 | 0.13 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 0 | 1 | 0.5996 | 0.4905 | 1 | 0 | decreciente |
| `entrada_principal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `flag_salida` | 0 | 1 | 0.5896 | 0.4924 | 0 | 0 | decreciente |
| `salida_filtrada` | 0 | 0.9507 | 0.5741 | 0.2813 | 0 | 0.13 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_activo`: valor final = 0 (arranca en 1, delta = 1).
**Convergencia** de `flag_salida`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `entrada_principal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_activo`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

A t=3 s (3 constantes de tiempo), la salida esta a ≈0.950 del valor final. Al desactivar el filtro, la ODE cambia a tau*dx/dt=-x (decaimiento libre). En t=4 s (1s despues): 0.950*e^-1≈0.350. En t=5 s: 0.950*e^-2≈0.128. Verifica que fmi2SetBoolean modifica la ODE correctamente en tiempo real.
