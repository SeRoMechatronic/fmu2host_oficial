/**
 * fmu_t.h — Interfaz abstracta unificada para FMUs FMI 2.0
 *
 * Cubre ambos modos FMI 2.0:
 *   Co-Simulation (CS) — la FMU integra internamente → do_step
 *   Model Exchange (ME) — tú integras externamente → get_derivatives + solver
 *
 * Patrón de uso (struct apuntando a sí mismo):
 *   1. El modelo concreto define un struct con fmu_t como PRIMER campo.
 *   2. Sus funciones internas reciben fmu_t *self y hacen cast al tipo concreto.
 *   3. El código de aplicación solo ve fmu_t * — no sabe qué modelo hay debajo.
 *   4. Los punteros que el modelo no implementa se dejan en NULL.
 *
 * Compatible con host (x86/x64) y MCU bare-metal (sin malloc).
 */

#ifndef FMU_T_H
#define FMU_T_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Tipos propios — independientes del SDK FMI para mayor portabilidad
 * ========================================================================= */

typedef double       fmu_real_t;    /* coincide con fmi2Real        (64-bit) */
typedef int          fmu_bool_t;    /* coincide con fmi2Boolean     (32-bit) */
typedef int          fmu_int_t;     /* coincide con fmi2Integer     (32-bit) */
typedef const char * fmu_string_t;  /* coincide con fmi2String (puntero C)   */
typedef unsigned int fmu_vref_t;    /* coincide con fmi2ValueReference       */
typedef uint64_t     fmu_tick_t;    /* ticks de reloj de plataforma          */

typedef enum {
    FMU_OK      = 0,
    FMU_WARNING = 1,
    FMU_ERROR   = 2,
    FMU_FATAL   = 3,
} fmu_status_t;

typedef enum {
    FMU_MODE_CS = 0,   /* Co-Simulation: usar do_step              */
    FMU_MODE_ME = 1,   /* Model Exchange: usar get_derivatives      */
} fmu_mode_t;

/* =========================================================================
 * Interfaz abstracta fmu_t
 *
 * Punteros a NULL = función no implementada por este modelo.
 * Usar FMU_CALL() para invocar de forma segura.
 *
 * Correspondencia con FMI 2.0:
 *   initialize        → fmi2EnterInitializationMode + fmi2ExitInitializationMode
 *   terminate         → fmi2Terminate
 *   do_step           → fmi2DoStep                         [CS]
 *   set_time          → fmi2SetTime                        [ME]
 *   get_derivatives   → fmi2GetDerivatives                 [ME]
 *   get_cont_states   → fmi2GetContinuousStates            [ME]
 *   set_cont_states   → fmi2SetContinuousStates            [ME]
 *   completed_step       → fmi2CompletedIntegratorStep        [ME]
 *   enter_event_mode     → fmi2EnterEventMode                 [ME]
 *   new_discrete_states  → fmi2NewDiscreteStates              [ME]
 *   enter_cont_mode      → fmi2EnterContinuousTimeMode        [ME]
 *   get_real          → fmi2GetReal
 *   set_real          → fmi2SetReal
 *   get_boolean       → fmi2GetBoolean
 *   set_boolean       → fmi2SetBoolean
 *   get_integer       → fmi2GetInteger
 *   set_integer       → fmi2SetInteger
 *   get_string        → fmi2GetString
 *   set_string        → fmi2SetString
 *   get_clock         → plataforma específica (HAL)
 * ========================================================================= */

typedef struct fmu_t {

    /* ── Metadatos (solo lectura) ─────────────────────────────────────────── */
    const char *model_name;
    const char *guid;
    fmu_mode_t  mode;           /* CS o ME — determina qué punteros usar      */
    int         n_states;       /* número de estados continuos (0 si ninguno) */
    fmu_real_t  step_size;      /* h en segundos                              */
    fmu_real_t  current_time;   /* actualizado tras cada paso                 */
    fmu_bool_t  termination_requested; /* FMI requested graceful termination   */
    fmu_bool_t  next_event_time_defined; /* ME time event is scheduled          */
    fmu_real_t  next_event_time; /* next scheduled ME time event               */

    /* ── Ciclo de vida ────────────────────────────────────────────────────── */
    fmu_status_t (*initialize)(struct fmu_t *self);
    fmu_status_t (*terminate) (struct fmu_t *self);
    fmu_status_t (*reset)     (struct fmu_t *self);

    /* ── Co-Simulation ────────────────────────────────────────────────────── */
    fmu_status_t (*do_step)(struct fmu_t *self, fmu_real_t t, fmu_real_t h);

    /* ── Model Exchange ───────────────────────────────────────────────────── */
    fmu_status_t (*set_time)         (struct fmu_t *self, fmu_real_t t);
    fmu_status_t (*get_derivatives)  (struct fmu_t *self, fmu_real_t *dx, int n);
    fmu_status_t (*get_cont_states)  (struct fmu_t *self, fmu_real_t *x,  int n);
    fmu_status_t (*set_cont_states)  (struct fmu_t *self, const fmu_real_t *x, int n);
    fmu_status_t (*completed_step)       (struct fmu_t *self, fmu_bool_t *enter_event_mode);
    fmu_status_t (*enter_event_mode)     (struct fmu_t *self);
    fmu_status_t (*new_discrete_states)  (struct fmu_t *self,
                                          fmu_bool_t *more_states_needed,
                                          fmu_bool_t *terminate);
    fmu_status_t (*enter_cont_mode)      (struct fmu_t *self);
    fmu_status_t (*get_event_indicators) (struct fmu_t *self, fmu_real_t *ei, int n);

    /* ── Acceso a variables por valueReference ────────────────────────────── */
    fmu_status_t (*get_real)   (struct fmu_t *self, const fmu_vref_t *vr, int n, fmu_real_t *out);
    fmu_status_t (*set_real)   (struct fmu_t *self, const fmu_vref_t *vr, int n, const fmu_real_t *in);
    fmu_status_t (*get_boolean)(struct fmu_t *self, const fmu_vref_t *vr, int n, fmu_bool_t *out);
    fmu_status_t (*set_boolean)(struct fmu_t *self, const fmu_vref_t *vr, int n, const fmu_bool_t *in);
    fmu_status_t (*get_integer)(struct fmu_t *self, const fmu_vref_t *vr, int n, fmu_int_t *out);
    fmu_status_t (*set_integer)(struct fmu_t *self, const fmu_vref_t *vr, int n, const fmu_int_t *in);
    /* fmi2String = const char*: get devuelve punteros a strings internas de la FMU */
    fmu_status_t (*get_string) (struct fmu_t *self, const fmu_vref_t *vr, int n, fmu_string_t *out);
    fmu_status_t (*set_string) (struct fmu_t *self, const fmu_vref_t *vr, int n, const fmu_string_t *in);

    /* ── Reloj de plataforma (HAL) ────────────────────────────────────────── */
    fmu_tick_t   tick_freq;      /* ticks por segundo de esta plataforma       */
    fmu_tick_t (*get_clock)(struct fmu_t *self);

} fmu_t;

/* =========================================================================
 * Macros de conveniencia
 * ========================================================================= */

/* Invoca fn(self, ...) solo si el puntero no es NULL */
#define FMU_CALL(m, fn, ...) \
    ((m)->fn ? (m)->fn((m), ##__VA_ARGS__) : FMU_OK)

/* Tiempo transcurrido en segundos entre t0 (ticks) y ahora */
static inline fmu_real_t fmu_elapsed_s(fmu_t *m, fmu_tick_t t0)
{
    return (fmu_real_t)(m->get_clock(m) - t0) / (fmu_real_t)m->tick_freq;
}

#ifdef __cplusplus
}
#endif

#endif /* FMU_T_H */
