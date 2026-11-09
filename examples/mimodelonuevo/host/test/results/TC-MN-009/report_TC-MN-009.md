# TC-MN-009 — Salida siempre positiva y creciente durante activacion

## Descripcion del test

Con entrada=1.0 y activo=true, salida es monotona creciente.

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

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada` monotona creciente: OK |
| ✅ | `salida_filtrada` >= 0.0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.01 | 1 | 1 | 0 | 0.00995 |
| 0.02 | 1 | 1 | 0 | 0.0198 |
| 2.51 | 1 | 1 | 1 | 0.9187 |
| 5 | 1 | 1 | 1 | 0.9933 |
| 5 | 1 | 1 | 1 | 0.9933 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `flag_salida` | 0 | 1 | 0.8606 | 0.3468 | 0 | 1 | creciente |
| `salida_filtrada` | 0 | 0.9933 | 0.8011 | 0.2473 | 0 | 0.9933 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `salida_filtrada`: valor final = 0.9933 (arranca en 0, delta = 0.9933).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La respuesta al escalon de un filtro de primer orden es monotonamente creciente (exponencial creciente). Cualquier oscilacion en salida_filtrada indicaria un error en la integracion de la ODE tau*dx/dt = u-x.
