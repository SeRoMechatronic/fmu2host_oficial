/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para MuchosEstados — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : MuchosEstados
 * GUID   : {c3a45dfb-0863-485d-8cc5-47ecfd93da7d}
 * Estados: 8  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "muchosestados_api.h"
#include "muchosestados_adapter.h"

#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#define SIM_ERROR(msg)       fprintf(stderr, "%s", msg)
#define SIM_DELAY(h)         ((void)(h))

static int process_events(fmu_t *m)
{
    if (FMU_CALL(m, enter_event_mode) > FMU_WARNING) return -1;
    fmu_bool_t more = 1, terminate = 0;
    while (more && !terminate) {
        if (FMU_CALL(m, new_discrete_states, &more, &terminate) > FMU_WARNING)
            return -1;
    }
    if (terminate) return -1;
    return (FMU_CALL(m, enter_cont_mode) <= FMU_WARNING) ? 0 : -1;
}

int main(int argc, char *argv[])
{
    SimConfig cfg = get_config();

    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);
    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h     = atof(argv[2]);
    if (argc >= 4 && !strchr(argv[3], '=')) cfg.use_rk4 = (strcmp(argv[3], "rk4") == 0);

    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    #define _MAX_SCHED 512
    double _cli_u = 0.0; int _has_u = 0;
    struct { double t; double val; } _sched_u[_MAX_SCHED]; int _ns_u = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "u") == 0 && _ns_u < _MAX_SCHED) {
                _sched_u[_ns_u].t   = _at_t;
                _sched_u[_ns_u++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "u") == 0) { _cli_u = (double)(atof(_eq+1)); _has_u = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = muchosestados_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_u = MUCHOSESTADOS_VR_U;
    const fmu_vref_t vr_todos_activos = MUCHOSESTADOS_VR_TODOS_ACTIVOS;
    const fmu_vref_t vr_y1 = MUCHOSESTADOS_VR_Y1;
    const fmu_vref_t vr_y2 = MUCHOSESTADOS_VR_Y2;
    const fmu_vref_t vr_y3 = MUCHOSESTADOS_VR_Y3;
    const fmu_vref_t vr_y4 = MUCHOSESTADOS_VR_Y4;
    const fmu_vref_t vr_y5 = MUCHOSESTADOS_VR_Y5;
    const fmu_vref_t vr_y6 = MUCHOSESTADOS_VR_Y6;
    const fmu_vref_t vr_y7 = MUCHOSESTADOS_VR_Y7;
    const fmu_vref_t vr_y8 = MUCHOSESTADOS_VR_Y8;

    fmu_real_t solver_buf[MUCHOSESTADOS_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? MUCHOSESTADOS_RK4_BUF_SIZE : MUCHOSESTADOS_EULER_BUF_SIZE);

    fmu_real_t x[MUCHOSESTADOS_N_STATES];
    FMU_CALL(m, get_cont_states, x, MUCHOSESTADOS_N_STATES);

    fmu_real_t ei_prev[MUCHOSESTADOS_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[MUCHOSESTADOS_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, MUCHOSESTADOS_N_EVENT_INDICATORS);

    SIM_PRINT("t,u,todos_activos,y1,y2,y3,y4,y5,y6,y7,y8\n");

    double t = 0.0;
    for (;;) {

        MuchosEstados_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_u) in.u = (double)_cli_u;
        if (_ns_u > 0) {
            double _bv = (double)in.u; double _bt = -1e300;
            for (int _si = 0; _si < _ns_u; _si++)
                if (t >= _sched_u[_si].t && _sched_u[_si].t >= _bt)
                    { _bv = _sched_u[_si].val; _bt = _sched_u[_si].t; }
            in.u = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_u = (fmu_real_t)in.u;
            FMU_CALL(m, set_real, &vr_u, 1, (const fmu_real_t *)&_i_u);
        }

        FMU_CALL(m, set_cont_states, x, MUCHOSESTADOS_N_STATES);

        MuchosEstados_Outputs out = {0};
        {
            fmu_bool_t _o_todos_activos = 0;
            FMU_CALL(m, get_boolean, &vr_todos_activos, 1, &_o_todos_activos);
            out.todos_activos = (int)_o_todos_activos;
        }
        {
            fmu_real_t _o_y1 = 0.0;
            FMU_CALL(m, get_real, &vr_y1, 1, &_o_y1);
            out.y1 = (double)_o_y1;
        }
        {
            fmu_real_t _o_y2 = 0.0;
            FMU_CALL(m, get_real, &vr_y2, 1, &_o_y2);
            out.y2 = (double)_o_y2;
        }
        {
            fmu_real_t _o_y3 = 0.0;
            FMU_CALL(m, get_real, &vr_y3, 1, &_o_y3);
            out.y3 = (double)_o_y3;
        }
        {
            fmu_real_t _o_y4 = 0.0;
            FMU_CALL(m, get_real, &vr_y4, 1, &_o_y4);
            out.y4 = (double)_o_y4;
        }
        {
            fmu_real_t _o_y5 = 0.0;
            FMU_CALL(m, get_real, &vr_y5, 1, &_o_y5);
            out.y5 = (double)_o_y5;
        }
        {
            fmu_real_t _o_y6 = 0.0;
            FMU_CALL(m, get_real, &vr_y6, 1, &_o_y6);
            out.y6 = (double)_o_y6;
        }
        {
            fmu_real_t _o_y7 = 0.0;
            FMU_CALL(m, get_real, &vr_y7, 1, &_o_y7);
            out.y7 = (double)_o_y7;
        }
        {
            fmu_real_t _o_y8 = 0.0;
            FMU_CALL(m, get_real, &vr_y8, 1, &_o_y8);
            out.y8 = (double)_o_y8;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, in.u, (int)out.todos_activos, out.y1, out.y2, out.y3, out.y4, out.y5, out.y6, out.y7, out.y8);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, MUCHOSESTADOS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, MUCHOSESTADOS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, MUCHOSESTADOS_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < MUCHOSESTADOS_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < MUCHOSESTADOS_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, MUCHOSESTADOS_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, MUCHOSESTADOS_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
