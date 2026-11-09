# TC-CT-005 — Justo fuera de la banda muerta — ledAlcanzado inactivo

## Descripcion del test

temperatura=0.512, consigna=0.50: |error|=1.2 > epsilon=1.0 → ledAlcanzado=false.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 0.1 s |
| Paso de integracion | 0.1 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`temperatura=0.512`  
`consigna=0.5`

## Simulacion: ME-RK4

- Pasos simulados: 2  |  Tiempo total: 0.1 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `ledAlcanzado` final: esperado 0±0, obtenido 0 |
| ✅ | `ledPorDebajo` final: esperado 1±0, obtenido 1 |

### Muestra de datos (inicio / mitad / final)

| t | consigna | temperatura | ledAlcanzado | ledPorDebajo | ledPorEncima | ventilador |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 0.5 | 0.512 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.512 | 0 | 1 | 0 | 0 |
| 0 | 0.5 | 0.512 | 1 | 0 | 0 | 0 |
| 0.1 | 0.5 | 0.512 | 0 | 1 | 0 | 0 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `consigna` | 0.5 | 0.5 | 0.5 | 0 | 0.5 | 0.5 | constante |
| `temperatura` | 0.512 | 0.512 | 0.512 | 0 | 0.512 | 0.512 | constante |
| `ledAlcanzado` | 0 | 1 | 0.5 | 0.7071 | 1 | 0 | variable |
| `ledPorDebajo` | 0 | 1 | 0.5 | 0.7071 | 0 | 1 | variable |
| `ledPorEncima` | 0 | 0 | 0 | 0 | 0 | 0 | constante |
| `ventilador` | 0 | 0 | 0 | 0 | 0 | 0 | constante |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Variables algebraicas constantes:** `consigna`=0.5, `temperatura`=0.512, `ledPorEncima`=0, `ventilador`=0 — sin dinamica transitoria, solo dependencia combinacional de la entrada.
**Salida binaria `ledPorEncima`:** estado final = inactivo (FALSE/0) (media = 0).
**Salida binaria `ventilador`:** estado final = inactivo (FALSE/0) (media = 0).

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

error = (0.50-0.512)*100 = -1.2 grados. |error|=1.2 > epsilon=1.0: ledAlcanzado=FALSE. ledPorDebajo=TRUE (50 < 51.2-1 = 50.2). Complementario de TC-CT-004: 0.1 grado adicional saca el error de la banda muerta. Verifica que la banda muerta es exactamente +/-epsilon.
