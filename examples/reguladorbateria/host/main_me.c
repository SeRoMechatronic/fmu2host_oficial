/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para ReguladorBateria — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : ReguladorBateria
 * GUID   : {69132570-939a-43d4-814a-e9b7801e344c}
 * Estados: 2  |  Indicadores: 3
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "reguladorbateria_api.h"
#include "reguladorbateria_adapter.h"

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
    double _cli_carga_conectada = 0.0; int _has_carga_conectada = 0;
    struct { double t; double val; } _sched_carga_conectada[_MAX_SCHED]; int _ns_carga_conectada = 0;
    double _cli_tension_bateria = 0.0; int _has_tension_bateria = 0;
    struct { double t; double val; } _sched_tension_bateria[_MAX_SCHED]; int _ns_tension_bateria = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "carga_conectada") == 0 && _ns_carga_conectada < _MAX_SCHED) {
                _sched_carga_conectada[_ns_carga_conectada].t   = _at_t;
                _sched_carga_conectada[_ns_carga_conectada++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "tension_bateria") == 0 && _ns_tension_bateria < _MAX_SCHED) {
                _sched_tension_bateria[_ns_tension_bateria].t   = _at_t;
                _sched_tension_bateria[_ns_tension_bateria++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "carga_conectada") == 0) { _cli_carga_conectada = (double)((atoi(_eq+1) != 0)); _has_carga_conectada = 1; }
            if (strcmp(argv[_oi], "tension_bateria") == 0) { _cli_tension_bateria = (double)(atof(_eq+1)); _has_tension_bateria = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = reguladorbateria_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_carga_conectada = REGULADORBATERIA_VR_CARGA_CONECTADA;
    const fmu_vref_t vr_tension_bateria = REGULADORBATERIA_VR_TENSION_BATERIA;
    const fmu_vref_t vr_carga_completa = REGULADORBATERIA_VR_CARGA_COMPLETA;
    const fmu_vref_t vr_cargando = REGULADORBATERIA_VR_CARGANDO;
    const fmu_vref_t vr_fallo_sobretension = REGULADORBATERIA_VR_FALLO_SOBRETENSION;
    const fmu_vref_t vr_corriente_carga = REGULADORBATERIA_VR_CORRIENTE_CARGA;

    fmu_real_t solver_buf[REGULADORBATERIA_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? REGULADORBATERIA_RK4_BUF_SIZE : REGULADORBATERIA_EULER_BUF_SIZE);

    fmu_real_t x[REGULADORBATERIA_N_STATES];
    FMU_CALL(m, get_cont_states, x, REGULADORBATERIA_N_STATES);

    fmu_real_t ei_prev[REGULADORBATERIA_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[REGULADORBATERIA_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, REGULADORBATERIA_N_EVENT_INDICATORS);

    SIM_PRINT("t,carga_conectada,tension_bateria,carga_completa,cargando,fallo_sobretension,corriente_carga\n");

    double t = 0.0;
    for (;;) {

        ReguladorBateria_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_carga_conectada) in.carga_conectada = (int)_cli_carga_conectada;
        if (_ns_carga_conectada > 0) {
            double _bv = (double)in.carga_conectada; double _bt = -1e300;
            for (int _si = 0; _si < _ns_carga_conectada; _si++)
                if (t >= _sched_carga_conectada[_si].t && _sched_carga_conectada[_si].t >= _bt)
                    { _bv = _sched_carga_conectada[_si].val; _bt = _sched_carga_conectada[_si].t; }
            in.carga_conectada = (int)_bv;
        }
        if (_has_tension_bateria) in.tension_bateria = (double)_cli_tension_bateria;
        if (_ns_tension_bateria > 0) {
            double _bv = (double)in.tension_bateria; double _bt = -1e300;
            for (int _si = 0; _si < _ns_tension_bateria; _si++)
                if (t >= _sched_tension_bateria[_si].t && _sched_tension_bateria[_si].t >= _bt)
                    { _bv = _sched_tension_bateria[_si].val; _bt = _sched_tension_bateria[_si].t; }
            in.tension_bateria = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t _i_carga_conectada = (fmu_bool_t)in.carga_conectada;
            FMU_CALL(m, set_boolean, &vr_carga_conectada, 1, (const fmu_bool_t *)&_i_carga_conectada);
            fmu_bool_t _more = 1, _term = 0;
            while (_more && !_term)
                FMU_CALL(m, new_discrete_states, &_more, &_term);
            FMU_CALL(m, enter_cont_mode);
            FMU_CALL(m, set_time, (fmu_real_t)t);
        }
        {
            fmu_real_t _i_tension_bateria = (fmu_real_t)in.tension_bateria;
            FMU_CALL(m, set_real, &vr_tension_bateria, 1, (const fmu_real_t *)&_i_tension_bateria);
        }

        FMU_CALL(m, set_cont_states, x, REGULADORBATERIA_N_STATES);

        ReguladorBateria_Outputs out = {0};
        {
            fmu_bool_t _o_carga_completa = 0;
            FMU_CALL(m, get_boolean, &vr_carga_completa, 1, &_o_carga_completa);
            out.carga_completa = (int)_o_carga_completa;
        }
        {
            fmu_bool_t _o_cargando = 0;
            FMU_CALL(m, get_boolean, &vr_cargando, 1, &_o_cargando);
            out.cargando = (int)_o_cargando;
        }
        {
            fmu_bool_t _o_fallo_sobretension = 0;
            FMU_CALL(m, get_boolean, &vr_fallo_sobretension, 1, &_o_fallo_sobretension);
            out.fallo_sobretension = (int)_o_fallo_sobretension;
        }
        {
            fmu_real_t _o_corriente_carga = 0.0;
            FMU_CALL(m, get_real, &vr_corriente_carga, 1, &_o_corriente_carga);
            out.corriente_carga = (double)_o_corriente_carga;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.carga_conectada, in.tension_bateria, (int)out.carga_completa, (int)out.cargando, (int)out.fallo_sobretension, out.corriente_carga);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, REGULADORBATERIA_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, REGULADORBATERIA_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, REGULADORBATERIA_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < REGULADORBATERIA_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < REGULADORBATERIA_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, REGULADORBATERIA_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, REGULADORBATERIA_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
