#!/usr/bin/env python3
"""
fmu_codegen_mcu.py — Generador de adapter MCU para FMUs FMI 2.0

Genera los archivos necesarios para ejecutar un modelo FMU en un
microcontrolador (MCU) SIN necesitar el runtime de OpenModelica.

Las ecuaciones ODE se extraen directamente del source de la FMU
(comentarios tipo SIMPLE_ASSIGN generados por OpenModelica) y se
reimplementan en C puro, compatible con cualquier MCU (ESP32, STM32, etc.).

Uso:
    python fmu_codegen_mcu.py <fmu_o_dir> <output_dir>

    <fmu_o_dir>   Ruta al directorio FMU (con modelDescription.xml) o a un .fmu.
    <output_dir>  Directorio donde se generan los archivos MCU.
                  Convencion recomendada: examples/<modelo>/mcu/

Genera (4 archivos):
    <modelo>_mcu.h   Struct concreto, constantes VR_*, declaracion de mcu_create()
    <modelo>_mcu.c   Implementacion directa de fmu_t con las ecuaciones ODE
    CMakeLists.txt   Build del ejecutable MCU (sobreescrito siempre)
    main.c           Loop de simulacion limpio para MCU (solo si no existe)

El ejecutable de test en host se llama <modelo>_mcu.
Solo funciona con modelos ME con al menos 1 estado continuo.

Limitaciones:
    - Solo extrae ecuaciones de tipo SIMPLE_ASSIGN (ODE puras, sin IF/WHEN)
    - Solo estados de tipo Real (no Integer ni Boolean)
    - Los modelos CS puros no generan adapter MCU

Requisitos: Python 3.8+  |  Solo stdlib  |  fmu_parser.py en el mismo directorio
"""

import sys
import os
import re

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from fmu_parser import (
    FMUInfo, Variable,
    parse_fmu, extract_fmu,
    generate_sim_loop, register_in_parent_cmake,
)

import xml.etree.ElementTree as ET


# =============================================================================
# Helpers de conversion Modelica → C
# =============================================================================

# Convierte (EXPR)^N → pow(EXPR, N)   — parentesis ya presentes
_POWER_PAREN_RE = re.compile(r'\(([^()]+)\)\s*\^\s*([\d.e+\-]+)')
# Convierte ATOM^N → pow(ATOM, N)     — identificador o numero simple
_POWER_ATOM_RE  = re.compile(r'([a-zA-Z_][\w.]*)\s*\^\s*([\d.e+\-]+)')


def _mcu_safe_field(name: str) -> str:
    """
    Convierte un nombre de variable Modelica a identificador C valido
    para usarlo como campo de struct:
        omega       → omega
        der(omega)  → der_omega
        A[1,1]      → A_1_1
    """
    s = name
    for ch in "()[]., ":
        s = s.replace(ch, "_")
    while "__" in s:
        s = s.replace("__", "_")
    return s.strip("_") or "var"


def _inline_cses(expr: str, cse_map: dict, max_iter: int = 8) -> str:
    """
    Sustituye variables CSE ($cseN) en una expresion hasta que no queden.

    OpenModelica genera subexpresiones comunes como:
        $cse2 = sin(theta)
        $DER.omega = -$cse2 * g / L

    Esta funcion las inlinea:
        -sin(theta) * g / L

    Args:
        expr:     Expresion Modelica a procesar.
        cse_map:  Diccionario {nombre_cse: expresion_modelica}.
        max_iter: Maximo de pasadas (por si hay CSEs anidadas).
    """
    for _ in range(max_iter):
        changed = False
        for cse, val in cse_map.items():
            if cse in expr:
                expr = expr.replace(cse, f"({val})")
                changed = True
        if not changed:
            break
    return expr


def _modelica_to_c(expr: str, subst: list) -> str:
    """
    Convierte una expresion Modelica a C:
      1. Sustituye nombres de variables Modelica por accesos al struct (m->campo)
      2. Convierte el operador ^ a llamadas pow()

    Args:
        expr:  Expresion Modelica (ya con CSEs inlineadas).
        subst: Lista de (nombre_modelica, expresion_c), ordenada de mayor
               a menor longitud para evitar sustituciones parciales.
    """
    result = expr
    # Sustituir nombres usando word boundary para evitar sustituciones parciales
    for model_name, c_expr in subst:
        result = re.sub(r'\b' + re.escape(model_name) + r'\b', c_expr, result)
    # Convertir operador ^ a pow()
    result = _POWER_PAREN_RE.sub(r'pow(\1, \2)', result)
    result = _POWER_ATOM_RE.sub(r'pow(\1, \2)', result)
    return result


# =============================================================================
# Extractor de ecuaciones ODE del source de la FMU
# =============================================================================

def parse_mcu_data(fmu_dir: str, info: FMUInfo) -> dict | None:
    """
    Extrae las ecuaciones ODE del source C generado por OpenModelica.

    OpenModelica añade comentarios estructurados antes de cada asignacion:
        /*
        equation index: 5
        type: SIMPLE_ASSIGN
        $DER.x = sigma * (y - x)
        */

    Esta funcion los parsea para obtener las derivadas dx[i]/dt y las
    expresiones de salida en terminos de los estados y parametros.

    Args:
        fmu_dir: Directorio de la FMU.
        info:    Metadatos del modelo.

    Returns:
        Dict con:
          state_vars   lista de {name, vr, start} en orden del array de estados
          param_vars   lista de Variable con causality='parameter'
          input_vars   lista de Variable con causality='input'
          deriv_exprs  {estado_idx: expresion_C} — dx[i]/dt
          output_exprs {vr: (nombre, expresion_C)} — salidas computadas
          ok           True si todas las derivadas fueron extraidas
          note         Mensaje de diagnostico
        None si el modelo no tiene ME o no tiene estados.
    """
    if not info.has_me or info.n_states == 0:
        return None

    # ── Paso 1: determinar el orden de los estados via ModelStructure ─────────
    # Los estados siguen el orden de <Derivatives><Unknown index="i"/></Derivatives>
    # Cada Unknown[index=i] apunta a una variable derivada; su atributo 'derivative'
    # en el XML apunta al indice de la variable de estado correspondiente.
    xml_path = os.path.join(fmu_dir, "modelDescription.xml")
    tree = ET.parse(xml_path)
    root = tree.getroot()

    all_xml_vars: dict = {}
    for idx, sv in enumerate(root.findall(".//ScalarVariable"), 1):
        real_el  = sv.find("Real")
        deriv_of = 0
        start_v  = None
        if real_el is not None:
            d = real_el.get("derivative")
            deriv_of = int(d) if d else 0
            start_v  = real_el.get("start")
        all_xml_vars[idx] = {
            "name":      sv.get("name", ""),
            "vr":        int(sv.get("valueReference", 0)),
            "causality": sv.get("causality", "local"),
            "deriv_of":  deriv_of,
            "start":     start_v,
        }

    struct_el = root.find("ModelStructure")
    deriv_indices: list = []
    if struct_el is not None:
        for unk in struct_el.findall("Derivatives/Unknown"):
            deriv_indices.append(int(unk.get("index")))

    # Para cada derivada, encontrar la variable de estado correspondiente
    state_vars: list = []
    for d_idx in deriv_indices:
        d_info = all_xml_vars.get(d_idx, {})
        s_idx  = d_info.get("deriv_of", 0)
        s_info = all_xml_vars.get(s_idx)
        if s_info:
            state_vars.append(s_info)

    param_vars  = [v for v in info.variables if v.causality == "parameter"]
    input_vars  = [v for v in info.variables if v.causality == "input"]
    output_vars = [v for v in info.variables if v.causality == "output"]

    if len(state_vars) != info.n_states:
        return {
            "ok": False,
            "note": f"Estado no resuelto: {len(state_vars)}/{info.n_states}",
            "state_vars": state_vars, "param_vars": param_vars,
            "input_vars": input_vars, "deriv_exprs": {}, "output_exprs": {},
        }

    # ── Paso 2: leer y parsear el .c principal de la FMU ─────────────────────
    src_path = os.path.join(fmu_dir, "sources", f"{info.model_identifier}.c")
    if not os.path.exists(src_path):
        return {
            "ok": False,
            "note": f"Fuente no encontrada: {src_path}",
            "state_vars": state_vars, "param_vars": param_vars,
            "input_vars": input_vars, "deriv_exprs": {}, "output_exprs": {},
        }

    with open(src_path, "r", encoding="utf-8", errors="replace") as f:
        src = f.read()

    # Regex para bloques de comentario SIMPLE_ASSIGN:
    #   /*\nequation index: N\ntype: SIMPLE_ASSIGN\n<lhs> = <rhs>\n*/
    eq_re = re.compile(
        r"/\*\r?\nequation index:\s*\d+\r?\ntype:\s*SIMPLE_ASSIGN\r?\n"
        r"([^\r\n]+)\r?\n\s*\*/"
    )

    cse_map:    dict = {}   # "$cseN" → expresion Modelica sin sustituir
    deriv_raw:  dict = {}   # nombre_estado → expresion Modelica de la derivada
    output_raw: dict = {}   # nombre_salida → expresion Modelica de la salida

    for m in eq_re.finditer(src):
        body = m.group(1).strip()
        if "=" not in body:
            continue
        lhs, _, rhs = body.partition("=")
        lhs = lhs.strip()
        rhs = rhs.strip()

        if lhs.startswith("$DER.") or lhs.startswith("$der."):
            # Ecuacion de derivada: $DER.x = sigma*(y-x)
            deriv_raw[lhs.split(".", 1)[1]] = rhs
        elif lhs.startswith("$") or lhs.startswith("_D_"):
            # Variable CSE interna: $cse2 = sin(theta)
            cse_map[lhs] = rhs
        else:
            # Posible variable de salida: x_out = x
            output_raw[lhs] = rhs

    # ── Paso 3: inline CSEs y conversion a C ──────────────────────────────────
    state_names = [v["name"] for v in state_vars]
    param_names = [v.name for v in param_vars]
    input_names = [v.name for v in input_vars]

    # Lista de sustituciones Modelica → C, ordenada de mayor a menor longitud
    # para que "sigma" no sustituya dentro de "sigma_total" (si existiera).
    subst: list = []
    for n in state_names + param_names + input_names:
        subst.append((n, f"m->{_mcu_safe_field(n)}"))
    subst.sort(key=lambda x: len(x[0]), reverse=True)

    # Resolver CSEs anidadas ($cse1 puede depender de $cse2)
    for cse in list(cse_map.keys()):
        others = {k: v for k, v in cse_map.items() if k != cse}
        cse_map[cse] = _inline_cses(cse_map[cse], others)

    # Convertir derivadas a C
    deriv_exprs: dict = {}
    for der_var, raw in deriv_raw.items():
        if der_var in state_names:
            idx = state_names.index(der_var)
            deriv_exprs[idx] = _modelica_to_c(_inline_cses(raw, cse_map), subst)

    # Convertir salidas a C
    out_vr_map = {v.name: v.vr for v in output_vars}
    output_exprs: dict = {}
    for out_name, raw in output_raw.items():
        if out_name in out_vr_map:
            c_expr = _modelica_to_c(_inline_cses(raw, cse_map), subst)
            output_exprs[out_vr_map[out_name]] = (out_name, c_expr)

    ok   = len(deriv_exprs) == info.n_states
    note = "" if ok else f"Solo {len(deriv_exprs)}/{info.n_states} derivadas extraidas"

    return {
        "state_vars":   state_vars,
        "param_vars":   param_vars,
        "input_vars":   input_vars,
        "deriv_exprs":  deriv_exprs,
        "output_exprs": output_exprs,
        "ok":           ok,
        "note":         note,
    }


# =============================================================================
# Generador del header MCU  (<modelo>_mcu.h)
# =============================================================================

def generate_mcu_header(info: FMUInfo, mcu: dict) -> str:
    """
    Genera <modelo>_mcu.h con:
      - Constantes identicas al adapter HOST (VR_*, N_STATES, buffer sizes)
      - Typedef del struct concreto con campos para estados, parametros, entradas
      - Declaracion de <modelo>_mcu_create()

    El header es completamente autonomo: no necesita <modelo>_adapter.h.

    Args:
        info: Metadatos del modelo.
        mcu:  Datos extraidos por parse_mcu_data().
    """
    U = info.upper
    L = info.lower

    state_vars = mcu.get("state_vars", [])
    param_vars = mcu.get("param_vars", [])
    input_vars = mcu.get("input_vars", [])

    lines: list = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_mcu.h")
    a(f" * @brief  Adapter MCU para {info.model_name} — ecuaciones directas, SIN runtime OpenModelica.")
    a(f" *")
    a(f" *  Este header es autonomo: no depende de {L}_adapter.h ni del runtime.")
    a(f" *  Incluye las mismas constantes VR_*, N_STATES y buffer sizes que el")
    a(f" *  adapter HOST, para que main.c sea intercambiable entre ambos.")
    a(f" *")
    a(f" *  Para el adapter HOST (PC con OpenModelica), ver {L}_adapter.h.")
    a(f" *")
    a(f" * @note  AUTO-GENERADO por fmu_codegen_mcu.py. No editar manualmente.")
    a(f" *        Regenerar con: python fmu_codegen_mcu.py <fmu_dir> <output_dir>")
    a(f" */")
    a(f"")
    a(f"#ifndef {U}_MCU_H")
    a(f"#define {U}_MCU_H")
    a(f"")
    a(f'#include <math.h>')
    a(f'#include "fmu_t.h"')
    a(f'#include "fmu_solver.h"   /* FMU_EULER_WORK_SIZE, FMU_RK4_WORK_SIZE */')
    a(f"")

    # ── Metadatos ──────────────────────────────────────────────────────────────
    a(f"/** @defgroup {L}_mcu_meta Metadatos del modelo (MCU)")
    a(f" *  Identicos a los de {L}_adapter.h para que main.c sea compartible.")
    a(f" *  @{{")
    a(f" */")
    a(f'#define {U}_MODEL_NAME         "{info.model_name}"')
    a(f'#define {U}_GUID               "{info.guid}"')
    a(f'#define {U}_N_STATES           {info.n_states}   /*!< Estados continuos del modelo */')
    a(f'#define {U}_N_EVENT_INDICATORS {info.n_event_indicators}')
    a(f'#define {U}_EULER_BUF_SIZE     FMU_EULER_WORK_SIZE({U}_N_STATES)  /*!< Buffer Euler */')
    a(f'#define {U}_RK4_BUF_SIZE       FMU_RK4_WORK_SIZE({U}_N_STATES)    /*!< Buffer RK4 */')
    a(f"/** @}} */")
    a(f"")

    # ── ValueReferences ───────────────────────────────────────────────────────
    groups = [
        ("Entradas",   "input"),
        ("Salidas",    "output"),
        ("Parametros", "parameter"),
        ("Locales",    "local"),
    ]
    a(f"/** @defgroup {L}_mcu_vr ValueReferences")
    a(f" *  @{{")
    a(f" */")
    for label, causality in groups:
        group = [v for v in info.variables if v.causality == causality]
        if not group:
            continue
        a(f"/** @name {label} */")
        a(f"/** @{{ */")
        for v in group:
            define  = f"{U}_VR_{v.define_name}"
            comment = f"{v.type_}, {v.causality}"
            if v.start is not None:
                comment += f", start={v.start}"
            a(f"#define {define:<48} {v.vr}u   /*!< {comment} */")
        a(f"/** @}} */")
        a(f"")
    a(f"/** @}} */")
    a(f"")

    # ── Struct concreto ────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief Struct concreto del adapter MCU para {info.model_name}.")
    a(f" *")
    a(f" * Contiene todos los datos del modelo en una estructura estatica")
    a(f" * (sin heap). El campo 'base' DEBE ser el primero para que el")
    a(f" * cast ({L}_mcu_t *) <-> (fmu_t *) sea valido en C.")
    a(f" *")
    a(f" * Los parametros pueden modificarse antes/despues de initialize()")
    a(f" * mediante set_real() para ajustar el modelo sin recompilar.")
    a(f" */")
    a(f"typedef struct {{")
    a(f"    fmu_t      base;   /**< Interfaz publica fmu_t — DEBE SER EL PRIMER CAMPO */")

    if state_vars:
        a(f"    /* ── Estados continuos (integrados por el solver) ── */")
        for i, sv in enumerate(state_vars):
            start_str = f" start={sv['start']}" if sv.get("start") else ""
            a(f"    fmu_real_t {_mcu_safe_field(sv['name']):<20}; /**< state[{i}]{start_str} */")

    if param_vars:
        a(f"    /* ── Parametros (ajustables via set_real antes de simular) ── */")
        for pv in param_vars:
            if pv.type_ != "Real":
                continue
            start_str = f" default={pv.start}" if pv.start else ""
            a(f"    fmu_real_t {_mcu_safe_field(pv.name):<20}; /**< parametro{start_str} */")

    if input_vars:
        a(f"    /* ── Entradas (actualizar cada paso via set_real) ── */")
        for iv in input_vars:
            if iv.type_ != "Real":
                continue
            a(f"    fmu_real_t {_mcu_safe_field(iv.name):<20}; /**< entrada */")

    a(f"}} {L}_mcu_t;")
    a(f"")

    a(f"/**")
    a(f" * @brief  Devuelve la instancia singleton del adapter MCU para {info.model_name}.")
    a(f" * @return Puntero a fmu_t listo para llamar initialize().")
    a(f" * @note   Instancia estatica — no usa heap. Apta para MCU sin malloc.")
    a(f" * @note   En MCU: conecta get_clock y tick_freq antes de simular si")
    a(f" *         necesitas medir tiempo real con fmu_elapsed_s().")
    a(f" */")
    a(f"fmu_t *{L}_mcu_create(void);")
    a(f"")
    a(f"#endif /* {U}_MCU_H */")

    return "\n".join(lines) + "\n"


# =============================================================================
# Generador del source MCU  (<modelo>_mcu.c)
# =============================================================================

def generate_mcu_source(info: FMUInfo, mcu: dict) -> str:
    """
    Genera <modelo>_mcu.c: implementacion directa de fmu_t con las
    ecuaciones ODE del modelo extraidas del source de la FMU.

    No depende del runtime de OpenModelica — solo necesita math.h y fmu_t.h.
    Listo para compilar en ESP32, STM32, Arduino, o cualquier MCU con compilador C99.

    Args:
        info: Metadatos del modelo.
        mcu:  Datos extraidos por parse_mcu_data().
    """
    U = info.upper
    L = info.lower

    state_vars   = mcu.get("state_vars",   [])
    param_vars   = mcu.get("param_vars",   [])
    input_vars   = mcu.get("input_vars",   [])
    deriv_exprs  = mcu.get("deriv_exprs",  {})
    output_exprs = mcu.get("output_exprs", {})
    ok           = mcu.get("ok",           False)
    note         = mcu.get("note",         "")

    output_vars = [v for v in info.variables if v.causality == "output"]
    n = info.n_states

    real_params = [pv for pv in param_vars if pv.type_ == "Real"]
    real_inputs = [iv for iv in input_vars  if iv.type_ == "Real"]

    lines: list = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_mcu.c")
    a(f" * @brief  Adapter MCU para {info.model_name} — implementacion directa de fmu_t.")
    a(f" *")
    a(f" *  Contiene las ecuaciones ODE del modelo en C puro, sin ninguna")
    a(f" *  dependencia del runtime de OpenModelica. Compatible con C99.")
    a(f" *")
    if not ok and note:
        a(f" * @warning Extraccion parcial de ecuaciones: {note}")
        a(f" *          Completa manualmente los TODO en _get_derivatives().")
        a(f" *")
    a(f" * @note  AUTO-GENERADO por fmu_codegen_mcu.py. No editar manualmente.")
    a(f" *        Regenerar con: python fmu_codegen_mcu.py <fmu_dir> <output_dir>")
    a(f" */")
    a(f"")
    a(f'#include <math.h>      /* sin, cos, pow, sqrt, etc. */')
    a(f'#include "fmu_t.h"     /* fmu_t, fmu_status_t, FMU_OK, FMU_ERROR */')
    a(f'#include "{L}_mcu.h"   /* {L}_mcu_t, constantes VR_* */')
    a(f"")

    # ── _initialize ───────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief Inicializa estados y parametros con los valores por defecto del modelo.")
    a(f" *        Equivale a un reset a condiciones iniciales.")
    a(f" */")
    a(f"static fmu_status_t _initialize(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    if state_vars:
        a(f"    /* Condiciones iniciales de los estados */")
        for sv in state_vars:
            start = sv.get("start") or "0.0"
            a(f"    m->{_mcu_safe_field(sv['name']):<20} = {start};")
    if real_params:
        a(f"    /* Valores por defecto de parametros (del modelDescription.xml) */")
        for pv in real_params:
            a(f"    m->{_mcu_safe_field(pv.name):<20} = {pv.start or '0.0'};")
    if real_inputs:
        a(f"    /* Entradas: inicializar a cero (el usuario las actualiza cada paso) */")
        for iv in real_inputs:
            a(f"    m->{_mcu_safe_field(iv.name):<20} = 0.0;")
    a(f"    self->current_time = 0.0;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    a(f"static fmu_status_t _terminate(fmu_t *self) {{ (void)self; return FMU_OK; }}")
    a(f"")

    a(f"static fmu_status_t _set_time(fmu_t *self, fmu_real_t t)")
    a(f"{{")
    a(f"    self->current_time = t;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _get_derivatives — NUCLEO del adapter MCU ─────────────────────────────
    a(f"/**")
    a(f" * @brief Calcula las derivadas dx/dt del sistema ODE.")
    a(f" *")
    a(f" *  Esta es la funcion clave del adapter MCU: implementa directamente")
    a(f" *  las ecuaciones del modelo sin necesitar el runtime de OpenModelica.")
    a(f" *")
    a(f" *  Ecuaciones extraidas del source de la FMU (tipo SIMPLE_ASSIGN).")
    a(f" *  El solver (Euler o RK4) llama a esta funcion en cada paso.")
    a(f" */")
    a(f"static fmu_status_t _get_derivatives(fmu_t *self, fmu_real_t *dx, int n_dx)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    if (n_dx < {n}) return FMU_ERROR;")

    if ok:
        for i in range(n):
            c_expr = deriv_exprs.get(i, "0.0 /* TODO: ecuacion no extraida */")
            a(f"    dx[{i}] = {c_expr};")
    else:
        a(f"    /* Las ecuaciones no pudieron extraerse automaticamente.")
        a(f"     * {note}")
        a(f"     * Completa manualmente segun el modelo original. */")
        for i in range(n):
            a(f"    dx[{i}] = 0.0; /* TODO */")

    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _get_cont_states / _set_cont_states ───────────────────────────────────
    a(f"/* Lee el vector de estados desde los campos del struct */")
    a(f"static fmu_status_t _get_cont_states(fmu_t *self, fmu_real_t *x, int n_x)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    if (n_x < {n}) return FMU_ERROR;")
    for i, sv in enumerate(state_vars):
        a(f"    x[{i}] = m->{_mcu_safe_field(sv['name'])};")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
    a(f"/* Escribe el vector de estados al struct (tras cada paso del solver) */")
    a(f"static fmu_status_t _set_cont_states(fmu_t *self, const fmu_real_t *x, int n_x)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    if (n_x < {n}) return FMU_ERROR;")
    for i, sv in enumerate(state_vars):
        a(f"    m->{_mcu_safe_field(sv['name'])} = x[{i}];")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── Manejo de eventos (stubs — modelo sin eventos discretos) ─────────────
    a(f"/* Stubs de gestion de eventos (este modelo no tiene eventos discretos).")
    a(f" * Son necesarios para que process_events() en main.c no entre en bucle. */")
    a(f"static fmu_status_t _completed_step(fmu_t *self, fmu_bool_t *enter_event)")
    a(f"{{")
    a(f"    (void)self;")
    a(f"    *enter_event = 0;   /* sin eventos — no necesitamos entrar en EventMode */")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
    a(f"static fmu_status_t _enter_event_mode(fmu_t *self)  {{ (void)self; return FMU_OK; }}")
    a(f"")
    a(f"static fmu_status_t _new_discrete_states(fmu_t *self,")
    a(f"                                         fmu_bool_t *more, fmu_bool_t *terminate)")
    a(f"{{")
    a(f"    (void)self;")
    a(f"    *more      = 0;   /* no se necesitan mas iteraciones */")
    a(f"    *terminate = 0;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
    a(f"static fmu_status_t _enter_cont_mode(fmu_t *self)   {{ (void)self; return FMU_OK; }}")
    a(f"")

    # ── _get_real ─────────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief Lee variables reales por su ValueReference.")
    a(f" *")
    a(f" *  Estados: se leen del struct directamente.")
    a(f" *  Salidas: se calculan inline (expresion derivada de las ecuaciones).")
    a(f" *  Parametros/Entradas: se leen del struct.")
    a(f" */")
    a(f"static fmu_status_t _get_real(fmu_t *self, const fmu_vref_t *vr, int n_vr,")
    a(f"                              fmu_real_t *out)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    for (int i = 0; i < n_vr; i++) {{")
    a(f"        switch (vr[i]) {{")

    for sv in state_vars:
        a(f"            case {sv['vr']}u: out[i] = m->{_mcu_safe_field(sv['name'])}; break; /* {sv['name']} */")
    for ov in output_vars:
        if ov.vr in output_exprs:
            _, c_expr = output_exprs[ov.vr]
            a(f"            case {ov.vr}u: out[i] = {c_expr}; break; /* {ov.name} */")
        else:
            a(f"            case {ov.vr}u: out[i] = 0.0; break; /* {ov.name} — TODO */")
    for pv in real_params:
        a(f"            case {pv.vr}u: out[i] = m->{_mcu_safe_field(pv.name)}; break; /* {pv.name} */")
    for iv in real_inputs:
        a(f"            case {iv.vr}u: out[i] = m->{_mcu_safe_field(iv.name)}; break; /* {iv.name} */")

    a(f"            default: return FMU_ERROR;")
    a(f"        }}")
    a(f"    }}")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _set_real ─────────────────────────────────────────────────────────────
    has_writable = state_vars or real_params or real_inputs
    a(f"/**")
    a(f" * @brief Escribe variables reales por su ValueReference.")
    a(f" *")
    a(f" *  Solo son escritas las variables que tienen sentido modificar:")
    a(f" *  estados (condiciones iniciales), parametros y entradas.")
    a(f" *  Las salidas calculadas son de solo lectura.")
    a(f" */")
    a(f"static fmu_status_t _set_real(fmu_t *self, const fmu_vref_t *vr, int n_vr,")
    a(f"                              const fmu_real_t *in)")
    a(f"{{")
    if has_writable:
        a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    for (int i = 0; i < n_vr; i++) {{")
    a(f"        switch (vr[i]) {{")
    for sv in state_vars:
        a(f"            case {sv['vr']}u: m->{_mcu_safe_field(sv['name'])} = in[i]; break; /* {sv['name']} */")
    for pv in real_params:
        a(f"            case {pv.vr}u: m->{_mcu_safe_field(pv.name)} = in[i]; break; /* {pv.name} */")
    for iv in real_inputs:
        a(f"            case {iv.vr}u: m->{_mcu_safe_field(iv.name)} = in[i]; break; /* {iv.name} */")
    a(f"            default: return FMU_ERROR;")
    a(f"        }}")
    a(f"    }}")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── Instancia estatica y create() ─────────────────────────────────────────
    a(f"/* Instancia estatica — vive en BSS del MCU, sin heap. */")
    a(f"static {L}_mcu_t _instance;")
    a(f"")
    a(f"/**")
    a(f" * @brief Inicializa y devuelve la instancia singleton del adapter MCU.")
    a(f" *")
    a(f" *  Conecta todos los punteros de funcion de fmu_t y devuelve el puntero")
    a(f" *  a la interfaz publica. Llama initialize() antes de simular.")
    a(f" *")
    a(f" * @note  Para MCU con timer hardware: antes de simular, conecta:")
    a(f" *          b->tick_freq = <ticks_por_segundo>;")
    a(f" *          b->get_clock = <funcion_timer>;")
    a(f" *        Esto permite usar fmu_elapsed_s() para medir tiempo real.")
    a(f" */")
    a(f"fmu_t *{L}_mcu_create(void)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = &_instance;")
    a(f"    fmu_t     *b = &m->base;")
    a(f"    b->model_name          = \"{info.model_name}\";")
    a(f"    b->guid                = \"{info.guid}\";")
    a(f"    b->mode                = FMU_MODE_ME;")
    a(f"    b->n_states            = {n};")
    a(f"    b->step_size           = 0.0;")
    a(f"    b->current_time        = 0.0;")
    a(f"    b->initialize          = _initialize;")
    a(f"    b->terminate           = _terminate;")
    a(f"    b->reset               = NULL;")
    a(f"    b->do_step             = NULL;   /* ME: usar fmu_euler_step o fmu_rk4_step */")
    a(f"    b->set_time            = _set_time;")
    a(f"    b->get_derivatives     = _get_derivatives;")
    a(f"    b->get_cont_states     = _get_cont_states;")
    a(f"    b->set_cont_states     = _set_cont_states;")
    a(f"    b->completed_step      = _completed_step;")
    a(f"    b->enter_event_mode    = _enter_event_mode;")
    a(f"    b->new_discrete_states = _new_discrete_states;")
    a(f"    b->enter_cont_mode     = _enter_cont_mode;")
    a(f"    b->get_event_indicators = NULL;")
    a(f"    b->get_real    = _get_real;")
    a(f"    b->set_real    = _set_real;")
    a(f"    b->get_boolean = NULL;   /* sin variables Boolean en este modelo */")
    a(f"    b->set_boolean = NULL;")
    a(f"    b->get_integer = NULL;   /* sin variables Integer en este modelo */")
    a(f"    b->set_integer = NULL;")
    a(f"    b->get_string  = NULL;   /* sin variables String en este modelo  */")
    a(f"    b->set_string  = NULL;")
    a(f"    b->tick_freq   = 0;      /* TODO MCU: asignar frecuencia del timer */")
    a(f"    b->get_clock   = NULL;   /* TODO MCU: asignar funcion de lectura del timer */")
    a(f"    return b;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


# =============================================================================
# Generador de CMakeLists.txt  (mcu/)
# =============================================================================

def generate_cmake_mcu(info: FMUInfo) -> str:
    """
    Genera el CMakeLists.txt para el target MCU en mcu/.

    Target: <modelo>_mcu
    Compila SOLO main.c + <modelo>_mcu.c — sin ninguna fuente de la FMU.

    MCU_STDIO_OUTPUT se define para el ejecutable de test en host:
    activa printf en el main.c MCU, permitiendo comparar numericamente
    la salida con el adapter HOST y verificar que las ecuaciones son correctas.

    Args:
        info: Metadatos del modelo.
    """
    L = info.lower

    lines = []
    a = lines.append

    a(f"# CMakeLists.txt — MCU example: {info.model_name}")
    a(f"# Generado por fmu_codegen_mcu.py — puedes editarlo libremente.")
    a(f"#")
    a(f"# Compila SOLO main.c + {L}_mcu.c — sin ninguna fuente del runtime OpenModelica.")
    a(f"# Ideal para verificar en host antes de flashear al MCU real.")
    a(f"#")
    a(f"# Para el equivalente HOST (con runtime OpenModelica), ver ../host/CMakeLists.txt")
    a(f"")
    a(f"cmake_minimum_required(VERSION 3.16)")
    a(f"")
    a(f"add_executable({L}_mcu")
    a(f"    main.c")
    a(f"    {L}_mcu.c")
    a(f")")
    a(f"")
    a(f"target_include_directories({L}_mcu PRIVATE")
    a(f'    "${{CMAKE_CURRENT_SOURCE_DIR}}"')
    a(f")")
    a(f"")
    a(f"# Libreria fmi: solvers Euler/RK4 + headers fmu_t.h (C99 puro, apto para MCU)")
    a(f"target_link_libraries({L}_mcu PRIVATE fmi)")
    a(f"")
    a(f"# MCU_STDIO_OUTPUT: activa printf en el main.c MCU para test numerico en host.")
    a(f"# En un MCU real, compilar sin esta definicion y reemplazar SIM_PRINT por UART.")
    a(f"target_compile_definitions({L}_mcu PRIVATE MCU_STDIO_OUTPUT)")
    a(f"")
    a(f"add_test(NAME {L}_mcu COMMAND {L}_mcu)")

    return "\n".join(lines)


# =============================================================================
# Generador de main.c  (mcu/)
# =============================================================================

def generate_main_mcu(info: FMUInfo) -> str:
    """
    Genera main.c limpio para el target MCU.

    Diferencias con el antiguo main.c mixto:
      - Sin #ifdef MCU_TARGET (este main.c ES el MCU, siempre)
      - Incluye directamente <modelo>_mcu.h
      - SIM_PRINT/SIM_DELAY/SIM_ERROR son TODOs de UART en MCU real
      - MCU_STDIO_OUTPUT (definido en CMake) los redirige a printf para test en host
      - Llama directamente a <modelo>_mcu_create()

    Args:
        info: Metadatos del modelo.
    """
    L = info.lower
    U = info.upper

    lines = []
    a = lines.append

    # ── Cabecera ───────────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @file   main.c")
    a(f" * @brief  Loop de simulacion MCU para {info.model_name}.")
    a(f" *")
    a(f" *  Usa el adapter MCU que implementa directamente las ecuaciones ODE,")
    a(f" *  SIN necesitar el runtime de OpenModelica.")
    a(f" *  Listo para compilar en ESP32, STM32, Arduino, o cualquier MCU C99.")
    a(f" *")
    a(f" *  Para simular en PC con el runtime OpenModelica, usar ../host/main.c")
    a(f" *")
    a(f" * Modelo : {info.model_name}")
    a(f" * GUID   : {info.guid}")
    a(f" * Modo   : {'ME' if info.has_me else 'CS'} | Estados: {info.n_states} | Indicadores: {info.n_event_indicators}")
    a(f" *")
    if info.has_me and not info.is_discrete:
        a(f" * Tipo: Model Exchange con {info.n_states} estado(s) continuo(s).")
        a(f" * El solver Euler integra dx/dt; cambia a fmu_rk4_step() si necesitas mas precision.")
    a(f" *")
    a(f" * GENERADO por fmu_codegen_mcu.py — rellena los TODO segun tu plataforma MCU.")
    a(f" */")
    a(f"")
    a(f"#include <math.h>")
    if info.has_me and not info.is_discrete:
        a(f'#include "fmu_solver.h"   /* fmu_euler_step / fmu_rk4_step — C99 puro */')
    a(f'#include "{L}_mcu.h"     /* adapter MCU — ecuaciones directas, sin runtime */')
    a(f"")
    a(f"/* ── TODO: incluir los headers de tu plataforma MCU ───────────────────────── */")
    a(f"/* #include \"stm32xx_hal.h\"  (STM32 HAL) */")
    a(f"/* #include \"Arduino.h\"       (Arduino/ESP32) */")
    a(f"/* #include \"driver/uart.h\"   (ESP-IDF) */")
    a(f"")
    a(f"#ifndef M_PI")
    a(f"#define M_PI 3.14159265358979323846")
    a(f"#endif")
    a(f"")
    a(f"/* ── Macros de salida/entrada/error ───────────────────────────────────────── */")
    a(f"/* MCU_STDIO_OUTPUT se define en CMakeLists.txt para test numerico en host.")
    a(f"   En un MCU real, no definas MCU_STDIO_OUTPUT y reemplaza los TODO. */")
    a(f"#ifdef MCU_STDIO_OUTPUT")
    a(f"#  include <stdio.h>")
    a(f"#  define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)")
    a(f"#  define SIM_DELAY(h)         ((void)(h))")
    a(f"#  define SIM_ERROR(msg)       fprintf(stderr, \"%s\", msg)")
    a(f"#else")
    a(f"/* TODO: reemplaza estas macros con las funciones de tu MCU: */")
    a(f"#  define SIM_PRINT(fmt, ...)  /* uart_printf(fmt, ##__VA_ARGS__)      */")
    a(f"#  define SIM_DELAY(h)         /* HAL_Delay((uint32_t)((h) * 1000U))  */")
    a(f"#  define SIM_ERROR(msg)       /* uart_puts(msg)                       */")
    a(f"#endif")
    a(f"")

    # ── Cuerpo compartido (process_events + main loop) ─────────────────────────
    a(generate_sim_loop(info, f"{L}_mcu_create()"))

    return "\n".join(lines)


# =============================================================================
# Punto de entrada
# =============================================================================

def main() -> None:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    fmu_input  = sys.argv[1]
    output_dir = sys.argv[2]

    try:
        fmu_dir = extract_fmu(fmu_input)
    except (ValueError, __import__("zipfile").BadZipFile) as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    if not os.path.isdir(fmu_dir):
        print(f"Error: '{fmu_dir}' no es un directorio valido.", file=sys.stderr)
        sys.exit(1)

    print(f"[mcu] Parseando {os.path.join(fmu_dir, 'modelDescription.xml')} ...")
    info = parse_fmu(fmu_dir)

    if not info.has_me or info.n_states == 0:
        print(f"[mcu] ERROR: este modelo no tiene ME con estados continuos.")
        print(f"[mcu]        El adapter MCU solo soporta modelos ME con ODE.")
        sys.exit(1)

    mode_str = (("CS" if info.has_cs else "") +
                ("/" if info.has_cs and info.has_me else "") +
                ("ME" if info.has_me else ""))
    print(f"[mcu] Modelo    : {info.model_name}")
    print(f"[mcu] Modo      : {mode_str}  |  Estados: {info.n_states}  |  Variables: {len(info.variables)}")

    # Extraer ecuaciones ODE del source de la FMU
    mcu = parse_mcu_data(fmu_dir, info)
    if mcu is None:
        print(f"[mcu] ERROR: no se pudo extraer datos MCU del modelo.")
        sys.exit(1)

    if mcu["ok"]:
        print(f"[mcu] Ecuaciones: {info.n_states}/{info.n_states} derivadas extraidas correctamente")
    else:
        print(f"[mcu] AVISO: extraccion parcial — {mcu['note']}")
        print(f"[mcu]        Completa los TODO en _get_derivatives() del .c generado.")

    os.makedirs(output_dir, exist_ok=True)

    # 1. Header MCU
    h_path = os.path.join(output_dir, f"{info.lower}_mcu.h")
    with open(h_path, "w", encoding="utf-8") as f:
        f.write(generate_mcu_header(info, mcu))
    print(f"[mcu] Generado  : {h_path}")

    # 2. Source MCU
    c_path = os.path.join(output_dir, f"{info.lower}_mcu.c")
    with open(c_path, "w", encoding="utf-8") as f:
        f.write(generate_mcu_source(info, mcu))
    print(f"[mcu] Generado  : {c_path}")

    # 3. CMakeLists.txt (siempre se sobreescribe)
    cmake_path = os.path.join(output_dir, "CMakeLists.txt")
    with open(cmake_path, "w", encoding="utf-8") as f:
        f.write(generate_cmake_mcu(info))
    print(f"[mcu] Generado  : {cmake_path}")

    # 4. main.c (solo si no existe — preserva modificaciones del usuario)
    main_path = os.path.join(output_dir, "main.c")
    if not os.path.exists(main_path):
        with open(main_path, "w", encoding="utf-8") as f:
            f.write(generate_main_mcu(info))
        print(f"[mcu] Generado  : {main_path}")
    else:
        print(f"[mcu] Conservado: {main_path}  (ya existe)")

    # 5. Registrar en el CMakeLists padre
    register_in_parent_cmake(output_dir)

    print(f"")
    print(f"[mcu] Siguiente paso:")
    print(f"      1. Rellena los TODO UART en main.c para tu plataforma MCU")
    print(f"      2. cmake --build <build_dir> --target {info.lower}_mcu  (test en host)")
    print(f"      3. Copia main.c + {info.lower}_mcu.h/c + fmu_solver.h/c al proyecto MCU")


if __name__ == "__main__":
    main()
