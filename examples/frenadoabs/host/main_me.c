/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para FrenadoABS — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : FrenadoABS
 * GUID   : {46fc3434-2fca-47d6-8ce3-46700e75280c}
 * Estados: 5  |  Indicadores: 4
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "frenadoabs_api.h"
#include "frenadoabs_adapter.h"

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
    double _cli_presion_pedal = 0.0; int _has_presion_pedal = 0;
    struct { double t; double val; } _sched_presion_pedal[_MAX_SCHED]; int _ns_presion_pedal = 0;
    double _cli_velocidad_rueda = 0.0; int _has_velocidad_rueda = 0;
    struct { double t; double val; } _sched_velocidad_rueda[_MAX_SCHED]; int _ns_velocidad_rueda = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "presion_pedal") == 0 && _ns_presion_pedal < _MAX_SCHED) {
                _sched_presion_pedal[_ns_presion_pedal].t   = _at_t;
                _sched_presion_pedal[_ns_presion_pedal++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "velocidad_rueda") == 0 && _ns_velocidad_rueda < _MAX_SCHED) {
                _sched_velocidad_rueda[_ns_velocidad_rueda].t   = _at_t;
                _sched_velocidad_rueda[_ns_velocidad_rueda++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "presion_pedal") == 0) { _cli_presion_pedal = (double)(atof(_eq+1)); _has_presion_pedal = 1; }
            if (strcmp(argv[_oi], "velocidad_rueda") == 0) { _cli_velocidad_rueda = (double)(atof(_eq+1)); _has_velocidad_rueda = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = frenadoabs_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_presion_pedal = FRENADOABS_VR_PRESION_PEDAL;
    const fmu_vref_t vr_velocidad_rueda = FRENADOABS_VR_VELOCIDAD_RUEDA;
    const fmu_vref_t vr_abs_activo = FRENADOABS_VR_ABS_ACTIVO;
    const fmu_vref_t vr_frenado_normal = FRENADOABS_VR_FRENADO_NORMAL;
    const fmu_vref_t vr_rueda_bloqueada = FRENADOABS_VR_RUEDA_BLOQUEADA;
    const fmu_vref_t vr_presion_modulada = FRENADOABS_VR_PRESION_MODULADA;

    fmu_real_t solver_buf[FRENADOABS_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? FRENADOABS_RK4_BUF_SIZE : FRENADOABS_EULER_BUF_SIZE);

    fmu_real_t x[FRENADOABS_N_STATES];
    FMU_CALL(m, get_cont_states, x, FRENADOABS_N_STATES);

    fmu_real_t ei_prev[FRENADOABS_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[FRENADOABS_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, FRENADOABS_N_EVENT_INDICATORS);

    SIM_PRINT("t,presion_pedal,velocidad_rueda,abs_activo,frenado_normal,rueda_bloqueada,presion_modulada\n");

    double t = 0.0;
    for (;;) {

        FrenadoABS_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_presion_pedal) in.presion_pedal = (double)_cli_presion_pedal;
        if (_ns_presion_pedal > 0) {
            double _bv = (double)in.presion_pedal; double _bt = -1e300;
            for (int _si = 0; _si < _ns_presion_pedal; _si++)
                if (t >= _sched_presion_pedal[_si].t && _sched_presion_pedal[_si].t >= _bt)
                    { _bv = _sched_presion_pedal[_si].val; _bt = _sched_presion_pedal[_si].t; }
            in.presion_pedal = (double)_bv;
        }
        if (_has_velocidad_rueda) in.velocidad_rueda = (double)_cli_velocidad_rueda;
        if (_ns_velocidad_rueda > 0) {
            double _bv = (double)in.velocidad_rueda; double _bt = -1e300;
            for (int _si = 0; _si < _ns_velocidad_rueda; _si++)
                if (t >= _sched_velocidad_rueda[_si].t && _sched_velocidad_rueda[_si].t >= _bt)
                    { _bv = _sched_velocidad_rueda[_si].val; _bt = _sched_velocidad_rueda[_si].t; }
            in.velocidad_rueda = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_presion_pedal = (fmu_real_t)in.presion_pedal;
            FMU_CALL(m, set_real, &vr_presion_pedal, 1, (const fmu_real_t *)&_i_presion_pedal);
        }
        {
            fmu_real_t _i_velocidad_rueda = (fmu_real_t)in.velocidad_rueda;
            FMU_CALL(m, set_real, &vr_velocidad_rueda, 1, (const fmu_real_t *)&_i_velocidad_rueda);
        }

        FMU_CALL(m, set_cont_states, x, FRENADOABS_N_STATES);

        FrenadoABS_Outputs out = {0};
        {
            fmu_bool_t _o_abs_activo = 0;
            FMU_CALL(m, get_boolean, &vr_abs_activo, 1, &_o_abs_activo);
            out.abs_activo = (int)_o_abs_activo;
        }
        {
            fmu_bool_t _o_frenado_normal = 0;
            FMU_CALL(m, get_boolean, &vr_frenado_normal, 1, &_o_frenado_normal);
            out.frenado_normal = (int)_o_frenado_normal;
        }
        {
            fmu_bool_t _o_rueda_bloqueada = 0;
            FMU_CALL(m, get_boolean, &vr_rueda_bloqueada, 1, &_o_rueda_bloqueada);
            out.rueda_bloqueada = (int)_o_rueda_bloqueada;
        }
        {
            fmu_real_t _o_presion_modulada = 0.0;
            FMU_CALL(m, get_real, &vr_presion_modulada, 1, &_o_presion_modulada);
            out.presion_modulada = (double)_o_presion_modulada;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.presion_pedal, in.velocidad_rueda, (int)out.abs_activo, (int)out.frenado_normal, (int)out.rueda_bloqueada, out.presion_modulada);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, FRENADOABS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, FRENADOABS_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, FRENADOABS_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < FRENADOABS_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < FRENADOABS_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, FRENADOABS_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, FRENADOABS_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
