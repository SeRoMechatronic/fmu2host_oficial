# TC-SP-005 — Parametro String 'ruta' con barras — sin truncamiento

## Descripcion del test

El modelo se inicializa con ruta='/datos/planta/linea_A/modulo_02' (31 chars).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=2.0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 68.0±1e-09, obtenido 68 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 2 | 68 |
| 0.1 | 2 | 68 |
| 0.2 | 2 | 68 |
| 0.4 | 2 | 68 |
| 0.5 | 2 | 68 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 2 | 2 | 2 | 0 | 2 | 2 | constante |
| `y` | 68 | 68 | 68 | 0 | 68 | 68 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=2, `y`=68 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

Las barras '/' en el parametro ruta no deben interpretarse como separadores de path en el codegen. Con u=2, y=68 confirma que la inicializacion fue exitosa y que las barras se tratan como caracteres literales en el String de FMI 2.0.
