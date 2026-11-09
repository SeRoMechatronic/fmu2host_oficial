# TC-SP-006 — Parametro String 'especial' con delimitadores '=;/' — sin truncamiento

## Descripcion del test

especial='val=3.14;tag=alpha_beta;unit=m2/s': sin interpretacion erronea.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=3.0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 102.0±1e-09, obtenido 102 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 3 | 102 |
| 0.1 | 3 | 102 |
| 0.2 | 3 | 102 |
| 0.4 | 3 | 102 |
| 0.5 | 3 | 102 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 3 | 3 | 3 | 0 | 3 | 3 | constante |
| `y` | 102 | 102 | 102 | 0 | 102 | 102 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=3, `y`=102 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El parametro 'especial' contiene = ; y / que podrian ser malinterpretados. Si el codegen usa = como delimitador de asignacion CLI, podria truncar el String en el primer '='. Con u=3, y=102 confirma que todos los caracteres especiales se trataron como parte del String.
