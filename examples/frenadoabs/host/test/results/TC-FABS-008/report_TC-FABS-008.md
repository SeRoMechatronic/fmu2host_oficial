# TC-FABS-008 — frenado_normal requiere pedal > 0.05 — frontera exacta

## Descripcion del test

pedal=0.03 (<= 0.05): frenado_normal=false aunque sin ABS.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`velocidad_rueda=0.6`  
`presion_pedal=0.03`

## Simulacion: ME-RK4

- Pasos simulados: 101  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `frenado_normal` final: esperado 0±0, obtenido 0 |
| ✅ | `abs_activo` final: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | presion_pedal | velocidad_rueda | abs_activo | frenado_normal | rueda_bloqueada | presion_modulada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.03 | 0.6 | 0 | 0 | 0 | 0 |
| 0.01 | 0.03 | 0.6 | 0 | 0 | 0 | 0.003525 |
| 0.02 | 0.03 | 0.6 | 0 | 0 | 0 | 0.006636 |
| 0.5 | 0.03 | 0.6 | 0 | 0 | 0 | 0.02994 |
| 0.99 | 0.03 | 0.6 | 0 | 0 | 0 | 0.03 |
| 1 | 0.03 | 0.6 | 0 | 0 | 0 | 0.03 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `presion_pedal` | 0.03 | 0.03 | 0.03 | 0 | 0.03 | 0.03 | constante |
| `velocidad_rueda` | 0.6 | 0.6 | 0.6 | 0 | 0.6 | 0.6 | constante |
| `abs_activo` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `frenado_normal` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `rueda_bloqueada` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `presion_modulada` | 0 | 0.03 | 0.02747 | 0.005851 | 0 | 0.03 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `presion_modulada`: valor final = 0.03 (arranca en 0, delta = 0.03).
**Variables algebraicas constantes:** `presion_pedal`=0.03, `velocidad_rueda`=0.6, `abs_activo`=0, `frenado_normal`=0, `rueda_bloqueada`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `abs_activo`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `frenado_normal`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `rueda_bloqueada`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Con velocidad constante (lambda→0, abs_activo=FALSE) y pedal=0.03 < 0.05, frenado_normal=FALSE. La condicion es: lambda<=0.15 AND presion_pedal > 0.05. El pedal de 3% no supera el umbral activo de 5%. Verifica que la condicion de pedal activo tiene umbral en 0.05 (estricto >).
