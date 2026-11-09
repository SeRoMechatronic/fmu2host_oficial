# TC-PN-001 — Condiciones iniciales — angulo=2.618, omega=0

## Descripcion del test

En t=0: angulo=2.618 rad (150°), velocidad=0, energia≈8.496 J.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.01 s |
| Paso de integracion | 0.001 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
*(sin entradas)*

## Simulacion: ME-RK4

- Pasos simulados: 11  |  Tiempo total: 0.01 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `angulo`@t=0.0: esperado 2.618±0.001, obtenido 2.618 |
| ✅ | `velocidad_angular`@t=0.0: esperado 0.0±1e-06, obtenido 0 |
| ✅ | `energia_total`@t=0.0: esperado 8.496±0.01, obtenido 8.49574 |
| ✅ | `en_reposo`@t=0.0: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | en_reposo | angulo | energia_total | velocidad_angular |
| --- | --- | --- | --- | --- |
| 0 | 1 | 2.618 | 8.496 | 0 |
| 0.001 | 1 | 2.618 | 8.496 | -0.004905 |
| 0.002 | 1 | 2.618 | 8.496 | -0.00981 |
| 0.005 | 0 | 2.618 | 8.496 | -0.02453 |
| 0.009 | 0 | 2.618 | 8.496 | -0.04415 |
| 0.01 | 0 | 2.618 | 8.496 | -0.04906 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `en_reposo` | 0 | 1 | 0.2727 | 0.4671 | 1 | 0 | decreciente |
| `angulo` | 2.618 | 2.618 | 2.618 | 8.446e-05 | 2.618 | 2.618 | decreciente |
| `energia_total` | 8.496 | 8.496 | 8.496 | 0 | 8.496 | 8.496 | constante |
| `velocidad_angular` | -0.04906 | 0 | -0.02453 | 0.01627 | 0 | -0.04906 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 4 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Conservacion de energia** (`energia_total`): valor medio = 8.496 J, deriva total = 0 J (0.00%) en 0.01 s — excelente.
**Convergencia** de `en_reposo`: valor final = 0 (arranca en 1, delta = 1).
**Variables algebraicas constantes:** `energia_total`=8.496 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Dinamica rapida** en `en_reposo`: tasa de cambio maxima = 1000 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (4 checks OK, 0 FAIL)

El pendulo parte de 150° con velocidad angular nula. La energia inicial E0 = -g*L*cos(2.618) = -9.81*(-0.866) ≈ 8.496 J. en_reposo=true porque |omega|=0 < 0.01. Este test verifica la inicializacion correcta del pendulo no lineal de gran amplitud.
