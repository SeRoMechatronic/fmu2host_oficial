# TC-MN-004 — Cruce de umbral flag_salida en t≈0.693 s

## Descripcion del test

flag_salida cambia a true cuando salida_filtrada cruza 0.5.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.5 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=1.0`  
`flag_activo=1`

## Simulacion: ME-RK4

- Pasos simulados: 1502  |  Tiempo total: 1.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `flag_salida`@t=0.6: esperado 0±0, obtenido 0 |
| ✅ | `flag_salida`@t=0.75: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.001 | 1 | 1 | 0 | 0.0009995 |
| 0.002 | 1 | 1 | 0 | 0.001998 |
| 0.751 | 1 | 1 | 1 | 0.5281 |
| 1.5 | 1 | 1 | 1 | 0.7769 |
| 1.5 | 1 | 1 | 1 | 0.7769 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `flag_salida` | 0 | 1 | 0.5379 | 0.4987 | 0 | 1 | creciente |
| `salida_filtrada` | 0 | 0.7769 | 0.4822 | 0.2205 | 0 | 0.7769 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 1000 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El cruce de 0.5 ocurre en t=ln(2)≈0.693 s. Antes (t=0.6 s), la salida es 1-e^-0.6≈0.451<0.5, por lo que flag_salida=false. Despues (t=0.75 s), la salida es 1-e^-0.75≈0.528>0.5, flag_salida=true. Verifica que el umbral booleano de salida se calcula correctamente.
