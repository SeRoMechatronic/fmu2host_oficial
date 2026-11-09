#!/usr/bin/env python3
"""
fmu_codegen_host.py — Generador de adapters HOST para FMUs FMI 2.0

Genera los archivos necesarios para simular una FMU en PC (host)
usando el runtime de OpenModelica. Se generan DOS adapters independientes
cuando la FMU soporta ambos modos:

  Model Exchange (ME): el llamador controla el solver (Euler / RK4).
  Co-Simulation  (CS): la FMU integra internamente; solo se llama do_step().

Uso:
    python fmu_codegen_host.py <fmu_o_dir> <output_dir>

    <fmu_o_dir>   Directorio FMU (con modelDescription.xml) o archivo .fmu.
    <output_dir>  Directorio de salida. Convencion: examples/<modelo>/host/

Genera (hasta 9 archivos):
    <modelo>_adapter.h      Constantes VR_*, metadatos, declaraciones create_me/cs()
    <modelo>_adapter_me.c   Wrapper ME: instancia como ModelExchange (si has_me)
    <modelo>_adapter_cs.c   Wrapper CS: instancia como CoSimulation   (si has_cs)
    <modelo>_api.h          Structs Inputs/Outputs/SimConfig + declaraciones
    main_me.c               Loop ME auto-generado, no editar (si has_me, siempre)
    main_cs.c               Loop CS con do_step (si has_cs, siempre regenerado)
    scenario.c              UNICO archivo editable: get_config/get_inputs/on_outputs
    CMakeLists.txt          Targets: <modelo>_host_me y/o <modelo>_host_cs

Arquitectura modular (ME y CS):
    scenario.c   — EDITAR: define get_config(), get_inputs(), on_outputs()
    main_me.c    — NO EDITAR: loop completo auto-generado
    <modelo>_api.h — NO EDITAR: structs y declaraciones auto-generadas

Requisitos: Python 3.8+  |  Solo stdlib  |  fmu_parser.py en el mismo directorio
"""

import sys
import os
import re
from dataclasses import replace as dc_replace

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from fmu_parser import (
    FMUInfo, Variable,
    parse_fmu, extract_fmu,
    generate_sim_loop, register_in_parent_cmake,
)


# =============================================================================
# Helpers para el API de structs
# =============================================================================

def _api_c_type(v: Variable) -> str:
    """Mapea tipo FMU al tipo C plano usado en los structs de la API."""
    if v.type_ == "Real":    return "double"
    if v.type_ == "Boolean": return "int"
    if v.type_ == "Integer": return "int"
    if v.type_ == "String":  return "const char *"
    return "double"


def _safe_field(name: str) -> str:
    """Convierte un nombre de variable Modelica a identificador C valido en minusculas."""
    s = re.sub(r'[^a-zA-Z0-9_]', '_', name.lower())
    while '__' in s:
        s = s.replace('__', '_')
    s = s.strip('_')
    return ('f_' + s) if (s and s[0].isdigit()) else (s if s else 'var_')


# =============================================================================
# Header compartido  (<modelo>_adapter.h)
# =============================================================================

def generate_adapter_header(info: FMUInfo, fmu_dir: str) -> str:
    """
    Genera <modelo>_adapter.h compartido por _adapter_me.c y _adapter_cs.c.

    Contiene:
      - #define de metadatos (nombre, GUID, modo, estados)
      - #define de tamanios de buffer para solvers (ME)
      - #define VR_* por variable agrupados por causalidad
      - Declaraciones de create_me() y/o create_cs()
    """
    U = info.upper
    L = info.lower
    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_adapter.h")
    a(f" * @brief  Interfaz fmu_t HOST para {info.model_name}.")
    a(f" *")
    a(f" *  Header compartido por _adapter_me.c y _adapter_cs.c.")
    a(f" *  Contiene constantes VR_*, tamanios de buffer y declaraciones create_*().")
    a(f" *")
    a(f" * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.")
    a(f" */")
    a(f"")
    a(f"#ifndef {U}_ADAPTER_H")
    a(f"#define {U}_ADAPTER_H")
    a(f"")
    a(f'#include "fmu_t.h"')
    a(f'#include "fmu_solver.h"')
    a(f"")

    # Metadatos
    a(f"/** @defgroup {L}_meta Metadatos del modelo */")
    a(f"/** @{{ */")
    a(f'#define {U}_MODEL_NAME          "{info.model_name}"')
    a(f'#define {U}_GUID                "{info.guid}"')
    a(f'#define {U}_N_STATES            {info.n_states}')
    a(f'#define {U}_N_EVENT_INDICATORS  {info.n_event_indicators}')
    a(f"/** @}} */")
    a(f"")

    # Buffer solvers (ME)
    a(f"/** @defgroup {L}_solver Tamanios de buffer para solvers Euler y RK4 (ME) */")
    a(f"/** @{{ */")
    a(f"#define {U}_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE({U}_N_STATES)")
    a(f"#define {U}_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE({U}_N_STATES)")
    a(f"/** @}} */")
    a(f"")

    # ValueReferences
    groups = [
        ("Entradas",              "input"),
        ("Salidas",               "output"),
        ("Parametros",            "parameter"),
        ("Parametros calculados", "calculatedParameter"),
        ("Locales",               "local"),
    ]
    a(f"/** @defgroup {L}_vr ValueReferences (de modelDescription.xml) */")
    a(f"/** @{{ */")
    for label, causality in groups:
        group = [v for v in info.variables if v.causality == causality]
        if not group:
            continue
        a(f"/** @name {label} */")
        a(f"/** @{{ */")
        for v in group:
            define  = f"{U}_VR_{v.define_name}"
            comment = f"{v.type_}, {v.causality}, {v.variability}"
            if v.start is not None:
                comment += f", start={v.start}"
            a(f"#define {define:<48} {v.vr}u   /*!< {comment} */")
        a(f"/** @}} */")
        a(f"")
    a(f"/** @}} */")
    a(f"")

    # Declaraciones de create
    if info.has_me:
        a(f"/** @brief Devuelve el adapter Model Exchange para {info.model_name}.")
        a(f" *  Usa fmu_euler_step() o fmu_rk4_step() para integrar. */")
        a(f"fmu_t *{L}_create_me(void);")
        a(f"")
    if info.has_cs:
        a(f"/** @brief Devuelve el adapter Co-Simulation para {info.model_name}.")
        a(f" *  Llama solo a FMU_CALL(m, do_step, t, h) — la FMU integra internamente. */")
        a(f"fmu_t *{L}_create_cs(void);")
        a(f"")

    a(f"#endif /* {U}_ADAPTER_H */")

    return "\n".join(lines) + "\n"


# =============================================================================
# Header de API  (<modelo>_api.h)  — structs Inputs / Outputs / SimConfig
# =============================================================================

def generate_api_header(info: FMUInfo) -> str:
    """
    Genera <modelo>_api.h con:
      - SimConfig       { t_end, h, use_rk4 }
      - <ID>_Inputs     { un campo por variable de entrada }  (si hay entradas)
      - <ID>_Outputs    { un campo por variable de salida  }  (si hay salidas)
      - Declaraciones de get_config() y get_inputs()

    El usuario implementa esas funciones en scenario.c.
    """
    U   = info.upper
    L   = info.lower
    ID  = info.model_identifier
    inputs  = info.vars_of_causality("input")
    outputs = info.vars_of_causality("output")

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_api.h")
    a(f" * @brief  API de simulacion para {info.model_name}.")
    a(f" *")
    a(f" *  Define los structs de entrada/salida y la configuracion de simulacion.")
    a(f" *  Implementa get_config() y get_inputs() en scenario.c.")
    a(f" *")
    a(f" * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.")
    a(f" */")
    a(f"")
    a(f"#ifndef {U}_API_H")
    a(f"#define {U}_API_H")
    a(f"")
    a(f"/** Configuracion de la simulacion. Devuelta por get_config(). */")
    a(f"typedef struct {{")
    a(f"    double t_end;    /**< Tiempo final de simulacion (s) */")
    a(f"    double h;        /**< Paso de integracion (s) */")
    a(f"    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */")
    a(f"}} SimConfig;")
    a(f"")

    if inputs:
        a(f"/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */")
        a(f"typedef struct {{")
        for v in inputs:
            f  = _safe_field(v.name)
            ct = _api_c_type(v)
            a(f"    {ct:<16} {f};   /**< {v.type_} input '{v.name}' */")
        a(f"}} {ID}_Inputs;")
        a(f"")

    if outputs:
        a(f"/** Salidas del modelo en cada instante t. */")
        a(f"typedef struct {{")
        for v in outputs:
            f  = _safe_field(v.name)
            ct = _api_c_type(v)
            a(f"    {ct:<16} {f};   /**< {v.type_} output '{v.name}' */")
        a(f"}} {ID}_Outputs;")
        a(f"")

    a(f"/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */")
    a(f"SimConfig get_config(void);")
    a(f"")
    if inputs:
        a(f"/** Rellena las entradas en el instante t. Definir en scenario.c. */")
        a(f"void get_inputs(double t, {ID}_Inputs *in);")
        a(f"")
    if outputs:
        a(f"/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */")
        a(f"void on_outputs(double t, const {ID}_Outputs *out);")
        a(f"")

    a(f"#endif /* {U}_API_H */")

    return "\n".join(lines) + "\n"


# =============================================================================
# Generador de adapter interno (compartido entre ME y CS)
# =============================================================================

def _generate_adapter(info: FMUInfo, fmu_dir: str, mode: str) -> str:
    """
    Genera el source de un adapter HOST para el modo indicado.

    Args:
        info:    Metadatos del modelo.
        fmu_dir: Directorio FMU.
        mode:    'me' para Model Exchange, 'cs' para Co-Simulation.
    """
    assert mode in ('me', 'cs')
    is_me = (mode == 'me')

    U = info.upper
    L = info.lower
    P = info.identifier_for(mode) + "_"

    fmi2_type_enum = "fmi2ModelExchange" if is_me else "fmi2CoSimulation"
    mode_define    = "FMU_MODE_ME"       if is_me else "FMU_MODE_CS"
    mode_label     = "Model Exchange"    if is_me else "Co-Simulation"
    create_fn      = f"{L}_create_me"   if is_me else f"{L}_create_cs"
    suffix         = "_me"              if is_me else "_cs"

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_adapter{suffix}.c")
    a(f" * @brief  Wrapper fmu_t HOST ({mode_label}) para {info.model_name}.")
    a(f" *")
    a(f" *  Instancia la FMU como {fmi2_type_enum} y delega TODAS las")
    a(f" *  operaciones al runtime de OpenModelica. No reimplementa ecuaciones.")
    a(f" *")
    if is_me:
        a(f" *  Usar con main_me.c + fmu_euler_step() o fmu_rk4_step().")
    else:
        a(f" *  Usar con main_cs.c + FMU_CALL(m, do_step, t, h).")
    a(f" *")
    a(f" * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.")
    a(f" */")
    a(f"/* Source artifact: {info.model_name} (path intentionally omitted). */")
    a(f"")
    a(f'#include <stdlib.h>')
    a(f'#include <stdio.h>')
    a(f'#include <stdarg.h>')
    a(f'#include <stddef.h>')
    a(f'#include <string.h>')
    a(f"")
    a(f'#include "fmi2_api.h"')
    a(f'#include "fmu_t.h"')
    a(f'#include "{L}_adapter.h"')
    a(f"")

    # Externs
    a(f"/* Funciones FMI 2.0 del runtime de OpenModelica (prefijo '{P}') */")
    a(f"extern fmi2Component {P}fmi2Instantiate(")
    a(f"    fmi2String, fmi2Type, fmi2String, fmi2String,")
    a(f"    const fmi2CallbackFunctions *, fmi2Boolean, fmi2Boolean);")
    a(f"extern fmi2Status {P}fmi2SetupExperiment(")
    a(f"    fmi2Component, fmi2Boolean, fmi2Real, fmi2Real, fmi2Boolean, fmi2Real);")
    a(f"extern fmi2Status {P}fmi2EnterInitializationMode(fmi2Component);")
    a(f"extern fmi2Status {P}fmi2ExitInitializationMode(fmi2Component);")
    a(f"extern fmi2Status {P}fmi2Terminate(fmi2Component);")
    a(f"extern void       {P}fmi2FreeInstance(fmi2Component);")
    a(f"extern fmi2Status {P}fmi2Reset(fmi2Component);")
    a(f"")

    if not is_me:
        a(f"/* Co-Simulation: la FMU avanza internamente un paso h */")
        a(f"extern fmi2Status {P}fmi2DoStep(")
        a(f"    fmi2Component, fmi2Real, fmi2Real, fmi2Boolean);")
        a(f"")

    if is_me:
        a(f"/* Model Exchange: el llamador integra con su solver */")
        a(f"extern fmi2Status {P}fmi2SetTime(fmi2Component, fmi2Real);")
        a(f"extern fmi2Status {P}fmi2SetContinuousStates(fmi2Component, const fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2GetDerivatives(fmi2Component, fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2GetContinuousStates(fmi2Component, fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2CompletedIntegratorStep(")
        a(f"    fmi2Component, fmi2Boolean, fmi2Boolean *, fmi2Boolean *);")
        a(f"extern fmi2Status {P}fmi2EnterEventMode(fmi2Component);")
        a(f"extern fmi2Status {P}fmi2NewDiscreteStates(fmi2Component, fmi2EventInfo *);")
        a(f"extern fmi2Status {P}fmi2EnterContinuousTimeMode(fmi2Component);")
        a(f"extern fmi2Status {P}fmi2GetEventIndicators(fmi2Component, fmi2Real *, size_t);")
        a(f"")

    for type_ in ("Real", "Integer", "Boolean", "String"):
        if not info.has_type(type_):
            continue
        fmi2t = Variable("", 0, "", "", type_).fmi2_type
        a(f"extern fmi2Status {P}fmi2Get{type_}(")
        a(f"    fmi2Component, const fmi2ValueReference *, size_t, {fmi2t} *);")
        a(f"extern fmi2Status {P}fmi2Set{type_}(")
        a(f"    fmi2Component, const fmi2ValueReference *, size_t, const {fmi2t} *);")
        a(f"")

    # Callbacks
    a(f"static void _logger(fmi2ComponentEnvironment env, fmi2String inst,")
    a(f"                    fmi2Status status, fmi2String cat,")
    a(f"                    fmi2String msg, ...) {{")
    a(f"    (void)env; (void)inst; (void)status;")
    a(f"    va_list args; va_start(args, msg);")
    a(f"    fprintf(stderr, \"[{info.model_name}/%s] \", cat);")
    a(f"    vfprintf(stderr, msg, args);")
    a(f"    fprintf(stderr, \"\\n\");")
    a(f"    va_end(args);")
    a(f"}}")
    a(f"")
    a(f"static const fmi2CallbackFunctions _callbacks = {{")
    a(f"    .logger               = _logger,")
    a(f"    .allocateMemory       = calloc,")
    a(f"    .freeMemory           = free,")
    a(f"    .stepFinished         = NULL,")
    a(f"    .componentEnvironment = NULL,")
    a(f"}};")
    a(f"")
    a(f"static fmu_status_t _status(fmi2Status st)")
    a(f"{{")
    a(f"    if (st == fmi2OK) return FMU_OK;")
    a(f"    if (st == fmi2Warning) return FMU_WARNING;")
    a(f"    if (st == fmi2Fatal) return FMU_FATAL;")
    a(f"    return FMU_ERROR;")
    a(f"}}")
    a(f"")

    # Struct concreto
    a(f"typedef struct {{")
    a(f"    fmu_t         base;   /* PRIMER CAMPO: permite cast (fmu_t *) -> ({L}_t *) */")
    a(f"    fmi2Component inst;   /* Handle opaco de la instancia FMI 2.0 */")
    a(f"}} {L}_t;")
    a(f"#define SELF(p)  (({L}_t *)(p))")
    a(f"")

    # _compute_res_uri
    a(f"#if defined(_WIN32)")
    a(f"#  include <windows.h>")
    a(f"static void _compute_res_uri(char *out, size_t n) {{")
    a(f"    char buf[MAX_PATH];")
    a(f"    GetModuleFileNameA(NULL, buf, MAX_PATH);")
    a(f"    char *sep = strrchr(buf, '\\\\'); if (sep) *sep = '\\0';")
    a(f"    for (char *p = buf; *p; p++) if (*p == '\\\\') *p = '/';")
    a(f'    snprintf(out, n, "file:///%s", buf);')
    a(f"}}")
    a(f"#elif defined(__linux__)")
    a(f"#  include <unistd.h>")
    a(f"static void _compute_res_uri(char *out, size_t n) {{")
    a(f"    char buf[4096] = {{0}};")
    a(f"    ssize_t len = readlink(\"/proc/self/exe\", buf, sizeof(buf) - 1);")
    a(f"    if (len > 0) {{ char *sep = strrchr(buf, '/'); if (sep) *sep = '\\0'; }}")
    a(f'    snprintf(out, n, "file://%s", buf);')
    a(f"}}")
    a(f"#elif defined(__APPLE__)")
    a(f"#  include <mach-o/dyld.h>")
    a(f"static void _compute_res_uri(char *out, size_t n) {{")
    a(f"    char buf[4096]; uint32_t sz = (uint32_t)sizeof(buf);")
    a(f"    _NSGetExecutablePath(buf, &sz);")
    a(f"    char *sep = strrchr(buf, '/'); if (sep) *sep = '\\0';")
    a(f'    snprintf(out, n, "file://%s", buf);')
    a(f"}}")
    a(f"#else")
    a(f"static void _compute_res_uri(char *out, size_t n) {{ snprintf(out, n, \"\"); }}")
    a(f"#endif")
    a(f"")

    # _initialize
    a(f"static fmu_status_t _initialize(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    char _res_uri[4096];")
    a(f"    _compute_res_uri(_res_uri, sizeof(_res_uri));")
    a(f"    c->inst = {P}fmi2Instantiate(")
    a(f"        {U}_MODEL_NAME, {fmi2_type_enum},")
    a(f"        {U}_GUID, _res_uri,")
    a(f"        &_callbacks, fmi2False, fmi2False);")
    a(f"    if (!c->inst) return FMU_ERROR;")
    a(f"    fmi2Status st = {P}fmi2SetupExperiment(c->inst, fmi2False, 0.0, 0.0, fmi2False, 0.0);")
    a(f"    if (st > fmi2Warning) goto fail;")
    a(f"    st = {P}fmi2EnterInitializationMode(c->inst);")
    a(f"    if (st > fmi2Warning) goto fail;")
    a(f"    st = {P}fmi2ExitInitializationMode(c->inst);")
    a(f"    if (st > fmi2Warning) goto fail;")
    a(f"    self->current_time = 0.0;")
    a(f"    self->termination_requested = 0;")
    a(f"    self->next_event_time_defined = 0;")
    a(f"    self->next_event_time = 0.0;")
    a(f"    return FMU_OK;")
    a(f"fail:")
    a(f"    {P}fmi2FreeInstance(c->inst);")
    a(f"    c->inst = NULL;")
    a(f"    return _status(st);")
    a(f"}}")
    a(f"")

    a(f"static fmu_status_t _terminate(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    if (!c->inst) return FMU_OK;")
    a(f"    fmi2Status st = {P}fmi2Terminate(c->inst);")
    a(f"    {P}fmi2FreeInstance(c->inst);")
    a(f"    c->inst = NULL;")
    a(f"    return _status(st);")
    a(f"}}")
    a(f"")

    a(f"static fmu_status_t _reset(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    fmi2Status st = {P}fmi2Reset(c->inst);")
    a(f"    self->current_time = 0.0;")
    a(f"    return _status(st);")
    a(f"}}")
    a(f"")

    if not is_me:
        a(f"static fmu_status_t _do_step(fmu_t *self, fmu_real_t t, fmu_real_t h)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2DoStep(c->inst, (fmi2Real)t, (fmi2Real)h, fmi2True);")
        a(f"    if (st == fmi2OK || st == fmi2Warning) {{")
        a(f"        self->current_time = t + h;")
        a(f"        return FMU_OK;")
        a(f"    }}")
        a(f"    return FMU_ERROR;")
        a(f"}}")
        a(f"")

    if is_me:
        a(f"static fmu_status_t _set_time(fmu_t *self, fmu_real_t t)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2SetTime(c->inst, (fmi2Real)t);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _get_derivatives(fmu_t *self, fmu_real_t *dx, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetDerivatives(c->inst, (fmi2Real *)dx, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _get_cont_states(fmu_t *self, fmu_real_t *x, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetContinuousStates(c->inst, (fmi2Real *)x, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _set_cont_states(fmu_t *self, const fmu_real_t *x, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2SetContinuousStates(c->inst, (const fmi2Real *)x, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _completed_step(fmu_t *self, fmu_bool_t *enter_event)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Boolean ev = fmi2False, term = fmi2False;")
        a(f"    fmi2Status st = {P}fmi2CompletedIntegratorStep(c->inst, fmi2True, &ev, &term);")
        a(f"    *enter_event = (fmu_bool_t)ev;")
        a(f"    self->termination_requested = (fmu_bool_t)term;")
        a(f"    return _status(st);")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _enter_event_mode(fmu_t *self)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2EnterEventMode(c->inst);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _new_discrete_states(fmu_t *self,")
        a(f"    fmu_bool_t *more, fmu_bool_t *terminate)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2EventInfo ei = {{fmi2False, fmi2False, fmi2False, fmi2False, fmi2False, 0.0}};")
        a(f"    fmi2Status st = {P}fmi2NewDiscreteStates(c->inst, &ei);")
        a(f"    *more      = (fmu_bool_t)ei.newDiscreteStatesNeeded;")
        a(f"    *terminate = (fmu_bool_t)ei.terminateSimulation;")
        a(f"    self->termination_requested = (fmu_bool_t)ei.terminateSimulation;")
        a(f"    self->next_event_time_defined = (fmu_bool_t)ei.nextEventTimeDefined;")
        a(f"    self->next_event_time = (fmu_real_t)ei.nextEventTime;")
        a(f"    return _status(st);")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _enter_cont_mode(fmu_t *self)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2EnterContinuousTimeMode(c->inst);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _get_event_indicators(fmu_t *self, fmu_real_t *ei, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetEventIndicators(c->inst, (fmi2Real *)ei, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")

    for type_ in ("Real", "Integer", "Boolean", "String"):
        if not info.has_type(type_):
            continue
        fmi2t  = Variable("", 0, "", "", type_).fmi2_type
        fmu_t_ = Variable("", 0, "", "", type_).c_type
        tl     = type_.lower()
        a(f"static fmu_status_t _get_{tl}(fmu_t *self,")
        a(f"    const fmu_vref_t *vr, int n, {fmu_t_} *out)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2Get{type_}(")
        a(f"        c->inst, (const fmi2ValueReference *)vr, (size_t)n, ({fmi2t} *)out);")
        a(f"    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"static fmu_status_t _set_{tl}(fmu_t *self,")
        a(f"    const fmu_vref_t *vr, int n, const {fmu_t_} *in)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2Set{type_}(")
        a(f"        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (const {fmi2t} *)in);")
        a(f"    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")

    # Instancia estatica
    a(f"static {L}_t _instance{suffix} = {{")
    a(f"    .base = {{")
    a(f"        .model_name   = {U}_MODEL_NAME,")
    a(f"        .guid         = {U}_GUID,")
    a(f"        .mode         = {mode_define},")
    a(f"        .n_states     = {U}_N_STATES,")
    a(f"        .step_size    = 0.01,")
    a(f"        .current_time = 0.0,")
    a(f"        .initialize   = _initialize,")
    a(f"        .terminate    = _terminate,")
    a(f"        .reset        = _reset,")

    if is_me:
        a(f"        .do_step              = NULL,")
        a(f"        .set_time             = _set_time,")
        a(f"        .get_derivatives      = _get_derivatives,")
        a(f"        .get_cont_states      = _get_cont_states,")
        a(f"        .set_cont_states      = _set_cont_states,")
        a(f"        .completed_step       = _completed_step,")
        a(f"        .enter_event_mode     = _enter_event_mode,")
        a(f"        .new_discrete_states  = _new_discrete_states,")
        a(f"        .enter_cont_mode      = _enter_cont_mode,")
        a(f"        .get_event_indicators = _get_event_indicators,")
    else:
        a(f"        .do_step              = _do_step,")
        a(f"        .set_time             = NULL,")
        a(f"        .get_derivatives      = NULL,")
        a(f"        .get_cont_states      = NULL,")
        a(f"        .set_cont_states      = NULL,")
        a(f"        .completed_step       = NULL,")
        a(f"        .enter_event_mode     = NULL,")
        a(f"        .new_discrete_states  = NULL,")
        a(f"        .enter_cont_mode      = NULL,")
        a(f"        .get_event_indicators = NULL,")

    for type_ in ("real", "boolean", "integer", "string"):
        Type = type_.capitalize()
        if info.has_type(Type):
            a(f"        .get_{type_:<10} = _get_{type_},")
            a(f"        .set_{type_:<10} = _set_{type_},")
        else:
            a(f"        .get_{type_:<10} = NULL,")
            a(f"        .set_{type_:<10} = NULL,")

    a(f"        .get_clock    = NULL,")
    a(f"        .tick_freq    = 0,")
    a(f"    }},")
    a(f"    .inst = NULL,")
    a(f"}};")
    a(f"")
    a(f"fmu_t *{create_fn}(void)")
    a(f"{{")
    a(f"    return &_instance{suffix}.base;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


def generate_adapter_me(info: FMUInfo, fmu_dir: str) -> str:
    """Genera <modelo>_adapter_me.c — instancia como ModelExchange."""
    return _generate_adapter(info, fmu_dir, 'me')


def generate_adapter_cs(info: FMUInfo, fmu_dir: str) -> str:
    """Genera <modelo>_adapter_cs.c — instancia como CoSimulation."""
    return _generate_adapter(info, fmu_dir, 'cs')


# =============================================================================
# Generadores de main_me.c, scenario.c y main_cs.c
# =============================================================================

def generate_scenario_me(info: FMUInfo) -> str:
    """
    Genera scenario.c: UNICO archivo editable por el usuario.

    Define get_config() para ajustar tiempo/paso y get_inputs() para
    proporcionar entradas al modelo en cada instante t.
    """
    L  = info.lower
    ID = info.model_identifier
    inputs = info.vars_of_causality("input")

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   scenario.c")
    a(f" * @brief  Escenario de simulacion para {info.model_name}.")
    a(f" *")
    a(f" *  UNICO archivo que debes editar.")
    a(f" *  Ajusta get_config() para cambiar tiempo y paso de simulacion.")
    if inputs:
        a(f" *  Ajusta get_inputs() para proporcionar entradas en cada instante t.")
    a(f" */")
    a(f"")
    a(f'#include "{L}_api.h"')
    a(f"")
    a(f"SimConfig get_config(void)")
    a(f"{{")
    a(f"    return (SimConfig){{")
    a(f"        .t_end   = 1.0,")
    a(f"        .h       = 0.01,")
    a(f"        .use_rk4 = 0,")
    a(f"    }};")
    a(f"}}")
    a(f"")

    if inputs:
        a(f"void get_inputs(double t, {ID}_Inputs *in)")
        a(f"{{")
        a(f"    (void)t;")
        a(f"    /* Ajusta las entradas segun tu escenario: */")
        for v in inputs:
            f = _safe_field(v.name)
            a(f"    /* in->{f} = ...; */")
        a(f"}}")
        a(f"")

    outputs = info.vars_of_causality("output")
    if outputs:
        a(f"void on_outputs(double t, const {ID}_Outputs *out)")
        a(f"{{")
        a(f"    (void)t;")
        a(f"    /* Reacciona a las salidas del modelo: */")
        for v in outputs:
            f = _safe_field(v.name)
            a(f"    /* if (out->{f}) {{ ... }} */")
        a(f"}}")
        a(f"")

    return "\n".join(lines)


def generate_main_me(info: FMUInfo) -> str:
    """
    Genera main_me.c (auto-generado, no editar).

    Loop ME que usa los structs de <modelo>_api.h y llama a
    get_config() / get_inputs() definidos por el usuario en scenario.c.
    """
    L  = info.lower
    U  = info.upper
    ID = info.model_identifier

    inputs  = info.vars_of_causality("input")
    outputs = info.vars_of_causality("output")

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   main_me.c")
    a(f" * @brief  Loop ME auto-generado para {info.model_name} — no editar.")
    a(f" *")
    a(f" *  Personaliza get_config() y get_inputs() en scenario.c.")
    a(f" *")
    a(f" * Modelo : {info.model_name}")
    a(f" * GUID   : {info.guid}")
    a(f" * Estados: {info.n_states}  |  Indicadores: {info.n_event_indicators}")
    a(f" *")
    a(f" * GENERADO por fmu_codegen_host.py — no editar manualmente.")
    a(f" */")
    a(f"")
    a(f"#include <stdio.h>")
    a(f"#include <stdlib.h>")
    a(f"#include <string.h>")
    a(f"#include <math.h>")
    if info.n_states > 0:
        a(f'#include "fmu_solver.h"')
    a(f'#include "{L}_api.h"')
    a(f'#include "{L}_adapter.h"')
    a(f"")
    a(f"#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)")
    a(f"#define SIM_ERROR(msg)       fprintf(stderr, \"%s\", msg)")
    a(f"#define SIM_DELAY(h)         ((void)(h))")
    a(f"")

    # process_events
    a(f"static int process_events(fmu_t *m)")
    a(f"{{")
    a(f"    if (FMU_CALL(m, enter_event_mode) > FMU_WARNING) return -1;")
    a(f"    fmu_bool_t more = 1, terminate = 0;")
    a(f"    while (more && !terminate) {{")
    a(f"        if (FMU_CALL(m, new_discrete_states, &more, &terminate) > FMU_WARNING)")
    a(f"            return -1;")
    a(f"    }}")
    a(f"    if (terminate) return -1;")
    a(f"    return (FMU_CALL(m, enter_cont_mode) <= FMU_WARNING) ? 0 : -1;")
    a(f"}}")
    a(f"")

    # Inputs escalares no-String: se pueden sobrescribir por CLI (name=val / name@t=val).
    # El nombre CLI es el nombre FMU original (v.name), igual que en el runner de tests.
    cli_inputs = [v for v in inputs if v.type_ in ("Real", "Integer", "Boolean")]

    def _cli_const_parse(v):
        if v.type_ == "Real":    return "atof(_eq+1)"
        return "(atoi(_eq+1) != 0)" if v.type_ == "Boolean" else "atoi(_eq+1)"

    # main
    a(f"int main(int argc, char *argv[])")
    a(f"{{")
    a(f"    SimConfig cfg = get_config();")
    a(f"")
    # ── Override de tiempo/paso/solver por CLI: argv[1]=t_end argv[2]=h argv[3]=solver ──
    # Prioridad sobre get_config(), de modo que la bateria de tests pueda fijar el
    # horizonte y el paso de cada caso (necesario para que los estimulos programados
    # name@t=val caigan dentro de la simulacion). Los tokens name=val se saltan aqui.
    a(f"    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);")
    a(f"    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h     = atof(argv[2]);")
    if info.n_states > 0:
        a(f'    if (argc >= 4 && !strchr(argv[3], \'=\')) cfg.use_rk4 = (strcmp(argv[3], "rk4") == 0);')
    a(f"")
    a(f"    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {{")
    a(f"        SIM_ERROR(\"Error: expected finite t_end >= 0 and h > 0\\n\");")
    a(f"        return 2;")
    a(f"    }}")
    a(f"")

    # ── Override de entradas por CLI (name=val constante, name@t=val programado) ──
    # El valor CLI tiene prioridad sobre get_inputs() del scenario.c, igual que en
    # el loop CS. Permite que la bateria de tests inyecte estimulos en modo ME.
    if cli_inputs:
        a(f"    #define _MAX_SCHED 512")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f"    double _cli_{f} = 0.0; int _has_{f} = 0;")
            a(f"    struct {{ double t; double val; }} _sched_{f}[_MAX_SCHED]; int _ns_{f} = 0;")
        a(f"")
        a(f"    for (int _oi = 1; _oi < argc; _oi++) {{")
        a(f"        char *_at = strchr(argv[_oi], '@');")
        a(f"        char *_eq = strchr(argv[_oi], '=');")
        a(f"        if (!_eq) continue;")
        a(f"        if (_at && _at < _eq) {{")
        a(f"            *_at = '\\0'; *_eq = '\\0';")
        a(f"            double _at_t = atof(_at + 1);")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f'            if (strcmp(argv[_oi], "{v.name}") == 0 && _ns_{f} < _MAX_SCHED) {{')
            a(f"                _sched_{f}[_ns_{f}].t   = _at_t;")
            a(f"                _sched_{f}[_ns_{f}++].val = (double)({_cli_const_parse(v)});")
            a(f"            }}")
        a(f"            *_at = '@'; *_eq = '=';")
        a(f"        }} else {{")
        a(f"            *_eq = '\\0';")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f'            if (strcmp(argv[_oi], "{v.name}") == 0) {{ _cli_{f} = (double)({_cli_const_parse(v)}); _has_{f} = 1; }}')
        a(f"            *_eq = '=';")
        a(f"        }}")
        a(f"    }}")
        a(f"")
    else:
        a(f"    (void)argc; (void)argv;")
        a(f"")

    a(f"    fmu_t *m = {L}_create_me();")
    a(f"    if (m->initialize(m) != FMU_OK) {{")
    a(f"        SIM_ERROR(\"Error: initialize() fallo\\n\");")
    a(f"        return 1;")
    a(f"    }}")
    a(f"")
    a(f"    if (process_events(m) != 0) {{")
    a(f"        SIM_ERROR(\"Error: eventos iniciales\\n\");")
    a(f"        m->terminate(m);")
    a(f"        return 1;")
    a(f"    }}")
    a(f"")

    # VRefs
    for v in inputs:
        f = _safe_field(v.name)
        a(f"    const fmu_vref_t vr_{f} = {U}_VR_{v.define_name};")
    for v in outputs:
        f = _safe_field(v.name)
        a(f"    const fmu_vref_t vr_{f} = {U}_VR_{v.define_name};")
    if inputs or outputs:
        a(f"")

    # Continuous ME: solver and state buffer
    if info.n_states > 0:
        a(f"    fmu_real_t solver_buf[{U}_RK4_BUF_SIZE];")
        a(f"    fmu_solver_t solver;")
        a(f"    fmu_solver_init(&solver, solver_buf,")
        a(f"                   cfg.use_rk4 ? {U}_RK4_BUF_SIZE : {U}_EULER_BUF_SIZE);")
        a(f"")
        a(f"    fmu_real_t x[{U}_N_STATES];")
        a(f"    FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
        a(f"")
        if info.n_event_indicators > 0:
            a(f"    fmu_real_t ei_prev[{U}_N_EVENT_INDICATORS];")
            a(f"    fmu_real_t ei_curr[{U}_N_EVENT_INDICATORS];")
            a(f"    FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
            a(f"")

    # CSV header
    col_names = ["t"] + [v.name for v in inputs] + [v.name for v in outputs]
    a(f'    SIM_PRINT("{",".join(col_names)}\\n");')
    a(f"")

    # Main loop
    a(f"    double t = 0.0;")
    a(f"    for (;;) {{")
    a(f"")

    if inputs:
        a(f"        {ID}_Inputs in = {{0}};")
        a(f"        get_inputs(t, &in);")
        a(f"")
        # Override por CLI: prioridad sobre get_inputs(). Constante (_has) o
        # ultimo schedule vigente (mayor t <= actual).
        if cli_inputs:
            for v in cli_inputs:
                f       = _safe_field(v.name)
                apitype = _api_c_type(v)
                a(f"        if (_has_{f}) in.{f} = ({apitype})_cli_{f};")
                a(f"        if (_ns_{f} > 0) {{")
                a(f"            double _bv = (double)in.{f}; double _bt = -1e300;")
                a(f"            for (int _si = 0; _si < _ns_{f}; _si++)")
                a(f"                if (t >= _sched_{f}[_si].t && _sched_{f}[_si].t >= _bt)")
                a(f"                    {{ _bv = _sched_{f}[_si].val; _bt = _sched_{f}[_si].t; }}")
                a(f"            in.{f} = ({apitype})_bv;")
                a(f"        }}")
            a(f"")

    if info.is_discrete:
        # ME discreto: event mode en cada paso
        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        a(f"        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {{")
        for v in inputs:
            f     = _safe_field(v.name)
            ftype = v.c_type
            setfn = f"set_{v.type_.lower()}"
            if v.type_ == "String":
                # fmi2SetString con NULL provoca segfault en el runtime: pasar "".
                a(f"            {ftype} _i_{f} = (in.{f} ? ({ftype})in.{f} : ({ftype})\"\");")
            else:
                a(f"            {ftype} _i_{f} = ({ftype})in.{f};")
            a(f"            FMU_CALL(m, {setfn}, &vr_{f}, 1, (const {ftype} *)&_i_{f});")
        a(f"            fmu_bool_t more = 1, terminate = 0;")
        a(f"            while (more && !terminate)")
        a(f"                FMU_CALL(m, new_discrete_states, &more, &terminate);")
        a(f"            FMU_CALL(m, enter_cont_mode);")
        a(f"        }}")
        a(f"")
    else:
        # ME continuo: fijar tiempo, entradas y estados antes de leer salidas.
        # IMPORTANTE (FMI 2.0): las entradas DISCRETAS (Boolean/Integer) solo
        # pueden cambiarse en Event Mode. Hacer fmi2SetBoolean/SetInteger en
        # Continuous Time Mode deja el runtime de OpenModelica en un estado
        # invalido y el siguiente fmi2SetTime falla. Por eso los inputs
        # discretos se aplican dentro de un ciclo de eventos y solo los inputs
        # Real (continuos) se fijan en Continuous Time Mode.
        real_inputs     = [v for v in inputs if v.type_ in ("Real",)]
        discrete_inputs = [v for v in inputs if v.type_ in ("Boolean", "Integer")]
        string_inputs   = [v for v in inputs if v.type_ == "String"]

        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        if discrete_inputs:
            a(f"        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {{")
            for v in discrete_inputs:
                f     = _safe_field(v.name)
                ftype = v.c_type
                setfn = f"set_{v.type_.lower()}"
                a(f"            {ftype} _i_{f} = ({ftype})in.{f};")
                a(f"            FMU_CALL(m, {setfn}, &vr_{f}, 1, (const {ftype} *)&_i_{f});")
            a(f"            fmu_bool_t _more = 1, _term = 0;")
            a(f"            while (_more && !_term)")
            a(f"                FMU_CALL(m, new_discrete_states, &_more, &_term);")
            a(f"            FMU_CALL(m, enter_cont_mode);")
            a(f"            FMU_CALL(m, set_time, (fmu_real_t)t);")
            a(f"        }}")
        for v in string_inputs:
            f     = _safe_field(v.name)
            ftype = v.c_type
            a(f"        {{")
            a(f"            {ftype} _i_{f} = (in.{f} ? ({ftype})in.{f} : ({ftype})\"\");")
            a(f"            FMU_CALL(m, set_string, &vr_{f}, 1, (const {ftype} *)&_i_{f});")
            a(f"        }}")
        for v in real_inputs:
            f     = _safe_field(v.name)
            ftype = v.c_type
            a(f"        {{")
            a(f"            {ftype} _i_{f} = ({ftype})in.{f};")
            a(f"            FMU_CALL(m, set_real, &vr_{f}, 1, (const {ftype} *)&_i_{f});")
            a(f"        }}")
        if inputs:
            a(f"")
        a(f"        FMU_CALL(m, set_cont_states, x, {U}_N_STATES);")
        a(f"")

    # Leer salidas
    if outputs:
        a(f"        {ID}_Outputs out = {{0}};")
        for v in outputs:
            f       = _safe_field(v.name)
            ftype   = v.c_type
            getfn   = f"get_{v.type_.lower()}"
            apitype = _api_c_type(v)
            if v.type_ == "Real":
                init = "0.0"
            elif v.type_ == "String":
                init = "NULL"
            else:
                init = "0"
            a(f"        {{")
            a(f"            {ftype} _o_{f} = {init};")
            a(f"            FMU_CALL(m, {getfn}, &vr_{f}, 1, &_o_{f});")
            a(f"            out.{f} = ({apitype})_o_{f};")
            a(f"        }}")
        a(f"        on_outputs(t, &out);")
        a(f"")

    # Fila CSV
    fmt_parts = ["%.10g"]
    val_parts = ["t"]
    for v in inputs:
        f = _safe_field(v.name)
        if v.type_ in ("Boolean", "Integer"):
            fmt_parts.append("%d"); val_parts.append(f"(int)in.{f}")
        elif v.type_ == "String":
            fmt_parts.append("%s"); val_parts.append(f"(in.{f} ? in.{f} : \"\")")
        else:
            fmt_parts.append("%.10g"); val_parts.append(f"in.{f}")
    for v in outputs:
        f = _safe_field(v.name)
        if v.type_ in ("Boolean", "Integer"):
            fmt_parts.append("%d"); val_parts.append(f"(int)out.{f}")
        elif v.type_ == "String":
            fmt_parts.append("%s"); val_parts.append(f"(out.{f} ? out.{f} : \"\")")
        else:
            fmt_parts.append("%.10g"); val_parts.append(f"out.{f}")
    a(f'        SIM_PRINT("{",".join(fmt_parts)}\\n", {", ".join(val_parts)});')
    a(f"")
    a(f"        if (t >= cfg.t_end) break;")
    a(f"        double step = cfg.h;")
    a(f"        if (t + step > cfg.t_end) step = cfg.t_end - t;")
    a(f"        if (m->next_event_time_defined && m->next_event_time > t &&")
    a(f"            m->next_event_time < t + step)")
    a(f"            step = m->next_event_time - t;")
    a(f"")

    # Paso de integracion (solo ME continuo)
    if info.n_states > 0:
        a(f"        if (cfg.use_rk4)")
        a(f"            fmu_rk4_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)step);")
        a(f"        else")
        a(f"            fmu_euler_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)step);")
        a(f"")
        if info.n_event_indicators > 0:
            a(f"        FMU_CALL(m, get_event_indicators, ei_curr, {U}_N_EVENT_INDICATORS);")
            a(f"        fmu_bool_t zero_cross = 0;")
            a(f"        for (int i = 0; i < {U}_N_EVENT_INDICATORS; i++) {{")
            a(f"            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) {{ zero_cross = 1; break; }}")
            a(f"        }}")
            a(f"        for (int i = 0; i < {U}_N_EVENT_INDICATORS; i++)")
            a(f"            ei_prev[i] = ei_curr[i];")
            a(f"")
            a(f"        fmu_bool_t enter_event = 0;")
            a(f"        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {{")
            a(f"            SIM_ERROR(\"Error: fmi2CompletedIntegratorStep failed\\n\");")
            a(f"            break;")
            a(f"        }}")
            a(f"        if (m->termination_requested) break;")
            a(f"        if (enter_event || zero_cross) {{")
            a(f"            if (process_events(m) != 0) break;")
            a(f"            FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"            FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
            a(f"        }}")
        else:
            a(f"        fmu_bool_t enter_event = 0;")
            a(f"        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {{")
            a(f"            SIM_ERROR(\"Error: fmi2CompletedIntegratorStep failed\\n\");")
            a(f"            break;")
            a(f"        }}")
            a(f"        if (m->termination_requested) break;")
            a(f"        if (enter_event) {{")
            a(f"            if (process_events(m) != 0) break;")
            a(f"            FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"        }}")
        a(f"")

    a(f"        t += step;")
    a(f"        SIM_DELAY(step);")
    a(f"    }}")
    a(f"")
    a(f"    m->terminate(m);")
    a(f"    return 0;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


def _generate_main_cs_legacy(info: FMUInfo) -> str:
    """
    Genera main_cs.c: loop de simulacion Co-Simulation.

    La FMU integra internamente: este loop solo llama do_step(t, h).
    No hay solver externo, no hay buffer de estados.
    """
    L = info.lower

    # Para generate_sim_loop, presentamos la FMU como CS-only
    # (has_me=False fuerza el camino do_step en el generador)
    info_cs = dc_replace(info, has_me=False)

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   main_cs.c")
    a(f" * @brief  Loop de simulacion HOST — Co-Simulation — para {info.model_name}.")
    a(f" *")
    a(f" *  El adapter instancia la FMU como CoSimulation.")
    a(f" *  Este loop solo avanza el tiempo: la FMU integra internamente.")
    a(f" *  Para Model Exchange (solver externo Euler/RK4), ver main_me.c.")
    a(f" *")
    a(f" * Modelo : {info.model_name}")
    a(f" * GUID   : {info.guid}")
    a(f" *")
    a(f" * GENERADO por fmu_codegen_host.py — rellena los TODO segun tu aplicacion.")
    a(f" */")
    a(f"")
    a(f"#include <stdio.h>")
    a(f"#include <stdlib.h>")
    a(f"#include <string.h>")
    a(f"#include <math.h>")
    a(f'#include "{L}_adapter.h"')
    a(f"")
    a(f"#ifndef M_PI")
    a(f"#define M_PI 3.14159265358979323846")
    a(f"#endif")
    a(f"")
    a(f"#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)")
    a(f"#define SIM_DELAY(h)         ((void)(h))")
    a(f"#define SIM_ERROR(msg)       fprintf(stderr, \"%s\", msg)")
    a(f"")

    a(generate_sim_loop(info_cs, f"{L}_create_cs()", csv_output=True, cli_args=True))

    return "\n".join(lines)


def generate_main_cs(info: FMUInfo) -> str:
    """Generate the typed CS loop that shares the user-owned scenario with ME."""
    L, U, ID = info.lower, info.upper, info.model_identifier
    inputs = info.vars_of_causality("input")
    outputs = info.vars_of_causality("output")
    cli_inputs = [v for v in inputs if v.type_ in ("Real", "Integer", "Boolean")]

    def cli_value(v):
        if v.type_ == "Real":
            return "atof(_eq + 1)"
        if v.type_ == "Boolean":
            return "(atoi(_eq + 1) != 0)"
        return "atoi(_eq + 1)"

    lines = []
    a = lines.append
    a("/**")
    a(f" * @file main_cs.c -- generated typed Co-Simulation loop for {info.model_name}.")
    a(" * scenario.c is shared by the ME and CS executables.")
    a(" */")
    a("#include <stdio.h>")
    a("#include <stdlib.h>")
    a("#include <string.h>")
    a("#include <math.h>")
    a(f'#include "{L}_api.h"')
    a(f'#include "{L}_adapter.h"')
    a("")
    a('#define SIM_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)')
    a('#define SIM_ERROR(msg) fprintf(stderr, "%s", msg)')
    a('#define SIM_DELAY(h) ((void)(h))')
    a("")
    a("int main(int argc, char *argv[])")
    a("{")
    a("    SimConfig cfg = get_config();")
    a("    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);")
    a("    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h = atof(argv[2]);")
    a("    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {")
    a('        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\\n");')
    a("        return 2;")
    a("    }")
    a("")

    if cli_inputs:
        a("    #define MAX_SCHEDULE 512")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f"    double cli_{f} = 0.0; int has_{f} = 0;")
            a(f"    struct {{ double t; double val; }} sched_{f}[MAX_SCHEDULE]; int ns_{f} = 0;")
        a("    for (int oi = 1; oi < argc; oi++) {")
        a("        char *_at = strchr(argv[oi], '@');")
        a("        char *_eq = strchr(argv[oi], '=');")
        a("        if (!_eq) continue;")
        a("        if (_at && _at < _eq) {")
        a("            *_at = '\\0'; *_eq = '\\0';")
        a("            double at_t = atof(_at + 1);")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f'            if (strcmp(argv[oi], "{v.name}") == 0 && ns_{f} < MAX_SCHEDULE) {{')
            a(f"                sched_{f}[ns_{f}].t = at_t;")
            a(f"                sched_{f}[ns_{f}++].val = (double)({cli_value(v)});")
            a("            }")
        a("            *_at = '@'; *_eq = '=';")
        a("        } else {")
        a("            *_eq = '\\0';")
        for v in cli_inputs:
            f = _safe_field(v.name)
            a(f'            if (strcmp(argv[oi], "{v.name}") == 0) {{ cli_{f} = (double)({cli_value(v)}); has_{f} = 1; }}')
        a("            *_eq = '=';")
        a("        }")
        a("    }")
    else:
        a("    (void)argc; (void)argv;")
    a("")
    a(f"    fmu_t *m = {L}_create_cs();")
    a("    if (m->initialize(m) > FMU_WARNING) {")
    a('        SIM_ERROR("Error: initialize() failed\\n");')
    a("        return 1;")
    a("    }")
    for v in inputs:
        a(f"    const fmu_vref_t vr_{_safe_field(v.name)} = {U}_VR_{v.define_name};")
    for v in outputs:
        a(f"    const fmu_vref_t vr_{_safe_field(v.name)} = {U}_VR_{v.define_name};")
    a("")
    columns = ["t"] + [v.name for v in inputs] + [v.name for v in outputs]
    a(f'    SIM_PRINT("{",".join(columns)}\\n");')
    a("    double t = 0.0;")
    a("    for (;;) {")

    if inputs:
        a(f"        {ID}_Inputs in = {{0}};")
        a("        get_inputs(t, &in);")
        for v in cli_inputs:
            f, ct = _safe_field(v.name), _api_c_type(v)
            a(f"        if (has_{f}) in.{f} = ({ct})cli_{f};")
            a(f"        if (ns_{f} > 0) {{")
            a(f"            double best = (double)in.{f}; double best_t = -1e300;")
            a(f"            for (int si = 0; si < ns_{f}; si++)")
            a(f"                if (t >= sched_{f}[si].t && sched_{f}[si].t >= best_t)")
            a(f"                    {{ best = sched_{f}[si].val; best_t = sched_{f}[si].t; }}")
            a(f"            in.{f} = ({ct})best;")
            a("        }")
        for v in inputs:
            f, ft = _safe_field(v.name), v.c_type
            if v.type_ == "String":
                a(f"        {ft} set_{f} = in.{f} ? ({ft})in.{f} : ({ft})\"\";")
            else:
                a(f"        {ft} set_{f} = ({ft})in.{f};")
            a(f"        if (FMU_CALL(m, set_{v.type_.lower()}, &vr_{f}, 1, (const {ft} *)&set_{f}) > FMU_WARNING) {{")
            a(f'            SIM_ERROR("Error: setting input {v.name} failed\\n");')
            a("            m->terminate(m); return 1;")
            a("        }")

    if outputs:
        a(f"        {ID}_Outputs out = {{0}};")
        for v in outputs:
            f, ft, at = _safe_field(v.name), v.c_type, _api_c_type(v)
            init = "0.0" if v.type_ == "Real" else ("NULL" if v.type_ == "String" else "0")
            a(f"        {ft} got_{f} = {init};")
            a(f"        if (FMU_CALL(m, get_{v.type_.lower()}, &vr_{f}, 1, &got_{f}) > FMU_WARNING) {{")
            a(f'            SIM_ERROR("Error: reading output {v.name} failed\\n");')
            a("            m->terminate(m); return 1;")
            a("        }")
            a(f"        out.{f} = ({at})got_{f};")
        a("        on_outputs(t, &out);")

    formats, values = ["%.10g"], ["t"]
    for variables, obj in ((inputs, "in"), (outputs, "out")):
        for v in variables:
            f = _safe_field(v.name)
            if v.type_ in ("Boolean", "Integer"):
                formats.append("%d"); values.append(f"(int){obj}.{f}")
            elif v.type_ == "String":
                formats.append("%s"); values.append(f"({obj}.{f} ? {obj}.{f} : \"\")")
            else:
                formats.append("%.10g"); values.append(f"{obj}.{f}")
    a(f'        SIM_PRINT("{",".join(formats)}\\n", {", ".join(values)});')
    a("        if (t >= cfg.t_end) break;")
    a("        double step = cfg.h;")
    a("        if (t + step > cfg.t_end) step = cfg.t_end - t;")
    a("        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {")
    a('            SIM_ERROR("Error: fmi2DoStep failed\\n");')
    a("            m->terminate(m); return 1;")
    a("        }")
    a("        t += step;")
    a("        SIM_DELAY(step);")
    a("    }")
    a("    m->terminate(m);")
    a("    return 0;")
    a("}")
    return "\n".join(lines) + "\n"


# =============================================================================
# CMakeLists.txt  (host/) — dos targets
# =============================================================================

def generate_cmake_host(info: FMUInfo, fmu_dir: str) -> str:
    """
    Genera CMakeLists.txt con un target por modo soportado:
      <modelo>_host_me  — si has_me
      <modelo>_host_cs  — si has_cs
    Ambos compilan contra las mismas fuentes FMU y comparten recursos.
    """
    # Rutas a las fuentes/recursos del FMU expresadas RELATIVAS a la raiz del
    # repositorio (el directorio que contiene models/ y examples/), de modo que
    # el proyecto generado sea reproducible al clonarlo en cualquier ubicacion.
    # En CMake se resuelven contra ${FMU2HOST_ROOT}, definido en el CMakeLists
    # raiz como ${CMAKE_SOURCE_DIR}. Se mantiene la ruta absoluta solo como
    # respaldo si el FMU queda fuera del arbol del repositorio.
    L = info.lower
    sources_dir_abs = os.path.abspath(os.path.join(fmu_dir, "sources"))
    repo_root = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))

    def _repo_relative(path_abs: str) -> str:
        """Devuelve '${FMU2HOST_ROOT}/<rel>' si path esta bajo la raiz; si no, ruta absoluta."""
        try:
            rel = os.path.relpath(path_abs, repo_root)
        except ValueError:
            rel = None
        if rel is None or rel.startswith(".."):
            return path_abs.replace(os.sep, "/")
        return "${FMU2HOST_ROOT}/" + rel.replace(os.sep, "/")

    sources_abs = _repo_relative(sources_dir_abs)

    known_include_subdirs = ["fmi", "fmi-export", "fmi2", "include"]
    found_subdirs = [
        d for d in known_include_subdirs
        if os.path.isdir(os.path.join(fmu_dir, "sources", d))
    ]

    res_dir   = os.path.join(fmu_dir, "resources")
    res_files = sorted(
        f for f in os.listdir(res_dir)
        if os.path.isfile(os.path.join(res_dir, f))
    ) if os.path.isdir(res_dir) else []
    has_res = bool(res_files)
    res_abs = _repo_relative(os.path.abspath(res_dir)) if has_res else ""

    is_omc = "OpenModelica" in info.generation_tool

    targets = []
    if info.has_me:
        targets.append(("me", f"main_me.c", f"{L}_adapter_me.c"))
    if info.has_cs:
        targets.append(("cs", f"main_cs.c", f"{L}_adapter_cs.c"))

    lines = []
    a = lines.append

    a(f"# CMakeLists.txt — HOST example: {info.model_name}")
    a(f"# Generado por fmu_codegen_host.py.")
    a(f"# Herramienta: {info.generation_tool}")
    a(f"#")
    a(f"# Targets:")
    for mode, _, _ in targets:
        a(f"#   {L}_host_{mode}  — instancia como {'ModelExchange' if mode=='me' else 'CoSimulation'}")
    a(f"")
    a(f"cmake_minimum_required(VERSION 3.16)")
    a(f"")
    # FMU2HOST_ROOT: raiz del repo. Definida normalmente por el CMakeLists raiz;
    # el fallback permite construir este subdirectorio de forma aislada.
    a(f"if(NOT DEFINED FMU2HOST_ROOT)")
    a(f'    get_filename_component(FMU2HOST_ROOT "${{CMAKE_CURRENT_SOURCE_DIR}}/../../.." ABSOLUTE)')
    a(f"endif()")
    a(f"")
    a(f'set(FMU_SRC "{sources_abs}")')
    a(f'file(GLOB_RECURSE FMU_SOURCES "${{FMU_SRC}}/*.c")')
    a(f"")

    if is_omc:
        a(f"# Parche MSVC: 'const int x[0] = {{}}' (C2466) generado por OpenModelica")
        a(f"if(MSVC)")
        a(f"    foreach(_SRC ${{FMU_SOURCES}})")
        a(f'        file(READ "${{_SRC}}" _CONTENT)')
        a(f'        string(FIND "${{_CONTENT}}" "[0] = {{}}" _ZERO_ARR)')
        a(f'        if(NOT _ZERO_ARR EQUAL -1)')
        a(f'            get_filename_component(_NAME "${{_SRC}}" NAME_WE)')
        a(f'            set(_FIXED "${{CMAKE_CURRENT_BINARY_DIR}}/${{_NAME}}_msvc.c")')
        a(f'            string(REPLACE "const int columns[0] = {{}};"')
        a(f'                           "const int columns[1] = {{0}};" _CONTENT "${{_CONTENT}}")')
        a(f'            string(REPLACE "const int rows[0] = {{}};"')
        a(f'                           "const int rows[1] = {{0}};" _CONTENT "${{_CONTENT}}")')
        a(f'            file(WRITE "${{_FIXED}}" "${{_CONTENT}}")')
        a(f'            list(REMOVE_ITEM FMU_SOURCES "${{_SRC}}")')
        a(f'            list(APPEND FMU_SOURCES "${{_FIXED}}")')
        a(f'        endif()')
        a(f"    endforeach()")
        a(f"endif()")
        a(f"")

    # Un bloque add_executable por target
    for mode, main_file, adapter_file in targets:
        tgt = f"{L}_host_{mode}"
        a(f"# -- Target {tgt} {'(Model Exchange)' if mode=='me' else '(Co-Simulation)'} --")
        a(f"add_executable({tgt}")
        a(f"    {main_file}")
        a(f"    scenario.c")
        a(f"    {adapter_file}")
        a(f"    ${{FMU_SOURCES}}")
        a(f")")
        a(f"target_include_directories({tgt} PRIVATE")
        a(f'    "${{FMU_SRC}}"')
        for sd in found_subdirs:
            a(f'    "${{FMU_SRC}}/{sd}"')
        a(f'    "${{CMAKE_CURRENT_SOURCE_DIR}}"')
        a(f")")
        a(f"target_link_libraries({tgt} PRIVATE fmi)")
        a(f"target_compile_definitions({tgt} PRIVATE")
        a(f"    FMI2_FUNCTION_PREFIX={info.identifier_for(mode)}_")
        a(f")")
        a(f"if(WIN32)")
        a(f"    target_link_libraries({tgt} PRIVATE ws2_32)")
        a(f"endif()")

        if has_res:
            a(f"")
            for bf in res_files:
                a(f'configure_file("{res_abs}/{bf}"')
                a(f'    "${{CMAKE_CURRENT_BINARY_DIR}}/{bf}" COPYONLY)')
                a(f"add_custom_command(TARGET {tgt} POST_BUILD")
                a(f"    COMMAND ${{CMAKE_COMMAND}} -E copy_if_different")
                a(f'        "{res_abs}/{bf}"')
                a(f'        "$<TARGET_FILE_DIR:{tgt}>/{bf}"')
                a(f'    COMMENT "Copiando {bf}"')
                a(f")")
            a(f"set_target_properties({tgt} PROPERTIES")
            a(f'    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:{tgt}>"')
            a(f")")

        a(f"")
        if has_res:
            a(f"add_test(NAME {tgt} COMMAND {tgt}")
            a(f'    WORKING_DIRECTORY "$<TARGET_FILE_DIR:{tgt}>")')
        else:
            a(f"add_test(NAME {tgt} COMMAND {tgt})")
        a(f"")

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

    os.makedirs(output_dir, exist_ok=True)

    print(f"[host] Parseando {os.path.join(fmu_dir, 'modelDescription.xml')} ...")
    info = parse_fmu(fmu_dir)

    mode_str = (("CS" if info.has_cs else "") +
                ("/" if info.has_cs and info.has_me else "") +
                ("ME" if info.has_me else ""))
    print(f"[host] Modelo    : {info.model_name}")
    print(f"[host] Modo      : {mode_str}  |  Estados: {info.n_states}  |  Variables: {len(info.variables)}")

    def write_always(path, content, tag="Generado"):
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"[host] {tag:<10}: {path}")

    def write_if_new(path, content):
        if not os.path.exists(path):
            with open(path, "w", encoding="utf-8") as f:
                f.write(content)
            print(f"[host] Generado  : {path}")
        else:
            print(f"[host] Conservado: {path}  (ya existe)")

    # 1. Header compartido del adapter
    write_always(os.path.join(output_dir, f"{info.lower}_adapter.h"),
                 generate_adapter_header(info, fmu_dir))

    # 1b. API header (structs Inputs / Outputs / SimConfig)
    write_always(os.path.join(output_dir, f"{info.lower}_api.h"),
                 generate_api_header(info))

    # 2. Adapters por modo
    if info.has_me:
        write_always(os.path.join(output_dir, f"{info.lower}_adapter_me.c"),
                     generate_adapter_me(info, fmu_dir))
    if info.has_cs:
        write_always(os.path.join(output_dir, f"{info.lower}_adapter_cs.c"),
                     generate_adapter_cs(info, fmu_dir))

    # 3. CMakeLists (siempre se sobreescribe)
    write_always(os.path.join(output_dir, "CMakeLists.txt"),
                 generate_cmake_host(info, fmu_dir))

    # 4. main_me.c (siempre se sobreescribe — auto-generado, no editar)
    if info.has_me:
        write_always(os.path.join(output_dir, "main_me.c"),
                     generate_main_me(info))

    # 4b. scenario.c (solo si no existe — el usuario lo edita)
    write_if_new(os.path.join(output_dir, "scenario.c"),
                 generate_scenario_me(info))

    # 4c. main_cs.c (siempre derivado de metadatos; scenario.c sigue preservado)
    if info.has_cs:
        write_always(os.path.join(output_dir, "main_cs.c"),
                     generate_main_cs(info))

    # 5. Registrar en CMakeLists padre
    register_in_parent_cmake(output_dir)

    targets = []
    if info.has_me:
        targets.append(f"{info.lower}_host_me")
    if info.has_cs:
        targets.append(f"{info.lower}_host_cs")

    print(f"")
    print(f"[host] Targets generados: {', '.join(targets)}")
    print(f"[host] Siguiente paso:")
    if info.has_me:
        print(f"       1. Edita scenario.c para ajustar get_config() y get_inputs()")
    for t in targets:
        print(f"       2. cmake --build <build_dir> --target {t}")


if __name__ == "__main__":
    main()
