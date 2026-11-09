/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para CrecimientoPoblacional — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : CrecimientoPoblacional
 * GUID   : {6f1a99bb-380b-404d-acf5-24f241c917f3}
 * Estados: 1  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "crecimientopoblacional_api.h"
#include "crecimientopoblacional_adapter.h"

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
    double _cli_tasa_entrada = 0.0; int _has_tasa_entrada = 0;
    struct { double t; double val; } _sched_tasa_entrada[_MAX_SCHED]; int _ns_tasa_entrada = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "tasa_entrada") == 0 && _ns_tasa_entrada < _MAX_SCHED) {
                _sched_tasa_entrada[_ns_tasa_entrada].t   = _at_t;
                _sched_tasa_entrada[_ns_tasa_entrada++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "tasa_entrada") == 0) { _cli_tasa_entrada = (double)(atof(_eq+1)); _has_tasa_entrada = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = crecimientopoblacional_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_tasa_entrada = CRECIMIENTOPOBLACIONAL_VR_TASA_ENTRADA;
    const fmu_vref_t vr_superpoblacion = CRECIMIENTOPOBLACIONAL_VR_SUPERPOBLACION;
    const fmu_vref_t vr_poblacion = CRECIMIENTOPOBLACIONAL_VR_POBLACION;
    const fmu_vref_t vr_saturacion = CRECIMIENTOPOBLACIONAL_VR_SATURACION;
    const fmu_vref_t vr_tasa_crecimiento = CRECIMIENTOPOBLACIONAL_VR_TASA_CRECIMIENTO;

    fmu_real_t solver_buf[CRECIMIENTOPOBLACIONAL_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? CRECIMIENTOPOBLACIONAL_RK4_BUF_SIZE : CRECIMIENTOPOBLACIONAL_EULER_BUF_SIZE);

    fmu_real_t x[CRECIMIENTOPOBLACIONAL_N_STATES];
    FMU_CALL(m, get_cont_states, x, CRECIMIENTOPOBLACIONAL_N_STATES);

    fmu_real_t ei_prev[CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS);

    SIM_PRINT("t,tasa_entrada,superpoblacion,poblacion,saturacion,tasa_crecimiento\n");

    double t = 0.0;
    for (;;) {

        CrecimientoPoblacional_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_tasa_entrada) in.tasa_entrada = (double)_cli_tasa_entrada;
        if (_ns_tasa_entrada > 0) {
            double _bv = (double)in.tasa_entrada; double _bt = -1e300;
            for (int _si = 0; _si < _ns_tasa_entrada; _si++)
                if (t >= _sched_tasa_entrada[_si].t && _sched_tasa_entrada[_si].t >= _bt)
                    { _bv = _sched_tasa_entrada[_si].val; _bt = _sched_tasa_entrada[_si].t; }
            in.tasa_entrada = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_tasa_entrada = (fmu_real_t)in.tasa_entrada;
            FMU_CALL(m, set_real, &vr_tasa_entrada, 1, (const fmu_real_t *)&_i_tasa_entrada);
        }

        FMU_CALL(m, set_cont_states, x, CRECIMIENTOPOBLACIONAL_N_STATES);

        CrecimientoPoblacional_Outputs out = {0};
        {
            fmu_bool_t _o_superpoblacion = 0;
            FMU_CALL(m, get_boolean, &vr_superpoblacion, 1, &_o_superpoblacion);
            out.superpoblacion = (int)_o_superpoblacion;
        }
        {
            fmu_real_t _o_poblacion = 0.0;
            FMU_CALL(m, get_real, &vr_poblacion, 1, &_o_poblacion);
            out.poblacion = (double)_o_poblacion;
        }
        {
            fmu_real_t _o_saturacion = 0.0;
            FMU_CALL(m, get_real, &vr_saturacion, 1, &_o_saturacion);
            out.saturacion = (double)_o_saturacion;
        }
        {
            fmu_real_t _o_tasa_crecimiento = 0.0;
            FMU_CALL(m, get_real, &vr_tasa_crecimiento, 1, &_o_tasa_crecimiento);
            out.tasa_crecimiento = (double)_o_tasa_crecimiento;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g\n", t, in.tasa_entrada, (int)out.superpoblacion, out.poblacion, out.saturacion, out.tasa_crecimiento);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, CRECIMIENTOPOBLACIONAL_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, CRECIMIENTOPOBLACIONAL_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, CRECIMIENTOPOBLACIONAL_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, CRECIMIENTOPOBLACIONAL_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
