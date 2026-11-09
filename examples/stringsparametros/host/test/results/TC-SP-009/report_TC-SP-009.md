# TC-SP-009 — Parametro String 'largo' — 98 caracteres sin truncamiento

## Descripcion del test

largo='aaa...' (98 'a'): buffer debe ser >=99 bytes.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=5.0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 170.0±1e-09, obtenido 170 |
| ✅ | `y` sin NaN/Inf: OK |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 5 | 170 |
| 0.1 | 5 | 170 |
| 0.2 | 5 | 170 |
| 0.4 | 5 | 170 |
| 0.5 | 5 | 170 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 5 | 5 | 5 | 0 | 5 | 5 | constante |
| `y` | 170 | 170 | 170 | 0 | 170 | 170 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=5, `y`=170 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

TEST DE DESBORDAMIENTO DE BUFFER. El String de 98 'a' requiere un buffer de al menos 99 bytes (98 chars + terminador nulo). Si el codegen usa char[32] o char[64], hay buffer overflow. Con u=5, y=170 indica que la inicializacion se completo sin corrupcion. Ejecutar con AddressSanitizer para mayor certeza.
