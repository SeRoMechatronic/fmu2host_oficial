# TC-MN-010 — Sin NaN ni Inf en simulacion completa

## Descripcion del test

5 segundos de simulacion del filtro sin valores invalidos.

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
| ✅ | `salida_filtrada` sin NaN/Inf: OK |

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

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `salida_filtrada`: valor final = 0.9933 (arranca en 0, delta = 0.9933).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El modelo Mi_Modelo_Nuevo tiene un nombre con guiones bajos que testa el codegen de nombres de identificadores C. Si el codegen genera funciones invalidas (ej. con guiones), el ejecutable no compila y este test no podra ejecutarse. La ejecucion exitosa confirma implicitamente que el naming es correcto.
