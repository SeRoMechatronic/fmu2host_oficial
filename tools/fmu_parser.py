#!/usr/bin/env python3
"""
fmu_parser.py — Modulo compartido de parsing FMI 2.0

Usado por fmu_codegen_host.py.
NO ejecutar directamente.

Contenido:
    Variable         Dataclass: una variable escalar del modelDescription.xml
    FMUInfo          Dataclass: todos los metadatos de la FMU
    parse_fmu()      Lee modelDescription.xml y devuelve FMUInfo
    extract_fmu()    Descomprime un .fmu (ZIP) si hace falta
    _group_variables()       Agrupa variables con patron nombre[N] en arrays C
    generate_sim_loop()      Genera el cuerpo del loop de simulacion
    register_in_parent_cmake()  Añade add_subdirectory() al CMakeLists padre

Requisitos:
    Python 3.8+  |  Solo stdlib
"""

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
    """Representa una ScalarVariable del modelDescription.xml de la FMU."""

    name:        str
    vr:          int   # valueReference
    causality:   str   # input | output | parameter | local | independent
    variability: str   # constant | fixed | tunable | discrete | continuous
    type_:       str   # Real | Integer | Boolean | String
    start:       Optional[str] = None  # valor inicial declarado en el XML

    @property
    def define_name(self) -> str:
        """
        Nombre del #define C para este VR.
        Convierte el nombre Modelica a UPPER_SNAKE_CASE limpio:
            der(x)  ->  DER_X
            A[1,1]  ->  A_1_1
        """
        safe = (self.name.upper()
                .replace(".", "_")
                .replace("(", "_").replace(")", "")
                .replace("[", "_").replace("]", "")
                .replace(",", "_")
                .replace(" ", "_"))
        while "__" in safe:
            safe = safe.replace("__", "_")
        return safe.strip("_")

    @property
    def c_type(self) -> str:
        """Tipo C propio de la capa fmu_t (fmu_real_t, fmu_int_t, ...)."""
        return {
            "Real":    "fmu_real_t",
            "Integer": "fmu_int_t",
            "Boolean": "fmu_bool_t",
            "String":  "fmu_string_t",
        }.get(self.type_, "fmu_real_t")

    @property
    def fmi2_type(self) -> str:
        """Tipo C del SDK FMI 2.0 (fmi2Real, fmi2Integer, ...)."""
        return {
            "Real":    "fmi2Real",
            "Integer": "fmi2Integer",
            "Boolean": "fmi2Boolean",
            "String":  "fmi2String",
        }.get(self.type_, "fmi2Real")


@dataclass
class FMUInfo:
    """
    Metadatos de una FMU FMI 2.0 extraidos de modelDescription.xml.

    Campos principales:
        model_name         Nombre legible del modelo
        model_identifier   Prefijo de funciones C (ej. "SistemaLorenz")
        guid               GUID unico de esta version
        has_cs / has_me    Modos soportados
        n_states           Numero de estados continuos (ME)
        n_event_indicators Numero de indicadores de evento
        variables          Lista de todas las ScalarVariable
    """
    model_name:        str
    model_identifier:  str
    guid:              str
    description:       str
    generation_tool:   str   # ej. "OpenModelica v1.25.7"
    has_cs:            bool
    has_me:            bool
    n_states:          int
    n_event_indicators: int
    variables:         List[Variable] = field(default_factory=list)
    me_identifier:     Optional[str] = None
    cs_identifier:     Optional[str] = None

    def identifier_for(self, mode: str) -> str:
        """Return the FMI C-symbol identifier declared for *mode*."""
        if mode == "me":
            if not self.has_me or not self.me_identifier:
                raise ValueError("The FMU does not declare a Model Exchange identifier.")
            return self.me_identifier
        if mode == "cs":
            if not self.has_cs or not self.cs_identifier:
                raise ValueError("The FMU does not declare a Co-Simulation identifier.")
            return self.cs_identifier
        raise ValueError(f"Unknown FMI mode: {mode!r}")

    # ── Propiedades derivadas ──────────────────────────────────────────────────

    @property
    def prefix(self) -> str:
        """Prefijo de funciones FMI: ModelIdentifier_ (ej. 'SistemaLorenz_')"""
        return self.model_identifier + "_"

    @property
    def lower(self) -> str:
        """model_identifier en minusculas (para nombres de archivo y target CMake)."""
        return self.model_identifier.lower()

    @property
    def upper(self) -> str:
        """model_identifier en mayusculas (para #define)."""
        return self.model_identifier.upper()

    @property
    def mode_define(self) -> str:
        """ME tiene preferencia sobre CS (solver propio = mas control en MCU)."""
        return "FMU_MODE_ME" if self.has_me else "FMU_MODE_CS"

    @property
    def fmi2_type_enum(self) -> str:
        """Tipo fmi2Type para fmi2Instantiate."""
        return "fmi2ModelExchange" if self.has_me else "fmi2CoSimulation"

    @property
    def is_discrete(self) -> bool:
        """True si ME sin estados continuos (modelo puramente algebraico/discreto)."""
        return self.has_me and self.n_states == 0

    # ── Filtros de variables ───────────────────────────────────────────────────

    def vars_of_causality(self, causality: str) -> List[Variable]:
        """Devuelve solo las variables con la causalidad indicada."""
        return [v for v in self.variables if v.causality == causality]

    def has_type(self, type_: str) -> bool:
        """True si alguna variable es del tipo FMI indicado."""
        return any(v.type_ == type_ for v in self.variables)


# =============================================================================
# Parser de modelDescription.xml
# =============================================================================

def parse_fmu(fmu_dir: str) -> FMUInfo:
    """
    Lee modelDescription.xml y devuelve FMUInfo con todos los metadatos.

    Args:
        fmu_dir: Ruta al directorio de la FMU (con modelDescription.xml).

    Returns:
        FMUInfo completamente relleno.

    Raises:
        FileNotFoundError: Si no existe modelDescription.xml.
        ValueError: Si la FMU no declara ningun modo (CS ni ME).
    """
    xml_path = os.path.join(fmu_dir, "modelDescription.xml")
    if not os.path.exists(xml_path):
        raise FileNotFoundError(f"No se encontro: {xml_path}")

    tree = ET.parse(xml_path)
    root = tree.getroot()

    fmi_version = root.get("fmiVersion", "")
    if fmi_version != "2.0":
        raise ValueError(
            f"Unsupported FMI version {fmi_version!r}; fmu2host supports FMI 2.0 only."
        )

    # ── Atributos raiz ────────────────────────────────────────────────────────
    model_name      = root.get("modelName",      "UnknownModel")
    guid            = root.get("guid",           "{00000000-0000-0000-0000-000000000000}")
    description     = root.get("description",    "")
    generation_tool = root.get("generationTool", "")
    n_event_ind     = int(root.get("numberOfEventIndicators", "0"))

    # ── Modo: CoSimulation / ModelExchange ────────────────────────────────────
    has_cs = root.find("CoSimulation")  is not None
    has_me = root.find("ModelExchange") is not None

    if not has_cs and not has_me:
        raise ValueError("La FMU no declara CoSimulation ni ModelExchange.")

    # FMI permits different C symbol prefixes for ME and CS.  Keep both and use
    # a stable canonical identifier only for generated filenames/API types.
    me_identifier = (
        root.find("ModelExchange").get("modelIdentifier", model_name)
        if has_me else None
    )
    cs_identifier = (
        root.find("CoSimulation").get("modelIdentifier", model_name)
        if has_cs else None
    )
    model_identifier = me_identifier or cs_identifier or model_name

    # ── Numero de estados continuos (uno por <Unknown> en <Derivatives>) ──────
    n_states = 0
    structure = root.find("ModelStructure")
    if structure is not None:
        derivatives = structure.find("Derivatives")
        if derivatives is not None:
            n_states = len(list(derivatives))

    # ── Variables escalares ───────────────────────────────────────────────────
    variables = []
    for sv in root.findall(".//ScalarVariable"):
        name        = sv.get("name", "unknown")
        vr          = int(sv.get("valueReference", 0))
        causality   = sv.get("causality",   "local")
        variability = sv.get("variability", "continuous")

        # FMI 2.0 scalar types supported by the generated typed API.
        type_ = None
        start = None
        for t in ("Real", "Integer", "Boolean", "String"):
            elem = sv.find(t)
            if elem is not None:
                type_ = t
                start = elem.get("start")
                break

        if type_ is None:
            unsupported = next((child.tag for child in list(sv)), "unknown")
            raise ValueError(
                f"Unsupported FMI scalar type {unsupported!r} for variable {name!r}. "
                "Supported types are Real, Integer, Boolean, and String."
            )

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
        me_identifier=me_identifier,
        cs_identifier=cs_identifier,
    )


# =============================================================================
# Descompresor de .fmu (ZIP)
# =============================================================================

def extract_fmu(fmu_path: str) -> str:
    """
    Descomprime un archivo .fmu (ZIP) junto al propio archivo y devuelve
    la ruta del directorio resultante.
    Si fmu_path ya es un directorio, lo devuelve sin modificar.

    Args:
        fmu_path: Ruta a un .fmu o a un directorio FMU ya descomprimido.

    Returns:
        Ruta al directorio con modelDescription.xml.

    Raises:
        ValueError: Si no es un directorio ni un .fmu valido.
    """
    if os.path.isdir(fmu_path):
        if os.path.exists(os.path.join(fmu_path, "modelDescription.xml")):
            return fmu_path
        # Directorio sin modelDescription.xml: buscar .fmu dentro
        fmu_files = [f for f in os.listdir(fmu_path) if f.lower().endswith(".fmu")]
        if not fmu_files:
            raise ValueError(f"'{fmu_path}' no contiene modelDescription.xml ni ningun .fmu")
        fmu_path = os.path.join(fmu_path, fmu_files[0])

    if not fmu_path.lower().endswith(".fmu"):
        raise ValueError(f"'{fmu_path}' no es un directorio ni un archivo .fmu")

    if not zipfile.is_zipfile(fmu_path):
        raise ValueError(f"'{fmu_path}' no es un ZIP valido")

    extract_dir = os.path.splitext(fmu_path)[0]   # quita .fmu
    os.makedirs(extract_dir, exist_ok=True)

    with zipfile.ZipFile(fmu_path, "r") as z:
        z.extractall(extract_dir)

    print(f"[codegen] Descomprimido: {fmu_path}")
    print(f"[codegen]            -> {extract_dir}")
    return extract_dir


# =============================================================================
# Agrupacion de variables en arrays
# =============================================================================

# Detecta el patron nombre[N] donde N es un entero positivo
_ARRAY_IDX_RE = re.compile(r'^(.+)\[(\d+)\]$')


def _group_variables(variables: List[Variable]) -> list:
    """
    Detecta variables con patron 'nombre[N]' (indices 1..N consecutivos)
    y las agrupa como arrays C. El resto se devuelven como escalares.

    Esto hace el main.c generado mas legible cuando el modelo tiene
    vectores (ej. u[1], u[2], u[3] → float u[3]).

    Returns:
        Lista de dicts con uno de estos formatos:
          {'kind': 'scalar', 'var': Variable}
          {'kind': 'array',  'base': str, 'vars': [...], 'n': int,
                             'type_': str, 'causality': str}
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
            # Solo agrupa si los indices son 1, 2, ..., N consecutivos
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
# Generador del cuerpo de simulacion compartido (HOST y MCU)
# =============================================================================

def generate_sim_loop(info: FMUInfo, create_call: str,
                      csv_output: bool = False,
                      cli_args: bool = False) -> str:
    """
    Genera el cuerpo del loop de simulacion en C: process_events() + main().

    Args:
        info:        Metadatos del modelo.
        create_call: Expresion C para crear el modelo.
        csv_output:  Si True, imprime salida en formato CSV (header + filas).
                     Si False (default), usa columnas alineadas con espacios.
        cli_args:    Si True, main() acepta argumentos CLI: t_end h [solver].
                     El solver ("euler"/"rk4") solo aplica a modelos ME con estados.
                     Si False (default), t_end y h son constantes TODO.

    Returns:
        Fragmento de codigo C listo para insertar en main.c.
    """
    U = info.upper

    inputs  = info.vars_of_causality("input")
    outputs = info.vars_of_causality("output")
    in_groups  = _group_variables(inputs)
    out_groups = _group_variables(outputs)

    # ── Tabla de tipos C / FMI / formato printf ────────────────────────────────
    _type_map = {
        "Real":    ("set_real",    "get_real",    "fmu_real_t",   "0.0", ".6f", "(double){v}"),
        "Integer": ("set_integer", "get_integer", "fmu_int_t",    "0",   "d",   "(int){v}"),
        "Boolean": ("set_boolean", "get_boolean", "fmu_bool_t",   "0",   "s",   '{v} ? "true" : "false"'),
        "String":  ("set_string",  "get_string",  "fmu_string_t", '""',  "s",   '{v} ? {v} : ""'),
    }

    def safe(name: str) -> str:
        """Convierte nombre de variable a identificador C valido (minusculas)."""
        s = name.lower()
        for ch in "()[].- ":
            s = s.replace(ch, "_")
        while "__" in s:
            s = s.replace("__", "_")
        return s.strip("_")

    def safe_base(name: str) -> str:
        return safe(name)

    def vinfo(v: Variable):
        return _type_map.get(v.type_, _type_map["Real"])

    def vinfo_type(type_: str):
        return _type_map.get(type_, _type_map["Real"])

    def get_init(v: Variable) -> str:
        """Devuelve el valor inicial C para una variable, usando v.start si existe."""
        _, _, _, default_init, _, _ = vinfo(v)
        if v.start is None:
            return default_init
        if v.type_ == "Boolean":
            s = v.start.strip().lower()
            return "1" if s in ("true", "1") else "0"
        elif v.type_ == "String":
            s = v.start.strip()
            return s if (s.startswith('"') and s.endswith('"')) else f'"{s}"'
        else:
            return v.start

    def col_w(name: str) -> int:
        return max(12, len(name) + 2)

    def hdr_fmt_s(name: str) -> str:
        return f"%-{col_w(name)}s"

    def val_fmt_s(name: str, type_: str) -> str:
        _, _, _, _, spec, _ = vinfo_type(type_)
        w = col_w(name)
        return f"%-{w}.6f" if spec == ".6f" else f"%-{w}{spec}"

    def val_cast_s(type_: str, varname: str) -> str:
        _, _, _, _, _, cast_t = vinfo_type(type_)
        return cast_t.replace("{v}", varname)

    def _is_discrete(v: Variable) -> bool:
        return v.variability == "discrete" or v.type_ in ("Boolean", "Integer")

    def _group_is_discrete(g: dict) -> bool:
        vars_ = [g['var']] if g['kind'] == 'scalar' else g['vars']
        return all(_is_discrete(v) for v in vars_)

    disc_groups = [g for g in in_groups if _group_is_discrete(g)]
    cont_groups = [g for g in in_groups if not _group_is_discrete(g)]

    lines: list = []
    a = lines.append

    # ── process_events (solo ME) ───────────────────────────────────────────────
    if info.has_me:
        a(f"/**")
        a(f" * @brief  Procesa los eventos discretos del modelo FMI hasta convergencia.")
        a(f" * @param  m  Puntero al modelo fmu_t.")
        a(f" * @retval  0  OK")
        a(f" * @retval -1  Error o el modelo solicita terminar.")
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

    # ── main() ────────────────────────────────────────────────────────────────
    a(f"/**")
    a(f" * @brief  Punto de entrada. Inicializa el modelo y ejecuta el loop de simulacion.")
    a(f" * @return 0 exito | 1 error de inicializacion.")
    a(f" */")
    _me_with_states = info.has_me and not info.is_discrete and info.n_states > 0

    if cli_args:
        a(f"int main(int argc, char *argv[])")
    else:
        a(f"int main(void)")
    a(f"{{")
    if cli_args:
        a(f"    double t_end  = 1.0;")
        a(f"    double h      = 0.01;")
        if _me_with_states:
            a(f"    int    use_rk4 = 0;")
        a(f"    if (argc >= 2) t_end = atof(argv[1]);")
        a(f"    if (argc >= 3) h     = atof(argv[2]);")
        if _me_with_states:
            a(f'    if (argc >= 4) use_rk4 = (strcmp(argv[3], "rk4") == 0);')
        a(f"")
    a(f"    fmu_t *m = {create_call};")
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
            if cli_args:
                a(f"    static fmu_real_t solver_buf[{U}_RK4_BUF_SIZE];")
                a(f"    fmu_solver_t solver;")
                a(f"    fmu_solver_init(&solver, solver_buf,")
                a(f"                   use_rk4 ? {U}_RK4_BUF_SIZE : {U}_EULER_BUF_SIZE);")
                a(f"")
            else:
                a(f"    /* ── Seleccionar solver ────────────────────────────────────────────────────")
                a(f"     * Descomenta UN bloque y comenta el otro segun la precision que necesites. */")
                a(f"")
                a(f"    /* Euler: rapido, 1 evaluacion de derivadas por paso.")
                a(f"     * Suficiente para paso h pequeno (h <= 0.01 s en la mayoria de modelos). */")
                a(f"    static fmu_real_t solver_buf[{U}_EULER_BUF_SIZE];")
                a(f"    fmu_solver_t solver;")
                a(f"    fmu_solver_init(&solver, solver_buf, {U}_EULER_BUF_SIZE);")
                a(f"")
                a(f"    /* RK4: mas preciso, 4 evaluaciones por paso.")
                a(f"     * Necesario para modelos rigidos o pasos h grandes.")
                a(f"    static fmu_real_t solver_buf[{U}_RK4_BUF_SIZE];")
                a(f"    fmu_solver_t solver;")
                a(f"    fmu_solver_init(&solver, solver_buf, {U}_RK4_BUF_SIZE);")
                a(f"    */")
                a(f"")
            a(f"    fmu_real_t x[{U}_N_STATES];")
            a(f"    FMU_CALL(m, get_cont_states, x, {U}_N_STATES);")
            a(f"")
            if info.n_event_indicators > 0:
                a(f"    fmu_real_t ei_prev[{U}_N_EVENT_INDICATORS];")
                a(f"    fmu_real_t ei_curr[{U}_N_EVENT_INDICATORS];")
                a(f"    FMU_CALL(m, get_event_indicators, ei_prev, {U}_N_EVENT_INDICATORS);")
                a(f"")

    a(f"    double t = 0.0;")
    if not cli_args:
        a(f"    double t_end = 1.0;   /* TODO: ajustar tiempo final (s) */")
        a(f"    double h     = 0.01;  /* TODO: ajustar paso de integracion (s) */")
    a(f"")

    # ── ValueReferences ───────────────────────────────────────────────────────
    def emit_vr(g: dict):
        if g['kind'] == 'scalar':
            v = g['var']
            a(f"    const fmu_vref_t vr_{safe(v.name)} = {U}_VR_{v.define_name};")
        else:
            sb  = safe_base(g['base'])
            n   = g['n']
            defs = ", ".join(f"{U}_VR_{v.define_name}" for v in g['vars'])
            a(f"    const fmu_vref_t vr_{sb}[{n}] = {{{defs}}};")

    for g in in_groups:
        emit_vr(g)
    for g in out_groups:
        emit_vr(g)
    if in_groups or out_groups:
        a(f"")

    # ── Declarar variables de entrada (antes del bucle) ──────────────────────
    if in_groups:
        a(f"    /* TODO: actualizar en cada iteracion desde sensores reales */")
        for g in in_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                _, _, ctype, _, _, _ = vinfo(v)
                a(f"    {ctype} u_{safe(v.name)} = {get_init(v)};")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, _, ctype, _, _, _ = vinfo_type(g['type_'])
                inits = ", ".join(get_init(v) for v in g['vars'])
                a(f"    {ctype} u_{sb}[{n}] = {{{inits}}};")
        a(f"")

    # Prev para inputs discretos (ME con estados)
    if info.has_me and not info.is_discrete and disc_groups:
        for g in disc_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                _, _, ctype, _, _, _ = vinfo(v)
                a(f"    {ctype} u_{safe(v.name)}_prev = {get_init(v)};")
            else:
                sb = safe_base(g['base'])
                n  = g['n']
                _, _, ctype, _, _, _ = vinfo_type(g['type_'])
                inits = ", ".join(get_init(v) for v in g['vars'])
                a(f"    {ctype} u_{sb}_prev[{n}] = {{{inits}}};")
        a(f"")

    # ── Tablas de schedule para cambios de entrada en tiempo: name@t=val ────────
    def _norm_arg(name: str) -> str:
        """Normaliza nombre FMU para CLI: 'v_real[1]' → 'v_real_1_'"""
        return name.replace("[", "_").replace("]", "_")

    sched_vars = []  # [(c_var_expr, sched_name, fname, ctype, sched_val_expr, const_parse)]
    if cli_args and in_groups:
        for g in in_groups:
            if g['kind'] == 'scalar':
                v = g['var']
                if v.type_ == 'String':
                    continue
                _, _, ctype, _, _, _ = vinfo(v)
                c_expr   = f"u_{safe(v.name)}"
                sname    = safe(v.name)
                fname    = _norm_arg(v.name)
                if v.type_ == 'Real':
                    const_p = f"(fmu_real_t)atof(_eq+1)"
                    sval_p  = "atof(_eq+1)"
                elif v.type_ == 'Integer':
                    const_p = f"(fmu_int_t)atoi(_eq+1)"
                    sval_p  = "(double)atoi(_eq+1)"
                else:
                    const_p = f"(fmu_bool_t)(atoi(_eq+1) != 0)"
                    sval_p  = "(double)(atoi(_eq+1) != 0)"
                sched_vars.append((c_expr, sname, fname, ctype, sval_p, const_p))
            else:
                for idx, v in enumerate(g['vars']):
                    if v.type_ == 'String':
                        continue
                    sb = safe_base(g['base'])
                    _, _, ctype, _, _, _ = vinfo(v)
                    c_expr  = f"u_{sb}[{idx}]"
                    sname   = f"{sb}_{idx}"
                    fname   = _norm_arg(v.name)
                    if v.type_ == 'Real':
                        const_p = f"(fmu_real_t)atof(_eq+1)"
                        sval_p  = "atof(_eq+1)"
                    elif v.type_ == 'Integer':
                        const_p = f"(fmu_int_t)atoi(_eq+1)"
                        sval_p  = "(double)atoi(_eq+1)"
                    else:
                        const_p = f"(fmu_bool_t)(atoi(_eq+1) != 0)"
                        sval_p  = "(double)(atoi(_eq+1) != 0)"
                    sched_vars.append((c_expr, sname, fname, ctype, sval_p, const_p))

        if sched_vars:
            a(f"    #define _MAX_SCHED 512")
            for (c_expr, sname, fname, ctype, sval_p, const_p) in sched_vars:
                a(f"    struct {{ double t; double val; }} _sched_{sname}[_MAX_SCHED]; int _ns_{sname} = 0;")
            a(f"")

    # ── Override de entradas via CLI: nombre=val o nombre@t=val ─────────────────
    if cli_args and in_groups and sched_vars:
        a(f"    /* Sobrescribir entradas via CLI: nombre=val o nombre@t=val */")
        a(f"    for (int _oi = 1; _oi < argc; _oi++) {{")
        a(f"        char *_at = strchr(argv[_oi], '@');")
        a(f"        char *_eq = strchr(argv[_oi], '=');")
        a(f"        if (!_eq) continue;")
        a(f"        if (_at && _at < _eq) {{")
        a(f"            /* name@t=val — programar cambio de entrada en tiempo */")
        a(f"            *_at = '\\0'; *_eq = '\\0';")
        a(f"            double _at_t = atof(_at + 1);")
        for (c_expr, sname, fname, ctype, sval_p, const_p) in sched_vars:
            a(f'            if (strcmp(argv[_oi], "{fname}") == 0 && _ns_{sname} < _MAX_SCHED) {{')
            a(f"                _sched_{sname}[_ns_{sname}].t   = _at_t;")
            a(f"                _sched_{sname}[_ns_{sname}++].val = {sval_p};")
            a(f"            }}")
        a(f"            *_at = '@'; *_eq = '=';")
        a(f"        }} else {{")
        a(f"            /* name=val — valor constante inicial */")
        a(f"            *_eq = '\\0';")
        for (c_expr, sname, fname, ctype, sval_p, const_p) in sched_vars:
            a(f'            if (strcmp(argv[_oi], "{fname}") == 0) {{ {c_expr} = {const_p}; }}')
        a(f"            *_eq = '=';")
        a(f"        }}")
        a(f"    }}")
        a(f"")

    # ── Cabecera de columnas ───────────────────────────────────────────────────
    hdr_fmts  = ["%-10s"]
    hdr_names = ['"t"']
    for g in in_groups:
        for v in ([g['var']] if g['kind'] == 'scalar' else g['vars']):
            hdr_fmts.append(hdr_fmt_s(v.name))
            hdr_names.append(f'"{v.name}"')
    for g in out_groups:
        for v in ([g['var']] if g['kind'] == 'scalar' else g['vars']):
            hdr_fmts.append(hdr_fmt_s(v.name))
            hdr_names.append(f'"{v.name}"')
    if csv_output:
        col_names = ["t"]
        for g in in_groups + out_groups:
            for v in ([g['var']] if g['kind'] == 'scalar' else g['vars']):
                col_names.append(v.name)
        a(f'    SIM_PRINT("{",".join(col_names)}\\n");')
    else:
        a(f'    SIM_PRINT("{("  ".join(hdr_fmts))}\\n", {", ".join(hdr_names)});')
    a(f"")

    # ── Bucle principal ────────────────────────────────────────────────────────
    a(f"    while (t <= t_end) {{")
    a(f"")

    def emit_set(g: dict, prefix: str = "        "):
        if g['kind'] == 'scalar':
            v = g['var']
            set_fn, _, ctype, _, _, _ = vinfo(v)
            a(f"{prefix}FMU_CALL(m, {set_fn}, &vr_{safe(v.name)}, 1, (const {ctype} *)&u_{safe(v.name)});")
        else:
            sb = safe_base(g['base'])
            n  = g['n']
            set_fn, _, ctype, _, _, _ = vinfo_type(g['type_'])
            a(f"{prefix}FMU_CALL(m, {set_fn}, vr_{sb}, {n}, (const {ctype} *)u_{sb});")

    # Actualizar entradas en el bucle (produccion: leer desde sensor real)
    if in_groups:
        a(f"        /* TODO: u_nombre = leer_sensor(); */")
        a(f"")

    # ── Aplicar schedules de entrada en el bucle ───────────────────────────────
    if cli_args and in_groups and sched_vars:
        a(f"        /* Aplicar cambios de entrada programados (name@t=val) */")
        for (c_expr, sname, fname, ctype, sval_p, const_p) in sched_vars:
            a(f"        if (_ns_{sname} > 0) {{")
            a(f"            double _bv = (double)({c_expr}); double _bt = -1e300;")
            a(f"            for (int _si = 0; _si < _ns_{sname}; _si++)")
            a(f"                if (t >= _sched_{sname}[_si].t && _sched_{sname}[_si].t >= _bt)")
            a(f"                    {{ _bv = _sched_{sname}[_si].val; _bt = _sched_{sname}[_si].t; }}")
            a(f"            {c_expr} = ({ctype})_bv;")
            a(f"        }}")
        a(f"")

    # ── Helper: emite el bloque de lectura y escritura de salidas ─────────────
    # Se llama ANTES del paso de integracion para ME-continuo y CS,
    # y DESPUES del update de estados discretos para ME-discreto.
    # Esto garantiza que la fila CSV etiquetada con t contenga el estado en t
    # (no el estado despues del paso, que corresponde a t+h).

    def _build_print_stmts():
        """Devuelve una lista de lineas C para leer salidas e imprimir la fila."""
        out = []
        def oa(s): out.append(s)

        if out_groups:
            for g in out_groups:
                if g['kind'] == 'scalar':
                    v = g['var']
                    _, _, ctype, init, _, _ = vinfo(v)
                    oa(f"        {ctype} y_{safe(v.name)} = {init};")
                else:
                    sb = safe_base(g['base'])
                    n  = g['n']
                    _, _, ctype, init, _, _ = vinfo_type(g['type_'])
                    inits = ", ".join([init] * n)
                    oa(f"        {ctype} y_{sb}[{n}] = {{{inits}}};")
            for g in out_groups:
                if g['kind'] == 'scalar':
                    v = g['var']
                    _, get_fn, ctype, _, _, _ = vinfo(v)
                    oa(f"        FMU_CALL(m, {get_fn}, &vr_{safe(v.name)}, 1, &y_{safe(v.name)});")
                else:
                    sb = safe_base(g['base'])
                    n  = g['n']
                    _, get_fn, ctype, _, _, _ = vinfo_type(g['type_'])
                    oa(f"        FMU_CALL(m, {get_fn}, vr_{sb}, {n}, y_{sb});")
            oa(f"")

        row_fmts = ["%-10.4f"]
        row_vals = ["t"]
        for g in in_groups:
            for i, v in enumerate([g['var']] if g['kind'] == 'scalar' else g['vars']):
                row_fmts.append(val_fmt_s(v.name, v.type_))
                if g['kind'] == 'scalar':
                    row_vals.append(val_cast_s(v.type_, f"u_{safe(v.name)}"))
                else:
                    row_vals.append(val_cast_s(v.type_, f"u_{safe_base(g['base'])}[{i}]"))
        for g in out_groups:
            for i, v in enumerate([g['var']] if g['kind'] == 'scalar' else g['vars']):
                row_fmts.append(val_fmt_s(v.name, v.type_))
                if g['kind'] == 'scalar':
                    row_vals.append(val_cast_s(v.type_, f"y_{safe(v.name)}"))
                else:
                    row_vals.append(val_cast_s(v.type_, f"y_{safe_base(g['base'])}[{i}]"))

        if csv_output:
            def _csv_fmt(type_: str) -> str:
                return "%d" if type_ in ("Boolean", "Integer") else ("%.10g" if type_ != "String" else "%s")
            def _csv_cast(type_: str, varname: str) -> str:
                return f"(int)({varname})" if type_ in ("Boolean", "Integer") else varname
            csv_fmts = ["%.10g"]
            csv_vals = ["t"]
            for g in in_groups:
                for i, v in enumerate([g['var']] if g['kind'] == 'scalar' else g['vars']):
                    csv_fmts.append(_csv_fmt(v.type_))
                    vn = f"u_{safe(v.name)}" if g['kind'] == 'scalar' else f"u_{safe_base(g['base'])}[{i}]"
                    csv_vals.append(_csv_cast(v.type_, vn))
            for g in out_groups:
                for i, v in enumerate([g['var']] if g['kind'] == 'scalar' else g['vars']):
                    csv_fmts.append(_csv_fmt(v.type_))
                    vn = f"y_{safe(v.name)}" if g['kind'] == 'scalar' else f"y_{safe_base(g['base'])}[{i}]"
                    csv_vals.append(_csv_cast(v.type_, vn))
            oa(f'        SIM_PRINT("{",".join(csv_fmts)}\\n", {", ".join(csv_vals)});')
        else:
            oa(f'        SIM_PRINT("{("  ".join(row_fmts))}\\n", {", ".join(row_vals)});')
        oa(f"")
        return out

    def emit_print():
        for ln in _build_print_stmts():
            a(ln)

    # ── Cuerpo segun modo ──────────────────────────────────────────────────────
    if info.is_discrete:
        # ME discreto: EventMode cada paso — el estado se actualiza en event mode,
        # luego se leen salidas. Las salidas reflejan el estado en t (correcto).
        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        a(f"        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {{")
        for g in in_groups:
            emit_set(g, prefix="            ")
        a(f"            fmu_bool_t more = 1, terminate = 0;")
        a(f"            while (more && !terminate)")
        a(f"                FMU_CALL(m, new_discrete_states, &more, &terminate);")
        a(f"            FMU_CALL(m, enter_cont_mode);")
        a(f"        }}")
        a(f"")
        emit_print()

    elif info.has_me:
        # ME continuo — imprime ANTES del paso de integracion:
        # la fila etiquetada t contiene el estado en t, no en t+h.
        a(f"        FMU_CALL(m, set_time, (fmu_real_t)t);")
        a(f"")

        if disc_groups:
            cond_parts = []
            for g in disc_groups:
                if g['kind'] == 'scalar':
                    v = g['var']
                    cond_parts.append(f"u_{safe(v.name)} != u_{safe(v.name)}_prev")
                else:
                    sb = safe_base(g['base'])
                    cond_parts.append(f"_disc_{sb}_changed")

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

        # Leer y mostrar salidas ANTES del paso (estado en t, no en t+h)
        a(f"        /* Salidas en t (antes del paso de integracion) */")
        a(f"        FMU_CALL(m, set_cont_states, x, {U}_N_STATES);")
        emit_print()

        if cli_args:
            a(f"        if (use_rk4)")
            a(f"            fmu_rk4_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)h);")
            a(f"        else")
            a(f"            fmu_euler_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)h);")
        else:
            a(f"        fmu_euler_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)h);")
            a(f"        /* fmu_rk4_step(m, &solver, x, {U}_N_STATES, (fmu_real_t)t, (fmu_real_t)h); */")
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
        # Co-Simulation — imprime ANTES de do_step (estado en t, no en t+h)
        for g in in_groups:
            emit_set(g)
        a(f"")
        a(f"        /* Salidas en t (antes de do_step) */")
        emit_print()
        a(f"        FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)h);")

    a(f"        t += h;")
    a(f"        SIM_DELAY(h);  /* host: no-op  |  MCU: espera h segundos con tu timer */")
    a(f"    }}")
    a(f"")
    a(f"    m->terminate(m);")
    a(f"    return 0;")
    a(f"}}")
    a(f"")

    return "\n".join(lines)


# =============================================================================
# Registro en el CMakeLists.txt padre
# =============================================================================

def register_in_parent_cmake(output_dir: str) -> None:
    """
    Busca el CMakeLists.txt padre (subiendo hasta 2 niveles) y añade
    add_subdirectory(<ruta_relativa>) si no esta ya.

    Ejemplo:
        output_dir = .../examples/sistemalorenz/host/
        Encuentra  .../examples/CMakeLists.txt
        Añade      add_subdirectory(sistemalorenz/host)

    Esto evita editar manualmente el CMakeLists padre tras cada codegen.
    """
    output_dir = os.path.abspath(output_dir)

    for levels_up in (1, 2):
        parent = output_dir
        for _ in range(levels_up):
            parent = os.path.dirname(parent)
        parent_cmake = os.path.join(parent, "CMakeLists.txt")

        if not os.path.isfile(parent_cmake):
            continue

        # Ruta relativa del output al padre (normalizada con '/')
        rel = os.path.relpath(output_dir, parent).replace(os.sep, "/")
        line = f"add_subdirectory({rel})"

        with open(parent_cmake, "r", encoding="utf-8") as f:
            content = f.read()

        # Comparacion case-insensitive para Windows (mismo directorio, distinto case)
        if line.lower() in content.lower():
            print(f"[codegen] Ya registrado : {parent_cmake}  ({line})")
            return

        if not content.endswith("\n"):
            content += "\n"
        content += line + "\n"

        with open(parent_cmake, "w", encoding="utf-8") as f:
            f.write(content)

        print(f"[codegen] Registrado en: {parent_cmake}  (+{line})")
        return

    # Si no se encontro CMakeLists padre, no hacer nada
