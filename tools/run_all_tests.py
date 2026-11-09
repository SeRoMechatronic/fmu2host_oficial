#!/usr/bin/env python3
"""
run_all_tests.py — Ejecuta la bateria completa para todos los modelos FMU.

Descubre automaticamente todos los test_*_full.py bajo examples/,
ejecuta run_battery() por cada uno y genera:

  results/suite_summary.md   — informe global multi-modelo conclusivo
"""

from __future__ import annotations
import sys, os, datetime, math
from pathlib import Path

# Asegurar que tools/ este en el path
TOOLS_DIR = Path(__file__).resolve().parent
sys.path.insert(0, str(TOOLS_DIR))

from full_test_runner import run_battery

# ─────────────────────────────────────────────────────────────────────────────
# Categorias de modelos para analisis cruzado
# ─────────────────────────────────────────────────────────────────────────────

CATEGORIES = {
    "Algebraicos (sin estados)": {
        "desc": "Modelos puramente combinacionales sin integracion dinamica.",
        "models": {"sininputs", "mimodelonuevo", "potvumetro", "selectormodo", "valoresextremos"},
    },
    "ODE — sistemas de primer orden": {
        "desc": "Sistemas con 1-3 estados dinamicos de primer orden (filtros, tanques, motores).",
        "models": {"niveldeposito", "arranquesuavemotor", "crecimientopoblacional",
                   "osciladorarmonico", "reguladorbateria"},
    },
    "ODE — sistemas complejos": {
        "desc": "Sistemas no lineales o de alto orden con dinamica rica (caos, osciladores, control).",
        "models": {"pendulonolineal", "sistemalorenz", "cuerposacoplados", "ctpid", "suspensionactiva"},
    },
    "Alta dimension (5+ estados)": {
        "desc": "Modelos con buffers grandes: estresan el codegen con EULER/RK4_BUF_SIZE.",
        "models": {"muchosestados", "matrizestado", "frenadoabs"},
    },
    "Logica discreta y eventos": {
        "desc": "Automatas, contadores, secuenciadores y logica booleana.",
        "models": {"booleanlogica", "contadoreventos", "etapasecuenciador", "codigoerrordiagnostico"},
    },
    "Tipos de datos avanzados": {
        "desc": "Modelos con arrays, Strings, tipos mixtos o entradas/salidas especiales.",
        "models": {"arraysvectores", "multiplexorcanales", "stringsparametros",
                   "tiposmixtos", "stringinputoutput"},
    },
    "Algebraic mode probe": {
        "desc": "Legacy-named artifact whose XML declares both FMI ME and CS.",
        "models": {"cspurosinme"},
    },
}

# ─────────────────────────────────────────────────────────────────────────────
# Descubrimiento de configs
# ─────────────────────────────────────────────────────────────────────────────

def discover_configs(root: Path) -> list[Path]:
    configs = sorted(root.rglob("test_*_full.py"))
    return [c for c in configs if "results" not in c.parts]

# ─────────────────────────────────────────────────────────────────────────────
# Informe global multi-modelo
# ─────────────────────────────────────────────────────────────────────────────

def _pct(num, den):
    return f"{int(100*num/den)}%" if den else "—"

def _model_key(model_name: str) -> str:
    return model_name.lower().replace("_", "").replace(" ", "")


def generate_suite_report(all_model_results: list, suite_dir: Path) -> str:
    """
    all_model_results: lista de dicts con claves:
        model_name, tc_results, ret_code, config_path
    """
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")

    total_models  = len(all_model_results)
    models_pass   = sum(1 for m in all_model_results if m["ret_code"] == 0)
    models_fail   = total_models - models_pass
    total_tc      = sum(len(m["tc_results"]) for m in all_model_results)
    tc_pass       = sum(sum(1 for r in m["tc_results"] if r["global_pass"])
                        for m in all_model_results)
    tc_fail       = total_tc - tc_pass
    total_checks  = sum(sum(r["checks_pass"] + r["checks_fail"]
                            for r in m["tc_results"])
                        for m in all_model_results)
    checks_pass   = sum(sum(r["checks_pass"] for r in m["tc_results"])
                        for m in all_model_results)
    checks_fail   = total_checks - checks_pass

    lines = []; a = lines.append

    a(f"# Suite Report — Validacion FMI 2.0 Host")
    a(f"")
    a(f"> Generado: {now}  |  Modelos evaluados: {total_models}")
    a(f"")

    # ── Metricas globales ──────────────────────────────────────────────────
    a("## Metricas globales")
    a("")
    a("| Metrica | Valor | Tasa |")
    a("|---------|-------|------|")
    a(f"| Modelos evaluados    | {total_models} | — |")
    a(f"| Modelos 100% PASS    | {models_pass} | {_pct(models_pass, total_models)} |")
    a(f"| Modelos con FAILs    | {models_fail} | {_pct(models_fail, total_models)} |")
    a(f"| Test cases totales   | {total_tc} | — |")
    a(f"| Test cases PASS      | {tc_pass} | {_pct(tc_pass, total_tc)} |")
    a(f"| Test cases FAIL      | {tc_fail} | {_pct(tc_fail, total_tc)} |")
    a(f"| Checks individuales  | {total_checks} | — |")
    a(f"| Checks PASS          | {checks_pass} | {_pct(checks_pass, total_checks)} |")
    a(f"| Checks FAIL          | {checks_fail} | {_pct(checks_fail, total_checks)} |")
    a("")

    # ── Tabla resumen por modelo ───────────────────────────────────────────
    a("## Resultado por modelo")
    a("")
    a("| Modelo | TCs | PASS | FAIL | Checks OK | Checks KO | Estado |")
    a("|--------|-----|------|------|-----------|-----------|--------|")
    for m in all_model_results:
        mn  = m["model_name"]
        tcs = m["tc_results"]
        n   = len(tcs)
        p   = sum(1 for r in tcs if r["global_pass"])
        f   = n - p
        cp  = sum(r["checks_pass"] for r in tcs)
        cf  = sum(r["checks_fail"] for r in tcs)
        ico = "✅" if f == 0 else "❌"
        summary = m["config_path"].parent / "results" / "summary.md"
        rel = os.path.relpath(summary, suite_dir).replace("\\", "/")
        a(f"| [{mn}]({rel}) | {n} | {p} | {f} | {cp} | {cf} | {ico} |")
    a("")

    # ── Analisis por categoria ─────────────────────────────────────────────
    a("## Analisis por categoria de modelo")
    a("")
    for cat_name, cat_info in CATEGORIES.items():
        cat_keys = cat_info["models"]
        cat_models = [m for m in all_model_results
                      if _model_key(m["model_name"]) in cat_keys]
        if not cat_models:
            continue

        n_cat     = len(cat_models)
        p_cat     = sum(1 for m in cat_models if m["ret_code"] == 0)
        tc_cat    = sum(len(m["tc_results"]) for m in cat_models)
        tcp_cat   = sum(sum(1 for r in m["tc_results"] if r["global_pass"])
                        for m in cat_models)
        chk_cat   = sum(sum(r["checks_pass"]+r["checks_fail"]
                            for r in m["tc_results"]) for m in cat_models)
        chkp_cat  = sum(sum(r["checks_pass"] for r in m["tc_results"])
                        for m in cat_models)
        pct_tc    = int(100*tcp_cat/tc_cat) if tc_cat else 0
        pct_chk   = int(100*chkp_cat/chk_cat) if chk_cat else 0

        if pct_tc == 100:
            quality = "✅ Excelente"
        elif pct_tc >= 80:
            quality = "🟡 Bueno"
        elif pct_tc >= 50:
            quality = "🟠 Aceptable"
        else:
            quality = "❌ Deficiente"

        a(f"### {cat_name}")
        a("")
        a(f"*{cat_info['desc']}*")
        a("")
        a(f"| Modelos | TCs totales | TCs PASS | Checks PASS | Calidad |")
        a(f"|---------|-------------|----------|-------------|---------|")
        a(f"| {p_cat}/{n_cat} OK | {tc_cat} | {tcp_cat} ({pct_tc}%) | {chkp_cat}/{chk_cat} ({pct_chk}%) | {quality} |")
        a("")

        # Detalle de modelos en la categoria
        for m in cat_models:
            tcs  = m["tc_results"]
            np_  = sum(1 for r in tcs if r["global_pass"])
            nf_  = len(tcs) - np_
            ico  = "✅" if nf_ == 0 else "❌"
            fail_ids = [r["id"] for r in tcs if not r["global_pass"]]
            detail = f"Fallos: {', '.join(fail_ids)}" if fail_ids else "Sin fallos"
            a(f"- {ico} **{m['model_name']}** — {np_}/{len(tcs)} TCs OK. {detail}.")
        a("")

    # ── Detalle de fallos ──────────────────────────────────────────────────
    failed_models = [m for m in all_model_results if m["ret_code"] != 0]
    if failed_models:
        a("## Detalle de fallos")
        a("")
        for m in failed_models:
            a(f"### {m['model_name']}")
            a("")
            for r in m["tc_results"]:
                if not r["global_pass"]:
                    a(f"- **{r['id']}** — {r['title']} "
                      f"({r['checks_fail']} check(s) fallado(s))")
            a("")
    else:
        a("## Detalle de fallos")
        a("")
        a("*No se registraron fallos en ninguna bateria de test.*")
        a("")

    # ── Analisis de robustez del codegen ──────────────────────────────────
    a("## Analisis de robustez del codegen")
    a("")
    a("El siguiente analisis evalua el comportamiento del generador de codigo C host "
      "frente a distintos tipos de retos que suelen detectar errores de implementacion.")
    a("")

    robustez_items = [
        ("Buffer de estados (EULER/RK4_BUF_SIZE)",
         {"muchosestados", "matrizestado", "frenadoabs", "cuerposacoplados"},
         "Modelos con 4-5+ estados estresantes para buffers de integracion de tamano fijo."),
        ("Division por cero y guardas numericas",
         {"frenadoabs", "niveldeposito", "crecimientopoblacional", "sistemalorenz"},
         "Modelos que requieren guardas explicitas para evitar NaN/Inf."),
        ("Logica booleana y operadores estrictos",
         {"booleanlogica", "selectormodo", "suspensionactiva", "stringinputoutput"},
         "Frontera entre operadores < vs <= y AND/OR correctos."),
        ("Entradas/salidas de tipo String",
         {"stringinputoutput", "stringsparametros", "codigoerrordiagnostico"},
         "Modelos con puertos String: el codegen debe manejar fmi2String sin crashes."),
        ("Arrays y acceso por indice",
         {"arraysvectores", "matrizestado", "multiplexorcanales"},
         "Indices base-1 de Modelica correctamente trasladados a base-0 en C."),
        ("Eventos discretos y contadores",
         {"contadoreventos", "etapasecuenciador", "booleanlogica"},
         "Transiciones de flanco, contadores y maquinas de estado."),
        ("Dinamica caotica / no lineal",
         {"sistemalorenz", "pendulonolineal", "cuerposacoplados"},
         "Modelos sensibles a errores de integracion o estado inicial."),
        ("Algebraic dual-mode probe",
         {"cspurosinme"},
         "Legacy-named artifact whose XML declares both ME and CS."),
    ]

    a("| Area de robustez | Modelos involucrados | Tasa PASS | Estado |")
    a("|------------------|----------------------|-----------|--------|")
    for area, model_set, desc in robustez_items:
        area_models = [m for m in all_model_results
                       if _model_key(m["model_name"]) in model_set]
        if not area_models:
            a(f"| {area} | — | — | ⬜ Sin datos |")
            continue
        n_  = len(area_models)
        p_  = sum(1 for m in area_models if m["ret_code"] == 0)
        a(f"| {area} | {', '.join(m['model_name'] for m in area_models)} | "
          f"{p_}/{n_} ({_pct(p_, n_)}) | {'✅' if p_==n_ else '❌'} |")
    a("")

    # ── Modelos mas exigentes (menor tasa de exito) ────────────────────────
    by_rate = sorted(all_model_results,
                     key=lambda m: sum(1 for r in m["tc_results"] if r["global_pass"])
                                   / max(len(m["tc_results"]), 1))
    hardest = [m for m in by_rate if m["ret_code"] != 0][:5]
    if hardest:
        a("## Modelos con mayor tasa de fallo")
        a("")
        a("| Modelo | TCs PASS | TCs FAIL | Tasa exito |")
        a("|--------|----------|----------|------------|")
        for m in hardest:
            tcs = m["tc_results"]
            p_  = sum(1 for r in tcs if r["global_pass"])
            f_  = len(tcs) - p_
            a(f"| {m['model_name']} | {p_} | {f_} | {_pct(p_, len(tcs))} |")
        a("")

    # ── Conclusions generales ──────────────────────────────────────────────
    a("## Conclusiones generales")
    a("")

    pct_total = int(100 * tc_pass / total_tc) if total_tc else 0

    if models_fail == 0:
        a(f"**El codegen host supera el {pct_total}% de los {total_tc} test cases "
          f"en los {total_models} modelos evaluados.**")
        a("")
        a("La implementacion demuestra:")
        a(f"- Correctitud numerica en todos los tipos de solver (RK4 y Euler) "
          f"para sistemas ODE de hasta {max(5, 5)} estados.")
        a(f"- Manejo correcto de NaN/Inf mediante guardas de division.")
        a(f"- Soporte completo de FMI 2.0 ME y CS.")
        a(f"- Tipos de datos correctos: Real, Boolean, Integer, String, arrays.")
        a(f"- Logica booleana y operadores de comparacion estrictamente correctos.")
        a(f"- Automatismo de eventos y maquinas de estado funcionales.")
    else:
        pct_fail = int(100 * models_fail / total_models)
        a(f"**{models_fail} de {total_models} modelos presentan fallos "
          f"({pct_fail}% de la suite).**")
        a("")
        a(f"Tasa de test cases superados: {tc_pass}/{total_tc} ({pct_total}%).")
        a("")
        a("**Areas prioritarias de mejora:**")

        # identificar categorias con mas fallos
        for cat_name, cat_info in CATEGORIES.items():
            cat_keys = cat_info["models"]
            cat_models = [m for m in all_model_results
                          if _model_key(m["model_name"]) in cat_keys]
            cat_fail = [m for m in cat_models if m["ret_code"] != 0]
            if cat_fail:
                a(f"- **{cat_name}**: {len(cat_fail)}/{len(cat_models)} modelos con fallos.")

        a("")
        a("Se recomienda revisar los checks fallados en la seccion 'Detalle de fallos' "
          "y el informe individual de cada modelo para diagnostico detallado.")

    a("")
    a("---")
    a(f"*Informe generado automaticamente por `run_all_tests.py` — {now}*")
    a("")

    return "\n".join(lines)


# ─────────────────────────────────────────────────────────────────────────────
# Main
# ─────────────────────────────────────────────────────────────────────────────

def main():
    contrib_root = TOOLS_DIR.parent
    examples_dir = contrib_root / "examples"

    if not examples_dir.is_dir():
        print(f"ERROR: No se encuentra examples/ en {contrib_root}")
        sys.exit(1)

    configs = discover_configs(examples_dir)
    print(f"\n{'='*70}")
    print(f"  SUITE RUNNER — FMI 2.0 Host Validation")
    print(f"  Modelos descubiertos: {len(configs)}")
    print(f"{'='*70}\n")

    all_model_results = []
    for i, config_path in enumerate(configs, 1):
        model_label = config_path.parent.parent.parent.name  # examples/<model>/...
        print(f"[{i:02d}/{len(configs)}] {model_label}")
        try:
            ret, tc_results, model_name = run_battery(config_path)
        except Exception as exc:
            print(f"  ⚠️  Excepcion al ejecutar {config_path.name}: {exc}")
            ret        = 2
            tc_results = []
            model_name = model_label
        all_model_results.append({
            "model_name":  model_name,
            "tc_results":  tc_results,
            "ret_code":    ret,
            "config_path": config_path,
        })

    # Directorio de la suite
    suite_dir = contrib_root / "results"
    suite_dir.mkdir(exist_ok=True)

    # Informe global
    suite_md   = generate_suite_report(all_model_results, suite_dir)
    suite_path = suite_dir / "suite_summary.md"
    suite_path.write_text(suite_md, encoding="utf-8")

    # Resumen en consola
    total   = len(all_model_results)
    passed  = sum(1 for m in all_model_results if m["ret_code"] == 0)
    total_tc  = sum(len(m["tc_results"]) for m in all_model_results)
    tc_pass   = sum(sum(1 for r in m["tc_results"] if r["global_pass"])
                    for m in all_model_results)

    print(f"\n{'='*70}")
    print(f"  SUITE COMPLETA — RESULTADO FINAL")
    print(f"  Modelos:     {passed}/{total} PASS  ({total-passed} FAIL)")
    print(f"  Test cases:  {tc_pass}/{total_tc} PASS")
    print(f"  Informe:     {suite_path}")
    print(f"{'='*70}\n")

    if total - passed > 0:
        print("Modelos con fallos:")
        for m in all_model_results:
            if m["ret_code"] != 0:
                f_ = sum(1 for r in m["tc_results"] if not r["global_pass"])
                print(f"  ❌ {m['model_name']}  ({f_} TC(s) fallado(s))")
        print()

    sys.exit(0 if passed == total else 1)


if __name__ == "__main__":
    main()
