/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para CuerposAcoplados — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : CuerposAcoplados
 * GUID   : {524f87b0-4900-4b8c-a309-98239f39e4fa}
 * Estados: 4  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "cuerposacoplados_api.h"
#include "cuerposacoplados_adapter.h"

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
    double _cli_fuerza_externa = 0.0; int _has_fuerza_externa = 0;
    struct { double t; double val; } _sched_fuerza_externa[_MAX_SCHED]; int _ns_fuerza_externa = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "fuerza_externa") == 0 && _ns_fuerza_externa < _MAX_SCHED) {
                _sched_fuerza_externa[_ns_fuerza_externa].t   = _at_t;
                _sched_fuerza_externa[_ns_fuerza_externa++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "fuerza_externa") == 0) { _cli_fuerza_externa = (double)(atof(_eq+1)); _has_fuerza_externa = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = cuerposacoplados_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_fuerza_externa = CUERPOSACOPLADOS_VR_FUERZA_EXTERNA;
    const fmu_vref_t vr_en_fase = CUERPOSACOPLADOS_VR_EN_FASE;
    const fmu_vref_t vr_energia_total = CUERPOSACOPLADOS_VR_ENERGIA_TOTAL;
    const fmu_vref_t vr_pos1 = CUERPOSACOPLADOS_VR_POS1;
    const fmu_vref_t vr_pos2 = CUERPOSACOPLADOS_VR_POS2;
    const fmu_vref_t vr_vel1 = CUERPOSACOPLADOS_VR_VEL1;
    const fmu_vref_t vr_vel2 = CUERPOSACOPLADOS_VR_VEL2;

    fmu_real_t solver_buf[CUERPOSACOPLADOS_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? CUERPOSACOPLADOS_RK4_BUF_SIZE : CUERPOSACOPLADOS_EULER_BUF_SIZE);

    fmu_real_t x[CUERPOSACOPLADOS_N_STATES];
    FMU_CALL(m, get_cont_states, x, CUERPOSACOPLADOS_N_STATES);

    fmu_real_t ei_prev[CUERPOSACOPLADOS_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[CUERPOSACOPLADOS_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, CUERPOSACOPLADOS_N_EVENT_INDICATORS);

    SIM_PRINT("t,fuerza_externa,en_fase,energia_total,pos1,pos2,vel1,vel2\n");

    double t = 0.0;
    for (;;) {

        CuerposAcoplados_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_fuerza_externa) in.fuerza_externa = (double)_cli_fuerza_externa;
        if (_ns_fuerza_externa > 0) {
            double _bv = (double)in.fuerza_externa; double _bt = -1e300;
            for (int _si = 0; _si < _ns_fuerza_externa; _si++)
                if (t >= _sched_fuerza_externa[_si].t && _sched_fuerza_externa[_si].t >= _bt)
                    { _bv = _sched_fuerza_externa[_si].val; _bt = _sched_fuerza_externa[_si].t; }
            in.fuerza_externa = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_fuerza_externa = (fmu_real_t)in.fuerza_externa;
            FMU_CALL(m, set_real, &vr_fuerza_externa, 1, (const fmu_real_t *)&_i_fuerza_externa);
        }

        FMU_CALL(m, set_cont_states, x, CUERPOSACOPLADOS_N_STATES);

        CuerposAcoplados_Outputs out = {0};
        {
            fmu_bool_t _o_en_fase = 0;
            FMU_CALL(m, get_boolean, &vr_en_fase, 1, &_o_en_fase);
            out.en_fase = (int)_o_en_fase;
        }
        {
            fmu_real_t _o_energia_total = 0.0;
            FMU_CALL(m, get_real, &vr_energia_total, 1, &_o_energia_total);
            out.energia_total = (double)_o_energia_total;
        }
        {
            fmu_real_t _o_pos1 = 0.0;
            FMU_CALL(m, get_real, &vr_pos1, 1, &_o_pos1);
            out.pos1 = (double)_o_pos1;
        }
        {
            fmu_real_t _o_pos2 = 0.0;
            FMU_CALL(m, get_real, &vr_pos2, 1, &_o_pos2);
            out.pos2 = (double)_o_pos2;
        }
        {
            fmu_real_t _o_vel1 = 0.0;
            FMU_CALL(m, get_real, &vr_vel1, 1, &_o_vel1);
            out.vel1 = (double)_o_vel1;
        }
        {
            fmu_real_t _o_vel2 = 0.0;
            FMU_CALL(m, get_real, &vr_vel2, 1, &_o_vel2);
            out.vel2 = (double)_o_vel2;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, in.fuerza_externa, (int)out.en_fase, out.energia_total, out.pos1, out.pos2, out.vel1, out.vel2);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, CUERPOSACOPLADOS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, CUERPOSACOPLADOS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, CUERPOSACOPLADOS_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < CUERPOSACOPLADOS_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < CUERPOSACOPLADOS_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, CUERPOSACOPLADOS_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, CUERPOSACOPLADOS_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
