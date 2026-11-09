# TC-CED-007 — Temperatura + tension — temperatura gana (prioridad 3 vs 2)

## Descripcion del test

Con ambos fallos activos, la temperatura (prioridad 3) debe prevalecer sobre la subtension (prioridad 2).

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.2 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.9`  
`tension=0.05`  
`vibracion=0.4`

## Simulacion: ME-RK4

- Pasos simulados: 3  |  Tiempo total: 0.2 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `codigo_error` final: esperado 101±0, obtenido 101 |
| ✅ | `nivel_prioridad` final: esperado 3±0, obtenido 3 |
| ✅ | `parada_emergencia` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | temperatura | tension | vibracion | factor_reduccion | codigo_error | parada_emergencia | nivel_prioridad |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.9 | 0.05 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.05 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.05 | 0.4 | 0 | 101 | 1 | 3 |
| 0.1 | 0.9 | 0.05 | 0.4 | 0 | 101 | 1 | 3 |
| 0.2 | 0.9 | 0.05 | 0.4 | 0 | 101 | 1 | 3 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `temperatura` | 0.9 | 0.9 | 0.9 | 0 | 0.9 | 0.9 | constante |
| `tension` | 0.05 | 0.05 | 0.05 | 0 | 0.05 | 0.05 | constante |
| `vibracion` | 0.4 | 0.4 | 0.4 | 0 | 0.4 | 0.4 | constante |
| `factor_reduccion` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `codigo_error` | 101 | 101 | 101 | 0 | 101 | 101 | constante |
| `parada_emergencia` | 1 | 1 | 1 | 0 | 1 | 1 | constante |
| `nivel_prioridad` | 3 | 3 | 3 | 0 | 3 | 3 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 3 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `temperatura`=0.9, `tension`=0.05, `vibracion`=0.4, `factor_reduccion`=0, `codigo_error`=101, `parada_emergencia`=1, `nivel_prioridad`=3 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `factor_reduccion`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `parada_emergencia`:** estado final = activo (TRUE/1) (media = 1).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (3 checks OK, 0 FAIL)

Con sobretemperatura (nivel 3) y subtension (nivel 2) simultaneas, el cascade de prioridades selecciona correctamente la condicion mas critica: temperatura. El codigo 101 se reporta, no el 202. La parada de emergencia se activa porque el nivel maximo es 3. Este es el test clave de la logica de prioridades del sistema de diagnostico.
