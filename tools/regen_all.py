"""Regenerate every derived host file while preserving user-owned scenarios."""
import subprocess
import sys
import os

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

MODEL_MAP = {
    "ArranqueSuaveMotor":    "arranquesuavemotor",
    "ArraysVectores":        "arraysvectores",
    "BooleanLogica":         "booleanlogica",
    "CS_Puro/CSPuro_SinME":  "cspuro",   # FMU lives in a sub-dir with different name
    "CTPID":                 "ctpid",
    "CodigoErrorDiagnostico":"codigoerrordiagnostico",
    "ContadorEventos":       "contadoreventos",
    "CrecimientoPoblacional":"crecimientopoblacional",
    "CuerposAcoplados":      "cuerposacoplados",
    "EtapaSecuenciador":     "etapasecuenciador",
    "FrenadoABS":            "frenadoabs",
    "MatrizEstado":          "matrizestado",
    "Mi_Modelo_Nuevo":       "mimodelonuevo",
    "MuchosEstados":         "muchosestados",
    "MultiplexorCanales":    "multiplexorcanales",
    "NivelDeposito":         "niveldeposito",
    "OsciladorArmonico":     "osciladorarmonico",
    "PenduloNoLineal":       "pendulonolineal",
    "PotVumetro":            "potvumetro",
    "ReguladorBateria":      "reguladorbateria",
    "SelectorModo":          "selectormodo",
    "SinInputs":             "sininputs",
    "SistemaLorenz":         "sistemalorenz",
    "StringInputOutput":     "stringinputoutput",
    "StringsParametros":     "stringsparametros",
    "SuspensionActiva":      "suspensionactiva",
    "TiposMixtos":           "tiposmixtos",
    "ValoresExtremos":       "valoresextremos",
    "testROMAN":             "testroman",
    "testUPM":               "testUPM",
}

ok = []
fail = []

for model_path, example_dir in MODEL_MAP.items():
    # Support "Dir/FMUName" form for CS_Puro
    parts = model_path.split("/")
    if len(parts) == 2:
        fmu_name = parts[1]
        fmu_path = os.path.join(BASE, "models", parts[0], f"{fmu_name}.fmu")
    else:
        fmu_name = parts[0]
        fmu_path = os.path.join(BASE, "models", fmu_name, f"{fmu_name}.fmu")

    out_path = os.path.join(BASE, "examples", example_dir, "host")

    if not os.path.exists(fmu_path):
        print(f"[SKIP] FMU not found: {fmu_path}")
        fail.append((fmu_name, "FMU not found"))
        continue

    print(f"[REGEN] {fmu_name} -> {example_dir}/host ...", end=" ", flush=True)
    r = subprocess.run(
        [sys.executable, os.path.join(BASE, "tools", "fmu_codegen_host.py"),
         fmu_path, out_path],
        capture_output=True, text=True, encoding="utf-8", errors="replace"
    )
    if r.returncode == 0:
        print("OK")
        ok.append(fmu_name)
    else:
        print(f"FAIL (exit {r.returncode})")
        print(r.stdout[-600:] if r.stdout else "")
        print(r.stderr[-600:] if r.stderr else "")
        fail.append((fmu_name, r.stderr[-200:]))

print(f"\n=== Regeneration: {len(ok)} OK, {len(fail)} FAIL ===")
for m, e in fail:
    print(f"  FAIL: {m} — {e}")
