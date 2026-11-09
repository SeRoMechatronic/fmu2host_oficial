#!/usr/bin/env python3
"""
test_utils.py — Framework compartido para los tests de cada modelo FMU.

Usado por cada test_<modelo>.py individual.
NO ejecutar directamente.

Flujo:
    1. Localiza los ejecutables _host_me y _host_cs en build/
    2. Corre 3 escenarios: ME+Euler, ME+RK4, CS
    3. Guarda resultados en results/ como CSV
    4. Genera graficas de comparacion
    5. Escribe un informe completo en Markdown

Requisitos:
    Python 3.8+  |  pandas  |  matplotlib
"""

import os
import sys
import subprocess
import csv
import math
import io
import datetime
from typing import Optional


# =============================================================================
# Importar pandas y matplotlib de forma opcional
# =============================================================================

try:
    import pandas as pd
    _HAS_PANDAS = True
except ImportError:
    _HAS_PANDAS = False

try:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import matplotlib.gridspec as gridspec
    _HAS_MPL = True
except ImportError:
    _HAS_MPL = False


# =============================================================================
# Localizacion de ejecutables
# =============================================================================

def _find_build_dir(test_file: str) -> str:
    """Sube desde test/ hasta la raiz del repositorio y devuelve build/."""
    # test_file: .../examples/<modelo>/host/test/test_<modelo>.py
    # subir 4 niveles: test/ -> host/ -> <modelo>/ -> examples/ -> repo root
    contrib = os.path.abspath(os.path.join(os.path.dirname(test_file),
                                           "..", "..", "..", ".."))
    return os.path.join(contrib, "build")


def _find_exes(test_file: str) -> dict:
    """
    Localiza los ejecutables _host_me y _host_cs para el modelo.

    Returns:
        dict con claves 'me' y/o 'cs' apuntando a rutas absolutas de .exe.
        Si un modo no existe, la clave no esta presente.
    """
    build = _find_build_dir(test_file)
    # ejemplos/<modelo>/host/ -> <modelo> es el nombre de la carpeta
    host_dir = os.path.abspath(os.path.join(os.path.dirname(test_file), ".."))
    model_folder = os.path.basename(os.path.dirname(host_dir))  # <modelo>

    release_dir = os.path.join(build, "examples", model_folder, "host", "Release")

    exes = {}
    if os.path.isdir(release_dir):
        for f in os.listdir(release_dir):
            if f.endswith("_host_me.exe"):
                exes["me"] = os.path.join(release_dir, f)
            elif f.endswith("_host_cs.exe"):
                exes["cs"] = os.path.join(release_dir, f)
    return exes


# =============================================================================
# Ejecucion del simulador
# =============================================================================

def run_simulation(exe: str, t_end: float, h: float,
                   solver: Optional[str] = None,
                   inputs: Optional[dict] = None,
                   timeout: int = 120) -> Optional[list]:
    """
    Ejecuta el simulador y devuelve los datos como lista de dicts.

    Args:
        exe:     Ruta al ejecutable.
        t_end:   Tiempo final de simulacion.
        h:       Paso de integracion.
        solver:  "euler", "rk4", o None (para CS que no tiene selector).
        inputs:  Dict de entradas a sobrescribir via CLI, e.g. {"pot": 0.7}.
        timeout: Segundos maximos de ejecucion.

    Returns:
        Lista de dicts {col: valor} por cada fila de la salida CSV,
        o None si fallo la ejecucion.
    """
    cmd = [exe, str(t_end), str(h)]
    if solver is not None:
        cmd.append(solver)
    if inputs:
        for name, val in inputs.items():
            cmd.append(f"{name}={val}")

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return None
    except FileNotFoundError:
        return None

    if result.returncode != 0:
        return None

    stdout = result.stdout.strip()
    if not stdout:
        return None

    lines = stdout.splitlines()
    if len(lines) < 2:
        return None

    reader = csv.DictReader(io.StringIO(stdout))
    rows = []
    for row in reader:
        parsed = {}
        for k, v in row.items():
            k = k.strip()
            v = v.strip() if v else v
            try:
                parsed[k] = int(v)
            except (ValueError, TypeError):
                try:
                    parsed[k] = float(v)
                except (ValueError, TypeError):
                    parsed[k] = v
        rows.append(parsed)
    return rows if rows else None


# =============================================================================
# Verificaciones
# =============================================================================

class CheckResult:
    def __init__(self, name: str, passed: bool, detail: str = ""):
        self.name = name
        self.passed = passed
        self.detail = detail

    def __repr__(self):
        status = "PASS" if self.passed else "FAIL"
        return f"[{status}] {self.name}" + (f" — {self.detail}" if self.detail else "")


def _get_col(rows: list, col: str) -> list:
    """Extrae los valores de una columna (ignora errores de parseo)."""
    vals = []
    for r in rows:
        v = r.get(col)
        if v is not None:
            vals.append(v)
    return vals


def check_always(rows: list, col: str, op: str, val,
                 name: str = None, tol: float = 0.0) -> CheckResult:
    """
    Verifica que TODOS los valores de 'col' cumplen la condicion op val.

    op: '>', '>=', '<', '<=', '==', '!=', 'abs<', 'abs<='
    tol: tolerancia para '==' (|actual - val| <= tol)
    """
    if name is None:
        name = f"siempre {col} {op} {val}"
    values = _get_col(rows, col)
    if not values:
        return CheckResult(name, False, f"columna '{col}' no encontrada")

    failures = []
    for i, v in enumerate(values):
        try:
            v_f = float(v)
        except (TypeError, ValueError):
            failures.append(f"fila {i}: no numerico ({v!r})")
            continue

        ok = True
        if op == ">":
            ok = v_f > val
        elif op == ">=":
            ok = v_f >= val
        elif op == "<":
            ok = v_f < val
        elif op == "<=":
            ok = v_f <= val
        elif op == "==":
            ok = abs(v_f - val) <= tol
        elif op == "!=":
            ok = v_f != val
        elif op == "abs<":
            ok = abs(v_f) < val
        elif op == "abs<=":
            ok = abs(v_f) <= val

        if not ok:
            failures.append(f"fila {i} t={rows[i].get('t','?'):.4g}: {v_f} {op} {val} FALSO")
            if len(failures) >= 3:
                failures.append("...")
                break

    if failures:
        return CheckResult(name, False, "; ".join(failures))
    return CheckResult(name, True, f"{len(values)} filas OK")


def check_eventually(rows: list, col: str, op: str, val,
                     name: str = None) -> CheckResult:
    """Verifica que AL MENOS UNA fila cumple la condicion."""
    if name is None:
        name = f"alguna vez {col} {op} {val}"
    values = _get_col(rows, col)
    if not values:
        return CheckResult(name, False, f"columna '{col}' no encontrada")

    for i, v in enumerate(values):
        try:
            v_f = float(v)
        except (TypeError, ValueError):
            continue
        ok = False
        if op == ">":
            ok = v_f > val
        elif op == ">=":
            ok = v_f >= val
        elif op == "<":
            ok = v_f < val
        elif op == "<=":
            ok = v_f <= val
        elif op == "==":
            ok = v_f == val
        elif op == "!=":
            ok = v_f != val
        elif op == "abs<":
            ok = abs(v_f) < val
        if ok:
            return CheckResult(name, True,
                               f"t={rows[i].get('t','?'):.4g}: {v_f}")
    return CheckResult(name, False, f"nunca cumplido en {len(values)} filas")


def check_at_t(rows: list, t_target: float, col: str, expected,
               tol: float = 0.05, name: str = None) -> CheckResult:
    """Verifica el valor de 'col' en el instante mas cercano a t_target."""
    if name is None:
        name = f"{col} @ t={t_target}"
    if not rows:
        return CheckResult(name, False, "sin datos")

    best = min(rows, key=lambda r: abs(float(r.get("t", 1e9)) - t_target))
    actual = best.get(col)
    t_actual = float(best.get("t", 0))

    if actual is None:
        return CheckResult(name, False, f"columna '{col}' no encontrada")

    try:
        a_f = float(actual)
        e_f = float(expected)
        if abs(a_f - e_f) <= tol:
            return CheckResult(name, True,
                               f"t={t_actual:.4g}: {a_f:.6g} ~= {e_f} (tol={tol})")
        return CheckResult(name, False,
                           f"t={t_actual:.4g}: {a_f:.6g} != {e_f} (tol={tol})")
    except (TypeError, ValueError):
        if str(actual) == str(expected):
            return CheckResult(name, True, f"t={t_actual:.4g}: '{actual}'")
        return CheckResult(name, False,
                           f"t={t_actual:.4g}: '{actual}' != '{expected}'")


def check_no_nan_inf(rows: list, name: str = "sin NaN/Inf") -> CheckResult:
    """Verifica que ningun valor numerico es NaN o Inf."""
    if not rows:
        return CheckResult(name, False, "sin datos")
    for i, row in enumerate(rows):
        for col, val in row.items():
            if isinstance(val, float):
                if math.isnan(val):
                    return CheckResult(name, False, f"NaN en '{col}' fila {i}")
                if math.isinf(val):
                    return CheckResult(name, False, f"Inf en '{col}' fila {i}")
    return CheckResult(name, True, f"{len(rows)} filas OK")


def check_final_t(rows: list, t_end: float, tol: float = 0.02,
                  name: str = "simulacion completa") -> CheckResult:
    """Verifica que la simulacion llego cerca de t_end."""
    if not rows:
        return CheckResult(name, False, "sin datos")
    t_last = float(rows[-1].get("t", 0))
    if abs(t_last - t_end) <= tol + t_end * 0.01:
        return CheckResult(name, True, f"t_final={t_last:.4g}")
    return CheckResult(name, False,
                       f"t_final={t_last:.4g}, esperado={t_end}")


def check_sign_changes(rows: list, col: str, min_changes: int,
                       name: str = None) -> CheckResult:
    """Cuenta cambios de signo en 'col' y verifica que hay al menos min_changes."""
    if name is None:
        name = f"{col} cambia de signo >= {min_changes}x"
    vals = _get_col(rows, col)
    if not vals:
        return CheckResult(name, False, f"columna '{col}' no encontrada")
    changes = 0
    prev = None
    for v in vals:
        try:
            f = float(v)
        except (TypeError, ValueError):
            continue
        if prev is not None and prev * f < 0:
            changes += 1
        if f != 0:
            prev = f
    if changes >= min_changes:
        return CheckResult(name, True, f"{changes} cambios de signo")
    return CheckResult(name, False, f"solo {changes} cambios (min={min_changes})")


def check_monotone(rows: list, col: str, direction: str = "dec",
                   name: str = None) -> CheckResult:
    """
    Verifica monotonia de 'col'.
    direction: 'inc' (creciente) o 'dec' (decreciente).
    """
    if name is None:
        name = f"{col} {'creciente' if direction == 'inc' else 'decreciente'}"
    vals = _get_col(rows, col)
    if not vals:
        return CheckResult(name, False, f"columna '{col}' no encontrada")
    try:
        floats = [float(v) for v in vals]
    except (TypeError, ValueError):
        return CheckResult(name, False, "valores no numericos")

    violations = []
    for i in range(1, len(floats)):
        if direction == "dec" and floats[i] > floats[i - 1] + 1e-10:
            violations.append(f"fila {i}: {floats[i]:.6g} > {floats[i-1]:.6g}")
        elif direction == "inc" and floats[i] < floats[i - 1] - 1e-10:
            violations.append(f"fila {i}: {floats[i]:.6g} < {floats[i-1]:.6g}")
        if len(violations) >= 3:
            violations.append("...")
            break

    if violations:
        return CheckResult(name, False, "; ".join(violations))
    return CheckResult(name, True, f"{len(floats)} puntos OK")


# =============================================================================
# Guardado de CSV
# =============================================================================

def save_csv(rows: list, path: str) -> None:
    """Guarda los datos en un archivo CSV."""
    if not rows:
        return
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=rows[0].keys())
        writer.writeheader()
        writer.writerows(rows)


# =============================================================================
# Generacion de graficas
# =============================================================================

def _output_cols(rows: list) -> list:
    """Devuelve columnas que no son 't' ni inputs (heuristica: todas menos 't')."""
    if not rows:
        return []
    return [c for c in rows[0].keys() if c != "t"]


def plot_scenarios(scenarios: dict, model_name: str, out_path: str) -> None:
    """
    Genera una grafica de comparacion con todas las variables de salida.

    Args:
        scenarios: dict {"ME Euler": rows, "ME RK4": rows, "CS": rows}
        model_name: nombre del modelo para el titulo
        out_path: ruta del PNG de salida
    """
    if not _HAS_MPL:
        return

    # Determinar columnas de salida (union de todos los escenarios)
    all_cols = []
    for rows in scenarios.values():
        if rows:
            for c in _output_cols(rows):
                if c not in all_cols:
                    all_cols.append(c)

    if not all_cols:
        return

    n_plots = len(all_cols)
    fig, axes = plt.subplots(n_plots, 1,
                             figsize=(12, max(3 * n_plots, 4)),
                             sharex=False, squeeze=False)

    colors = {"ME Euler": "#e74c3c", "ME RK4": "#2ecc71", "CS": "#3498db"}
    styles = {"ME Euler": "--", "ME RK4": "-", "CS": ":"}

    for ax_idx, col in enumerate(all_cols):
        ax = axes[ax_idx][0]
        for label, rows in scenarios.items():
            if not rows:
                continue
            ts = [float(r.get("t", 0)) for r in rows]
            try:
                ys = [float(r.get(col, float("nan"))) for r in rows]
            except (TypeError, ValueError):
                continue
            ax.plot(ts, ys,
                    color=colors.get(label, "black"),
                    linestyle=styles.get(label, "-"),
                    linewidth=1.4,
                    label=label,
                    alpha=0.85)
        ax.set_ylabel(col, fontsize=8)
        ax.grid(True, alpha=0.3)
        ax.legend(fontsize=7, loc="upper right")

    axes[-1][0].set_xlabel("t (s)")
    fig.suptitle(f"{model_name} — Comparacion ME Euler / ME RK4 / CS",
                 fontsize=11, fontweight="bold")
    plt.tight_layout()
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    plt.savefig(out_path, dpi=120, bbox_inches="tight")
    plt.close(fig)


def plot_single(rows: list, label: str, model_name: str, out_path: str) -> None:
    """Grafica individual para un escenario."""
    if not _HAS_MPL or not rows:
        return

    cols = _output_cols(rows)
    if not cols:
        return

    n = len(cols)
    fig, axes = plt.subplots(n, 1,
                             figsize=(10, max(2.5 * n, 3)),
                             sharex=True, squeeze=False)

    ts = [float(r.get("t", 0)) for r in rows]
    for i, col in enumerate(cols):
        ax = axes[i][0]
        try:
            ys = [float(r.get(col, float("nan"))) for r in rows]
        except (TypeError, ValueError):
            continue
        ax.plot(ts, ys, linewidth=1.4)
        ax.set_ylabel(col, fontsize=8)
        ax.grid(True, alpha=0.3)

    axes[-1][0].set_xlabel("t (s)")
    fig.suptitle(f"{model_name} — {label}", fontsize=10, fontweight="bold")
    plt.tight_layout()
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    plt.savefig(out_path, dpi=120, bbox_inches="tight")
    plt.close(fig)


# =============================================================================
# Generacion del informe
# =============================================================================

def _stats(rows: list, col: str) -> str:
    """Devuelve min/max/final como string."""
    vals = _get_col(rows, col)
    try:
        floats = [float(v) for v in vals]
        return (f"min={min(floats):.6g}  max={max(floats):.6g}"
                f"  final={floats[-1]:.6g}")
    except (TypeError, ValueError):
        return "no numerico"


def write_report(model_name: str,
                 scenarios: dict,
                 checks_by_scenario: dict,
                 params: dict,
                 out_path: str) -> None:
    """
    Escribe el informe completo en Markdown.

    Args:
        model_name:          Nombre del modelo.
        scenarios:           {"ME Euler": rows, "ME RK4": rows, "CS": rows}
        checks_by_scenario:  {"ME Euler": [CheckResult,...], ...}
        params:              {"t_end_me": X, "h_me": Y, "t_end_cs": Z, "h_cs": W}
        out_path:            Ruta del .md de salida.
    """
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    lines = []
    a = lines.append

    a(f"# Informe de test — {model_name}")
    a(f"")
    a(f"Generado: {now}")
    a(f"")

    # Parametros de simulacion
    a(f"## Parametros de simulacion")
    a(f"")
    a(f"| Escenario | t_end (s) | h (s) | Solver |")
    a(f"|-----------|-----------|-------|--------|")
    t_me = params.get("t_end_me", "—")
    h_me = params.get("h_me", "—")
    t_cs = params.get("t_end_cs", "—")
    h_cs = params.get("h_cs", "—")
    a(f"| ME Euler  | {t_me}    | {h_me}| Euler  |")
    a(f"| ME RK4    | {t_me}    | {h_me}| RK4    |")
    a(f"| CS        | {t_cs}    | {h_cs}| interno|")
    a(f"")

    # Resumen ejecutivo
    a(f"## Resumen de resultados")
    a(f"")
    total_pass = total_fail = 0
    for sc, checks in checks_by_scenario.items():
        p = sum(1 for c in checks if c.passed)
        f = sum(1 for c in checks if not c.passed)
        total_pass += p
        total_fail += f
        rows = scenarios.get(sc)
        status = "ejecutado" if rows is not None else "**NO EJECUTADO**"
        a(f"- **{sc}**: {status} | {p} PASS / {f} FAIL")
    a(f"")
    a(f"**Total: {total_pass} PASS / {total_fail} FAIL**")
    a(f"")

    # Detalle por escenario
    for sc_label, rows in scenarios.items():
        a(f"---")
        a(f"")
        a(f"## Escenario: {sc_label}")
        a(f"")

        if rows is None:
            a(f"> Ejecutable no encontrado o error al correr la simulacion.")
            a(f"")
            continue

        a(f"**Filas de datos:** {len(rows)}")
        a(f"")

        # Estadisticas de salidas
        if rows:
            cols = _output_cols(rows)
            if cols:
                a(f"### Estadisticas de variables de salida")
                a(f"")
                a(f"| Variable | min | max | final |")
                a(f"|----------|-----|-----|-------|")
                for col in cols:
                    vals = _get_col(rows, col)
                    try:
                        floats = [float(v) for v in vals]
                        a(f"| {col} | {min(floats):.6g} | {max(floats):.6g}"
                          f" | {floats[-1]:.6g} |")
                    except (TypeError, ValueError):
                        a(f"| {col} | — | — | {vals[-1] if vals else '—'} |")
                a(f"")

        # Checks
        checks = checks_by_scenario.get(sc_label, [])
        if checks:
            a(f"### Verificaciones")
            a(f"")
            for c in checks:
                icon = "[PASS]" if c.passed else "[FAIL]"
                a(f"- {icon} **{c.name}**" + (f": {c.detail}" if c.detail else ""))
            a(f"")

        # Primeras y ultimas filas
        if rows:
            a(f"### Muestra de datos")
            a(f"")
            sample = rows[:3] + (["..."] if len(rows) > 6 else []) + rows[-3:]
            cols_all = list(rows[0].keys())
            a("| " + " | ".join(cols_all) + " |")
            a("| " + " | ".join(["---"] * len(cols_all)) + " |")
            for r in sample:
                if r == "...":
                    a("| " + " | ".join(["..."] * len(cols_all)) + " |")
                else:
                    vals_str = []
                    for c in cols_all:
                        v = r.get(c, "")
                        try:
                            vals_str.append(f"{float(v):.6g}")
                        except (TypeError, ValueError):
                            vals_str.append(str(v))
                    a("| " + " | ".join(vals_str) + " |")
            a(f"")

    # Graficas
    a(f"---")
    a(f"")
    a(f"## Graficas generadas")
    a(f"")
    a(f"- `{model_name}_comparacion.png` — Comparacion de los 3 escenarios")
    a(f"- `{model_name}_me_euler.png` — ME con solver Euler")
    a(f"- `{model_name}_me_rk4.png` — ME con solver RK4")
    a(f"- `{model_name}_cs.png` — Co-Simulation")
    a(f"")
    a(f"---")
    a(f"")
    a(f"*Informe generado automaticamente por test_utils.py*")

    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))


# =============================================================================
# Punto de entrada principal
# =============================================================================

def run_test_battery(test_file: str, config: dict) -> int:
    """
    Ejecuta la bateria de tests completa para un modelo.

    Args:
        test_file: __file__ del test_<modelo>.py que llama esta funcion.
        config:    Diccionario de configuracion del modelo. Claves:
                     model_name      str   Nombre legible del modelo
                     t_end_me        float Tiempo final para ME (default 10.0)
                     h_me            float Paso ME (default 0.01)
                     t_end_cs        float Tiempo final para CS (default igual a ME)
                     h_cs            float Paso CS (default igual a ME)
                     checks_me_euler list  Lista de dicts de checks para ME+Euler
                     checks_me_rk4   list  Lista de dicts de checks para ME+RK4
                     checks_cs       list  Lista de dicts de checks para CS

    Returns:
        0 si todos los checks pasan, 1 si alguno falla, 2 si ningun exe encontrado.
    """
    model_name  = config.get("model_name", os.path.basename(os.path.dirname(test_file)))
    t_end_me    = float(config.get("t_end_me", 10.0))
    h_me        = float(config.get("h_me", 0.01))
    t_end_cs    = float(config.get("t_end_cs", t_end_me))
    h_cs        = float(config.get("h_cs", h_me))
    test_inputs = config.get("test_inputs", {})

    test_dir    = os.path.dirname(os.path.abspath(test_file))
    results_dir = os.path.join(test_dir, "results")
    os.makedirs(results_dir, exist_ok=True)

    exes = _find_exes(test_file)
    if not exes:
        print(f"[ERROR] No se encontraron ejecutables para {model_name}")
        print(f"        Verifica que el build este completo en build/examples/")
        return 2

    print(f"\n{'='*60}")
    print(f"  TEST BATTERY — {model_name}")
    print(f"{'='*60}")

    # -- Correr simulaciones ---------------------------------------------------
    scenarios = {}
    if test_inputs:
        print(f"  Entradas de test: {test_inputs}")

    print(f"\n[1/3] ME + Euler  (t_end={t_end_me}, h={h_me})")
    if "me" in exes:
        rows_euler = run_simulation(exes["me"], t_end_me, h_me, "euler", inputs=test_inputs)
        scenarios["ME Euler"] = rows_euler
        if rows_euler:
            save_csv(rows_euler,
                     os.path.join(results_dir, f"{model_name.lower()}_me_euler.csv"))
            plot_single(rows_euler, "ME Euler", model_name,
                        os.path.join(results_dir, f"{model_name.lower()}_me_euler.png"))
            print(f"    {len(rows_euler)} filas  ->  CSV + PNG guardados")
        else:
            print(f"    ERROR al ejecutar")
    else:
        scenarios["ME Euler"] = None
        print(f"    Ejecutable ME no disponible")

    print(f"\n[2/3] ME + RK4    (t_end={t_end_me}, h={h_me})")
    if "me" in exes:
        rows_rk4 = run_simulation(exes["me"], t_end_me, h_me, "rk4", inputs=test_inputs)
        scenarios["ME RK4"] = rows_rk4
        if rows_rk4:
            save_csv(rows_rk4,
                     os.path.join(results_dir, f"{model_name.lower()}_me_rk4.csv"))
            plot_single(rows_rk4, "ME RK4", model_name,
                        os.path.join(results_dir, f"{model_name.lower()}_me_rk4.png"))
            print(f"    {len(rows_rk4)} filas  ->  CSV + PNG guardados")
        else:
            print(f"    ERROR al ejecutar")
    else:
        scenarios["ME RK4"] = None
        print(f"    Ejecutable ME no disponible")

    print(f"\n[3/3] CS          (t_end={t_end_cs}, h={h_cs})")
    if "cs" in exes:
        rows_cs = run_simulation(exes["cs"], t_end_cs, h_cs, solver=None, inputs=test_inputs)
        scenarios["CS"] = rows_cs
        if rows_cs:
            save_csv(rows_cs,
                     os.path.join(results_dir, f"{model_name.lower()}_cs.csv"))
            plot_single(rows_cs, "CS", model_name,
                        os.path.join(results_dir, f"{model_name.lower()}_cs.png"))
            print(f"    {len(rows_cs)} filas  ->  CSV + PNG guardados")
        else:
            print(f"    ERROR al ejecutar")
    else:
        scenarios["CS"] = None
        print(f"    Ejecutable CS no disponible")

    # -- Grafica de comparacion ------------------------------------------------
    plot_scenarios(scenarios, model_name,
                   os.path.join(results_dir, f"{model_name.lower()}_comparacion.png"))

    # -- Ejecutar checks -------------------------------------------------------
    def _run_checks(rows, check_defs: list) -> list:
        results = []
        if not rows:
            return results

        # Check base siempre presente
        results.append(check_no_nan_inf(rows))

        for cd in check_defs:
            kind = cd.get("type", "always")
            col  = cd.get("col", "")
            op   = cd.get("op", ">")
            val  = cd.get("val", 0)
            tol  = cd.get("tol", 0.0)
            name = cd.get("name", None)

            if kind == "always":
                results.append(check_always(rows, col, op, val, name=name, tol=tol))
            elif kind == "eventually":
                results.append(check_eventually(rows, col, op, val, name=name))
            elif kind == "at_t":
                t_target = cd.get("t", 0.0)
                results.append(check_at_t(rows, t_target, col, val, tol=tol, name=name))
            elif kind == "sign_changes":
                min_ch = cd.get("min_changes", 2)
                results.append(check_sign_changes(rows, col, min_ch, name=name))
            elif kind == "monotone":
                direction = cd.get("direction", "dec")
                results.append(check_monotone(rows, col, direction, name=name))
            elif kind == "final_t":
                t_end_check = cd.get("t_end", t_end_me)
                results.append(check_final_t(rows, t_end_check, name=name))

        return results

    checks_by_scenario = {
        "ME Euler": _run_checks(scenarios["ME Euler"],
                                config.get("checks_me_euler", [])),
        "ME RK4":   _run_checks(scenarios["ME RK4"],
                                config.get("checks_me_rk4", [])),
        "CS":       _run_checks(scenarios["CS"],
                                config.get("checks_cs", [])),
    }

    # -- Imprimir resultados ---------------------------------------------------
    print(f"\n{'-'*60}")
    print(f"  RESULTADOS DE CHECKS")
    print(f"{'-'*60}")
    total_pass = total_fail = 0
    for sc, checks in checks_by_scenario.items():
        if not checks:
            continue
        p = sum(1 for c in checks if c.passed)
        f = sum(1 for c in checks if not c.passed)
        total_pass += p
        total_fail += f
        status = "OK" if f == 0 else "X"
        print(f"\n  {status} {sc}: {p} PASS / {f} FAIL")
        for c in checks:
            icon = "  OK" if c.passed else "  X"
            print(f"    {icon} {c.name}" +
                  (f"\n          -> {c.detail}" if c.detail and not c.passed else ""))

    print(f"\n{'-'*60}")
    print(f"  TOTAL: {total_pass} PASS / {total_fail} FAIL")
    print(f"{'-'*60}\n")

    # -- Informe ---------------------------------------------------------------
    params = {"t_end_me": t_end_me, "h_me": h_me, "t_end_cs": t_end_cs, "h_cs": h_cs}
    report_path = os.path.join(results_dir, f"{model_name.lower()}_report.md")
    write_report(model_name, scenarios, checks_by_scenario, params, report_path)
    print(f"  Informe guardado: {report_path}")

    return 0 if total_fail == 0 else 1


if __name__ == "__main__":
    print("test_utils.py es un modulo auxiliar. Ejecuta test_<modelo>.py directamente.")

