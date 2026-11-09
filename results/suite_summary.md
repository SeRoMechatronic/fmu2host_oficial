# Suite Report — Validacion FMI 2.0 Host

> Generado: 2026-11-09 17:23  |  Modelos evaluados: 28

## Metricas globales

| Metrica | Valor | Tasa |
|---------|-------|------|
| Modelos evaluados    | 28 | — |
| Modelos 100% PASS    | 23 | 82% |
| Modelos con FAILs    | 5 | 17% |
| Test cases totales   | 279 | — |
| Test cases PASS      | 242 | 86% |
| Test cases FAIL      | 37 | 13% |
| Checks individuales  | 762 | — |
| Checks PASS          | 669 | 87% |
| Checks FAIL          | 93 | 12% |

## Resultado por modelo

| Modelo | TCs | PASS | FAIL | Checks OK | Checks KO | Estado |
|--------|-----|------|------|-----------|-----------|--------|
| [ArranqueSuaveMotor](../examples/arranquesuavemotor/host/test/results/summary.md) | 10 | 10 | 0 | 30 | 0 | ✅ |
| [ArraysVectores](../examples/arraysvectores/host/test/results/summary.md) | 10 | 2 | 8 | 6 | 33 | ❌ |
| [BooleanLogica](../examples/booleanlogica/host/test/results/summary.md) | 10 | 4 | 6 | 23 | 14 | ❌ |
| [CodigoErrorDiagnostico](../examples/codigoerrordiagnostico/host/test/results/summary.md) | 10 | 10 | 0 | 32 | 0 | ✅ |
| [ContadorEventos](../examples/contadoreventos/host/test/results/summary.md) | 10 | 2 | 8 | 15 | 16 | ❌ |
| [CrecimientoPoblacional](../examples/crecimientopoblacional/host/test/results/summary.md) | 10 | 10 | 0 | 18 | 0 | ✅ |
| [CSPuro_SinME](../examples/cspuro/host/test/results/summary.md) | 10 | 10 | 0 | 30 | 0 | ✅ |
| [CTPID](../examples/ctpid/host/test/results/summary.md) | 10 | 10 | 0 | 37 | 0 | ✅ |
| [CuerposAcoplados](../examples/cuerposacoplados/host/test/results/summary.md) | 10 | 10 | 0 | 31 | 0 | ✅ |
| [EtapaSecuenciador](../examples/etapasecuenciador/host/test/results/summary.md) | 12 | 1 | 11 | 9 | 19 | ❌ |
| [FrenadoABS](../examples/frenadoabs/host/test/results/summary.md) | 10 | 10 | 0 | 28 | 0 | ✅ |
| [MatrizEstado](../examples/matrizestado/host/test/results/summary.md) | 10 | 6 | 4 | 16 | 11 | ❌ |
| [Mi_Modelo_Nuevo](../examples/mimodelonuevo/host/test/results/summary.md) | 10 | 10 | 0 | 20 | 0 | ✅ |
| [MuchosEstados](../examples/muchosestados/host/test/results/summary.md) | 10 | 10 | 0 | 29 | 0 | ✅ |
| [MultiplexorCanales](../examples/multiplexorcanales/host/test/results/summary.md) | 10 | 10 | 0 | 25 | 0 | ✅ |
| [NivelDeposito](../examples/niveldeposito/host/test/results/summary.md) | 10 | 10 | 0 | 22 | 0 | ✅ |
| [OsciladorArmonico](../examples/osciladorarmonico/host/test/results/summary.md) | 10 | 10 | 0 | 21 | 0 | ✅ |
| [PenduloNoLineal](../examples/pendulonolineal/host/test/results/summary.md) | 10 | 10 | 0 | 15 | 0 | ✅ |
| [PotVumetro](../examples/potvumetro/host/test/results/summary.md) | 12 | 12 | 0 | 41 | 0 | ✅ |
| [ReguladorBateria](../examples/reguladorbateria/host/test/results/summary.md) | 7 | 7 | 0 | 18 | 0 | ✅ |
| [SelectorModo](../examples/selectormodo/host/test/results/summary.md) | 10 | 10 | 0 | 26 | 0 | ✅ |
| [SinInputs](../examples/sininputs/host/test/results/summary.md) | 8 | 8 | 0 | 14 | 0 | ✅ |
| [SistemaLorenz](../examples/sistemalorenz/host/test/results/summary.md) | 10 | 10 | 0 | 19 | 0 | ✅ |
| [StringInputOutput](../examples/stringinputoutput/host/test/results/summary.md) | 10 | 10 | 0 | 27 | 0 | ✅ |
| [StringsParametros](../examples/stringsparametros/host/test/results/summary.md) | 10 | 10 | 0 | 13 | 0 | ✅ |
| [SuspensionActiva](../examples/suspensionactiva/host/test/results/summary.md) | 10 | 10 | 0 | 31 | 0 | ✅ |
| [TiposMixtos](../examples/tiposmixtos/host/test/results/summary.md) | 10 | 10 | 0 | 31 | 0 | ✅ |
| [ValoresExtremos](../examples/valoresextremos/host/test/results/summary.md) | 10 | 10 | 0 | 42 | 0 | ✅ |

## Analisis por categoria de modelo

### Algebraicos (sin estados)

*Modelos puramente combinacionales sin integracion dinamica.*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 5/5 OK | 50 | 50 (100%) | 143/143 (100%) | ✅ Excelente |

- ✅ **Mi_Modelo_Nuevo** — 10/10 TCs OK. Sin fallos.
- ✅ **PotVumetro** — 12/12 TCs OK. Sin fallos.
- ✅ **SelectorModo** — 10/10 TCs OK. Sin fallos.
- ✅ **SinInputs** — 8/8 TCs OK. Sin fallos.
- ✅ **ValoresExtremos** — 10/10 TCs OK. Sin fallos.

### ODE — sistemas de primer orden

*Sistemas con 1-3 estados dinamicos de primer orden (filtros, tanques, motores).*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 5/5 OK | 47 | 47 (100%) | 109/109 (100%) | ✅ Excelente |

- ✅ **ArranqueSuaveMotor** — 10/10 TCs OK. Sin fallos.
- ✅ **CrecimientoPoblacional** — 10/10 TCs OK. Sin fallos.
- ✅ **NivelDeposito** — 10/10 TCs OK. Sin fallos.
- ✅ **OsciladorArmonico** — 10/10 TCs OK. Sin fallos.
- ✅ **ReguladorBateria** — 7/7 TCs OK. Sin fallos.

### ODE — sistemas complejos

*Sistemas no lineales o de alto orden con dinamica rica (caos, osciladores, control).*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 5/5 OK | 50 | 50 (100%) | 133/133 (100%) | ✅ Excelente |

- ✅ **CTPID** — 10/10 TCs OK. Sin fallos.
- ✅ **CuerposAcoplados** — 10/10 TCs OK. Sin fallos.
- ✅ **PenduloNoLineal** — 10/10 TCs OK. Sin fallos.
- ✅ **SistemaLorenz** — 10/10 TCs OK. Sin fallos.
- ✅ **SuspensionActiva** — 10/10 TCs OK. Sin fallos.

### Alta dimension (5+ estados)

*Modelos con buffers grandes: estresan el codegen con EULER/RK4_BUF_SIZE.*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 2/3 OK | 30 | 26 (86%) | 73/84 (86%) | 🟡 Bueno |

- ✅ **FrenadoABS** — 10/10 TCs OK. Sin fallos.
- ❌ **MatrizEstado** — 6/10 TCs OK. Fallos: TC-MZ-003, TC-MZ-004, TC-MZ-007, TC-MZ-008.
- ✅ **MuchosEstados** — 10/10 TCs OK. Sin fallos.

### Logica discreta y eventos

*Automatas, contadores, secuenciadores y logica booleana.*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 1/4 OK | 42 | 17 (40%) | 79/128 (61%) | ❌ Deficiente |

- ❌ **BooleanLogica** — 4/10 TCs OK. Fallos: TC-BL-005, TC-BL-006, TC-BL-007, TC-BL-008, TC-BL-009, TC-BL-010.
- ✅ **CodigoErrorDiagnostico** — 10/10 TCs OK. Sin fallos.
- ❌ **ContadorEventos** — 2/10 TCs OK. Fallos: TC-CE-002, TC-CE-003, TC-CE-004, TC-CE-005, TC-CE-006, TC-CE-007, TC-CE-008, TC-CE-010.
- ❌ **EtapaSecuenciador** — 1/12 TCs OK. Fallos: TC-ES-002, TC-ES-003, TC-ES-004, TC-ES-005, TC-ES-006, TC-ES-007, TC-ES-008, TC-ES-009, TC-ES-010, TC-ES-011, TC-ES-012.

### Tipos de datos avanzados

*Modelos con arrays, Strings, tipos mixtos o entradas/salidas especiales.*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 4/5 OK | 50 | 42 (84%) | 102/135 (75%) | 🟡 Bueno |

- ❌ **ArraysVectores** — 2/10 TCs OK. Fallos: TC-AV-002, TC-AV-003, TC-AV-004, TC-AV-006, TC-AV-007, TC-AV-008, TC-AV-009, TC-AV-010.
- ✅ **MultiplexorCanales** — 10/10 TCs OK. Sin fallos.
- ✅ **StringInputOutput** — 10/10 TCs OK. Sin fallos.
- ✅ **StringsParametros** — 10/10 TCs OK. Sin fallos.
- ✅ **TiposMixtos** — 10/10 TCs OK. Sin fallos.

### Algebraic mode probe

*Legacy-named artifact whose XML declares both FMI ME and CS.*

| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |
|---------|-------------|----------|-------------|---------|
| 1/1 OK | 10 | 10 (100%) | 30/30 (100%) | ✅ Excelente |

- ✅ **CSPuro_SinME** — 10/10 TCs OK. Sin fallos.

## Detalle de fallos

### ArraysVectores

- **TC-AV-002** — Todos unos — suma=4, doble=[2,2,2,2], alguno=true (5 check(s) fallado(s))
- **TC-AV-003** — Valores reales distintos — discriminador de indice (5 check(s) fallado(s))
- **TC-AV-004** — Un solo TRUE en el OR — alguno_true activado (1 check(s) fallado(s))
- **TC-AV-006** — Reales con signos mixtos — suma y dobles con signos (5 check(s) fallado(s))
- **TC-AV-007** — Enteros con signos mixtos — suma_int correcto (1 check(s) fallado(s))
- **TC-AV-008** — Magnitudes grandes — sin perdida de precision en suma (5 check(s) fallado(s))
- **TC-AV-009** — Cambio de un elemento en mitad de simulacion (4 check(s) fallado(s))
- **TC-AV-010** — Independencia de los 4 elementos — sin escrituras cruzadas (7 check(s) fallado(s))

### BooleanLogica

- **TC-BL-005** — D-latch: captura a=TRUE en flanco ascendente de clk (2 check(s) fallado(s))
- **TC-BL-006** — D-latch: captura a=FALSE en flanco — latch no es level-triggered (1 check(s) fallado(s))
- **TC-BL-007** — Contador de flancos — 3 flancos ascendentes (3 check(s) fallado(s))
- **TC-BL-008** — Sin doble conteo — clk=TRUE mantenido no cuenta multiples flancos (4 check(s) fallado(s))
- **TC-BL-009** — Todos los inputs activos simultaneamente — salidas combinadas (2 check(s) fallado(s))
- **TC-BL-010** — Reset a cero — outputs combinacionales inmediatos, secuenciales retenidos (2 check(s) fallado(s))

### ContadorEventos

- **TC-CE-002** — Un solo evento — contador pasa a 1 (2 check(s) fallado(s))
- **TC-CE-003** — Diez eventos — descomposicion BCD: decenas=1, unidades=0 (2 check(s) fallado(s))
- **TC-CE-004** — 47 eventos — BCD arbitrario: decenas=4, unidades=7 (3 check(s) fallado(s))
- **TC-CE-005** — Reset borra el contador — cuenta vuelve a 0 (1 check(s) fallado(s))
- **TC-CE-006** — Saturacion en 99 — 100 eventos, cuenta queda en 99 (2 check(s) fallado(s))
- **TC-CE-007** — El contador permanece en 99 tras la saturacion (1 check(s) fallado(s))
- **TC-CE-008** — Reset tras desbordamiento — contador vuelve a 0 (1 check(s) fallado(s))
- **TC-CE-010** — BCD en valor limite 99 — decenas=9, unidades=9 (4 check(s) fallado(s))

### EtapaSecuenciador

- **TC-ES-002** — Comando de arranque — entra en etapa 1 (1 check(s) fallado(s))
- **TC-ES-003** — Progreso dentro de la etapa 1 en t=5 s (2 check(s) fallado(s))
- **TC-ES-004** — Avance de etapa — etapa 1→2 tras 10 s con sensor confirmado (2 check(s) fallado(s))
- **TC-ES-005** — Sin avance sin confirmacion del sensor (2 check(s) fallado(s))
- **TC-ES-006** — Sensor exactamente en el umbral — sin avance (operador estricto) (1 check(s) fallado(s))
- **TC-ES-007** — Parada durante secuencia — vuelta inmediata a idle (1 check(s) fallado(s))
- **TC-ES-008** — Arrancar ignorado si ya en ejecucion (2 check(s) fallado(s))
- **TC-ES-009** — Secuencia completa — secuencia_completa=true al finalizar (2 check(s) fallado(s))
- **TC-ES-010** — Reinicio tras completion — nueva secuencia arranca correctamente (2 check(s) fallado(s))
- **TC-ES-011** — Progreso clamped a 1.0 cuando sensor bloquea el avance (2 check(s) fallado(s))
- **TC-ES-012** — Ciclo de parada y reinicio (2 check(s) fallado(s))

### MatrizEstado

- **TC-MZ-003** — Ordenacion de estados: x3 > x2 > x1 para u>0 (3 check(s) fallado(s))
- **TC-MZ-004** — Verificacion analitica en t=1.0 s (3 check(s) fallado(s))
- **TC-MZ-007** — Entrada negativa — estados negativos con mismo ordenamiento (3 check(s) fallado(s))
- **TC-MZ-008** — Cambio de entrada en t=1 s — sistema inestable sigue creciendo (2 check(s) fallado(s))

## Analisis de robustez del codegen

El siguiente analisis evalua el comportamiento del generador de codigo C host frente a distintos tipos de retos que suelen detectar errores de implementacion.

| Area de robustez | Modelos involucrados | Tasa PASS | Estado |
|------------------|----------------------|-----------|--------|
| Buffer de estados (EULER/RK4_BUF_SIZE) | CuerposAcoplados, FrenadoABS, MatrizEstado, MuchosEstados | 3/4 (75%) | ❌ |
| Division por cero y guardas numericas | CrecimientoPoblacional, FrenadoABS, NivelDeposito, SistemaLorenz | 4/4 (100%) | ✅ |
| Logica booleana y operadores estrictos | BooleanLogica, SelectorModo, StringInputOutput, SuspensionActiva | 3/4 (75%) | ❌ |
| Entradas/salidas de tipo String | CodigoErrorDiagnostico, StringInputOutput, StringsParametros | 3/3 (100%) | ✅ |
| Arrays y acceso por indice | ArraysVectores, MatrizEstado, MultiplexorCanales | 1/3 (33%) | ❌ |
| Eventos discretos y contadores | BooleanLogica, ContadorEventos, EtapaSecuenciador | 0/3 (0%) | ❌ |
| Dinamica caotica / no lineal | CuerposAcoplados, PenduloNoLineal, SistemaLorenz | 3/3 (100%) | ✅ |
| Algebraic dual-mode probe | CSPuro_SinME | 1/1 (100%) | ✅ |

## Modelos con mayor tasa de fallo

| Modelo | TCs PASS | TCs FAIL | Tasa exito |
|--------|----------|----------|------------|
| EtapaSecuenciador | 1 | 11 | 8% |
| ArraysVectores | 2 | 8 | 20% |
| ContadorEventos | 2 | 8 | 20% |
| BooleanLogica | 4 | 6 | 40% |
| MatrizEstado | 6 | 4 | 60% |

## Conclusiones generales

**5 de 28 modelos presentan fallos (17% de la suite).**

Tasa de test cases superados: 242/279 (86%).

**Areas prioritarias de mejora:**
- **Alta dimension (5+ estados)**: 1/3 modelos con fallos.
- **Logica discreta y eventos**: 3/4 modelos con fallos.
- **Tipos de datos avanzados**: 1/5 modelos con fallos.

Se recomienda revisar los checks fallados en la seccion 'Detalle de fallos' y el informe individual de cada modelo para diagnostico detallado.

---
*Informe generado automaticamente por `run_all_tests.py` — 2026-11-09 17:23*
