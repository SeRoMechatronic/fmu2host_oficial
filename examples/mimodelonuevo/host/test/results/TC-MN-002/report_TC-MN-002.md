# TC-MN-002 — Respuesta al escalon — 63% en t=tau=1.0 s

## Descripcion del test

Con entrada=1.0 y tau=1.0 s, la salida debe ser 0.632 en t=1 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=1.0`  
`flag_activo=1`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada` final: esperado 0.632±0.02, obtenido 0.632121 |
| ✅ | `flag_salida` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 1 | 0 | 0 |
| 0.01 | 1 | 1 | 0 | 0.00995 |
| 0.02 | 1 | 1 | 0 | 0.0198 |
| 0.5 | 1 | 1 | 0 | 0.3935 |
| 0.99 | 1 | 1 | 1 | 0.6284 |
| 1 | 1 | 1 | 1 | 0.6321 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `flag_salida` | 0 | 1 | 0.3069 | 0.4635 | 0 | 1 | creciente |
| `salida_filtrada` | 0 | 0.6321 | 0.3674 | 0.1838 | 0 | 0.6321 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=1 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `entrada_principal`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

La regla del 63% de los filtros de primer orden: a t=tau la salida alcanza 1-e^-1 ≈ 0.632 del valor final. Con tau=1.0 s y entrada=1.0, salida_filtrada(1)=0.632. flag_salida=true porque 0.632>0.5. Este es el test de referencia para verificar la constante de tiempo.
