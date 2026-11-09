# TC-MN-007 — Entrada grande — sin saturacion

## Descripcion del test

entrada=100.0 activa: salida debe converger a ≈99.3 en t=5 s.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`entrada_principal=100.0`  
`flag_activo=1`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `salida_filtrada` final: esperado 99.3±1.0, obtenido 99.3262 |
| ✅ | `flag_salida` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | flag_activo | entrada_principal | flag_salida | salida_filtrada |
| --- | --- | --- | --- | --- |
| 0 | 1 | 100 | 0 | 0 |
| 0.01 | 1 | 100 | 1 | 0.995 |
| 0.02 | 1 | 100 | 1 | 1.98 |
| 2.51 | 1 | 100 | 1 | 91.87 |
| 5 | 1 | 100 | 1 | 99.33 |
| 5 | 1 | 100 | 1 | 99.33 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `flag_activo` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `entrada_principal` | 100 | 100 | 100 | 0 | 100 | 100 | constante |
| `flag_salida` | 0 | 1 | 0.998 | 0.04463 | 0 | 1 | estable |
| `salida_filtrada` | 0 | 99.33 | 80.11 | 24.73 | 0 | 99.33 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `flag_salida`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `salida_filtrada`: valor final = 99.33 (arranca en 0, delta = 99.33).
**Variables algebraicas constantes:** `flag_activo`=1, `entrada_principal`=100 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `flag_activo`:** estado final = activo (TRUE/1) (media = 1).
**Dinamica rapida** en `flag_salida`: tasa de cambio maxima = 100 unidades/s.
**Dinamica rapida** en `salida_filtrada`: tasa de cambio maxima = 99.5 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

El filtro es lineal: una entrada de 100.0 produce una salida de 100*(1-e^-5)≈99.3 a t=5 s. No hay saturacion. flag_salida=true en cuanto salida>0.5. Verifica que el filtro escala correctamente con la magnitud de la entrada.
