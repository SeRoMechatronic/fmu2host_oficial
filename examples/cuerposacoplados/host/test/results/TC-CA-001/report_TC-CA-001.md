# TC-CA-001 — Condiciones iniciales en t=0

## Descripcion del test

pos1=1.0, pos2=-0.5, vel1=0, vel2=0.5, energia≈3.625, en_fase=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=0.0`

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `pos1`@t=0.0: esperado 1.0±1e-06, obtenido 1 |
| ✅ | `pos2`@t=0.0: esperado -0.5±1e-06, obtenido -0.5 |
| ✅ | `vel1`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `vel2`@t=0.0: esperado 0.5±1e-06, obtenido 0.5 |
| ✅ | `energia_total`@t=0.0: esperado 3.625±0.01, obtenido 3.625 |
| ✅ | `en_fase`@t=0.0: esperado 0±0, obtenido 0 |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.001 | 0 | 0 | 3.625 | 1 | -0.4995 | -0.0055 | 0.5012 |
| 0.002 | 0 | 0 | 3.625 | 1 | -0.499 | -0.011 | 0.5025 |
| 0.005 | 0 | 0 | 3.625 | 0.9999 | -0.4975 | -0.02749 | 0.5062 |
| 0.009 | 0 | 0 | 3.625 | 0.9998 | -0.4954 | -0.04948 | 0.5112 |
| 0.01 | 0 | 0 | 3.625 | 0.9997 | -0.4949 | -0.05497 | 0.5125 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `en_fase` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `energia_total` | 3.625 | 3.625 | 3.625 | 0 | 3.625 | 3.625 | constante |
| `pos1` | 0.9997 | 1 | 0.9999 | 9.467e-05 | 1 | 0.9997 | decreciente |
| `pos2` | -0.5 | -0.4949 | -0.4975 | 0.001679 | -0.5 | -0.4949 | creciente |
| `vel1` | -0.05497 | 0 | -0.02749 | 0.01823 | 0 | -0.05497 | decreciente |
| `vel2` | 0.5 | 0.5125 | 0.5062 | 0.004133 | 0.5 | 0.5125 | creciente |

#### Analisis contextual

**✅ Verificacion completa:** los 6 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.625 J, deriva total = 0 J (0.00%) en 0.01 s — excelente.
**Variables algebraicas constantes:** `fuerza_externa`=0, `en_fase`=0, `energia_total`=3.625 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `fuerza_externa`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `en_fase`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (6 checks OK, 0 FAIL)

Los 4 estados tienen condiciones iniciales: x1=1.0, x2=-0.5, v1=0, v2=0.5. Energia inicial E0=0.5*1*0²+0.5*2*0.5²+0.5*4*1²+0.5*2*0.25+0.5*1*2.25=3.625 J. en_fase=FALSE porque sign(x1=1)>0 y sign(x2=-0.5)<0 (signos opuestos). Verifica que el buffer de estados de 4 elementos se inicializa correctamente.
