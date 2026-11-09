# TC-CP-009 — Cambio de tasa de inmigracion en t=2 s

## Descripcion del test

tasa_entrada cambia de 0 a 20 en t=2 s. Convergencia mas rapida.

## Configuracion de simulacion

| Parametro | Valor |
|-----------|-------|
| Tiempo final | 5.0 s |
| Paso de integracion | 0.01 s |
| Modo FMI | ME |
| Solver | rk4 |

**Entradas:**  
`tasa_entrada=0.0`  
`tasa_entrada`: t=0: 0.0, t=2.0: 20.0

## Simulacion: ME-RK4

- Pasos simulados: 502  |  Tiempo total: 5 s
- Grafica individual: [sim_me_rk4.png](sim_me_rk4.png)

### Resultado de checks

| Estado | Detalle |
|--------|---------|
| ✅ | `poblacion`@t=2.0: esperado 95.0±5.0, obtenido 95.7229 |
| ✅ | `poblacion` final: esperado 105.0±10.0, obtenido 105.42 |

### Muestra de datos (inicio / mitad / final)

| t | tasa_entrada | superpoblacion | poblacion | saturacion | tasa_crecimiento |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 2 | 0.02 | 6.86 |
| 0.01 | 0 | 0 | 2.07 | 0.0207 | 7.094 |
| 0.02 | 0 | 0 | 2.142 | 0.02142 | 7.336 |
| 2.51 | 20 | 1 | 104 | 1.04 | -14.45 |
| 5 | 20 | 1 | 105.4 | 1.054 | -20 |
| 5 | 20 | 1 | 105.4 | 1.054 | -20 |

## Analisis de datos

### Simulacion: ME-RK4

#### Estadisticas por variable de salida

| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |
|----------|-----|-----|-------|----------|---------|-------|----------------|
| `tasa_entrada` | 0 | 20 | 12.03 | 9.801 | 0 | 20 | creciente |
| `superpoblacion` | 0 | 1 | 0.5677 | 0.4959 | 0 | 1 | creciente |
| `poblacion` | 2 | 105.4 | 80.62 | 36.32 | 2 | 105.4 | creciente |
| `saturacion` | 0.02 | 1.054 | 0.8062 | 0.3632 | 0.02 | 1.054 | creciente |
| `tasa_crecimiento` | -20 | 87.5 | 8.597 | 35.78 | 6.86 | -20 | decreciente |

#### Analisis contextual

**✅ Verificacion completa:** los 2 check(s) definidos pasan — el comportamiento del modelo es coherente con la especificacion.
**Convergencia** de `tasa_entrada`: valor final = 20 (arranca en 0, delta = 20).
**Convergencia** de `superpoblacion`: valor final = 1 (arranca en 0, delta = 1).
**Convergencia** de `poblacion`: valor final = 105.4 (arranca en 2, delta = 103.4).
**Convergencia** de `saturacion`: valor final = 1.054 (arranca en 0.02, delta = 1.034).
**Convergencia** de `tasa_crecimiento`: valor final = -20 (arranca en 6.86, delta = 26.86).
**Dinamica rapida** en `tasa_entrada`: tasa de cambio maxima = 2000 unidades/s.
**Dinamica rapida** en `superpoblacion`: tasa de cambio maxima = 100 unidades/s.

## Interpretacion tecnica del test

**Resultado global: ✅ PASS** (2 checks OK, 0 FAIL)

A t=2 s la poblacion ya habra crecido notablemente (N≈70-80). Al aplicar inmigracion de 20 individuos/tiempo, el equilibrio se eleva por encima de K y la convergencia es mas rapida. A t=5 s, la poblacion debe superar 100 (N*>100 por la inmigracion). Verifica que fmi2SetReal se llama en el bucle de simulacion.
