/**
 * fmu_rk4.c — Solver Runge-Kutta de orden 4 (RK4) para FMUs Model Exchange
 *
 * Algoritmo clásico RK4:
 *
 *   k1 = f( x,           t       )
 *   k2 = f( x + h/2·k1, t + h/2 )
 *   k3 = f( x + h/2·k2, t + h/2 )
 *   k4 = f( x + h·k3,   t + h   )
 *
 *   x(t+h) = x(t) + (h/6)·(k1 + 2·k2 + 2·k3 + k4)
 *
 * Error de truncamiento local O(h^5) vs O(h^2) de Euler —
 * con el mismo h, RK4 es dramáticamente más preciso.
 *
 * Sin malloc. El buffer de trabajo (5·nx elementos) lo provee el caller.
 *
 * Layout del buffer (s->work):
 *   [ k1(nx) | k2(nx) | k3(nx) | k4(nx) | x_tmp(nx) ]
 *   índices:
 *     k1    = work + 0*nx
 *     k2    = work + 1*nx
 *     k3    = work + 2*nx
 *     k4    = work + 3*nx
 *     x_tmp = work + 4*nx
 */

#include "fmu_solver.h"
#include <stddef.h>  /* NULL */

/* =========================================================================
 * Función interna: evalúa derivadas en un punto arbitrario (x_eval, t_eval)
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
 * fmu_rk4_step
 *
 * Buffer de trabajo (s->work), tamaño mínimo FMU_RK4_WORK_SIZE(nx):
 *   k1    = &work[0    ]   nx elementos
 *   k2    = &work[nx   ]   nx elementos
 *   k3    = &work[2*nx ]   nx elementos
 *   k4    = &work[3*nx ]   nx elementos
 *   x_tmp = &work[4*nx ]   nx elementos — estado de prueba para cada ki
 * ========================================================================= */

fmu_status_t fmu_rk4_step(fmu_t *m, fmu_solver_t *s,
                           fmu_real_t *x, int nx,
                           fmu_real_t t, fmu_real_t h)
{
    /* Validaciones */
    if (m == NULL || s == NULL || x == NULL || nx <= 0) return FMU_ERROR;
    if (m->set_time        == NULL) return FMU_ERROR;
    if (m->set_cont_states == NULL) return FMU_ERROR;
    if (m->get_derivatives == NULL) return FMU_ERROR;
    if (s->size < FMU_RK4_WORK_SIZE(nx))   return FMU_ERROR;

    /* Punteros a las secciones del buffer de trabajo */
    fmu_real_t *k1    = s->work + 0 * nx;
    fmu_real_t *k2    = s->work + 1 * nx;
    fmu_real_t *k3    = s->work + 2 * nx;
    fmu_real_t *k4    = s->work + 3 * nx;
    fmu_real_t *x_tmp = s->work + 4 * nx;

    const fmu_real_t h2 = h * 0.5;   /* h/2 — reutilizado 2 veces */

    fmu_status_t st;

    /* ── k1 = f(x, t) ────────────────────────────────────────────────────── */
    st = eval_deriv(m, s, x, nx, t, k1);
    if (st != FMU_OK) return st;

    /* ── k2 = f(x + h/2·k1, t + h/2) ────────────────────────────────────── */
    for (int i = 0; i < nx; i++) {
        x_tmp[i] = x[i] + h2 * k1[i];
    }
    st = eval_deriv(m, s, x_tmp, nx, t + h2, k2);
    if (st != FMU_OK) return st;

    /* ── k3 = f(x + h/2·k2, t + h/2) ────────────────────────────────────── */
    for (int i = 0; i < nx; i++) {
        x_tmp[i] = x[i] + h2 * k2[i];
    }
    st = eval_deriv(m, s, x_tmp, nx, t + h2, k3);
    if (st != FMU_OK) return st;

    /* ── k4 = f(x + h·k3, t + h) ─────────────────────────────────────────── */
    for (int i = 0; i < nx; i++) {
        x_tmp[i] = x[i] + h * k3[i];
    }
    st = eval_deriv(m, s, x_tmp, nx, t + h, k4);
    if (st != FMU_OK) return st;

    /* ── Combinación RK4: x = x + h/6·(k1 + 2k2 + 2k3 + k4) ─────────────── */
    const fmu_real_t h6 = h / 6.0;
    for (int i = 0; i < nx; i++) {
        x[i] += h6 * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
    }

    /* ── Comunicar el estado final a la FMU ───────────────────────────────── */
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
