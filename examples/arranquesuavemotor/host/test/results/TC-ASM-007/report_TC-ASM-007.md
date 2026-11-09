# TC-ASM-007 — Overload exactamente en umbral — no fallo

## Descripcion del test

carga_motor=0.90 es exactamente el umbral. La condicion es estricta (carga > 0.9), por lo que no debe acumularse el integrador.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`orden_arranque=1`  
`carga_motor=0.9`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `fallo_sobrecarga` == 0 siempre: OK |

### Muestra de datos (inicio / mitad / final)

| t | orden_arranque | carga_motor | en_rampa | fallo_sobrecarga | motor_en_marcha | tension_aplicada |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 1 | 0.9 | 1 | 0 | 0 | 0 |
| 0.01 | 1 | 0.9 | 1 | 0 | 0 | 3.308e-05 |
| 0.02 | 1 | 0.9 | 1 | 0 | 0 | 0.0001313 |
| 2.51 | 1 | 0.9 | 1 | 0 | 0 | 0.4815 |
| 5 | 1 | 0.9 | 1 | 0 | 0 | 0.7734 |
| 5 | 1 | 0.9 | 1 | 0 | 0 | 0.7734 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `orden_arranque` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `carga_motor` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `en_rampa` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `fallo_sobrecarga` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `motor_en_marcha` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `tension_aplicada` | 0 | 0.7734 | 0.4366 | 0.2444 | 0 | 0.7734 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `orden_arranque`=1, `carga_motor`=0.9, `en_rampa`=1, `fallo_sobrecarga`=0, `motor_en_marcha`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `orden_arranque`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `en_rampa`:** estado final = activo (TRUE/1) (media = 1).
**Salida binaria `fallo_sobrecarga`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El umbral de sobrecarga es estrictamente mayor que 0.9 (umbral_sobrecarga=0.9). Con carga=0.9 exactamente, la condicion carga_motor > umbral es falsa, por lo que el integrador decae (der = -tiempo_sob/tau) en lugar de crecer. Este test valida la semantica de borde: '>' no es '>='.
