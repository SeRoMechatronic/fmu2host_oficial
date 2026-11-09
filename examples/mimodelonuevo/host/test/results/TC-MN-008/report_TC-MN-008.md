# TC-MN-008 — Entrada negativa — filtro rastrea valores negativos

## Descripcion del test

entrada=-1.0: salida converge a ≈-0.993, flag_salida=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=-1.0`  
`flag_activo=1`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada` final: esperado -0.993±0.01, obtenido -0.993262 |
| ✅ | `flag_salida` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | -1 | 0 | 0 |
| 0.01 | 1 | -1 | 0 | -0.00995 |
| 0.02 | 1 | -1 | 0 | -0.0198 |
| 2.51 | 1 | -1 | 0 | -0.9187 |
| 5 | 1 | -1 | 0 | -0.9933 |
| 5 | 1 | -1 | 0 | -0.9933 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | -1 | -1 | -1 | 0 | -1 | -1 | constante |
| `flag_salida` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_filtrada` | -0.9933 | 0 | -0.8011 | 0.2473 | 0 | -0.9933 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `salida_filtrada`: valor final = -0.9933 (arranca en 0, delta = 0.9933).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=-1, `flag_salida`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `flag_salida`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El filtro maneja correctamente entradas negativas. La salida converge a -1*(1-e^-5) ≈ -0.993, permaneciendo siempre negativa (< 0.5), por lo que flag_salida es siempre false. Verifica el manejo de signos en fmi2SetReal y en la solucion de la ODE.
