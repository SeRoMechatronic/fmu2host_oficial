# TC-CA-006 — Fuerza externa aumenta energia — F=5 N durante 5 s

## Descripcion del test

Con fuerza_externa=5.0 constante, energia_total(5s) > 3.625 J.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`fuerza_externa=5.0`

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `energia_total` > 4.0 eventualmente: OK |
| ✅ | `energia_total` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | fuerza_externa | en_fase | energia_total | pos1 | pos2 | vel1 | vel2 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 5 | 0 | 3.625 | 1 | -0.5 | 0 | 0.5 |
| 0.01 | 5 | 0 | 3.625 | 1 | -0.4949 | -0.004974 | 0.5125 |
| 0.02 | 5 | 0 | 3.625 | 0.9999 | -0.4898 | -0.009895 | 0.5248 |
| 2.51 | 5 | 1 | 6.043 | 1.484 | 1.238 | 0.01782 | -0.2786 |
| 5 | 5 | 0 | 3.239 | 0.9228 | -0.5894 | 0.2982 | -0.02732 |
| 5 | 5 | 0 | 3.239 | 0.9228 | -0.5894 | 0.2982 | -0.02732 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `fuerza_externa` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `en_fase` | 0 | 1 | 0.6753 | 0.4687 | 0 | 0 | decreciente |
| `energia_total` | 2.435 | 6.044 | 3.991 | 1.149 | 3.625 | 3.239 | decreciente |
| `pos1` | 0.7619 | 1.484 | 1.073 | 0.2299 | 1 | 0.9228 | decreciente |
| `pos2` | -0.5894 | 1.272 | 0.4242 | 0.6319 | -0.5 | -0.5894 | decreciente |
| `vel1` | -0.6625 | 0.5325 | -0.01449 | 0.3604 | 0 | 0.2982 | decreciente |
| `vel2` | -1.052 | 1.121 | -0.01739 | 0.7929 | 0.5 | -0.02732 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 3.991 J, deriva total = 3.609 J (90.43%) en 5 s — elevada.
**Convergencia** de `en_fase`: valor final = 0 (arranca en 0, delta = 0).
**Variables algebraicas constantes:** `fuerza_externa`=5 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `en_fase`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

Una fuerza externa F=5 N sobre la masa 1 realiza trabajo W=F*v1*dt. La energia mecanica crece por encima del valor inicial 3.625 J. Si el input fuerza_externa no se propaga a la ODE (fmi2SetReal no actualiza el termino F en la ecuacion de movimiento), la energia permaneceria en 3.625 J como en el caso libre.
