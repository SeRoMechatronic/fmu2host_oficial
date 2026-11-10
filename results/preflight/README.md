# FMI contract preflight

FMPy 0.3.29 validation accepts **28/30** source FMUs and rejects **2**.
Rejected archives are excluded from the conformance population and retained only as negative diagnostics.

| Model | Decision | Problems |
|---|---|---:|
| ArranqueSuaveMotor | accept | 0 |
| ArraysVectores | reject | 1 |
| BooleanLogica | accept | 0 |
| CodigoErrorDiagnostico | accept | 0 |
| ContadorEventos | accept | 0 |
| CrecimientoPoblacional | accept | 0 |
| CSPuro_SinME | accept | 0 |
| CTPID | accept | 0 |
| CuerposAcoplados | accept | 0 |
| EtapaSecuenciador | accept | 0 |
| FrenadoABS | accept | 0 |
| MatrizEstado | accept | 0 |
| Mi_Modelo_Nuevo | accept | 0 |
| MuchosEstados | accept | 0 |
| MultiplexorCanales | accept | 0 |
| NivelDeposito | accept | 0 |
| OsciladorArmonico | accept | 0 |
| PenduloNoLineal | accept | 0 |
| PotVumetro | accept | 0 |
| ReguladorBateria | accept | 0 |
| SelectorModo | accept | 0 |
| SinInputs | accept | 0 |
| SistemaLorenz | accept | 0 |
| StringInputOutput | reject | 6 |
| StringsParametros | accept | 0 |
| SuspensionActiva | accept | 0 |
| testROMAN | accept | 0 |
| testUPM | accept | 0 |
| TiposMixtos | accept | 0 |
| ValoresExtremos | accept | 0 |

Full validator messages and archive hashes are in `preflight.csv` and `preflight.json`.
