# TC-SP-008 — Parametro String 'unicode_str' — 27 caracteres ASCII

## Descripcion del test

unicode_str='Angstrom [A] delta+-epsilon': inicializacion exitosa.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.5 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`u=4.0`

## Simulacion: ME-RK4

- Pasos simulados: 6  |  Tiempo total: 0.5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `y` final: esperado 136.0±1e-09, obtenido 136 |

### Muestra de datos (inicio / mitad / final)

| t | u | y |
| --- | --- | --- |
| 0 | 4 | 136 |
| 0.1 | 4 | 136 |
| 0.2 | 4 | 136 |
| 0.4 | 4 | 136 |
| 0.5 | 4 | 136 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `u` | 4 | 4 | 4 | 0 | 4 | 4 | constante |
| `y` | 136 | 136 | 136 | 0 | 136 | 136 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 1 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `u`=4, `y`=136 — sin dinamica transitoria, solo dependencia combinacional de la entrada.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (1 checks OK, 0 FAIL)

El String con simbolos ASCII ([], +-) se almacena sin truncamiento. Aunque se llama 'unicode', son caracteres ASCII puros que el codegen debe manejar en un buffer de char sin conversion de encoding. Con u=4, y=136 confirma la inicializacion exitosa.
