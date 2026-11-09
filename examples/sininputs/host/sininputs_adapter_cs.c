/**
 * @file   sininputs_adapter_cs.c
 * @brief  Wrapper fmu_t HOST (Co-Simulation) para SinInputs.
 *
 *  Instancia la FMU como fmi2CoSimulation y delega TODAS las
 *  operaciones al runtime de OpenModelica. No reimplementa ecuaciones.
 *
 *  Usar con main_cs.c + FMU_CALL(m, do_step, t, h).
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */
/* Source artifact: SinInputs (path intentionally omitted). */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "fmi2_api.h"
#include "fmu_t.h"
#include "sininputs_adapter.h"

/* Funciones FMI 2.0 del runtime de OpenModelica (prefijo 'SinInputs_') */
extern fmi2Component SinInputs_fmi2Instantiate(
    fmi2String, fmi2Type, fmi2String, fmi2String,
    const fmi2CallbackFunctions *, fmi2Boolean, fmi2Boolean);
extern fmi2Status SinInputs_fmi2SetupExperiment(
    fmi2Component, fmi2Boolean, fmi2Real, fmi2Real, fmi2Boolean, fmi2Real);
extern fmi2Status SinInputs_fmi2EnterInitializationMode(fmi2Component);
extern fmi2Status SinInputs_fmi2ExitInitializationMode(fmi2Component);
extern fmi2Status SinInputs_fmi2Terminate(fmi2Component);
extern void       SinInputs_fmi2FreeInstance(fmi2Component);
extern fmi2Status SinInputs_fmi2Reset(fmi2Component);

/* Co-Simulation: la FMU avanza internamente un paso h */
extern fmi2Status SinInputs_fmi2DoStep(
    fmi2Component, fmi2Real, fmi2Real, fmi2Boolean);

extern fmi2Status SinInputs_fmi2GetReal(
    fmi2Component, const fmi2ValueReference *, size_t, fmi2Real *);
extern fmi2Status SinInputs_fmi2SetReal(
    fmi2Component, const fmi2ValueReference *, size_t, const fmi2Real *);

static void _logger(fmi2ComponentEnvironment env, fmi2String inst,
                    fmi2Status status, fmi2String cat,
                    fmi2String msg, ...) {
    (void)env; (void)inst; (void)status;
    va_list args; va_start(args, msg);
    fprintf(stderr, "[SinInputs/%s] ", cat);
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    va_end(args);
}

static const fmi2CallbackFunctions _callbacks = {
    .logger               = _logger,
    .allocateMemory       = calloc,
    .freeMemory           = free,
    .stepFinished         = NULL,
    .componentEnvironment = NULL,
};

static fmu_status_t _status(fmi2Status st)
{
    if (st == fmi2OK) return FMU_OK;
    if (st == fmi2Warning) return FMU_WARNING;
    if (st == fmi2Fatal) return FMU_FATAL;
    return FMU_ERROR;
}

typedef struct {
    fmu_t         base;   /* PRIMER CAMPO: permite cast (fmu_t *) -> (sininputs_t *) */
    fmi2Component inst;   /* Handle opaco de la instancia FMI 2.0 */
} sininputs_t;
#define SELF(p)  ((sininputs_t *)(p))

#if defined(_WIN32)
#  include <windows.h>
static void _compute_res_uri(char *out, size_t n) {
    char buf[MAX_PATH];
    GetModuleFileNameA(NULL, buf, MAX_PATH);
    char *sep = strrchr(buf, '\\'); if (sep) *sep = '\0';
    for (char *p = buf; *p; p++) if (*p == '\\') *p = '/';
    snprintf(out, n, "file:///%s", buf);
}
#elif defined(__linux__)
#  include <unistd.h>
static void _compute_res_uri(char *out, size_t n) {
    char buf[4096] = {0};
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len > 0) { char *sep = strrchr(buf, '/'); if (sep) *sep = '\0'; }
    snprintf(out, n, "file://%s", buf);
}
#elif defined(__APPLE__)
#  include <mach-o/dyld.h>
static void _compute_res_uri(char *out, size_t n) {
    char buf[4096]; uint32_t sz = (uint32_t)sizeof(buf);
    _NSGetExecutablePath(buf, &sz);
    char *sep = strrchr(buf, '/'); if (sep) *sep = '\0';
    snprintf(out, n, "file://%s", buf);
}
#else
static void _compute_res_uri(char *out, size_t n) { snprintf(out, n, ""); }
#endif

static fmu_status_t _initialize(fmu_t *self)
{
    sininputs_t *c = SELF(self);
    char _res_uri[4096];
    _compute_res_uri(_res_uri, sizeof(_res_uri));
    c->inst = SinInputs_fmi2Instantiate(
        SININPUTS_MODEL_NAME, fmi2CoSimulation,
        SININPUTS_GUID, _res_uri,
        &_callbacks, fmi2False, fmi2False);
    if (!c->inst) return FMU_ERROR;
    fmi2Status st = SinInputs_fmi2SetupExperiment(c->inst, fmi2False, 0.0, 0.0, fmi2False, 0.0);
    if (st > fmi2Warning) goto fail;
    st = SinInputs_fmi2EnterInitializationMode(c->inst);
    if (st > fmi2Warning) goto fail;
    st = SinInputs_fmi2ExitInitializationMode(c->inst);
    if (st > fmi2Warning) goto fail;
    self->current_time = 0.0;
    self->termination_requested = 0;
    self->next_event_time_defined = 0;
    self->next_event_time = 0.0;
    return FMU_OK;
fail:
    SinInputs_fmi2FreeInstance(c->inst);
    c->inst = NULL;
    return _status(st);
}

static fmu_status_t _terminate(fmu_t *self)
{
    sininputs_t *c = SELF(self);
    if (!c->inst) return FMU_OK;
    fmi2Status st = SinInputs_fmi2Terminate(c->inst);
    SinInputs_fmi2FreeInstance(c->inst);
    c->inst = NULL;
    return _status(st);
}

static fmu_status_t _reset(fmu_t *self)
{
    sininputs_t *c = SELF(self);
    fmi2Status st = SinInputs_fmi2Reset(c->inst);
    self->current_time = 0.0;
    return _status(st);
}

static fmu_status_t _do_step(fmu_t *self, fmu_real_t t, fmu_real_t h)
{
    sininputs_t *c = SELF(self);
    fmi2Status st = SinInputs_fmi2DoStep(c->inst, (fmi2Real)t, (fmi2Real)h, fmi2True);
    if (st == fmi2OK || st == fmi2Warning) {
        self->current_time = t + h;
        return FMU_OK;
    }
    return FMU_ERROR;
}

static fmu_status_t _get_real(fmu_t *self,
    const fmu_vref_t *vr, int n, fmu_real_t *out)
{
    sininputs_t *c = SELF(self);
    fmi2Status st = SinInputs_fmi2GetReal(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (fmi2Real *)out);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _set_real(fmu_t *self,
    const fmu_vref_t *vr, int n, const fmu_real_t *in)
{
    sininputs_t *c = SELF(self);
    fmi2Status st = SinInputs_fmi2SetReal(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (const fmi2Real *)in);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static sininputs_t _instance_cs = {
    .base = {
        .model_name   = SININPUTS_MODEL_NAME,
        .guid         = SININPUTS_GUID,
        .mode         = FMU_MODE_CS,
        .n_states     = SININPUTS_N_STATES,
        .step_size    = 0.01,
        .current_time = 0.0,
        .initialize   = _initialize,
        .terminate    = _terminate,
        .reset        = _reset,
        .do_step              = _do_step,
        .set_time             = NULL,
        .get_derivatives      = NULL,
        .get_cont_states      = NULL,
        .set_cont_states      = NULL,
        .completed_step       = NULL,
        .enter_event_mode     = NULL,
        .new_discrete_states  = NULL,
        .enter_cont_mode      = NULL,
        .get_event_indicators = NULL,
        .get_real       = _get_real,
        .set_real       = _set_real,
        .get_boolean    = NULL,
        .set_boolean    = NULL,
        .get_integer    = NULL,
        .set_integer    = NULL,
        .get_string     = NULL,
        .set_string     = NULL,
        .get_clock    = NULL,
        .tick_freq    = 0,
    },
    .inst = NULL,
};

fmu_t *sininputs_create_cs(void)
{
    return &_instance_cs.base;
}
