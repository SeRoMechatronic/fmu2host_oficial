#!/usr/bin/env python3
"""
fmu_codegen.py — Generador de adaptadores fmu_t desde FMUs source-code FMI 2.0

Uso:
    python fmu_codegen.py <fmu_o_dir> <output_dir>

<fmu_o_dir>  Ruta al archivo .fmu (ZIP) O a un directorio ya descomprimido.
             Si se pasa un .fmu, se descomprime automáticamente junto al archivo.
<output_dir> Directorio donde se escriben los archivos generados.

Genera (4 archivos):
    <modelo>_adapter.h    Constantes VR_*, metadatos, declaración de create()
    <modelo>_adapter.c    Implementación del wrapper fmu_t (WRAPPING, no editar)
    CMakeLists.txt        Build del ejemplo (sobreescrito en cada ejecución)
    main.c                Esqueleto del loop de simulación (solo si no existe ya)

Estrategia: WRAPPING
    El adapter generado delega todas las operaciones a las funciones FMI 2.0
    ya implementadas en el source de la FMU ({ModelIdentifier}_fmi2GetReal, etc.).
    No reimplementa ecuaciones — es un puente genérico y universal.

    Tipos FMI soportados: Real, Integer, Boolean, String
    Modos soportados: CoSimulation, ModelExchange, ambos

Requisitos:
    - Python 3.8+
    - Sin dependencias externas (solo stdlib)
"""

import sys
import os
import re
import zipfile
import xml.etree.ElementTree as ET
from dataclasses import dataclass, field
from typing import Optional, List


# =============================================================================
# Estructuras de datos
# =============================================================================

@dataclass
class Variable:
    name: str
    vr: int
    causality: str    # input | output | parameter | local | independent
    variability: str  # constant | fixed | tunable | discrete | continuous
    type_: str        # Real | Integer | Boolean | String
    start: Optional[str] = None

    @property
    def define_name(self) -> str:
        """Nombre del #define para el valueReference (limpio, mayúsculas, sin caracteres especiales)."""
        safe = (self.name.upper()
                .replace(".", "_")
                .replace("(", "_").replace(")", "")   # der(x) -> DER_X
                .replace("[", "_").replace("]", "")
                .replace(",", "_")                    # A[1,1] -> A_1_1
                .replace(" ", "_"))
        # Eliminar guiones bajos dobles y finales
        while "__" in safe:
            safe = safe.replace("__", "_")
        return safe.strip("_")

    @property
    def c_type(self) -> str:
        """Tipo C propio (fmu_*_t) correspondiente al tipo FMI."""
        mapping = {
            "Real":    "fmu_real_t",
            "Integer": "fmu_int_t",
            "Boolean": "fmu_bool_t",
            "String":  "fmu_string_t",
        }
        return mapping.get(self.type_, "fmu_real_t")

    @property
    def fmi2_type(self) -> str:
        """Tipo C del SDK FMI 2.0 correspondiente."""
        mapping = {
            "Real":    "fmi2Real",
            "Integer": "fmi2Integer",
            "Boolean": "fmi2Boolean",
            "String":  "fmi2String",
        }
        return mapping.get(self.type_, "fmi2Real")


@dataclass
class FMUInfo:
    model_name: str
    model_identifier: str
    guid: str
    description: str
    generation_tool: str    # herramienta de modelado (OpenModelica, Dymola, etc.)
    has_cs: bool
    has_me: bool
    n_states: int
    n_event_indicators: int
    variables: List[Variable] = field(default_factory=list)

    @property
    def prefix(self) -> str:
        """Prefijo de funciones FMI: ModelIdentifier_ (ej. RCFilter_)"""
        return self.model_identifier + "_"

    @property
    def lower(self) -> str:
        return self.model_identifier.lower()

    @property
    def upper(self) -> str:
        return self.model_identifier.upper()

    @property
    def mode_define(self) -> str:
        """ME tiene preferencia sobre CS en MCU (solver propio = más control)."""
        return "FMU_MODE_ME" if self.has_me else "FMU_MODE_CS"

    @property
    def fmi2_type_enum(self) -> str:
        """ME tiene prioridad: el adapter usa mode_define=ME → instanciar como ME."""
        if self.has_me:
            return "fmi2ModelExchange"
        return "fmi2CoSimulation"

    @property
    def is_discrete(self) -> bool:
        """True si el modelo ME no tiene estados continuos (puramente algebraico)."""
        return self.has_me and self.n_states == 0

    def vars_of_causality(self, causality: str) -> List[Variable]:
        return [v for v in self.variables if v.causality == causality]

    def has_type(self, type_: str) -> bool:
        return any(v.type_ == type_ for v in self.variables)

    def first_input(self) -> Optional[Variable]:
        """Primera variable de tipo input (para el template de main.c)."""
        return next((v for v in self.variables if v.causality == "input"), None)

    def first_output(self) -> Optional[Variable]:
        """Primera variable de tipo output (para el template de main.c)."""
        return next((v for v in self.variables if v.causality == "output"), None)


# =============================================================================
# Parser de modelDescription.xml
# =============================================================================

def parse_fmu(fmu_dir: str) -> FMUInfo:
    """Lee modelDescription.xml y devuelve FMUInfo con todos los metadatos."""
    xml_path = os.path.join(fmu_dir, "modelDescription.xml")
    if not os.path.exists(xml_path):
        raise FileNotFoundError(f"No se encontró: {xml_path}")

    tree = ET.parse(xml_path)
    root = tree.getroot()

    # Atributos raíz
    model_name       = root.get("modelName", "UnknownModel")
    guid             = root.get("guid", "{00000000-0000-0000-0000-000000000000}")
    description      = root.get("description", "")
    generation_tool  = root.get("generationTool", "")
    n_event_ind      = int(root.get("numberOfEventIndicators", "0"))

    # Modo: CoSimulation / ModelExchange
    has_cs = root.find("CoSimulation")  is not None
    has_me = root.find("ModelExchange") is not None

    if not has_cs and not has_me:
        raise ValueError("La FMU no declara CoSimulation ni ModelExchange.")

    # ModelIdentifier (puede diferir de modelName)
    if has_me:
        model_identifier = root.find("ModelExchange").get("modelIdentifier", model_name)
    else:
        model_identifier = root.find("CoSimulation").get("modelIdentifier", model_name)

    # Número de estados continuos: contamos <Unknown> en <Derivatives>
    n_states = 0
    structure = root.find("ModelStructure")
    if structure is not None:
        derivatives = structure.find("Derivatives")
        if derivatives is not None:
            n_states = len(list(derivatives))

    # Variables escalares
    variables = []
    for sv in root.findall(".//ScalarVariable"):
        name        = sv.get("name", "unknown")
        vr          = int(sv.get("valueReference", 0))
        causality   = sv.get("causality", "local")
        variability = sv.get("variability", "continuous")

        # Tipo y valor start (busca el primer hijo con nombre de tipo FMI)
        type_ = "Real"
        start = None
        for t in ("Real", "Integer", "Boolean", "String"):
            elem = sv.find(t)
            if elem is not None:
                type_ = t
                start = elem.get("start")
                break

        variables.append(Variable(
            name=name, vr=vr, causality=causality,
            variability=variability, type_=type_, start=start,
        ))

    # Ordenar por valueReference para que los #define sean legibles
    variables.sort(key=lambda v: v.vr)

    return FMUInfo(
        model_name=model_name,
        model_identifier=model_identifier,
        guid=guid,
        description=description,
        generation_tool=generation_tool,
        has_cs=has_cs,
        has_me=has_me,
        n_states=n_states,
        n_event_indicators=n_event_ind,
        variables=variables,
    )


# =============================================================================
# Generador del header  (<modelo>_adapter.h)
# =============================================================================

def generate_header(info: FMUInfo, fmu_dir: str) -> str:
    """
    Genera el archivo .h con:
      - #define de metadatos (nombre, GUID, modo, estados)
      - #define de tamaños de buffer de solver
      - #define VR_* por variable, agrupados por causalidad
      - declaración de la función create()
    """
    U = info.upper
    L = info.lower
    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_adapter.h")
    a(f" * @brief  Interfaz fmu_t para {info.model_name} (AUTO-GENERADO por fmu_codegen.py).")
    a(f" *         Contiene constantes VR_*, tamanios de buffer de solver y la")
    a(f" *         declaracion de {L}_create().")
    a(f" * @note   No editar manualmente. Regenerar con fmu_codegen.py.")
    a(f" */")
    a(f"")
    a(f"#ifndef {U}_ADAPTER_H")
    a(f"#define {U}_ADAPTER_H")
    a(f"")
    a(f'#include "fmu_t.h"')
    a(f'#include "fmu_solver.h"')
    a(f"")

    # ── Metadatos ──────────────────────────────────────────────────────────────
    a(f"/** @defgroup {L}_meta Metadatos del modelo")
    a(f" *  @{{")
    a(f" */")
    a(f'#define {U}_MODEL_NAME          "{info.model_name}" /*!< Nombre del modelo FMI */')
    a(f'#define {U}_GUID                "{info.guid}" /*!< GUID unico de esta version del modelo */')
    a(f'#define {U}_N_STATES            {info.n_states} /*!< Numero de estados continuos */')
    a(f'#define {U}_N_EVENT_INDICATORS  {info.n_event_indicators} /*!< Numero de indicadores de evento */')
    a(f'#define {U}_MODE                {info.mode_define} /*!< Modo FMI soportado */')
    a(f"/** @}} */")
    a(f"")

    # ── Tamaños de buffer para solvers ─────────────────────────────────────────
    a(f"/** @defgroup {L}_solver Tamanios de buffer para solvers")
    a(f" *  Solo relevantes en FMU_MODE_ME.")
    a(f" *  @{{")
    a(f" */")
    a(f"#define {U}_EULER_BUF_SIZE  FMU_EULER_WORK_SIZE({U}_N_STATES) /*!< Buffer Euler: n_states elementos */")
    a(f"#define {U}_RK4_BUF_SIZE    FMU_RK4_WORK_SIZE({U}_N_STATES)   /*!< Buffer RK4: 5*n_states elementos (k1,k2,k3,k4,x_tmp) */")
    a(f"/** @}} */")
    a(f"")

    # ── ValueReferences agrupados por causalidad ───────────────────────────────
    groups = [
        ("Entradas",              "input"),
        ("Salidas",               "output"),
        ("Parametros",            "parameter"),
        ("Parametros calculados", "calculatedParameter"),
        ("Locales",               "local"),
    ]
    a(f"/** @defgroup {L}_vr ValueReferences (de modelDescription.xml)")
    a(f" *  @{{")
    a(f" */")
    for label, causality in groups:
        group = [v for v in info.variables if v.causality == causality]
        if not group:
            continue
        a(f"/** @name {label} */")
        a(f"/** @{{ */")
        for v in group:
            define = f"{U}_VR_{v.define_name}"
            comment = f"{v.type_}, {v.causality}, {v.variability}"
            if v.start is not None:
                comment += f", start={v.start}"
            a(f"#define {define:<48} {v.vr}u   /*!< {comment} */")
        a(f"/** @}} */")
        a(f"")
    a(f"/** @}} */")
    a(f"")

    # ── Punto de entrada ───────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief  Obtiene la instancia singleton del modelo {info.model_name}.")
    a(f" * @return Puntero a la interfaz fmu_t lista para inicializar.")
    a(f" * @note   La instancia es estatica. Llama a initialize() antes de usar.")
    a(f" * @note   Para multiples instancias del mismo modelo, adaptar a malloc.")
    a(f" */")
    a(f"fmu_t *{L}_create(void);")
    a(f"")
    a(f"#endif /* {U}_ADAPTER_H */")

    return "\n".join(lines) + "\n"


# =============================================================================
# Generador del source  (<modelo>_adapter.c)
# =============================================================================

def generate_source(info: FMUInfo, fmu_dir: str) -> str:
    """
    Genera el archivo .c con:
      - Declaraciones extern de las funciones FMI 2.0 del modelo
      - Callbacks (logger, allocateMemory/freeMemory para host)
      - Struct concreto { fmu_t base; fmi2Component inst; }
      - Implementaciones de todos los punteros de fmu_t
      - Instancia estática y función create()
    """
    U = info.upper
    L = info.lower
    P = info.prefix   # "RCFilter_"

    # El resource URI se computa en runtime (ver _compute_res_uri en el adapter generado).
    # CMake copia los recursos junto al exe, así el directorio del exe == directorio de recursos.

    lines = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_adapter.c")
    a(f" * @brief  Wrapper fmu_t para {info.model_name} (AUTO-GENERADO por fmu_codegen.py).")
    a(f" *         Delega todas las operaciones a las funciones FMI 2.0 del modelo.")
    a(f" * @note   No editar manualmente. Regenerar con fmu_codegen.py.")
    a(f" */")
    a(f"/* Fuente: {os.path.abspath(fmu_dir)} */")
    a(f"")
    a(f'#include <stdlib.h>   /* calloc, free — host; sustituir por pool en MCU */')
    a(f'#include <stdio.h>    /* fprintf, vfprintf */')
    a(f'#include <stdarg.h>   /* va_list, va_start, va_end */')
    a(f'#include <stddef.h>   /* size_t */')
    a(f'#include <string.h>   /* strrchr */')
    a(f"")
    a(f'#include "fmi2_api.h"')
    a(f'#include "fmu_t.h"')
    a(f'#include "{L}_adapter.h"')
    a(f"")

    # ── Externs ────────────────────────────────────────────────────────────────
    a(f"/* =========================================================================")
    a(f" * Funciones FMI 2.0 implementadas en el source de la FMU.")
    a(f" * Se compilan por separado — ver CMakeLists.txt del ejemplo.")
    a(f" * El prefijo {P} viene del campo modelIdentifier en modelDescription.xml.")
    a(f" * ========================================================================= */")
    a(f"")

    # Ciclo de vida — siempre necesarias
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

    # Co-Simulation
    if info.has_cs:
        a(f"/* Co-Simulation: la FMU integra internamente paso a paso */")
        a(f"extern fmi2Status {P}fmi2DoStep(")
        a(f"    fmi2Component, fmi2Real, fmi2Real, fmi2Boolean);")
        a(f"")

    # Model Exchange
    if info.has_me:
        a(f"/* Model Exchange: el llamador integra con su propio solver */")
        a(f"extern fmi2Status {P}fmi2SetTime(fmi2Component, fmi2Real);")
        a(f"extern fmi2Status {P}fmi2SetContinuousStates(fmi2Component, const fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2GetDerivatives(fmi2Component, fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2GetContinuousStates(fmi2Component, fmi2Real *, size_t);")
        a(f"extern fmi2Status {P}fmi2CompletedIntegratorStep(")
        a(f"    fmi2Component, fmi2Boolean, fmi2Boolean *, fmi2Boolean *);")
        a(f"/* Gestion de eventos discretos */")
        a(f"extern fmi2Status {P}fmi2EnterEventMode(fmi2Component);")
        a(f"extern fmi2Status {P}fmi2NewDiscreteStates(fmi2Component, fmi2EventInfo *);")
        a(f"extern fmi2Status {P}fmi2EnterContinuousTimeMode(fmi2Component);")
        a(f"extern fmi2Status {P}fmi2GetEventIndicators(fmi2Component, fmi2Real *, size_t);")
        a(f"")

    # Get/Set por tipo — solo los que aparecen en el modelo
    for type_ in ("Real", "Integer", "Boolean", "String"):
        if not info.has_type(type_):
            continue
        fmi2t = Variable("", 0, "", "", type_).fmi2_type
        a(f"extern fmi2Status {P}fmi2Get{type_}(")
        a(f"    fmi2Component, const fmi2ValueReference *, size_t, {fmi2t} *);")
        a(f"extern fmi2Status {P}fmi2Set{type_}(")
        a(f"    fmi2Component, const fmi2ValueReference *, size_t, const {fmi2t} *);")
        a(f"")

    # ── Callbacks ──────────────────────────────────────────────────────────────
    a(f"/* =========================================================================")
    a(f" * Callbacks para fmi2Instantiate.")
    a(f" * Host (PC): usa calloc/free de stdlib.")
    a(f" * MCU: sustituir allocateMemory por un pool estatico y freeMemory por noop.")
    a(f" * ========================================================================= */")
    a(f"")
    a(f"static void _logger(fmi2ComponentEnvironment env, fmi2String inst,")
    a(f"                    fmi2Status status, fmi2String cat,")
    a(f"                    fmi2String msg, ...) {{")
    a(f"    (void)env; (void)inst; (void)status;")
    a(f"    va_list args;")
    a(f"    va_start(args, msg);")
    a(f"    fprintf(stderr, \"[{info.model_name}/%s] \", cat);")
    a(f"    vfprintf(stderr, msg, args);")
    a(f"    fprintf(stderr, \"\\n\");")
    a(f"    va_end(args);")
    a(f"}}")
    a(f"")
    a(f"static const fmi2CallbackFunctions _callbacks = {{")
    a(f"    .logger               = _logger,")
    a(f"    .allocateMemory       = calloc,  /* MCU: pool estatico */")
    a(f"    .freeMemory           = free,    /* MCU: noop          */")
    a(f"    .stepFinished         = NULL,    /* solo para CS async */")
    a(f"    .componentEnvironment = NULL,")
    a(f"}};")
    a(f"")

    # ── Struct concreto ────────────────────────────────────────────────────────
    a(f"/* =========================================================================")
    a(f" * Struct concreto — 'base' DEBE ser el primer campo para que el cast")
    a(f" * (fmu_t *) -> ({L}_t *) sea valido en C (mismo inicio de memoria).")
    a(f" * ========================================================================= */")
    a(f"")
    a(f"typedef struct {{")
    a(f"    fmu_t         base;   /* primer campo: misma dir. que {L}_t * */")
    a(f"    fmi2Component inst;   /* handle opaco de la instancia FMI     */")
    a(f"}} {L}_t;")
    a(f"")
    a(f"/* Cast seguro: fmu_t* → {L}_t* (valido porque base es el primer campo) */")
    a(f"#define SELF(p)  (({L}_t *)(p))")
    a(f"")
    a(f"/* =========================================================================")
    a(f" * _compute_res_uri — calcula en runtime el directorio del ejecutable.")
    a(f" * CMake copia los recursos junto al exe, por lo que ese directorio")
    a(f" * ES el directorio de recursos. Sin paths hardcodeados: portable entre maquinas.")
    a(f" * ========================================================================= */")
    a(f"#if defined(_WIN32)")
    a(f"#  include <windows.h>")
    a(f"static void _compute_res_uri(char *out, size_t n) {{")
    a(f"    char buf[MAX_PATH];")
    a(f"    GetModuleFileNameA(NULL, buf, MAX_PATH);")
    a(f"    char *sep = strrchr(buf, '\\\\');")
    a(f"    if (sep) *sep = '\\0';")
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

    # ── Implementaciones ───────────────────────────────────────────────────────
    a(f"/* =========================================================================")
    a(f" * Implementaciones de los punteros de fmu_t")
    a(f" * Todas delegan directamente a las funciones FMI del modelo (WRAPPING).")
    a(f" * ========================================================================= */")
    a(f"")

    # initialize
    a(f"/** @brief Instancia la FMU, configura el experimento y sale del modo inicializacion. */")
    a(f"static fmu_status_t _initialize(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    char _res_uri[4096];")
    a(f"    _compute_res_uri(_res_uri, sizeof(_res_uri));")
    a(f"    /* Instanciar la FMU — el GUID identifica univocamente la version del modelo */")
    a(f"    c->inst = {P}fmi2Instantiate(")
    a(f"        {U}_MODEL_NAME, {info.fmi2_type_enum},")
    a(f"        {U}_GUID, _res_uri,")
    a(f"        &_callbacks, fmi2False, fmi2False);")
    a(f"    if (!c->inst) return FMU_ERROR;")
    a(f"")
    a(f"    /* Configurar experimento con valores neutros; ajustar si la FMU lo requiere */")
    a(f"    {P}fmi2SetupExperiment(c->inst, fmi2False, 0.0, 0.0, fmi2False, 0.0);")
    a(f"    {P}fmi2EnterInitializationMode(c->inst);")
    a(f"    {P}fmi2ExitInitializationMode(c->inst);")
    a(f"    self->current_time = 0.0;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # terminate
    a(f"/** @brief Termina la simulacion y libera la instancia FMI. */")
    a(f"static fmu_status_t _terminate(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    {P}fmi2Terminate(c->inst);")
    a(f"    {P}fmi2FreeInstance(c->inst);")
    a(f"    c->inst = NULL;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # reset
    a(f"/** @brief Reinicia el modelo al estado inicial sin destruir la instancia FMI. */")
    a(f"static fmu_status_t _reset(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_t *c = SELF(self);")
    a(f"    fmi2Status st = {P}fmi2Reset(c->inst);")
    a(f"    self->current_time = 0.0;")
    a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
    a(f"}}")
    a(f"")

    # do_step (CS)
    if info.has_cs:
        a(f"/** @brief Co-Simulation: avanza la simulacion un paso h desde el instante t. */")
        a(f"static fmu_status_t _do_step(fmu_t *self, fmu_real_t t, fmu_real_t h)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2DoStep(")
        a(f"        c->inst, (fmi2Real)t, (fmi2Real)h, fmi2True);")
        a(f"    if (st == fmi2OK || st == fmi2Warning) {{")
        a(f"        self->current_time = t + h;")
        a(f"        return FMU_OK;")
        a(f"    }}")
        a(f"    return FMU_ERROR;")
        a(f"}}")
        a(f"")

    # ME functions
    if info.has_me:
        a(f"/** @brief Model Exchange: informa al modelo del instante de tiempo actual. */")
        a(f"static fmu_status_t _set_time(fmu_t *self, fmu_real_t t)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2SetTime(c->inst, (fmi2Real)t);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Model Exchange: obtiene el vector de derivadas dx/dt en el instante actual. */")
        a(f"static fmu_status_t _get_derivatives(fmu_t *self, fmu_real_t *dx, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetDerivatives(c->inst, (fmi2Real *)dx, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Model Exchange: lee el vector de estados continuos x[]. */")
        a(f"static fmu_status_t _get_cont_states(fmu_t *self, fmu_real_t *x, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetContinuousStates(c->inst, (fmi2Real *)x, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Model Exchange: escribe el vector de estados tras la integracion numerica. */")
        a(f"static fmu_status_t _set_cont_states(fmu_t *self, const fmu_real_t *x, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2SetContinuousStates(c->inst, (const fmi2Real *)x, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Model Exchange: notifica fin de paso; indica si hay que entrar en modo evento. */")
        a(f"static fmu_status_t _completed_step(fmu_t *self, fmu_bool_t *enter_event)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Boolean ev = fmi2False, term = fmi2False;")
        a(f"    fmi2Status st = {P}fmi2CompletedIntegratorStep(")
        a(f"        c->inst, fmi2True, &ev, &term);")
        a(f"    *enter_event = (fmu_bool_t)ev;")
        a(f"    (void)term;  /* gestion de terminacion: responsabilidad del llamador */")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Detiene la integracion y transiciona al modo de procesado de eventos. */")
        a(f"static fmu_status_t _enter_event_mode(fmu_t *self)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2EnterEventMode(c->inst);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Itera variables discretas hasta convergencia.")
        a(f" *  @param more_states_needed 1 si hay que llamar de nuevo, 0 si convergio.")
        a(f" *  @param terminate          1 si el modelo solicita terminar la simulacion. */")
        a(f"static fmu_status_t _new_discrete_states(fmu_t *self,")
        a(f"    fmu_bool_t *more_states_needed, fmu_bool_t *terminate)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2EventInfo ei;")
        a(f"    /* Inicializar la estructura para evitar basura en MSVC */")
        a(f"    ei.newDiscreteStatesNeeded           = fmi2False;")
        a(f"    ei.terminateSimulation               = fmi2False;")
        a(f"    ei.nominalsOfContinuousStatesChanged = fmi2False;")
        a(f"    ei.valuesOfContinuousStatesChanged   = fmi2False;")
        a(f"    ei.nextEventTimeDefined              = fmi2False;")
        a(f"    ei.nextEventTime                     = 0.0;")
        a(f"    fmi2Status st = {P}fmi2NewDiscreteStates(c->inst, &ei);")
        a(f"    *more_states_needed = (fmu_bool_t)ei.newDiscreteStatesNeeded;")
        a(f"    *terminate          = (fmu_bool_t)ei.terminateSimulation;")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/* Gestion de eventos: vuelve a modo tiempo-continuo tras resolver eventos */")
        a(f"static fmu_status_t _enter_cont_mode(fmu_t *self)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2EnterContinuousTimeMode(c->inst);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/* Model Exchange: indicadores de evento (zero-crossing functions) */")
        a(f"static fmu_status_t _get_event_indicators(fmu_t *self, fmu_real_t *ei, int n)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2GetEventIndicators(c->inst, (fmi2Real *)ei, (size_t)n);")
        a(f"    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")

    # get/set por tipo
    for type_ in ("Real", "Integer", "Boolean", "String"):
        if not info.has_type(type_):
            continue
        fmi2t  = Variable("", 0, "", "", type_).fmi2_type
        fmu_t_ = Variable("", 0, "", "", type_).c_type
        tl     = type_.lower()

        a(f"/** @brief Lee n variables de tipo {type_} identificadas por sus ValueReferences. */")
        a(f"static fmu_status_t _get_{tl}(fmu_t *self,")
        a(f"    const fmu_vref_t *vr, int n, {fmu_t_} *out)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2Get{type_}(")
        a(f"        c->inst, (const fmi2ValueReference *)vr, (size_t)n, ({fmi2t} *)out);")
        a(f"    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")
        a(f"/** @brief Escribe n variables de tipo {type_} identificadas por sus ValueReferences. */")
        a(f"static fmu_status_t _set_{tl}(fmu_t *self,")
        a(f"    const fmu_vref_t *vr, int n, const {fmu_t_} *in)")
        a(f"{{")
        a(f"    {L}_t *c = SELF(self);")
        a(f"    fmi2Status st = {P}fmi2Set{type_}(")
        a(f"        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (const {fmi2t} *)in);")
        a(f"    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;")
        a(f"}}")
        a(f"")

    # ── Instancia estática ─────────────────────────────────────────────────────
    a(f"/* =========================================================================")
    a(f" * Instancia estatica — el handle fmi2Component arranca en NULL.")
    a(f" * initialize() lo rellena; terminate() lo pone a NULL de nuevo.")
    a(f" * ========================================================================= */")
    a(f"")
    a(f"static {L}_t _instance = {{")
    a(f"    .base = {{")
    a(f"        .model_name   = {U}_MODEL_NAME,")
    a(f"        .guid         = {U}_GUID,")
    a(f"        .mode         = {info.mode_define},")
    a(f"        .n_states     = {U}_N_STATES,")
    a(f"        .step_size    = 0.01,   /* ajustar segun la aplicacion */")
    a(f"        .current_time = 0.0,")
    a(f"        .initialize   = _initialize,")
    a(f"        .terminate    = _terminate,")
    a(f"        .reset        = _reset,")

    if info.has_cs:
        a(f"        .do_step      = _do_step,")
    else:
        a(f"        .do_step      = NULL,   /* ME: usar fmu_euler_step / fmu_rk4_step */")

    if info.has_me:
        a(f"        .set_time            = _set_time,")
        a(f"        .get_derivatives     = _get_derivatives,")
        a(f"        .get_cont_states     = _get_cont_states,")
        a(f"        .set_cont_states     = _set_cont_states,")
        a(f"        .completed_step      = _completed_step,")
        a(f"        .enter_event_mode      = _enter_event_mode,")
        a(f"        .new_discrete_states   = _new_discrete_states,")
        a(f"        .enter_cont_mode       = _enter_cont_mode,")
        a(f"        .get_event_indicators  = _get_event_indicators,")
    else:
        a(f"        .set_time              = NULL,")
        a(f"        .get_derivatives       = NULL,")
        a(f"        .get_cont_states       = NULL,")
        a(f"        .set_cont_states       = NULL,")
        a(f"        .completed_step        = NULL,")
        a(f"        .enter_event_mode      = NULL,")
        a(f"        .new_discrete_states   = NULL,")
        a(f"        .enter_cont_mode       = NULL,")
        a(f"        .get_event_indicators  = NULL,")

    for type_ in ("real", "boolean", "integer", "string"):
        Type = type_.capitalize()
        if info.has_type(Type):
            a(f"        .get_{type_:<10} = _get_{type_},")
            a(f"        .set_{type_:<10} = _set_{type_},")
        else:
            a(f"        .get_{type_:<10} = NULL,")
            a(f"        .set_{type_:<10} = NULL,")

    a(f"        .get_clock    = NULL,   /* asignar en main segun plataforma */")
    a(f"        .tick_freq    = 0,")
    a(f"    }},")
    a(f"    .inst = NULL,")
    a(f"}};")
    a(f"")

    # create()
    a(f"fmu_t *{L}_create(void)")
    a(f"{{")
    a(f"    return &_instance.base;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


# =============================================================================
# Generador de CMakeLists.txt
# =============================================================================

def generate_cmake(info: FMUInfo, fmu_dir: str) -> str:
    """
    Genera el CMakeLists.txt listo para compilar el ejemplo.
    - Detecta subdirectorios de includes (fmi/, fmi-export/, ...).
    - Para FMUs de OpenModelica: parche MSVC de arrays de tamano 0 (C2466).
    - Si hay resources/: copia todos sus archivos al exe y al vcxproj dir automaticamente.
    - Emite nota si el modelo tiene entradas Boolean en ME (posible bug rising()).
    """
    sources_abs = os.path.abspath(os.path.join(fmu_dir, "sources")).replace(os.sep, "/")
    L = info.lower

    known_include_subdirs = ["fmi", "fmi-export", "fmi2", "include"]
    found_subdirs = [
        d for d in known_include_subdirs
        if os.path.isdir(os.path.join(fmu_dir, "sources", d))
    ]

    # Recursos de runtime: todos los archivos en resources/ (no solo .bin)
    res_dir = os.path.join(fmu_dir, "resources")
    res_files = sorted(
        f for f in os.listdir(res_dir)
        if os.path.isfile(os.path.join(res_dir, f))
    ) if os.path.isdir(res_dir) else []
    has_res = bool(res_files)
    res_abs = os.path.abspath(res_dir).replace(os.sep, "/") if has_res else ""

    is_omc = "OpenModelica" in info.generation_tool
    bool_inputs = [v for v in info.vars_of_causality("input") if v.type_ == "Boolean"]

    lines = []
    a = lines.append

    a(f"# CMakeLists.txt — Ejemplo {info.model_name}")
    a(f"# AUTO-GENERADO por fmu_codegen.py — puedes editarlo libremente")
    a(f"# Herramienta de modelado: {info.generation_tool}")
    a(f"")
    a(f"cmake_minimum_required(VERSION 3.16)")
    a(f"")
    a(f"# Ruta absoluta a los fuentes de la FMU.")
    a(f"# Cambia esta variable si mueves la FMU a otra ubicacion.")
    a(f'set(FMU_SRC "{sources_abs}")')
    a(f"")
    a(f"# Recopila todos los .c de la FMU recursivamente.")
    a(f"# Las FMUs de OpenModelica pueden tener 80+ archivos en subdirectorios.")
    a(f'file(GLOB_RECURSE FMU_SOURCES "${{FMU_SRC}}/*.c")')
    a(f"")

    # ── Parche MSVC: arrays de tamano 0 ──────────────────────────────────────
    if is_omc:
        a(f"# MSVC rechaza 'const int x[0] = {{}}' (error C2466) generado por OpenModelica.")
        a(f"# El siguiente bloque detecta y parchea en el build dir todos los .c afectados,")
        a(f"# sin modificar los fuentes originales de la FMU.")
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

        if bool_inputs and info.has_me:
            a(f"# NOTA: este modelo tiene entradas Boolean en ME FMU de OpenModelica.")
            a(f"# Si rising()/falling() no dispara correctamente, ver REPORTE.md sec. 4.2.")
            a(f"")

    # ── Ejecutable ────────────────────────────────────────────────────────────
    a(f"add_executable({L}_example")
    a(f"    main.c")
    a(f"    {L}_adapter.c")
    a(f"    ${{FMU_SOURCES}}")
    a(f")")
    a(f"")
    a(f"target_include_directories({L}_example PRIVATE")
    a(f'    "${{FMU_SRC}}"                       # headers raiz de la FMU')
    for sd in found_subdirs:
        a(f'    "${{FMU_SRC}}/{sd}"')
    a(f'    "${{CMAKE_CURRENT_SOURCE_DIR}}"       # {L}_adapter.h')
    a(f")")
    a(f"")
    a(f"# Enlaza contra la libreria fmi (solvers euler/rk4 + headers fmu_t.h)")
    a(f"target_link_libraries({L}_example PRIVATE fmi)")
    a(f"")
    a(f"# Define el prefijo de funciones FMI (requerido por el source de la FMU)")
    a(f"target_compile_definitions({L}_example PRIVATE")
    a(f"    FMI2_FUNCTION_PREFIX={info.model_identifier}_")
    a(f"    # Anadir defines especificos de la herramienta si la FMU los requiere:")
    a(f"    # OpenModelica: OMC_FMI_RUNTIME=1")
    a(f"    # Windows/MSVC: HAVE_UNISTD_H=0")
    a(f")")
    a(f"")
    a(f"if(WIN32)")
    a(f"    target_link_libraries({L}_example PRIVATE ws2_32)")
    a(f"endif()")

    # ── Recursos .bin ─────────────────────────────────────────────────────────
    if has_res:
        a(f"")
        a(f"# Recursos de runtime requeridos por la FMU.")
        a(f"# configure_file: copia al dir del vcxproj (cwd de VS con F5).")
        a(f"# POST_BUILD:     copia al dir del exe   (cwd al ejecutar desde Explorer).")
        for bf in res_files:
            a(f'configure_file("{res_abs}/{bf}"')
            a(f'    "${{CMAKE_CURRENT_BINARY_DIR}}/{bf}" COPYONLY)')
            a(f"add_custom_command(TARGET {L}_example POST_BUILD")
            a(f"    COMMAND ${{CMAKE_COMMAND}} -E copy_if_different")
            a(f'        "{res_abs}/{bf}"')
            a(f'        "$<TARGET_FILE_DIR:{L}_example>/{bf}"')
            a(f'    COMMENT "Copiando {bf}"')
            a(f")")
        a(f"set_target_properties({L}_example PROPERTIES")
        a(f'    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:{L}_example>"')
        a(f")")

    a(f"")
    if has_res:
        a(f"add_test(NAME {L} COMMAND {L}_example")
        a(f'    WORKING_DIRECTORY "$<TARGET_FILE_DIR:{L}_example>")')
    else:
        a(f"add_test(NAME {L} COMMAND {L}_example)")
    a(f"")

    # ── Target MCU (adapter standalone, sin runtime OpenModelica) ────────────
    if info.has_me and info.n_states > 0:
        a(f"# ── Ejecutable MCU (adapter directo, sin runtime OpenModelica) ──────────────")
        a(f"# Permite verificar en host que el adapter MCU produce los mismos resultados.")
        a(f"# Compila solo main.c + {L}_mcu.c — sin ninguna fuente de la FMU.")
        a(f"add_executable({L}_mcu_example")
        a(f"    main.c")
        a(f"    {L}_mcu.c")
        a(f")")
        a(f"target_include_directories({L}_mcu_example PRIVATE")
        a(f'    "${{CMAKE_CURRENT_SOURCE_DIR}}"')
        a(f")")
        a(f"target_link_libraries({L}_mcu_example PRIVATE fmi)")
        a(f"target_compile_definitions({L}_mcu_example PRIVATE MCU_TARGET MCU_STDIO_OUTPUT)")
        a(f"add_test(NAME {L}_mcu COMMAND {L}_mcu_example)")
        a(f"")

    return "\n".join(lines)


# =============================================================================
# Parser de ecuaciones ODE para adapter MCU (sin runtime OpenModelica)
# =============================================================================

_POWER_PAREN_RE = re.compile(r'\(([^()]+)\)\s*\^\s*([\d.e+\-]+)')
_POWER_ATOM_RE  = re.compile(r'([a-zA-Z_][\w.]*)\s*\^\s*([\d.e+\-]+)')


def _mcu_safe_field(name: str) -> str:
    """Convierte nombre de variable Modelica a identificador C valido para campo de struct."""
    s = name
    for ch in "()[]., ":
        s = s.replace(ch, "_")
    while "__" in s:
        s = s.replace("__", "_")
    return s.strip("_") or "var"


def _inline_cses(expr: str, cse_map: dict, max_iter: int = 8) -> str:
    """Sustituye variables CSE ($cseN, $cseM...) en expr hasta convergencia."""
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
    Convierte expresion Modelica a C:
      subst  lista de (modelica_name, c_expr) ya ordenada de mayor a menor longitud.
      ^      reemplazado por pow() (casos simples: (EXPR)^N y ATOM^N).
    """
    result = expr
    for model_name, c_expr in subst:
        result = re.sub(r'\b' + re.escape(model_name) + r'\b', c_expr, result)
    result = _POWER_PAREN_RE.sub(r'pow(\1, \2)', result)
    result = _POWER_ATOM_RE.sub(r'pow(\1, \2)', result)
    return result


def parse_mcu_data(fmu_dir: str, info: 'FMUInfo') -> Optional[dict]:
    """
    Extrae informacion de ecuaciones ODE del source de la FMU para generar
    el adapter MCU (implementacion directa, sin runtime OpenModelica).

    Retorna dict con:
      state_vars   lista de dicts {name,vr,start} en orden del array de estados
      param_vars   lista de Variable con causality='parameter'
      input_vars   lista de Variable con causality='input'
      deriv_exprs  {state_idx: c_expr}  —  expresion dx[i]/dt en C
      output_exprs {vr: (name, c_expr)} —  salidas en C
      ok           True si todas las derivadas fueron extraidas
      note         mensaje diagnostico

    Devuelve None si el modelo no es apto (CS-only o sin estados).
    """
    if not info.has_me or info.n_states == 0:
        return None

    # ── Paso 1: orden de variables de estado (via ModelStructure/Derivatives) ──
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

    state_vars: list = []
    for d_idx in deriv_indices:
        d_info = all_xml_vars.get(d_idx, {})
        s_idx  = d_info.get("deriv_of", 0)
        s_info = all_xml_vars.get(s_idx)
        if s_info:
            state_vars.append(s_info)

    param_vars = [v for v in info.variables if v.causality == "parameter"]
    input_vars = [v for v in info.variables if v.causality == "input"]
    output_vars = [v for v in info.variables if v.causality == "output"]

    if len(state_vars) != info.n_states:
        return {"ok": False,
                "note": f"Estado no resuelto: {len(state_vars)}/{info.n_states}",
                "state_vars": state_vars, "param_vars": param_vars,
                "input_vars": input_vars, "deriv_exprs": {}, "output_exprs": {}}

    # ── Paso 2: parsear fuente principal del modelo ──────────────────────────
    src_path = os.path.join(fmu_dir, "sources", f"{info.model_identifier}.c")
    if not os.path.exists(src_path):
        return {"ok": False,
                "note": f"Fuente no encontrada: {src_path}",
                "state_vars": state_vars, "param_vars": param_vars,
                "input_vars": input_vars, "deriv_exprs": {}, "output_exprs": {}}

    with open(src_path, "r", encoding="utf-8", errors="replace") as f:
        src = f.read()

    # Bloques SIMPLE_ASSIGN en comentarios
    eq_re = re.compile(
        r"/\*\r?\nequation index:\s*\d+\r?\ntype:\s*SIMPLE_ASSIGN\r?\n"
        r"([^\r\n]+)\r?\n\s*\*/"
    )

    cse_map:    dict = {}   # "$cseN"  → raw Modelica expr
    deriv_raw:  dict = {}   # der_var_name → raw Modelica expr
    output_raw: dict = {}   # output_var_name → raw Modelica expr

    for m in eq_re.finditer(src):
        body = m.group(1).strip()
        if "=" not in body:
            continue
        lhs, _, rhs = body.partition("=")
        lhs = lhs.strip()
        rhs = rhs.strip()
        if lhs.startswith("$DER.") or lhs.startswith("$der."):
            deriv_raw[lhs.split(".", 1)[1]] = rhs
        elif lhs.startswith("$") or lhs.startswith("_D_"):
            cse_map[lhs] = rhs
        else:
            output_raw[lhs] = rhs

    # ── Paso 3: inline CSEs y conversion a C ─────────────────────────────────
    state_names  = [v["name"] for v in state_vars]
    param_names  = [v.name for v in param_vars]
    input_names  = [v.name for v in input_vars]

    # Lista de sustituciones (nombre Modelica → acceso C), mayor longitud primero
    subst: list = []
    for n in state_names + param_names + input_names:
        subst.append((n, f"m->{_mcu_safe_field(n)}"))
    subst.sort(key=lambda x: len(x[0]), reverse=True)

    # Resolver CSEs (puede haber CSEs anidadas)
    for cse in list(cse_map.keys()):
        others = {k: v for k, v in cse_map.items() if k != cse}
        cse_map[cse] = _inline_cses(cse_map[cse], others)

    # Derivadas
    deriv_exprs: dict = {}
    for der_var, raw in deriv_raw.items():
        if der_var in state_names:
            idx = state_names.index(der_var)
            deriv_exprs[idx] = _modelica_to_c(_inline_cses(raw, cse_map), subst)

    # Salidas
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
# Generador del adapter MCU  (<modelo>_mcu.h  y  <modelo>_mcu.c)
# =============================================================================

def generate_mcu_header(info: 'FMUInfo', mcu: dict) -> str:
    """Genera <modelo>_mcu.h: struct concreto + declaracion de _mcu_create()."""
    U = info.upper
    L = info.lower
    lines: list = []
    a = lines.append

    a(f"/**")
    a(f" * @file   {L}_mcu.h")
    a(f" * @brief  Adapter MCU para {info.model_name} — ecuaciones directas, SIN runtime OpenModelica.")
    a(f" * @note   AUTO-GENERADO por fmu_codegen.py. No editar manualmente.")
    a(f" */")
    a(f"")
    a(f"#ifndef {U}_MCU_H")
    a(f"#define {U}_MCU_H")
    a(f"")
    a(f'#include <math.h>')
    a(f'#include "fmu_t.h"')
    a(f"")

    state_vars  = mcu.get("state_vars",  [])
    param_vars  = mcu.get("param_vars",  [])
    input_vars  = mcu.get("input_vars",  [])

    # ── Constantes compartidas con el adapter HOST ────────────────────────────
    a(f"/* ── Constantes del modelo (compatibles con {L}_adapter.h) ── */")
    a(f'#include "fmu_solver.h"   /* FMU_EULER_WORK_SIZE, FMU_RK4_WORK_SIZE */')
    a(f"")
    a(f"/** @defgroup {L}_mcu_meta Metadatos del modelo (MCU)")
    a(f" *  @{{")
    a(f" */")
    a(f'#define {U}_MODEL_NAME         "{info.model_name}" /*!< Nombre del modelo */')
    a(f'#define {U}_GUID               "{info.guid}" /*!< GUID del modelo */')
    a(f'#define {U}_N_STATES           {info.n_states} /*!< Numero de estados continuos */')
    a(f'#define {U}_N_EVENT_INDICATORS {info.n_event_indicators} /*!< Indicadores de evento */')
    a(f'#define {U}_EULER_BUF_SIZE     FMU_EULER_WORK_SIZE({U}_N_STATES) /*!< Buffer Euler */')
    a(f'#define {U}_RK4_BUF_SIZE       FMU_RK4_WORK_SIZE({U}_N_STATES)   /*!< Buffer RK4 */')
    a(f"/** @}} */")
    a(f"")

    # VR constants — same as HOST adapter
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
            define = f"{U}_VR_{v.define_name}"
            comment = f"{v.type_}, {v.causality}"
            if v.start is not None:
                comment += f", start={v.start}"
            a(f"#define {define:<48} {v.vr}u   /*!< {comment} */")
        a(f"/** @}} */")
        a(f"")
    a(f"/** @}} */")
    a(f"")

    a(f"/**")
    a(f" * @brief Struct concreto del adapter MCU para {info.model_name}.")
    a(f" *")
    a(f" * - La instancia es estatica: no usa heap, vive en BSS del MCU.")
    a(f" * - `base` DEBE ser el primer campo (cast fmu_t * <-> {L}_mcu_t *).")
    a(f" * - Parametros modificables antes/despues de initialize() via set_real().")
    a(f" */")
    a(f"typedef struct {{")
    a(f"    fmu_t      base;   /**< Interfaz publica fmu_t — DEBE SER PRIMER CAMPO */")

    if state_vars:
        a(f"    /* ── Estados continuos ── */")
        for i, sv in enumerate(state_vars):
            start_str = f" start={sv['start']}" if sv.get("start") else ""
            a(f"    fmu_real_t {_mcu_safe_field(sv['name']):<20}; /**< state[{i}]{start_str} */")

    if param_vars:
        a(f"    /* ── Parametros ── */")
        for pv in param_vars:
            if pv.type_ != "Real":
                continue
            start_str = f" default={pv.start}" if pv.start else ""
            a(f"    fmu_real_t {_mcu_safe_field(pv.name):<20}; /**< parameter{start_str} */")

    if input_vars:
        a(f"    /* ── Entradas ── */")
        for iv in input_vars:
            if iv.type_ != "Real":
                continue
            a(f"    fmu_real_t {_mcu_safe_field(iv.name):<20}; /**< input */")

    a(f"}} {L}_mcu_t;")
    a(f"")
    a(f"/**")
    a(f" * @brief  Obtiene la instancia singleton del adapter MCU para {info.model_name}.")
    a(f" * @return Puntero a la interfaz fmu_t lista para usar.")
    a(f" * @note   Llama initialize() antes de simular. La instancia es estatica (sin heap).")
    a(f" * @note   Para MCU: conecta get_clock y tick_freq antes de simular si necesitas")
    a(f" *         medir tiempo real (fmu_elapsed_s).")
    a(f" */")
    a(f"fmu_t *{L}_mcu_create(void);")
    a(f"")
    a(f"#endif /* {U}_MCU_H */")

    return "\n".join(lines) + "\n"


def generate_mcu_source(info: 'FMUInfo', mcu: dict) -> str:
    """Genera <modelo>_mcu.c: implementacion directa de fmu_t con ecuaciones del FMU."""
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
    state_names = [v["name"] for v in state_vars]
    n = info.n_states

    real_params = [pv for pv in param_vars if pv.type_ == "Real"]
    real_inputs = [iv for iv in input_vars  if iv.type_ == "Real"]

    lines: list = []
    a = lines.append

    # ── Cabecera ──────────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @file   {L}_mcu.c")
    a(f" * @brief  Adapter MCU para {info.model_name} (AUTO-GENERADO por fmu_codegen.py).")
    a(f" *         Implementacion directa de fmu_t — SIN runtime OpenModelica.")
    if not ok and note:
        a(f" * @warning {note}")
    a(f" * @note   No editar manualmente. Regenerar con fmu_codegen.py.")
    a(f" */")
    a(f"")
    a(f'#include <math.h>')
    a(f'#include "fmu_t.h"')
    a(f'#include "{L}_mcu.h"')
    a(f"")

    # ── _initialize ───────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief Inicializa estados y parametros a sus valores por defecto del FMU.")
    a(f" */")
    a(f"static fmu_status_t _initialize(fmu_t *self)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    if state_vars:
        a(f"    /* Condiciones iniciales */")
        for sv in state_vars:
            start = sv.get("start") or "0.0"
            a(f"    m->{_mcu_safe_field(sv['name']):<20} = {start};")
    if real_params:
        a(f"    /* Valores por defecto de parametros */")
        for pv in real_params:
            a(f"    m->{_mcu_safe_field(pv.name):<20} = {pv.start or '0.0'};")
    if real_inputs:
        a(f"    /* Entradas: inicializar a cero */")
        for iv in real_inputs:
            a(f"    m->{_mcu_safe_field(iv.name):<20} = 0.0;")
    a(f"    self->current_time = 0.0;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _terminate ────────────────────────────────────────────────────────────
    a(f"static fmu_status_t _terminate(fmu_t *self) {{ (void)self; return FMU_OK; }}")
    a(f"")

    # ── _set_time ─────────────────────────────────────────────────────────────
    a(f"static fmu_status_t _set_time(fmu_t *self, fmu_real_t t)")
    a(f"{{")
    a(f"    self->current_time = t;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _get_derivatives ──────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief Computa las derivadas dx/dt.")
    a(f" *        Ecuaciones extraidas del FMU source (tipo SIMPLE_ASSIGN).")
    a(f" */")
    a(f"static fmu_status_t _get_derivatives(fmu_t *self, fmu_real_t *dx, int n_dx)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    if (n_dx < {n}) return FMU_ERROR;")

    if ok:
        for i in range(n):
            sv_name = state_vars[i]["name"] if i < len(state_vars) else f"state{i}"
            c_expr = deriv_exprs.get(i, "0.0 /* TODO: ecuacion no extraida */")
            a(f"    dx[{i}] = {c_expr};")
    else:
        a(f"    /* TODO: ecuaciones no extraidas automaticamente — completar manualmente.")
        a(f"     * {note} */")
        for i in range(n):
            a(f"    dx[{i}] = 0.0; /* TODO */")

    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _get_cont_states / _set_cont_states ───────────────────────────────────
    a(f"static fmu_status_t _get_cont_states(fmu_t *self, fmu_real_t *x, int n_x)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    if (n_x < {n}) return FMU_ERROR;")
    for i, sv in enumerate(state_vars):
        a(f"    x[{i}] = m->{_mcu_safe_field(sv['name'])};")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
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
    a(f"static fmu_status_t _completed_step(fmu_t *self, fmu_bool_t *enter_event)")
    a(f"{{")
    a(f"    (void)self;")
    a(f"    *enter_event = 0;   /* sin eventos — no hay que entrar en modo evento */")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
    a(f"static fmu_status_t _enter_event_mode(fmu_t *self) {{ (void)self; return FMU_OK; }}")
    a(f"")
    a(f"static fmu_status_t _new_discrete_states(fmu_t *self,")
    a(f"                                          fmu_bool_t *more, fmu_bool_t *terminate)")
    a(f"{{")
    a(f"    (void)self;")
    a(f"    *more      = 0;   /* sin mas estados discretos */")
    a(f"    *terminate = 0;")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")
    a(f"static fmu_status_t _enter_cont_mode(fmu_t *self) {{ (void)self; return FMU_OK; }}")
    a(f"")

    # ── _get_real ─────────────────────────────────────────────────────────────
    a(f"static fmu_status_t _get_real(fmu_t *self, const fmu_vref_t *vr, int n_vr,")
    a(f"                              fmu_real_t *out)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = ({L}_mcu_t *)self;")
    a(f"    for (int i = 0; i < n_vr; i++) {{")
    a(f"        switch (vr[i]) {{")

    # States
    for sv in state_vars:
        a(f"            case {sv['vr']}u: out[i] = m->{_mcu_safe_field(sv['name'])}; break; /* {sv['name']} */")

    # Outputs
    for ov in output_vars:
        if ov.vr in output_exprs:
            _, c_expr = output_exprs[ov.vr]
            a(f"            case {ov.vr}u: out[i] = {c_expr}; break; /* {ov.name} */")
        else:
            a(f"            case {ov.vr}u: out[i] = 0.0; break; /* {ov.name} — TODO */")

    # Parameters (Real only)
    for pv in real_params:
        a(f"            case {pv.vr}u: out[i] = m->{_mcu_safe_field(pv.name)}; break; /* {pv.name} */")

    # Inputs (Real only)
    for iv in real_inputs:
        a(f"            case {iv.vr}u: out[i] = m->{_mcu_safe_field(iv.name)}; break; /* {iv.name} */")

    a(f"            default: return FMU_ERROR;")
    a(f"        }}")
    a(f"    }}")
    a(f"    return FMU_OK;")
    a(f"}}")
    a(f"")

    # ── _set_real ─────────────────────────────────────────────────────────────
    # Only writable: states (initial), tunable params, inputs
    has_writable = state_vars or real_params or real_inputs
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

    # ── Instancia y create() ──────────────────────────────────────────────────
    a(f"static {L}_mcu_t _instance;")
    a(f"")
    a(f"/**")
    a(f" * @brief Devuelve la instancia singleton del adapter MCU (sin heap).")
    a(f" * @note  Conecta get_clock y tick_freq si necesitas fmu_elapsed_s() en MCU.")
    a(f" */")
    a(f"fmu_t *{L}_mcu_create(void)")
    a(f"{{")
    a(f"    {L}_mcu_t *m = &_instance;")
    a(f"    fmu_t     *b = &m->base;")
    a(f"    b->model_name       = \"{info.model_name}\";")
    a(f"    b->guid             = \"{info.guid}\";")
    a(f"    b->mode             = FMU_MODE_ME;")
    a(f"    b->n_states         = {n};")
    a(f"    b->step_size        = 0.0;")
    a(f"    b->current_time     = 0.0;")
    a(f"    b->initialize       = _initialize;")
    a(f"    b->terminate        = _terminate;")
    a(f"    b->reset            = NULL;")
    a(f"    b->do_step          = NULL;")
    a(f"    b->set_time         = _set_time;")
    a(f"    b->get_derivatives  = _get_derivatives;")
    a(f"    b->get_cont_states  = _get_cont_states;")
    a(f"    b->set_cont_states  = _set_cont_states;")
    a(f"    b->completed_step         = _completed_step;")
    a(f"    b->enter_event_mode       = _enter_event_mode;")
    a(f"    b->new_discrete_states    = _new_discrete_states;")
    a(f"    b->enter_cont_mode        = _enter_cont_mode;")
    a(f"    b->get_event_indicators   = NULL;")
    a(f"    b->get_real    = _get_real;")
    a(f"    b->set_real    = _set_real;")
    a(f"    b->get_boolean = NULL;")
    a(f"    b->set_boolean = NULL;")
    a(f"    b->get_integer = NULL;")
    a(f"    b->set_integer = NULL;")
    a(f"    b->get_string  = NULL;")
    a(f"    b->set_string  = NULL;")
    a(f"    /* MCU timing — conectar antes de usar fmu_elapsed_s():")
    a(f"     *   b->tick_freq = <ticks_por_segundo>;")
    a(f"     *   b->get_clock = <funcion_timer>;        */")
    a(f"    b->tick_freq   = 0;")
    a(f"    b->get_clock   = NULL;")
    a(f"    return b;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


# =============================================================================
# Agrupacion de variables en arrays
# =============================================================================

_ARRAY_IDX_RE = re.compile(r'^(.+)\[(\d+)\]$')


def _group_variables(variables: List[Variable]):
    """
    Detecta variables con patron 'nombre[N]' (indices 1..N consecutivos)
    y las agrupa como arrays. El resto se devuelven como escalares.

    Retorna lista de dicts:
      {'kind': 'scalar', 'var': Variable}
      {'kind': 'array',  'base': str, 'vars': [Variable,...], 'n': int,
                         'type_': str, 'causality': str}

    El orden sigue la primera aparicion de cada grupo en la lista original.
    """
    from collections import OrderedDict
    buckets: dict = OrderedDict()
    order = []
    seen: set = set()

    for v in variables:
        m = _ARRAY_IDX_RE.match(v.name)
        if m:
            base, idx = m.group(1), int(m.group(2))
            key = (base, v.causality, v.type_)
            if key not in buckets:
                buckets[key] = []
            if key not in seen:
                order.append(('arr', key))
                seen.add(key)
            buckets[key].append((idx, v))
        else:
            order.append(('scalar', v))

    result = []
    for tag, payload in order:
        if tag == 'scalar':
            result.append({'kind': 'scalar', 'var': payload})
        else:
            key = payload
            items = sorted(buckets[key], key=lambda x: x[0])
            indices = [i for i, _ in items]
            n = len(items)
            if n > 1 and indices == list(range(1, n + 1)):
                result.append({
                    'kind':      'array',
                    'base':      key[0],
                    'vars':      [v for _, v in items],
                    'n':         n,
                    'type_':     key[2],
                    'causality': key[1],
                })
            else:
                for _, sv in items:
                    result.append({'kind': 'scalar', 'var': sv})

    return result


# =============================================================================
# Generador de main_template.c
# =============================================================================

def generate_main_template(info: FMUInfo) -> str:
    """
    Genera main.c: esqueleto de simulacion correcto para el tipo de modelo.
    Expone TODAS las entradas y salidas. Variables con patron 'nombre[N]'
    (indices 1..N consecutivos) se agrupan como arrays C para mayor claridad.
    """
    L = info.lower
    U = info.upper

    inputs  = info.vars_of_causality("input")
    outputs = info.vars_of_causality("output")

    # Agrupar variables en escalares / arrays
    in_groups  = _group_variables(inputs)
    out_groups = _group_variables(outputs)

    # ── Helpers internos ───────────────────────────────────────────────────
    _type_map = {
        "Real":    ("set_real",    "get_real",    "fmu_real_t",   "0.0", ".6f", "(double){v}"),
        "Integer": ("set_integer", "get_integer", "fmu_int_t",    "0",   "d",   "(int){v}"),
        "Boolean": ("set_boolean", "get_boolean", "fmu_bool_t",   "0",   "s",   '{v} ? "true" : "false"'),
        "String":  ("set_string",  "get_string",  "fmu_string_t", '""',  "s",   '{v} ? {v} : ""'),
    }

    def safe(name):
        s = name.lower()
        for ch in "()[].- ":
            s = s.replace(ch, "_")
        while "__" in s:
            s = s.replace("__", "_")
        return s.strip("_")

    def safe_base(name):
        """Identificador C para el nombre base de un array (sin indice)."""
        return safe(name)

    def vinfo(v):
        return _type_map.get(v.type_, _type_map["Real"])

    def vinfo_type(type_: str):
        return _type_map.get(type_, _type_map["Real"])

    def col_w(name):
        return max(12, len(name) + 2)

    def hdr_fmt_s(name):
        return f"%-{col_w(name)}s"

    def val_fmt_s(name, type_):
        _, _, _, _, spec, _ = vinfo_type(type_)
        w = col_w(name)
        return f"%-{w}.6f" if spec == ".6f" else f"%-{w}{spec}"

    def val_cast_s(type_, varname):
        _, _, _, _, _, cast_t = vinfo_type(type_)
        return cast_t.replace("{v}", varname)

    # Inputs discretos: Boolean, Integer, o variability==discrete
    def _is_discrete(v):
        return v.variability == "discrete" or v.type_ in ("Boolean", "Integer")

    def _group_is_discrete(g):
        vars_ = [g['var']] if g['kind'] == 'scalar' else g['vars']
        return all(_is_discrete(v) for v in vars_)

    # Grupos discretos y continuos
    disc_groups = [g for g in in_groups if _group_is_discrete(g)]
    cont_groups = [g for g in in_groups if not _group_is_discrete(g)]

    lines = []
    a = lines.append

    # ── Cabecera ───────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @file   main.c")
    a(f" * @brief  Loop de simulacion para {info.model_name} (GENERADO por fmu_codegen.py).")
    a(f" *         Rellena los TODO segun tu aplicacion.")
    a(f" *")
    a(f" * Modelo: {info.model_name}")
    a(f" * GUID:   {info.guid}")
    a(f" * Modo:   {'ME' if info.has_me else 'CS'} | Estados: {info.n_states} | Indicadores de evento: {info.n_event_indicators}")
    a(f" *")
    if info.has_me and info.is_discrete:
        a(f" * Tipo: Model Exchange DISCRETO (0 estados continuos).")
        a(f" * El modelo es puramente algebraico: cambias la entrada y lees la salida.")
        a(f" * No hay integracion numerica. Los cambios (eventos) se manejan con")
        a(f" * enter_event_mode -> new_discrete_states -> enter_cont_mode cada paso.")
    elif info.has_me:
        a(f" * Tipo: Model Exchange con {info.n_states} estado(s) continuo(s).")
        a(f" * El modelo expone derivadas dx/dt; tu codigo las integra con Euler o RK4.")
        a(f" * Usa fmu_euler_step() para rapidez o fmu_rk4_step() para mas precision.")
    else:
        a(f" * Tipo: Co-Simulation.")
        a(f" * La FMU integra internamente: solo necesitas llamar do_step() cada ciclo.")
    a(f" */")
    a(f"")
    a(f"#include <math.h>")
    if info.has_me and not info.is_discrete:
        a(f'#include "fmu_solver.h"   /* Euler/RK4 — C99 puro, compatible con MCU */')
    a(f"")
    a(f"#ifndef M_PI")
    a(f"#define M_PI 3.14159265358979323846  /* MSVC no lo define por defecto */")
    a(f"#endif")
    a(f"")
    a(f"/* ── Destino de compilacion ──────────────────────────────────────────────────")
    a(f" * Descomenta la siguiente linea para compilar en MCU.")
    a(f" * En host (PC) dejala comentada.                                            */")
    a(f"/* #define MCU_TARGET */")
    a(f"")
    a(f"#ifdef MCU_TARGET")
    a(f"/* TODO: incluir los headers de tu plataforma MCU                            */")
    a(f"/* #include \"stm32xx_hal.h\"                                                  */")
    a(f"/* #include \"uart_utils.h\"                                                   */")
    a(f'#  include "{L}_mcu.h"             /* adapter MCU sin runtime OpenModelica */')
    a(f"#  define MODEL_CREATE()  {L}_mcu_create()")
    a(f"/* MCU_STDIO_OUTPUT: define este simbolo en el CMake del test de host para  */")
    a(f"/* redirigir SIM_PRINT a printf y comparar numericamente con el adapter HOST*/")
    a(f"#  ifdef MCU_STDIO_OUTPUT")
    a(f"#    include <stdio.h>")
    a(f"#    define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)")
    a(f"#    define SIM_DELAY(h)         ((void)(h))")
    a(f"#    define SIM_ERROR(msg)       fprintf(stderr, \"%s\", msg)")
    a(f"#  else")
    a(f"/* Redirige la salida de datos a tu UART                                     */")
    a(f"#    define SIM_PRINT(fmt, ...)  /* TODO: uart_printf(fmt, ##__VA_ARGS__) */")
    a(f"/* Espera h segundos entre pasos (tiempo real)                               */")
    a(f"#    define SIM_DELAY(h)         /* TODO: HAL_Delay((uint32_t)((h) * 1000U)) */")
    a(f"/* Mensajes de error al arrancar                                             */")
    a(f"#    define SIM_ERROR(msg)       /* TODO: uart_puts(msg) */")
    a(f"#  endif  /* MCU_STDIO_OUTPUT */")
    a(f"")
    a(f"#else  /* host (PC) */")
    a(f'#  include "{L}_adapter.h"         /* adapter HOST con runtime OpenModelica */')
    a(f"#  define MODEL_CREATE()  {L}_create()")
    a(f"#include <stdio.h>")
    a(f"#  define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)")
    a(f"#  define SIM_DELAY(h)         ((void)(h))")
    a(f"#  define SIM_ERROR(msg)       fprintf(stderr, \"%s\", msg)")
    a(f"#endif")
    a(f"")

    # ── process_events ─────────────────────────────────────────────────────
    if info.has_me:
        a(f"/**")
        a(f" * @brief  Procesa los eventos discretos del modelo FMI hasta convergencia.")
        a(f" * @param  m  Puntero a la interfaz fmu_t del modelo.")
        a(f" * @retval  0 si los eventos se procesaron correctamente.")
        a(f" * @retval -1 si ocurrio un error o el modelo solicito terminar.")
        a(f" */")
        a(f"static int process_events(fmu_t *m)")
        a(f"{{")
        a(f"    if (FMU_CALL(m, enter_event_mode) != FMU_OK) return -1;")
        a(f"    fmu_bool_t more = 1, terminate = 0;")
        a(f"    while (more && !terminate) {{")
        a(f"        if (FMU_CALL(m, new_discrete_states, &more, &terminate) != FMU_OK)")
        a(f"            return -1;")
        a(f"    }}")
        a(f"    if (terminate) return -1;")
        a(f"    return (FMU_CALL(m, enter_cont_mode) == FMU_OK) ? 0 : -1;")
        a(f"}}")
        a(f"")

    # ── main() ─────────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief  Punto de entrada. Inicializa el modelo FMI y ejecuta el loop de simulacion.")
    a(f" * @return 0 si la simulacion termino correctamente, 1 si hubo un error de inicializacion.")
    a(f" */")
    a(f"int main(void)")
    a(f"{{")
    a(f"    fmu_t *m = MODEL_CREATE();")
    a(f"    if (m->initialize(m) != FMU_OK) {{")
    a(f"        SIM_ERROR(\"Error: initialize() fallo\\n\");")
    a(f"        return 1;")
    a(f"    }}")
    a(f"")

    if info.has_me:
        a(f"    if (process_events(m) != 0) {{")
        a(f"        SIM_ERROR(\"Error: eventos iniciales\\n\");")
        a(f"        m->terminate(m);")
        a(f"        return 1;")
        a(f"    }}")
        a(f"")
        if not info.is_discrete and info.n_states > 0:
            a(f"    static fmu_real_t solver_buf[{U}_EULER_BUF_SIZE];")
            a(f"    fmu_solver_t solver;")
            a(f"    fmu_solver_init(&solver, solver_buf, {U}_EULER_BUF_SIZE);")
            a(f"    fmu_real_t x[{U}_N_STATES];")
            a(f"    FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"")
            if info.n_event_indicators > 0:
                a(f"    fmu_real_t ei_prev[{U}_N_EVENT_INDICATORS];")
                a(f"    fmu_real_t ei_curr[{U}_N_EVENT_INDICATORS];")
                a(f"    FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
                a(f"")

    a(f"    double t     = 0.0;")
    a(f"    double t_end = 1.0;   /* TODO: tiempo final (s) */")
    a(f"    double h     = 0.01;  /* TODO: paso de tiempo (s) */")
    a(f"")

    # ── ValueReferences ────────────────────────────────────────────────────
    def emit_vr(g):
        if g['kind'] == 'scalar':
            v = g['var']
            a(f"    const fmu_vref_t vr_{safe(v.name)} = {U}_VR_{v.define_name};")
        else:
            sb = safe_base(g['base'])
            n  = g['n']
            defs = ", ".join(f"{U}_VR_{v.define_name}" for v in g['vars'])
            a(f"    const fmu_vref_t vr_{sb}[{n}] = {{{defs}}};")

    for g in in_groups:
        emit_vr(g)
    for g in out_groups:
        emit_vr(g)
    if in_groups or out_groups:
        a(f"")

    # ── u_prev para inputs discretos (ME con estados) ──────────────────────
    if info.has_me and not info.is_discrete and disc_groups:
        for g in disc_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                _, _, ctype, init, _, _ = vinfo(v)
                a(f"    {ctype} u_{safe(v.name)}_prev = {init};")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, _, ctype, init, _, _ = vinfo_type(g['type_'])
                inits = ", ".join([init] * n)
                a(f"    {ctype} u_{sb}_prev[{n}] = {{{inits}}};")
        a(f"")

    # ── Header de columnas ─────────────────────────────────────────────────
    hdr_fmts  = ["%-10s"]
    hdr_names = ['"t"']
    for g in in_groups:
        if g['kind'] == 'scalar':
            v = g['var']
            hdr_fmts.append(hdr_fmt_s(v.name))
            hdr_names.append(f'"{v.name}"')
        else:
            for i, v in enumerate(g['vars'], 1):
                hdr_fmts.append(hdr_fmt_s(v.name))
                hdr_names.append(f'"{v.name}"')
    for g in out_groups:
        if g['kind'] == 'scalar':
            v = g['var']
            hdr_fmts.append(hdr_fmt_s(v.name))
            hdr_names.append(f'"{v.name}"')
        else:
            for i, v in enumerate(g['vars'], 1):
                hdr_fmts.append(hdr_fmt_s(v.name))
                hdr_names.append(f'"{v.name}"')
    hdr_fmt_str  = "  ".join(hdr_fmts) + "\\n"
    hdr_args_str = ", ".join(hdr_names)
    a(f'    SIM_PRINT("{hdr_fmt_str}", {hdr_args_str});')
    a(f"")

    # ── Bucle principal ────────────────────────────────────────────────────
    a(f"    while (t <= t_end) {{")
    a(f"")

    # Declarar variables de entrada
    if in_groups:
        a(f"        /* TODO: obtener valores de entrada */")
        for g in in_groups:
            is_disc = g in disc_groups
            tag = "  /* TODO: discreto */" if (is_disc and not info.is_discrete) else "  /* TODO */"
            if g['kind'] == 'scalar':
                v = g['var']
                _, _, ctype, init, _, _ = vinfo(v)
                a(f"        {ctype} u_{safe(v.name)} = {init};{tag}")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, _, ctype, init, _, _ = vinfo_type(g['type_'])
                inits = ", ".join([init] * n)
                a(f"        {ctype} u_{sb}[{n}] = {{{inits}}};{tag}")
        a(f"")

    # ── Cuerpo segun modo ──────────────────────────────────────────────────
    def emit_set(g, prefix="        "):
        """Emite llamada set_* para un grupo (escalar o array)."""
        if g['kind'] == 'scalar':
            v = g['var']
            set_fn, _, ctype, _, _, _ = vinfo(v)
            a(f"{prefix}FMU_CALL(m, {set_fn}, &vr_{safe(v.name)}, 1, (const {ctype} *)&u_{safe(v.name)});")
        else:
            sb = safe_base(g['base'])
            n  = g['n']
            set_fn, _, ctype, _, _, _ = vinfo_type(g['type_'])
            a(f"{prefix}FMU_CALL(m, {set_fn}, vr_{sb}, {n}, (const {ctype} *)u_{sb});")

    if info.is_discrete:
        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        a(f"        /* Modelo discreto: EventMode cada paso, inputs dentro */")
        a(f"        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {{")
        for g in in_groups:
            emit_set(g, prefix="            ")
        a(f"            fmu_bool_t more = 1, terminate = 0;")
        a(f"            while (more && !terminate)")
        a(f"                FMU_CALL(m, new_discrete_states, &more, &terminate);")
        a(f"            FMU_CALL(m, enter_cont_mode);")
        a(f"        }}")

    elif info.has_me:
        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        a(f"")

        if disc_groups:
            # Condicion de cambio: escalar directo, array con flag
            cond_parts = []
            for g in disc_groups:
                if g['kind'] == 'scalar':
                    v = g['var']
                    cond_parts.append(f"u_{safe(v.name)} != u_{safe(v.name)}_prev")
                else:
                    sb = safe_base(g['base'])
                    cond_parts.append(f"_disc_{sb}_changed")

            # Emitir flags de cambio para arrays discretos
            arr_disc = [g for g in disc_groups if g['kind'] == 'array']
            if arr_disc:
                for g in arr_disc:
                    sb = safe_base(g['base'])
                    n  = g['n']
                    a(f"        int _disc_{sb}_changed = 0;")
                    a(f"        for (int _i = 0; _i < {n}; _i++)")
                    a(f"            if (u_{sb}[_i] != u_{sb}_prev[_i]) {{ _disc_{sb}_changed = 1; break; }}")
                a(f"")

            cond = " || ".join(cond_parts)
            a(f"        /* Inputs discretos: solo en EventMode cuando cambian */")
            a(f"        if ({cond}) {{")
            a(f"            if (FMU_CALL(m, enter_event_mode) == FMU_OK) {{")
            for g in disc_groups:
                emit_set(g, prefix="                ")
            a(f"                fmu_bool_t more = 1, terminate = 0;")
            a(f"                while (more && !terminate)")
            a(f"                    FMU_CALL(m, new_discrete_states, &more, &terminate);")
            a(f"                FMU_CALL(m, enter_cont_mode);")
            a(f"                FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"            }}")
            # Actualizar prev
            for g in disc_groups:
                if g['kind'] == 'scalar':
                    v = g['var']
                    a(f"            u_{safe(v.name)}_prev = u_{safe(v.name)};")
                else:
                    sb = safe_base(g['base'])
                    n  = g['n']
                    _, _, ctype, _, _, _ = vinfo_type(g['type_'])
                    a(f"            for (int _i = 0; _i < {n}; _i++) u_{sb}_prev[_i] = u_{sb}[_i];")
            if info.n_event_indicators > 0:
                a(f"            FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
            a(f"        }}")
            a(f"")

        for g in cont_groups:
            emit_set(g)
        if cont_groups:
            a(f"")

        a(f"        fmu_euler_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)h);")
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
            a(f"        FMU_CALL(m, completed_step, &enter_event);")
            a(f"        if (enter_event || zero_cross) {{")
            a(f"            if (process_events(m) != 0) break;")
            a(f"            FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"            FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
            a(f"        }}")
        else:
            a(f"        fmu_bool_t enter_event = 0;")
            a(f"        FMU_CALL(m, completed_step, &enter_event);")
            a(f"        if (enter_event) {{")
            a(f"            if (process_events(m) != 0) break;")
            a(f"            FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"        }}")

    else:
        for g in in_groups:
            emit_set(g)
        a(f"        FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)h);")

    a(f"")

    # ── Salidas ────────────────────────────────────────────────────────────
    if out_groups:
        for g in out_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                _, _, ctype, init, _, _ = vinfo(v)
                a(f"        {ctype} y_{safe(v.name)} = {init};")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, _, ctype, init, _, _ = vinfo_type(g['type_'])
                inits = ", ".join([init] * n)
                a(f"        {ctype} y_{sb}[{n}] = {{{inits}}};")
        for g in out_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                _, get_fn, ctype, _, _, _ = vinfo(v)
                a(f"        FMU_CALL(m, {get_fn}, &vr_{safe(v.name)}, 1, &y_{safe(v.name)});")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, get_fn, ctype, _, _, _ = vinfo_type(g['type_'])
                a(f"        FMU_CALL(m, {get_fn}, vr_{sb}, {n}, y_{sb});")
        a(f"")

    # ── printf fila de datos ───────────────────────────────────────────────
    row_fmts = ["%-10.4f"]
    row_vals = ["t"]
    for g in in_groups:
        if g['kind'] == 'scalar':
            v = g['var']
            row_fmts.append(val_fmt_s(v.name, v.type_))
            row_vals.append(val_cast_s(v.type_, f"u_{safe(v.name)}"))
        else:
            sb = safe_base(g['base'])
            for i, v in enumerate(g['vars']):
                row_fmts.append(val_fmt_s(v.name, v.type_))
                row_vals.append(val_cast_s(v.type_, f"u_{sb}[{i}]"))
    for g in out_groups:
        if g['kind'] == 'scalar':
            v = g['var']
            row_fmts.append(val_fmt_s(v.name, v.type_))
            row_vals.append(val_cast_s(v.type_, f"y_{safe(v.name)}"))
        else:
            sb = safe_base(g['base'])
            for i, v in enumerate(g['vars']):
                row_fmts.append(val_fmt_s(v.name, v.type_))
                row_vals.append(val_cast_s(v.type_, f"y_{sb}[{i}]"))
    row_fmt_str  = "  ".join(row_fmts) + "\\n"
    row_vals_str = ", ".join(row_vals)
    a(f'        SIM_PRINT("{row_fmt_str}", {row_vals_str});')
    a(f"")
    a(f"        t += h;")
    a(f"        SIM_DELAY(h);  /* host: no-op | MCU: espera h segundos con tu timer */")
    a(f"    }}")
    a(f"")
    a(f"    m->terminate(m);")
    a(f"    return 0;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


# =============================================================================
# Punto de entrada
# =============================================================================

def extract_fmu(fmu_path: str) -> str:
    """
    Descomprime un archivo .fmu (ZIP) junto al propio archivo.
    Devuelve la ruta del directorio resultante.
    Si ya es un directorio, lo devuelve sin modificar.
    """
    if os.path.isdir(fmu_path):
        return fmu_path

    if not fmu_path.lower().endswith(".fmu"):
        raise ValueError(f"'{fmu_path}' no es un directorio ni un archivo .fmu")

    if not zipfile.is_zipfile(fmu_path):
        raise ValueError(f"'{fmu_path}' no es un ZIP valido")

    extract_dir = os.path.splitext(fmu_path)[0]   # quita la extension .fmu
    os.makedirs(extract_dir, exist_ok=True)

    with zipfile.ZipFile(fmu_path, "r") as z:
        z.extractall(extract_dir)

    print(f"[codegen] Descomprimido: {fmu_path}")
    print(f"[codegen]       -> {extract_dir}")
    return extract_dir


def register_in_parent_cmake(output_dir: str, lower_name: str) -> None:
    """
    Si output_dir está dentro de un directorio que contiene un CMakeLists.txt,
    añade 'add_subdirectory(<lower_name>)' a ese archivo padre si no existe ya.
    Permite que el codegen sea el único paso manual — sin editar CMakeLists a mano.
    """
    parent_dir = os.path.abspath(os.path.join(output_dir, ".."))
    parent_cmake = os.path.join(parent_dir, "CMakeLists.txt")

    if not os.path.isfile(parent_cmake):
        return  # no hay CMakeLists padre — nada que hacer

    with open(parent_cmake, "r", encoding="utf-8") as f:
        content = f.read()

    line = f"add_subdirectory({lower_name})"
    if line in content:
        print(f"[codegen] Ya registrado en: {parent_cmake}")
        return

    # Añadir al final, con salto de línea si hace falta
    if not content.endswith("\n"):
        content += "\n"
    content += line + "\n"

    with open(parent_cmake, "w", encoding="utf-8") as f:
        f.write(content)

    print(f"[codegen] Registrado en : {parent_cmake}  (+{line})")


def main():
    # Forzar UTF-8 en stdout para que nombres/valores con caracteres no-ASCII
    # (griego, acentos, etc.) no provoquen UnicodeEncodeError en Windows.
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    fmu_input  = sys.argv[1]
    output_dir = sys.argv[2]

    # Acepta .fmu (ZIP) o directorio ya descomprimido
    try:
        fmu_dir = extract_fmu(fmu_input)
    except (ValueError, zipfile.BadZipFile) as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    if not os.path.isdir(fmu_dir):
        print(f"Error: '{fmu_dir}' no es un directorio valido.", file=sys.stderr)
        sys.exit(1)

    os.makedirs(output_dir, exist_ok=True)

    print(f"[codegen] Parseando {os.path.join(fmu_dir, 'modelDescription.xml')} ...")
    info = parse_fmu(fmu_dir)

    # Resumen del modelo
    mode_str = ("CS" if info.has_cs else "") + ("/" if info.has_cs and info.has_me else "") + ("ME" if info.has_me else "")
    print(f"[codegen] Modelo    : {info.model_name}")
    print(f"[codegen] Identifier: {info.model_identifier}")
    print(f"[codegen] Modo      : {mode_str}")
    print(f"[codegen] Estados   : {info.n_states}  |  Indicadores evento: {info.n_event_indicators}")
    print(f"[codegen] Variables : {len(info.variables)}")
    for v in info.variables:
        start_str = f"  start={v.start}" if v.start is not None else ""
        print(f"           vr={v.vr:>3}  {v.name:<32} {v.type_:<8} {v.causality}{start_str}")

    # ── Escribir archivos de adapter HOST (siempre) ─────────────────────────────

    # 1. Header del adapter HOST
    h_path = os.path.join(output_dir, f"{info.lower}_adapter.h")
    with open(h_path, "w", encoding="utf-8") as f:
        f.write(generate_header(info, fmu_dir))
    print(f"[codegen] Generado  : {h_path}")

    # 2. Source del adapter HOST
    c_path = os.path.join(output_dir, f"{info.lower}_adapter.c")
    with open(c_path, "w", encoding="utf-8") as f:
        f.write(generate_source(info, fmu_dir))
    print(f"[codegen] Generado  : {c_path}")

    # 3. CMakeLists.txt
    cmake_path = os.path.join(output_dir, "CMakeLists.txt")
    with open(cmake_path, "w", encoding="utf-8") as f:
        f.write(generate_cmake(info, fmu_dir))
    print(f"[codegen] Generado  : {cmake_path}")

    # 4. main.c — solo si no existe (preserva modificaciones del usuario)
    main_path = os.path.join(output_dir, "main.c")
    if not os.path.exists(main_path):
        with open(main_path, "w", encoding="utf-8") as f:
            f.write(generate_main_template(info))
        print(f"[codegen] Generado  : {main_path}")
    else:
        print(f"[codegen] Conservado: {main_path}  (ya existe, no se sobreescribe)")

    # ── Adapter MCU (ME con estados continuos) ───────────────────────────────────
    if info.has_me and info.n_states > 0:
        mcu = parse_mcu_data(fmu_dir, info)
        if mcu is not None:
            if mcu["ok"]:
                print(f"[codegen] MCU       : ecuaciones extraidas ({info.n_states} derivadas)")
            else:
                print(f"[codegen] MCU       : extraccion parcial — {mcu['note']}")

            mcu_h_path = os.path.join(output_dir, f"{info.lower}_mcu.h")
            with open(mcu_h_path, "w", encoding="utf-8") as f:
                f.write(generate_mcu_header(info, mcu))
            print(f"[codegen] Generado  : {mcu_h_path}")

            mcu_c_path = os.path.join(output_dir, f"{info.lower}_mcu.c")
            with open(mcu_c_path, "w", encoding="utf-8") as f:
                f.write(generate_mcu_source(info, mcu))
            print(f"[codegen] Generado  : {mcu_c_path}")
        else:
            print(f"[codegen] MCU       : omitido (CS-only o sin estados)")

    # 5. Registrar en el CMakeLists.txt del directorio padre (si existe).
    subdir_name = os.path.basename(os.path.abspath(output_dir))
    register_in_parent_cmake(output_dir, subdir_name)

    print(f"")
    print(f"[codegen] Siguiente paso:")
    print(f"          1. Rellena los TODO en main.c: t_end, h, fuente de entradas")
    print(f"          2. cmake --build <build_dir>  (target HOST)")
    if info.has_me and info.n_states > 0:
        print(f"          3. cmake --build <build_dir> --target {info.lower}_mcu_example  (target MCU)")


if __name__ == "__main__":
    main()
