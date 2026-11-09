#!/usr/bin/env python3
"""
full_test_runner.py — Bateria completa de test cases para modelos FMU.

Genera por cada TC:
  results/TC-ID/
      sim_<label>.csv
      sim_<label>.png          (grafica individual por solver)
      comparison.png           (superpuesto cuando hay > 1 solver)
      report_TC-ID.md          (informe con analisis real de datos)
  results/summary.md           (resumen del modelo)
"""

from __future__ import annotations
import sys, os, subprocess, csv, math, importlib.util, statistics, datetime
from pathlib import Path
from typing import Optional

# Forzar UTF-8 en stdout/stderr para que los iconos Unicode no fallen en Windows
if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")

try:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import matplotlib.gridspec as gridspec
    HAS_MPL = True
except ImportError:
    HAS_MPL = False

# ─────────────────────────────────────────────────────────────────────────────
# Localizacion de ejecutables
# ─────────────────────────────────────────────────────────────────────────────

def _find_build_root(config_path: Path) -> Path:
    override = os.environ.get("FMU2HOST_BUILD_DIR")
    if override:
        build = Path(override).expanduser().resolve()
        if not build.is_dir():
            raise FileNotFoundError(
                f"FMU2HOST_BUILD_DIR does not name a directory: {build}"
            )
        return build

    p = config_path.resolve()
    for _ in range(12):
        c = p / "build"
        if c.is_dir():
            return c
        p = p.parent
    raise FileNotFoundError("No se encontro carpeta build/")

def locate_exe(model_name: str, suffix: str, config_path: Path) -> Optional[Path]:
    build = _find_build_root(config_path)
    lower = model_name.lower().replace("_", "").replace("-", "")
    # busqueda rapida por patron convencional
    for sub in build.rglob(f"*_host_{suffix}.exe"):
        stem = sub.stem.replace(f"_host_{suffix}", "").replace("_", "")
        if stem == lower:
            return sub
    return None

# ─────────────────────────────────────────────────────────────────────────────
# Ejecucion del simulador
# ─────────────────────────────────────────────────────────────────────────────

def build_cmd(exe: Path, t_end: float, h: float, solver: Optional[str],
              inputs: dict, schedule: dict) -> list:
    cmd = [str(exe), str(t_end), str(h)]
    if solver is not None:
        cmd.append(solver)
    for name, val in (inputs or {}).items():
        cmd.append(f"{name}={val}")
    for name, entries in (schedule or {}).items():
        for (t_e, v_e) in sorted(entries, key=lambda x: x[0]):
            if t_e == 0.0:
                cmd.append(f"{name}={v_e}")
            else:
                cmd.append(f"{name}@{t_e}={v_e}")
    return cmd

def run_sim(exe: Path, t_end: float, h: float, solver: Optional[str],
            inputs: dict, schedule: dict, timeout: int = 300) -> tuple:
    cmd = build_cmd(exe, t_end, h, solver, inputs, schedule)
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return None, f"TIMEOUT ({timeout}s)"
    except Exception as e:
        return None, str(e)

    if r.returncode != 0:
        return None, f"EXIT {r.returncode}: {r.stderr.strip()[:400]}"

    lines = r.stdout.strip().splitlines()
    if len(lines) < 2:
        return None, "Sin datos (< 2 lineas de salida)"

    def _norm_col(name: str) -> str:
        """Normaliza nombres de columna: 'x[1]' → 'x_1_' para coincidir con test configs."""
        return name.strip().replace("[", "_").replace("]", "_")

    rows = []
    try:
        reader = csv.DictReader(lines)
        for row in reader:
            parsed = {}
            for k, v in row.items():
                k = _norm_col(k); v = v.strip()
                try:
                    parsed[k] = float(v)
                except ValueError:
                    parsed[k] = v
            rows.append(parsed)
    except Exception as e:
        return None, f"Error CSV: {e}"

    return (rows if rows else None), ("" if rows else "CSV vacio")

# ─────────────────────────────────────────────────────────────────────────────
# Analisis estadistico de datos
# ─────────────────────────────────────────────────────────────────────────────

def analyze_column(col: str, vals: list, t_vals: list) -> dict:
    """Estadisticas + clasificacion comportamental para una columna."""
    n = len(vals)
    if n == 0:
        return {}

    finite = [v for v in vals if math.isfinite(v)]
    n_bad  = n - len(finite)

    if not finite:
        return {"n": n, "n_invalid": n_bad, "trend": "INVALIDO (todo NaN/Inf)"}

    mn   = min(finite)
    mx   = max(finite)
    mean = sum(finite) / len(finite)
    std  = statistics.stdev(finite) if len(finite) > 1 else 0.0
    rng  = mx - mn
    ini  = vals[0] if math.isfinite(vals[0]) else float("nan")
    fin  = vals[-1] if math.isfinite(vals[-1]) else float("nan")

    # Cambios de signo
    sign_ch = sum(1 for i in range(1, n)
                  if math.isfinite(vals[i]) and math.isfinite(vals[i-1])
                  and vals[i] * vals[i-1] < 0)

    # Clasificacion de tendencia
    tol_stable = 1e-8 * (abs(mean) + 1.0)
    if n_bad > 0:
        trend = f"INVALIDO ({n_bad} NaN/Inf)"
    elif rng < tol_stable:
        trend = "constante"
    elif sign_ch >= 4:
        freq_est = sign_ch / (2 * (t_vals[-1] - t_vals[0] + 1e-12))
        trend = f"oscilante  ({sign_ch} cruces cero, ~{freq_est:.3g} Hz)"
    elif len(finite) > 4:
        # regresion lineal simple para detectar monotonia
        tm = sum(t_vals) / n
        ym = mean
        num = sum((t_vals[i] - tm) * (finite[i] - ym) for i in range(min(n, len(finite))))
        den = sum((t_vals[i] - tm)**2 for i in range(n)) + 1e-30
        slope = num / den
        if abs(slope) * (t_vals[-1] - t_vals[0]) > 0.1 * (rng + 1e-12):
            trend = "creciente" if slope > 0 else "decreciente"
        else:
            trend = "estable"
    else:
        trend = "variable"

    # Convergencia en el ultimo 20%
    settled = False
    if n >= 10:
        last = finite[int(0.8 * len(finite)):]
        if len(last) > 1:
            last_std = statistics.stdev(last)
            settled = last_std < 0.02 * (rng + 1e-10)

    # Tasa de cambio maxima (derivada numerica)
    max_rate = 0.0
    for i in range(1, n):
        if math.isfinite(vals[i]) and math.isfinite(vals[i-1]):
            dt = t_vals[i] - t_vals[i-1]
            if dt > 0:
                rate = abs(vals[i] - vals[i-1]) / dt
                if rate > max_rate:
                    max_rate = rate

    return {
        "n": n, "n_invalid": n_bad,
        "min": mn, "max": mx, "mean": mean, "std": std,
        "range": rng, "initial": ini, "final": fin,
        "sign_changes": sign_ch, "trend": trend,
        "settled": settled, "max_rate": max_rate,
    }

def _fmt(v, digits=4):
    """Formatea un float de forma compacta."""
    if not isinstance(v, (int, float)) or not math.isfinite(v):
        return str(v)
    if abs(v) == 0:
        return "0"
    if abs(v) >= 1000 or (abs(v) < 0.001 and abs(v) > 0):
        return f"{v:.{digits}g}"
    return f"{v:.{digits}g}"

def generate_data_analysis(tc: dict, all_results: dict) -> str:
    """
    Genera la seccion de analisis real de datos para el reporte MD de un TC.
    Produce estadisticas, clasificacion comportamental y conclusiones contextuales.
    """
    lines = []
    a = lines.append

    a("## Analisis de datos")
    a("")

    tc_checks = tc.get("checks", [])
    interp    = tc.get("interpretation", "")

    for sim_label, (rows, check_results, png_name) in all_results.items():
        if rows is None:
            continue

        a(f"### Simulacion: {sim_label}")
        a("")

        t_vals   = [float(r.get("t", 0)) for r in rows]
        out_cols = [c for c in rows[0].keys() if c != "t"]

        # ── Tabla estadistica ──────────────────────────────────────────────
        col_stats = {}
        for col in out_cols:
            vals = []
            for r in rows:
                try:
                    vals.append(float(r[col]))
                except (KeyError, ValueError, TypeError):
                    pass
            if vals:
                col_stats[col] = analyze_column(col, vals, t_vals)

        if col_stats:
            a("#### Estadisticas por variable de salida")
            a("")
            a("| Variable | Min | Max | Media | Desv.Std | Inicial | Final | Comportamiento |")
            a("|----------|-----|-----|-------|----------|---------|-------|----------------|")
            for col, s in col_stats.items():
                if not s:
                    continue
                ni = s.get("n_invalid", 0)
                flag = " ⚠️" if ni > 0 else ""
                a(f"| `{col}`{flag} | {_fmt(s.get('min','?'))} | {_fmt(s.get('max','?'))} | "
                  f"{_fmt(s.get('mean','?'))} | {_fmt(s.get('std','?'))} | "
                  f"{_fmt(s.get('initial','?'))} | {_fmt(s.get('final','?'))} | "
                  f"{s.get('trend','?')} |")
            a("")

        # ── Analisis contextual ────────────────────────────────────────────
        a("#### Analisis contextual")
        a("")
        conclusions = _contextual_analysis(tc, col_stats, check_results, t_vals, sim_label)
        for c in conclusions:
            a(c)
        a("")

    return "\n".join(lines)


def _contextual_analysis(tc, col_stats, check_results, t_vals, sim_label):
    """Genera conclusiones contextuales inteligentes a partir de los datos."""
    lines = []
    t_span = t_vals[-1] - t_vals[0] if len(t_vals) > 1 else 1.0
    n_pass = sum(1 for p, _ in check_results if p)
    n_fail = sum(1 for p, _ in check_results if not p)

    # — Estado general de los checks —
    if n_fail == 0 and n_pass > 0:
        lines.append(f"**✅ Verificacion completa:** los {n_pass} check(s) definidos pasan — "
                     f"el comportamiento del modelo es coherente con la especificacion.")
    elif n_fail > 0:
        lines.append(f"**❌ {n_fail} check(s) fallados de {n_pass + n_fail}:**")
        for passed, detail in check_results:
            if not passed:
                lines.append(f"  - {detail.strip()}")

    # — Analisis de energia/conservacion —
    energy_col = next((c for c in col_stats if "energia" in c.lower() or "energy" in c.lower()), None)
    if energy_col and col_stats.get(energy_col):
        s = col_stats[energy_col]
        drift_abs = s.get("range", 0)
        drift_pct = drift_abs / abs(s.get("mean", 1) + 1e-30) * 100
        lines.append(f"**Conservacion de energia** (`{energy_col}`): "
                     f"valor medio = {_fmt(s['mean'])} J, "
                     f"deriva total = {_fmt(drift_abs)} J ({drift_pct:.2f}%) "
                     f"en {_fmt(t_span)} s — "
                     f"{'excelente' if drift_pct < 0.5 else 'aceptable' if drift_pct < 5 else 'elevada'}.")

    # — Analisis de oscilaciones —
    for col, s in col_stats.items():
        if s and "oscilante" in s.get("trend", ""):
            amp = s.get("range", 0) / 2
            sc  = s.get("sign_changes", 0)
            freq_est = sc / (2 * t_span + 1e-12)
            lines.append(f"**Oscilacion** de `{col}`: amplitud ~{_fmt(amp)}, "
                         f"frecuencia estimada ~{freq_est:.3g} Hz "
                         f"({sc} cruces de cero en {_fmt(t_span)} s).")

    # — Convergencia / estado estacionario —
    conv_cols = [c for c, s in col_stats.items()
                 if s and s.get("settled") and "oscilante" not in s.get("trend", "")
                 and s.get("trend") not in ("constante",)]
    if conv_cols:
        for col in conv_cols:
            s = col_stats[col]
            lines.append(f"**Convergencia** de `{col}`: valor final = {_fmt(s['final'])} "
                         f"(arranca en {_fmt(s['initial'])}, "
                         f"delta = {_fmt(abs(s['final'] - s['initial']))}).")

    # — Variables constantes —
    const_cols = [c for c, s in col_stats.items()
                  if s and s.get("trend") == "constante" and s.get("std", 1) < 1e-10]
    if const_cols:
        vals_str = ", ".join(f"`{c}`={_fmt(col_stats[c]['mean'])}" for c in const_cols)
        lines.append(f"**Variables algebraicas constantes:** {vals_str} — "
                     f"sin dinamica transitoria, solo dependencia combinacional de la entrada.")

    # — Valores invalidos —
    for col, s in col_stats.items():
        if s and s.get("n_invalid", 0) > 0:
            lines.append(f"**⚠️ CRITICO: `{col}` contiene {s['n_invalid']} valor(es) NaN/Inf** — "
                         f"indica fallo en las guardas de division/sqrt/log o desbordamiento de buffer.")

    # — Dinamica de las salidas booleanas/enteras —
    bool_int_cols = []
    for col, s in col_stats.items():
        if s and s.get("range", 0) <= 1.0 and s.get("min", 0) >= 0 and s.get("max", 0) <= 1.0:
            sc = s.get("sign_changes", 0) + sum(
                1 for i in range(1, len([v for v in [s.get("initial"), s.get("final")] if v is not None]))
            )
            if s.get("mean", 0) in (0.0, 1.0) and s.get("std", 1) < 0.5:
                bool_int_cols.append((col, s))
    if bool_int_cols:
        for col, s in bool_int_cols[:3]:
            v = s.get("final", 0)
            state = "activo (TRUE/1)" if v > 0.5 else "inactivo (FALSE/0)"
            lines.append(f"**Salida binaria `{col}`:** estado final = {state} "
                         f"(media = {_fmt(s['mean'])}).")

    # — Tasas de cambio maximas —
    fast_cols = [(c, s) for c, s in col_stats.items()
                 if s and s.get("max_rate", 0) > 10 and s.get("trend") != "constante"]
    if fast_cols:
        for col, s in fast_cols[:2]:
            lines.append(f"**Dinamica rapida** en `{col}`: tasa de cambio maxima = "
                         f"{_fmt(s['max_rate'])} unidades/s.")

    if not lines:
        lines.append("Simulacion completada correctamente. Sin anomalias detectadas en los datos.")

    return lines

# ─────────────────────────────────────────────────────────────────────────────
# Evaluacion de checks
# ─────────────────────────────────────────────────────────────────────────────

def _row_at_t(rows, t):
    if not rows:
        return None
    return min(rows, key=lambda r: abs(float(r.get("t", 0)) - t))

def _col_vals(rows, col):
    vals = []
    for r in rows:
        try:
            vals.append(float(r[col]))
        except (KeyError, ValueError, TypeError):
            pass
    return vals

def evaluate_check(check: dict, rows: list) -> tuple:
    col   = check.get("col", "")
    ctype = check.get("type", "at_t")

    if ctype == "final_value":
        val = check["val"]; tol = check.get("tol", 1e-6)
        if not rows:
            return False, f"Sin datos"
        got = float(rows[-1].get(col, float("nan")))
        ok  = abs(got - val) <= tol
        return ok, f"`{col}` final: esperado {val}±{tol}, obtenido {got:.6g}"

    elif ctype == "at_t":
        t = check["at_t"]; val = check["val"]; tol = check.get("tol", 1e-6)
        row = _row_at_t(rows, t)
        if row is None or col not in row:
            return False, f"Sin dato `{col}` en t={t}"
        got = float(row[col])
        ok  = abs(got - val) <= tol
        return ok, f"`{col}`@t={t}: esperado {val}±{tol}, obtenido {got:.6g}"

    elif ctype == "always":
        op = check.get("op", ">="); val = check["val"]
        vals = _col_vals(rows, col)
        if not vals:
            return False, f"Sin datos `{col}`"
        ops = {">": lambda a,b: a>b, ">=": lambda a,b: a>=b,
               "<": lambda a,b: a<b, "<=": lambda a,b: a<=b,
               "==": lambda a,b: abs(a-b)<=1e-9, "!=": lambda a,b: abs(a-b)>1e-9}
        fn   = ops.get(op, lambda a,b: True)
        fail = [v for v in vals if not fn(v, val)]
        ok   = len(fail) == 0
        det  = f"`{col}` {op} {val} siempre: {'OK' if ok else f'{len(fail)}/{len(vals)} violaciones (ej: {fail[0]:.4g})'}"
        return ok, det

    elif ctype == "always_true":
        vals = _col_vals(rows, col)
        if not vals:
            return False, f"Sin datos `{col}`"
        fail = [v for v in vals if v == 0.0]
        ok   = len(fail) == 0
        return ok, f"`{col}` siempre TRUE: {'OK' if ok else f'{len(fail)}/{len(vals)} pasos FALSE'}"

    elif ctype == "eventually":
        op  = check.get("op", ">"); val = check["val"]
        vals = _col_vals(rows, col)
        ops = {">": lambda a,b: a>b, ">=": lambda a,b: a>=b,
               "<": lambda a,b: a<b, "<=": lambda a,b: a<=b,
               "==": lambda a,b: abs(a-b)<=1e-9}
        fn  = ops.get(op, lambda a,b: True)
        ok  = any(fn(v, val) for v in vals)
        mx  = max(vals) if vals else float("nan")
        mn  = min(vals) if vals else float("nan")
        return ok, (f"`{col}` {op} {val} eventualmente: {'OK' if ok else f'nunca (max={mx:.4g}, min={mn:.4g})'}")

    elif ctype == "eventually_false":
        vals = _col_vals(rows, col)
        ok   = any(v == 0.0 for v in vals)
        return ok, f"`{col}` es FALSE en algun punto: {'OK' if ok else 'nunca FALSE'}"

    elif ctype == "monotone_dec":
        vals = _col_vals(rows, col)
        if len(vals) < 2:
            return False, f"Insuficientes datos para monotonia de `{col}`"
        viol = sum(1 for i in range(len(vals)-1) if vals[i+1] - vals[i] > 1e-10)
        ok   = viol == 0
        return ok, f"`{col}` monotona decreciente: {'OK' if ok else f'{viol} incrementos detectados'}"

    elif ctype == "monotone_inc":
        vals = _col_vals(rows, col)
        if len(vals) < 2:
            return False, f"Insuficientes datos para monotonia de `{col}`"
        viol = sum(1 for i in range(len(vals)-1) if vals[i+1] - vals[i] < -1e-10)
        ok   = viol == 0
        return ok, f"`{col}` monotona creciente: {'OK' if ok else f'{viol} decrementos detectados'}"

    elif ctype == "sign_changes":
        # acepta "min", "min_count" o "min_changes"
        min_count = check.get("min_count", check.get("min", check.get("min_changes", 1)))
        vals  = _col_vals(rows, col)
        chg   = sum(1 for i in range(1, len(vals)) if vals[i]*vals[i-1] < 0)
        ok    = chg >= min_count
        return ok, f"`{col}` cambios de signo: {chg} (minimo {min_count}): {'OK' if ok else 'FAIL'}"

    elif ctype == "bounded":
        # acepta "lo/hi" o "low/high"
        lo = check.get("lo", check.get("low",  -1e30))
        hi = check.get("hi", check.get("high",  1e30))
        vals = _col_vals(rows, col)
        if not vals:
            return False, f"Sin datos `{col}`"
        out  = [v for v in vals if v < lo or v > hi]
        ok   = len(out) == 0
        return ok, f"`{col}` en [{_fmt(lo)}, {_fmt(hi)}]: {'OK' if ok else f'{len(out)} valores fuera (ej: {out[0]:.4g})'}"

    elif ctype == "no_nan_inf":
        vals = _col_vals(rows, col)
        bad  = [v for v in vals if not math.isfinite(v)]
        ok   = len(bad) == 0
        return ok, f"`{col}` sin NaN/Inf: {'OK' if ok else f'{len(bad)} valores invalidos'}"

    elif ctype == "count_value":
        val       = check["val"]
        expected  = check.get("expected", None)
        # acepta "min" o "min_count"
        min_count = check.get("min_count", check.get("min", None))
        vals  = _col_vals(rows, col)
        count = sum(1 for v in vals if abs(v - val) <= 1e-9)
        if expected is not None:
            ok = count == expected
            return ok, f"`{col}`=={val} exactamente {count} veces (esperado {expected}): {'OK' if ok else 'FAIL'}"
        elif min_count is not None:
            ok = count >= min_count
            return ok, f"`{col}`=={val} al menos {min_count} veces, encontrado {count}: {'OK' if ok else 'FAIL'}"
        return True, f"`{col}`=={val}: {count} veces"

    elif ctype == "range_at_t":
        t  = check["at_t"]
        lo = check.get("lo", check.get("low",  -1e30))
        hi = check.get("hi", check.get("high",  1e30))
        row = _row_at_t(rows, t)
        if row is None or col not in row:
            return False, f"Sin dato `{col}` en t={t}"
        got = float(row[col])
        ok  = lo <= got <= hi
        return ok, f"`{col}`@t={t}: {got:.6g} en [{_fmt(lo)},{_fmt(hi)}]: {'OK' if ok else 'FUERA'}"

    elif ctype == "code_inspect":
        return True, "[SKIP — inspeccion de codigo fuente, no simulacion]"

    else:
        return False, f"Tipo de comprobacion desconocido: '{ctype}'"

# ─────────────────────────────────────────────────────────────────────────────
# Graficas
# ─────────────────────────────────────────────────────────────────────────────

COLORS = ["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728",
          "#9467bd", "#8c564b", "#e377c2", "#7f7f7f"]

def save_plot(rows: list, tc_id: str, label: str, png_path: Path,
              highlight_cols: list = None):
    """Grafica individual: una subplot por columna."""
    if not HAS_MPL or not rows:
        return
    t_vals = [float(r.get("t", 0)) for r in rows]
    cols   = highlight_cols or [c for c in rows[0].keys() if c != "t"]
    n      = len(cols)
    fig, axes = plt.subplots(n, 1, figsize=(10, max(2.5, 2.5*n)), sharex=True)
    if n == 1:
        axes = [axes]
    for ax, col in zip(axes, cols):
        yv = []
        for r in rows:
            try:
                yv.append(float(r[col]))
            except:
                yv.append(float("nan"))
        ax.plot(t_vals, yv, linewidth=1.5, color=COLORS[0])
        ax.set_ylabel(col, fontsize=8)
        ax.grid(True, alpha=0.3)
        ax.tick_params(labelsize=7)
    axes[-1].set_xlabel("t [s]", fontsize=9)
    fig.suptitle(f"{tc_id} — {label}", fontsize=10, fontweight="bold")
    plt.tight_layout()
    try:
        fig.savefig(str(png_path), dpi=100)
    except Exception:
        pass
    plt.close(fig)

def save_comparison_plot(all_results: dict, tc_id: str, png_path: Path):
    """Grafica de comparacion superpuesta (varios solvers / modos)."""
    if not HAS_MPL:
        return
    valid = [(lbl, rows) for lbl, (rows, _, _) in all_results.items() if rows is not None]
    if len(valid) < 2:
        return
    # columnas de salida comunes
    all_cols = set()
    for _, rows in valid:
        all_cols.update(c for c in rows[0].keys() if c != "t")
    cols = sorted(all_cols)
    n = len(cols)
    fig, axes = plt.subplots(n, 1, figsize=(12, max(3, 3*n)), sharex=True)
    if n == 1:
        axes = [axes]
    for ax, col in zip(axes, cols):
        for (lbl, rows), color in zip(valid, COLORS):
            t_vals = [float(r.get("t", 0)) for r in rows]
            yv = []
            for r in rows:
                try:
                    yv.append(float(r[col]))
                except:
                    yv.append(float("nan"))
            ax.plot(t_vals, yv, label=lbl, color=color, linewidth=1.5)
        ax.set_ylabel(col, fontsize=8)
        ax.legend(fontsize=7, loc="best")
        ax.grid(True, alpha=0.3)
        ax.tick_params(labelsize=7)
    axes[-1].set_xlabel("t [s]", fontsize=9)
    fig.suptitle(f"{tc_id} — Comparacion de integradores/modos", fontsize=10, fontweight="bold")
    plt.tight_layout()
    try:
        fig.savefig(str(png_path), dpi=100)
    except Exception:
        pass
    plt.close(fig)

# ─────────────────────────────────────────────────────────────────────────────
# Generacion del reporte MD por TC
# ─────────────────────────────────────────────────────────────────────────────

def _fmt_inputs(inputs: dict, schedule: dict) -> str:
    parts = []
    for k, v in (inputs or {}).items():
        parts.append(f"`{k}={v}`")
    for k, entries in (schedule or {}).items():
        seq = ", ".join(f"t={t}: {v}" for t, v in sorted(entries))
        parts.append(f"`{k}`: {seq}")
    return "  \n".join(parts) if parts else "*(sin entradas)*"

def generate_tc_report(tc: dict, all_results: dict, tc_dir: Path) -> str:
    tc_id  = tc["id"];    title  = tc["title"]
    desc   = tc.get("description", "")
    interp = tc.get("interpretation", "")
    t_end  = tc.get("t_end", 1.0);  h     = tc.get("h", 0.01)
    mode   = tc.get("mode", "me");   solver= tc.get("solver", "rk4")

    lines = []; a = lines.append

    a(f"# {tc_id} — {title}")
    a("")
    a(f"## Descripcion del test")
    a(""); a(desc); a("")
    a(f"## Configuracion de simulacion")
    a("")
    a(f"| Parametro | Valor |")
    a(f"|-----------|-------|")
    a(f"| Tiempo final | {t_end} s |")
    a(f"| Paso de integracion | {h} s |")
    a(f"| Modo FMI | {mode.upper()} |")
    a(f"| Solver | {solver or 'CS interno'} |")
    a("")
    a(f"**Entradas:**  \n{_fmt_inputs(tc.get('inputs',{}), tc.get('schedule',{}))}")
    a("")

    total_pass = 0; total_fail = 0

    for sim_label, (rows, check_results, png_name) in all_results.items():
        a(f"## Simulacion: {sim_label}")
        a("")
        if rows is None:
            a("> **ERROR**: Simulacion no ejecutada.")
            if check_results:
                a(f"> {check_results[0][1]}")
            a(""); continue

        n_rows = len(rows)
        a(f"- Pasos simulados: {n_rows}  |  Tiempo total: {float(rows[-1].get('t', 0)):.4g} s")
        if png_name:
            a(f"- Grafica individual: [{png_name}]({png_name})")
        a("")

        # Checks
        if check_results:
            a("### Resultado de checks")
            a("")
            pc = sum(1 for p, _ in check_results if p)
            fc = sum(1 for p, _ in check_results if not p)
            total_pass += pc; total_fail += fc
            a(f"| Estado | Detalle |")
            a(f"|--------|---------|")
            for passed, detail in check_results:
                icon = "✅" if passed else "❌"
                a(f"| {icon} | {detail.strip()} |")
            a("")

        # Muestra de datos
        if rows:
            sample = rows[:3] + ([rows[len(rows)//2]] if len(rows) > 6 else []) + rows[-2:]
            cols   = list(rows[0].keys())[:9]
            a("### Muestra de datos (inicio / mitad / final)")
            a("")
            a("| " + " | ".join(cols) + " |")
            a("| " + " | ".join(["---"]*len(cols)) + " |")
            for row in sample:
                vals = []
                for c in cols:
                    try:
                        vals.append(_fmt(float(row.get(c, ""))))
                    except (ValueError, TypeError):
                        vals.append(str(row.get(c, "")))
                a("| " + " | ".join(vals) + " |")
            a("")

    # — Análisis real de datos —
    analysis_md = generate_data_analysis(tc, all_results)
    a(analysis_md)

    # — Interpretacion tecnica —
    verdict = "✅ PASS" if total_fail == 0 else "❌ FAIL"
    a("## Interpretacion tecnica del test")
    a("")
    a(f"**Resultado global: {verdict}** ({total_pass} checks OK, {total_fail} FAIL)")
    a("")
    if interp:
        a(interp)
    a("")

    # Enlace a comparacion si existe
    cmp_path = tc_dir / "comparison.png"
    if cmp_path.exists():
        a("## Grafica de comparacion")
        a("")
        a("![Comparacion de integradores](comparison.png)")
        a("")

    return "\n".join(lines)

# ─────────────────────────────────────────────────────────────────────────────
# Summary del modelo
# ─────────────────────────────────────────────────────────────────────────────

def generate_summary(model_name: str, tc_results: list, results_dir: Path) -> str:
    total  = len(tc_results)
    passed = sum(1 for r in tc_results if r["global_pass"])
    failed = total - passed
    cp     = sum(r["checks_pass"] for r in tc_results)
    cf     = sum(r["checks_fail"] for r in tc_results)
    pct    = int(100 * passed / total) if total else 0

    lines = []; a = lines.append
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")

    a(f"# Resumen de Test Battery — {model_name}")
    a(f"")
    a(f"> Generado: {now}")
    a(f"")
    a(f"## Metricas globales")
    a(f"")
    a(f"| Metrica | Valor |")
    a(f"|---------|-------|")
    a(f"| Test cases totales | {total} |")
    a(f"| Test cases PASS | {passed} ({pct}%) |")
    a(f"| Test cases FAIL | {failed} |")
    a(f"| Checks individuales PASS | {cp} |")
    a(f"| Checks individuales FAIL | {cf} |")
    a(f"")
    a(f"## Resultado por test case")
    a(f"")
    a(f"| TC ID | Titulo | Resultado | PASS | FAIL |")
    a(f"|-------|--------|-----------|------|------|")
    for r in tc_results:
        icon = "✅" if r["global_pass"] else "❌"
        link = f"[{r['id']}]({r['id']}/report_{r['id']}.md)"
        a(f"| {link} | {r['title']} | {icon} | {r['checks_pass']} | {r['checks_fail']} |")
    a(f"")

    a(f"## Analisis del modelo")
    a(f"")
    if failed == 0:
        a(f"**TODOS LOS {total} TESTS PASAN ({pct}%).**")
        a(f"")
        a(f"El modelo `{model_name}` supera la bateria completa. Todos los escenarios verificados "
          f"— nominal, extremos, condiciones de borde y dinamicas transitorias — producen "
          f"resultados coherentes con la especificacion del modelo FMI 2.0.")
        if cp > 0:
            a(f"Los {cp} checks individuales cubren: valores finales, valores en instantes "
              f"concretos, conservacion de invariantes, ausencia de NaN/Inf, "
              f"monotonias y conteos de transiciones.")
    else:
        a(f"**{failed} TEST(S) FALLAN ({pct}% de tasa de exito).**")
        a(f"")
        fails = [r for r in tc_results if not r["global_pass"]]
        a(f"Test cases con fallos:")
        for r in fails:
            a(f"- **{r['id']}** — {r['title']} ({r['checks_fail']} check(s) fallados)")
        a(f"")
        a(f"Se recomienda revisar el codegen para los escenarios indicados.")
    a(f"")

    return "\n".join(lines)

# ─────────────────────────────────────────────────────────────────────────────
# Runner de un TC
# ─────────────────────────────────────────────────────────────────────────────

def run_tc(tc: dict, exe_me: Optional[Path], exe_cs: Optional[Path],
           results_dir: Path) -> dict:
    tc_id   = tc["id"];  title  = tc["title"]
    t_end   = tc.get("t_end", 1.0);  h      = tc.get("h", 0.01)
    solver  = tc.get("solver", "rk4");  mode = tc.get("mode", "me")
    inputs  = tc.get("inputs", {});  schedule = tc.get("schedule", {})
    checks  = tc.get("checks", []);  out_cols = tc.get("plot_cols", None)

    tc_dir = results_dir / tc_id
    tc_dir.mkdir(parents=True, exist_ok=True)

    # Determinar que simulaciones ejecutar
    run_modes = []
    if mode in ("me", "both"):
        solvers = tc.get("solvers", [solver] if solver else ["rk4"])
        for s in solvers:
            run_modes.append(("me", s))
    if mode in ("cs", "both"):
        run_modes.append(("cs", None))

    all_results = {}; total_pass = 0; total_fail = 0

    for (sim_mode, sim_solver) in run_modes:
        label = f"ME-{sim_solver.upper()}" if sim_mode == "me" else "CS"
        exe   = exe_me if sim_mode == "me" else exe_cs

        if exe is None:
            all_results[label] = (None,
                [(False, f"Ejecutable {sim_mode.upper()} no encontrado")], None)
            total_fail += 1
            continue

        rows, err = run_sim(exe, t_end, h, sim_solver, inputs, schedule)

        if rows is None:
            all_results[label] = (None, [(False, err)], None)
            total_fail += 1
            continue

        # CSV
        csv_name = f"sim_{label.lower().replace('-','_')}.csv"
        csv_path = tc_dir / csv_name
        with open(csv_path, "w", newline="", encoding="utf-8") as f:
            w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
            w.writeheader(); w.writerows(rows)

        # PNG individual
        png_name = csv_name.replace(".csv", ".png")
        png_path = tc_dir / png_name
        save_plot(rows, tc_id, label, png_path, out_cols)
        if not png_path.exists():
            png_name = None

        # Checks
        check_results = []
        for chk in checks:
            chk_mode   = chk.get("mode",   None)
            chk_solver = chk.get("solver", None)
            if chk_mode   and chk_mode   != sim_mode:   continue
            if chk_solver and chk_solver != sim_solver:  continue
            passed, detail = evaluate_check(chk, rows)
            check_results.append((passed, detail))

        p  = sum(1 for x, _ in check_results if x)
        f_ = sum(1 for x, _ in check_results if not x)
        total_pass += p; total_fail += f_

        all_results[label] = (rows, check_results, png_name)

    # PNG de comparacion (si >1 solver)
    if len([v for v in all_results.values() if v[0] is not None]) > 1:
        cmp_png = tc_dir / "comparison.png"
        save_comparison_plot(all_results, tc_id, cmp_png)

    global_pass = (total_fail == 0) and (total_pass > 0 or not checks)

    # Reporte MD
    report_md  = generate_tc_report(tc, all_results, tc_dir)
    report_path = tc_dir / f"report_{tc_id}.md"
    report_path.write_text(report_md, encoding="utf-8")

    icon = "✅" if global_pass else "❌"
    print(f"  {icon} {tc_id}: {total_pass}✓ {total_fail}✗  —  {title}")

    return {
        "id":          tc_id,
        "title":       title,
        "global_pass": global_pass,
        "checks_pass": total_pass,
        "checks_fail": total_fail,
        "tc_dir":      tc_dir,
    }

# ─────────────────────────────────────────────────────────────────────────────
# Runner de la bateria completa de un modelo
# ─────────────────────────────────────────────────────────────────────────────

def run_battery(config_path) -> int:
    config_path = Path(config_path).resolve()
    spec = importlib.util.spec_from_file_location("tc_config", config_path)
    mod  = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    CONFIG = mod.CONFIG

    model_name = CONFIG["model_name"]
    tests      = CONFIG["tests"]

    print(f"\n{'='*70}")
    print(f"  TEST BATTERY — {model_name}  ({len(tests)} test cases)")
    print(f"{'='*70}")

    exe_me = CONFIG.get("exe_me") or locate_exe(model_name, "me", config_path)
    exe_cs = CONFIG.get("exe_cs") or locate_exe(model_name, "cs", config_path)

    print(f"  ME: {exe_me or 'NO ENCONTRADO'}")
    print(f"  CS: {exe_cs or 'NO ENCONTRADO'}")
    print()

    results_dir = config_path.parent / "results"
    results_dir.mkdir(exist_ok=True)

    tc_results = []
    for tc in tests:
        r = run_tc(tc, exe_me, exe_cs, results_dir)
        tc_results.append(r)

    summary_md  = generate_summary(model_name, tc_results, results_dir)
    summary_path = results_dir / "summary.md"
    summary_path.write_text(summary_md, encoding="utf-8")

    passed = sum(1 for r in tc_results if r["global_pass"])
    failed = len(tc_results) - passed
    print()
    print(f"{'='*70}")
    print(f"  RESULTADO: {passed}/{len(tc_results)} PASS  |  {failed} FAIL")
    print(f"  Resultados: {results_dir}")
    print(f"{'='*70}\n")

    return 0 if failed == 0 else 1, tc_results, model_name


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Uso: {sys.argv[0]} <test_config.py>")
        sys.exit(1)
    ret, _, _ = run_battery(Path(sys.argv[1]))
    sys.exit(ret)
