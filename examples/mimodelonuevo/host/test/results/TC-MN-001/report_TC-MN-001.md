# TC-MN-001 — Condiciones iniciales — filtro en reposo

## Descripcion del test

En t=0 con entrada=1.0 y filtro activo: salida=0, flag_salida=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=1.0`  
`flag_activo=1`

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `flag_salida`@t=0.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.001 | 1 | 1 | 0 | 0.0009995 |
| 0.002 | 1 | 1 | 0 | 0.001998 |
| 0.005 | 1 | 1 | 0 | 0.004988 |
| 0.009 | 1 | 1 | 0 | 0.00896 |
| 0.01 | 1 | 1 | 0 | 0.00995 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `flag_salida` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `salida_filtrada` | 0 | 0.00995 | 0.004983 | 0.0033 | 0 | 0.00995 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=1, `flag_salida`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `flag_salida`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El filtro de primer orden parte del estado inicial x(0)=0. Aunque la entrada es 1.0, la salida filtrada empieza en 0 y converge gradualmente. flag_salida=false porque 0.0 < 0.5. Este test verifica que la condicion inicial se respeta antes de cualquier integracion.
