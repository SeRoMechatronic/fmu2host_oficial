/**
 * fmu_euler.c — Solver Euler explícito (RK1) para FMUs Model Exchange
 *
 * Algoritmo:
 *   1. Evalúa la derivada en el punto actual:  dx = f(x, t)
 *   2. Avanza el estado:                       x += h * dx
 *   3. Notifica a la FMU que el paso terminó.
 *
 * Sin malloc. El buffer de trabajo lo provee el caller (ver fmu_solver.h).
 */

#include "fmu_solver.h"
#include <stddef.h>  /* NULL */

/* =========================================================================
 * Función interna: evalúa derivadas en un punto (x_eval, t_eval)
 *
 * Secuencia FMI 2.0 ME obligatoria:
 *   fmi2SetTime → fmi2SetContinuousStates → fmi2GetDerivatives
 * ========================================================================= */

static fmu_status_t eval_deriv(fmu_t *m, fmu_solver_t *s,
                                const fmu_real_t *x_eval, int nx,
                                fmu_real_t t_eval,
                                fmu_real_t *dx_out)
{
    fmu_status_t st;

    st = m->set_time(m, t_eval);
    if (st != FMU_OK) return st;

    st = m->set_cont_states(m, x_eval, nx);
    if (st != FMU_OK) return st;

    /* Re-aplicar entradas tras set_time/set_cont_states: algunos runtimes ME
     * no conservan los inputs entre evaluaciones de derivadas. */
    if (s->apply_inputs != NULL) s->apply_inputs(m, s->inputs_ctx);

    return m->get_derivatives(m, dx_out, nx);
}

/* =========================================================================
 * fmu_solver_init
 * ========================================================================= */

fmu_status_t fmu_solver_init(fmu_solver_t *s, fmu_real_t *work, int size)
{
    if (s == NULL || work == NULL || size <= 0) return FMU_ERROR;
    s->work = work;
    s->size = size;
    s->apply_inputs = NULL;
    s->inputs_ctx   = NULL;
    return FMU_OK;
}

/* =========================================================================
 * fmu_euler_step
 *
 * Buffer de trabajo (s->work):
 *   [ dx[0] .. dx[nx-1] ]
 *   total = nx elementos = FMU_EULER_WORK_SIZE(nx)
 * ========================================================================= */

fmu_status_t fmu_euler_step(fmu_t *m, fmu_solver_t *s,
                             fmu_real_t *x, int nx,
                             fmu_real_t t, fmu_real_t h)
{
    /* Validaciones */
    if (m == NULL || s == NULL || x == NULL || nx <= 0) return FMU_ERROR;
    if (m->set_time        == NULL) return FMU_ERROR;
    if (m->set_cont_states == NULL) return FMU_ERROR;
    if (m->get_derivatives == NULL) return FMU_ERROR;
    if (s->size < FMU_EULER_WORK_SIZE(nx))  return FMU_ERROR;

    fmu_real_t *dx = s->work;   /* dx[0..nx-1] */

    fmu_status_t st;

    /* ── Paso 1: dx = f(x, t) ─────────────────────────────────────────────── */
    st = eval_deriv(m, s, x, nx, t, dx);
    if (st != FMU_OK) return st;

    /* ── Paso 2: x = x + h·dx ────────────────────────────────────────────── */
    for (int i = 0; i < nx; i++) {
        x[i] += h * dx[i];
    }

    /* ── Paso 3: comunicar el nuevo estado a la FMU ───────────────────────── */
    st = m->set_time(m, t + h);
    if (st != FMU_OK) return st;

    st = m->set_cont_states(m, x, nx);
    if (st != FMU_OK) return st;

    /* completed_step NO se llama aquí: es responsabilidad del caller.
     * El main.c generado lo llama después de leer event indicators,
     * para poder propagar enter_event correctamente al bucle de eventos. */

    m->current_time = t + h;
    return FMU_OK;
}
