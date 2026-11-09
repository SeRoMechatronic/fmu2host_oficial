/**
 * @file   reguladorbateria_adapter_me.c
 * @brief  Wrapper fmu_t HOST (Model Exchange) para ReguladorBateria.
 *
 *  Instancia la FMU como fmi2ModelExchange y delega TODAS las
 *  operaciones al runtime de OpenModelica. No reimplementa ecuaciones.
 *
 *  Usar con main_me.c + fmu_euler_step() o fmu_rk4_step().
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */
/* Source artifact: ReguladorBateria (path intentionally omitted). */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "fmi2_api.h"
#include "fmu_t.h"
#include "reguladorbateria_adapter.h"

/* Funciones FMI 2.0 del runtime de OpenModelica (prefijo 'ReguladorBateria_') */
extern fmi2Component ReguladorBateria_fmi2Instantiate(
    fmi2String, fmi2Type, fmi2String, fmi2String,
    const fmi2CallbackFunctions *, fmi2Boolean, fmi2Boolean);
extern fmi2Status ReguladorBateria_fmi2SetupExperiment(
    fmi2Component, fmi2Boolean, fmi2Real, fmi2Real, fmi2Boolean, fmi2Real);
extern fmi2Status ReguladorBateria_fmi2EnterInitializationMode(fmi2Component);
extern fmi2Status ReguladorBateria_fmi2ExitInitializationMode(fmi2Component);
extern fmi2Status ReguladorBateria_fmi2Terminate(fmi2Component);
extern void       ReguladorBateria_fmi2FreeInstance(fmi2Component);
extern fmi2Status ReguladorBateria_fmi2Reset(fmi2Component);

/* Model Exchange: el llamador integra con su solver */
extern fmi2Status ReguladorBateria_fmi2SetTime(fmi2Component, fmi2Real);
extern fmi2Status ReguladorBateria_fmi2SetContinuousStates(fmi2Component, const fmi2Real *, size_t);
extern fmi2Status ReguladorBateria_fmi2GetDerivatives(fmi2Component, fmi2Real *, size_t);
extern fmi2Status ReguladorBateria_fmi2GetContinuousStates(fmi2Component, fmi2Real *, size_t);
extern fmi2Status ReguladorBateria_fmi2CompletedIntegratorStep(
    fmi2Component, fmi2Boolean, fmi2Boolean *, fmi2Boolean *);
extern fmi2Status ReguladorBateria_fmi2EnterEventMode(fmi2Component);
extern fmi2Status ReguladorBateria_fmi2NewDiscreteStates(fmi2Component, fmi2EventInfo *);
extern fmi2Status ReguladorBateria_fmi2EnterContinuousTimeMode(fmi2Component);
extern fmi2Status ReguladorBateria_fmi2GetEventIndicators(fmi2Component, fmi2Real *, size_t);

extern fmi2Status ReguladorBateria_fmi2GetReal(
    fmi2Component, const fmi2ValueReference *, size_t, fmi2Real *);
extern fmi2Status ReguladorBateria_fmi2SetReal(
    fmi2Component, const fmi2ValueReference *, size_t, const fmi2Real *);

extern fmi2Status ReguladorBateria_fmi2GetBoolean(
    fmi2Component, const fmi2ValueReference *, size_t, fmi2Boolean *);
extern fmi2Status ReguladorBateria_fmi2SetBoolean(
    fmi2Component, const fmi2ValueReference *, size_t, const fmi2Boolean *);

static void _logger(fmi2ComponentEnvironment env, fmi2String inst,
                    fmi2Status status, fmi2String cat,
                    fmi2String msg, ...) {
    (void)env; (void)inst; (void)status;
    va_list args; va_start(args, msg);
    fprintf(stderr, "[ReguladorBateria/%s] ", cat);
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
    fmu_t         base;   /* PRIMER CAMPO: permite cast (fmu_t *) -> (reguladorbateria_t *) */
    fmi2Component inst;   /* Handle opaco de la instancia FMI 2.0 */
} reguladorbateria_t;
#define SELF(p)  ((reguladorbateria_t *)(p))

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
    reguladorbateria_t *c = SELF(self);
    char _res_uri[4096];
    _compute_res_uri(_res_uri, sizeof(_res_uri));
    c->inst = ReguladorBateria_fmi2Instantiate(
        REGULADORBATERIA_MODEL_NAME, fmi2ModelExchange,
        REGULADORBATERIA_GUID, _res_uri,
        &_callbacks, fmi2False, fmi2False);
    if (!c->inst) return FMU_ERROR;
    fmi2Status st = ReguladorBateria_fmi2SetupExperiment(c->inst, fmi2False, 0.0, 0.0, fmi2False, 0.0);
    if (st > fmi2Warning) goto fail;
    st = ReguladorBateria_fmi2EnterInitializationMode(c->inst);
    if (st > fmi2Warning) goto fail;
    st = ReguladorBateria_fmi2ExitInitializationMode(c->inst);
    if (st > fmi2Warning) goto fail;
    self->current_time = 0.0;
    self->termination_requested = 0;
    self->next_event_time_defined = 0;
    self->next_event_time = 0.0;
    return FMU_OK;
fail:
    ReguladorBateria_fmi2FreeInstance(c->inst);
    c->inst = NULL;
    return _status(st);
}

static fmu_status_t _terminate(fmu_t *self)
{
    reguladorbateria_t *c = SELF(self);
    if (!c->inst) return FMU_OK;
    fmi2Status st = ReguladorBateria_fmi2Terminate(c->inst);
    ReguladorBateria_fmi2FreeInstance(c->inst);
    c->inst = NULL;
    return _status(st);
}

static fmu_status_t _reset(fmu_t *self)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2Reset(c->inst);
    self->current_time = 0.0;
    return _status(st);
}

static fmu_status_t _set_time(fmu_t *self, fmu_real_t t)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2SetTime(c->inst, (fmi2Real)t);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _get_derivatives(fmu_t *self, fmu_real_t *dx, int n)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2GetDerivatives(c->inst, (fmi2Real *)dx, (size_t)n);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _get_cont_states(fmu_t *self, fmu_real_t *x, int n)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2GetContinuousStates(c->inst, (fmi2Real *)x, (size_t)n);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _set_cont_states(fmu_t *self, const fmu_real_t *x, int n)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2SetContinuousStates(c->inst, (const fmi2Real *)x, (size_t)n);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _completed_step(fmu_t *self, fmu_bool_t *enter_event)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Boolean ev = fmi2False, term = fmi2False;
    fmi2Status st = ReguladorBateria_fmi2CompletedIntegratorStep(c->inst, fmi2True, &ev, &term);
    *enter_event = (fmu_bool_t)ev;
    self->termination_requested = (fmu_bool_t)term;
    return _status(st);
}

static fmu_status_t _enter_event_mode(fmu_t *self)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2EnterEventMode(c->inst);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _new_discrete_states(fmu_t *self,
    fmu_bool_t *more, fmu_bool_t *terminate)
{
    reguladorbateria_t *c = SELF(self);
    fmi2EventInfo ei = {fmi2False, fmi2False, fmi2False, fmi2False, fmi2False, 0.0};
    fmi2Status st = ReguladorBateria_fmi2NewDiscreteStates(c->inst, &ei);
    *more      = (fmu_bool_t)ei.newDiscreteStatesNeeded;
    *terminate = (fmu_bool_t)ei.terminateSimulation;
    self->termination_requested = (fmu_bool_t)ei.terminateSimulation;
    self->next_event_time_defined = (fmu_bool_t)ei.nextEventTimeDefined;
    self->next_event_time = (fmu_real_t)ei.nextEventTime;
    return _status(st);
}

static fmu_status_t _enter_cont_mode(fmu_t *self)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2EnterContinuousTimeMode(c->inst);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _get_event_indicators(fmu_t *self, fmu_real_t *ei, int n)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2GetEventIndicators(c->inst, (fmi2Real *)ei, (size_t)n);
    return (st == fmi2OK) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _get_real(fmu_t *self,
    const fmu_vref_t *vr, int n, fmu_real_t *out)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2GetReal(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (fmi2Real *)out);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _set_real(fmu_t *self,
    const fmu_vref_t *vr, int n, const fmu_real_t *in)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2SetReal(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (const fmi2Real *)in);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _get_boolean(fmu_t *self,
    const fmu_vref_t *vr, int n, fmu_bool_t *out)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2GetBoolean(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (fmi2Boolean *)out);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static fmu_status_t _set_boolean(fmu_t *self,
    const fmu_vref_t *vr, int n, const fmu_bool_t *in)
{
    reguladorbateria_t *c = SELF(self);
    fmi2Status st = ReguladorBateria_fmi2SetBoolean(
        c->inst, (const fmi2ValueReference *)vr, (size_t)n, (const fmi2Boolean *)in);
    return (st == fmi2OK || st == fmi2Warning) ? FMU_OK : FMU_ERROR;
}

static reguladorbateria_t _instance_me = {
    .base = {
        .model_name   = REGULADORBATERIA_MODEL_NAME,
        .guid         = REGULADORBATERIA_GUID,
        .mode         = FMU_MODE_ME,
        .n_states     = REGULADORBATERIA_N_STATES,
        .step_size    = 0.01,
        .current_time = 0.0,
        .initialize   = _initialize,
        .terminate    = _terminate,
        .reset        = _reset,
        .do_step              = NULL,
        .set_time             = _set_time,
        .get_derivatives      = _get_derivatives,
        .get_cont_states      = _get_cont_states,
        .set_cont_states      = _set_cont_states,
        .completed_step       = _completed_step,
        .enter_event_mode     = _enter_event_mode,
        .new_discrete_states  = _new_discrete_states,
        .enter_cont_mode      = _enter_cont_mode,
        .get_event_indicators = _get_event_indicators,
        .get_real       = _get_real,
        .set_real       = _set_real,
        .get_boolean    = _get_boolean,
        .set_boolean    = _set_boolean,
        .get_integer    = NULL,
        .set_integer    = NULL,
        .get_string     = NULL,
        .set_string     = NULL,
        .get_clock    = NULL,
        .tick_freq    = 0,
    },
    .inst = NULL,
};

fmu_t *reguladorbateria_create_me(void)
{
    return &_instance_me.base;
}
