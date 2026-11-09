/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para SuspensionActiva — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : SuspensionActiva
 * GUID   : {d502a71c-9992-47e0-952e-c751a997751d}
 * Estados: 2  |  Indicadores: 3
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "suspensionactiva_api.h"
#include "suspensionactiva_adapter.h"

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
    double _cli_perfil_bache = 0.0; int _has_perfil_bache = 0;
    struct { double t; double val; } _sched_perfil_bache[_MAX_SCHED]; int _ns_perfil_bache = 0;
    double _cli_velocidad_vehiculo = 0.0; int _has_velocidad_vehiculo = 0;
    struct { double t; double val; } _sched_velocidad_vehiculo[_MAX_SCHED]; int _ns_velocidad_vehiculo = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "perfil_bache") == 0 && _ns_perfil_bache < _MAX_SCHED) {
                _sched_perfil_bache[_ns_perfil_bache].t   = _at_t;
                _sched_perfil_bache[_ns_perfil_bache++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "velocidad_vehiculo") == 0 && _ns_velocidad_vehiculo < _MAX_SCHED) {
                _sched_velocidad_vehiculo[_ns_velocidad_vehiculo].t   = _at_t;
                _sched_velocidad_vehiculo[_ns_velocidad_vehiculo++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "perfil_bache") == 0) { _cli_perfil_bache = (double)(atof(_eq+1)); _has_perfil_bache = 1; }
            if (strcmp(argv[_oi], "velocidad_vehiculo") == 0) { _cli_velocidad_vehiculo = (double)(atof(_eq+1)); _has_velocidad_vehiculo = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = suspensionactiva_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_perfil_bache = SUSPENSIONACTIVA_VR_PERFIL_BACHE;
    const fmu_vref_t vr_velocidad_vehiculo = SUSPENSIONACTIVA_VR_VELOCIDAD_VEHICULO;
    const fmu_vref_t vr_actuador_saturado = SUSPENSIONACTIVA_VR_ACTUADOR_SATURADO;
    const fmu_vref_t vr_bache_detectado = SUSPENSIONACTIVA_VR_BACHE_DETECTADO;
    const fmu_vref_t vr_modo_confort = SUSPENSIONACTIVA_VR_MODO_CONFORT;
    const fmu_vref_t vr_fuerza_actuador = SUSPENSIONACTIVA_VR_FUERZA_ACTUADOR;

    fmu_real_t solver_buf[SUSPENSIONACTIVA_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? SUSPENSIONACTIVA_RK4_BUF_SIZE : SUSPENSIONACTIVA_EULER_BUF_SIZE);

    fmu_real_t x[SUSPENSIONACTIVA_N_STATES];
    FMU_CALL(m, get_cont_states, x, SUSPENSIONACTIVA_N_STATES);

    fmu_real_t ei_prev[SUSPENSIONACTIVA_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[SUSPENSIONACTIVA_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, SUSPENSIONACTIVA_N_EVENT_INDICATORS);

    SIM_PRINT("t,perfil_bache,velocidad_vehiculo,actuador_saturado,bache_detectado,modo_confort,fuerza_actuador\n");

    double t = 0.0;
    for (;;) {

        SuspensionActiva_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_perfil_bache) in.perfil_bache = (double)_cli_perfil_bache;
        if (_ns_perfil_bache > 0) {
            double _bv = (double)in.perfil_bache; double _bt = -1e300;
            for (int _si = 0; _si < _ns_perfil_bache; _si++)
                if (t >= _sched_perfil_bache[_si].t && _sched_perfil_bache[_si].t >= _bt)
                    { _bv = _sched_perfil_bache[_si].val; _bt = _sched_perfil_bache[_si].t; }
            in.perfil_bache = (double)_bv;
        }
        if (_has_velocidad_vehiculo) in.velocidad_vehiculo = (double)_cli_velocidad_vehiculo;
        if (_ns_velocidad_vehiculo > 0) {
            double _bv = (double)in.velocidad_vehiculo; double _bt = -1e300;
            for (int _si = 0; _si < _ns_velocidad_vehiculo; _si++)
                if (t >= _sched_velocidad_vehiculo[_si].t && _sched_velocidad_vehiculo[_si].t >= _bt)
                    { _bv = _sched_velocidad_vehiculo[_si].val; _bt = _sched_velocidad_vehiculo[_si].t; }
            in.velocidad_vehiculo = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_perfil_bache = (fmu_real_t)in.perfil_bache;
            FMU_CALL(m, set_real, &vr_perfil_bache, 1, (const fmu_real_t *)&_i_perfil_bache);
        }
        {
            fmu_real_t _i_velocidad_vehiculo = (fmu_real_t)in.velocidad_vehiculo;
            FMU_CALL(m, set_real, &vr_velocidad_vehiculo, 1, (const fmu_real_t *)&_i_velocidad_vehiculo);
        }

        FMU_CALL(m, set_cont_states, x, SUSPENSIONACTIVA_N_STATES);

        SuspensionActiva_Outputs out = {0};
        {
            fmu_bool_t _o_actuador_saturado = 0;
            FMU_CALL(m, get_boolean, &vr_actuador_saturado, 1, &_o_actuador_saturado);
            out.actuador_saturado = (int)_o_actuador_saturado;
        }
        {
            fmu_bool_t _o_bache_detectado = 0;
            FMU_CALL(m, get_boolean, &vr_bache_detectado, 1, &_o_bache_detectado);
            out.bache_detectado = (int)_o_bache_detectado;
        }
        {
            fmu_bool_t _o_modo_confort = 0;
            FMU_CALL(m, get_boolean, &vr_modo_confort, 1, &_o_modo_confort);
            out.modo_confort = (int)_o_modo_confort;
        }
        {
            fmu_real_t _o_fuerza_actuador = 0.0;
            FMU_CALL(m, get_real, &vr_fuerza_actuador, 1, &_o_fuerza_actuador);
            out.fuerza_actuador = (double)_o_fuerza_actuador;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.perfil_bache, in.velocidad_vehiculo, (int)out.actuador_saturado, (int)out.bache_detectado, (int)out.modo_confort, out.fuerza_actuador);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, SUSPENSIONACTIVA_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, SUSPENSIONACTIVA_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, SUSPENSIONACTIVA_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < SUSPENSIONACTIVA_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < SUSPENSIONACTIVA_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, SUSPENSIONACTIVA_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, SUSPENSIONACTIVA_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
