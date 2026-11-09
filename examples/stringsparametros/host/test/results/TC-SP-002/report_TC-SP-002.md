# TC-SP-002 — Salida numerica con entrada negativa

## Descripcion del test

u=-2.5: y = -2.5 * 34 = -85.0.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 1.0 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=-2.5`

## Simulacion: ME-RK4

- Pasos simulados: 12  |  Tiempo total: 1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado -85.0±1e-09, obtenido -85 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | -2.5 | -85 |
| 0.1 | -2.5 | -85 |
| 0.2 | -2.5 | -85 |
| 0.6 | -2.5 | -85 |
| 1 | -2.5 | -85 |
| 1 | -2.5 | -85 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | -2.5 | -2.5 | -2.5 | 0 | -2.5 | -2.5 | constante |
| `y` | -85 | -85 | -85 | 0 | -85 | -85 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=-2.5, `y`=-85 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

La multiplicacion u*34 funciona con valores negativos. Verifica que fmi2SetReal maneja correctamente entradas negativas incluso en presencia de parametros String complejos en la FMU.
