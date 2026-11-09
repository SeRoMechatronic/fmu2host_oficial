/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para NivelDeposito — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : NivelDeposito
 * GUID   : {654cd5a4-778a-4ee4-be67-8cfa8b991df8}
 * Estados: 1  |  Indicadores: 3
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "niveldeposito_api.h"
#include "niveldeposito_adapter.h"

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
    double _cli_valvula_manual = 0.0; int _has_valvula_manual = 0;
    struct { double t; double val; } _sched_valvula_manual[_MAX_SCHED]; int _ns_valvula_manual = 0;
    double _cli_sensor_nivel = 0.0; int _has_sensor_nivel = 0;
    struct { double t; double val; } _sched_sensor_nivel[_MAX_SCHED]; int _ns_sensor_nivel = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "valvula_manual") == 0 && _ns_valvula_manual < _MAX_SCHED) {
                _sched_valvula_manual[_ns_valvula_manual].t   = _at_t;
                _sched_valvula_manual[_ns_valvula_manual++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "sensor_nivel") == 0 && _ns_sensor_nivel < _MAX_SCHED) {
                _sched_sensor_nivel[_ns_sensor_nivel].t   = _at_t;
                _sched_sensor_nivel[_ns_sensor_nivel++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "valvula_manual") == 0) { _cli_valvula_manual = (double)((atoi(_eq+1) != 0)); _has_valvula_manual = 1; }
            if (strcmp(argv[_oi], "sensor_nivel") == 0) { _cli_sensor_nivel = (double)(atof(_eq+1)); _has_sensor_nivel = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = niveldeposito_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_valvula_manual = NIVELDEPOSITO_VR_VALVULA_MANUAL;
    const fmu_vref_t vr_sensor_nivel = NIVELDEPOSITO_VR_SENSOR_NIVEL;
    const fmu_vref_t vr_alarma_maximo = NIVELDEPOSITO_VR_ALARMA_MAXIMO;
    const fmu_vref_t vr_alarma_minimo = NIVELDEPOSITO_VR_ALARMA_MINIMO;
    const fmu_vref_t vr_bomba_activa = NIVELDEPOSITO_VR_BOMBA_ACTIVA;
    const fmu_vref_t vr_bomba = NIVELDEPOSITO_VR_BOMBA;

    fmu_real_t solver_buf[NIVELDEPOSITO_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? NIVELDEPOSITO_RK4_BUF_SIZE : NIVELDEPOSITO_EULER_BUF_SIZE);

    fmu_real_t x[NIVELDEPOSITO_N_STATES];
    FMU_CALL(m, get_cont_states, x, NIVELDEPOSITO_N_STATES);

    fmu_real_t ei_prev[NIVELDEPOSITO_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[NIVELDEPOSITO_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, NIVELDEPOSITO_N_EVENT_INDICATORS);

    SIM_PRINT("t,valvula_manual,sensor_nivel,alarma_maximo,alarma_minimo,bomba_activa,bomba\n");

    double t = 0.0;
    for (;;) {

        NivelDeposito_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_valvula_manual) in.valvula_manual = (int)_cli_valvula_manual;
        if (_ns_valvula_manual > 0) {
            double _bv = (double)in.valvula_manual; double _bt = -1e300;
            for (int _si = 0; _si < _ns_valvula_manual; _si++)
                if (t >= _sched_valvula_manual[_si].t && _sched_valvula_manual[_si].t >= _bt)
                    { _bv = _sched_valvula_manual[_si].val; _bt = _sched_valvula_manual[_si].t; }
            in.valvula_manual = (int)_bv;
        }
        if (_has_sensor_nivel) in.sensor_nivel = (double)_cli_sensor_nivel;
        if (_ns_sensor_nivel > 0) {
            double _bv = (double)in.sensor_nivel; double _bt = -1e300;
            for (int _si = 0; _si < _ns_sensor_nivel; _si++)
                if (t >= _sched_sensor_nivel[_si].t && _sched_sensor_nivel[_si].t >= _bt)
                    { _bv = _sched_sensor_nivel[_si].val; _bt = _sched_sensor_nivel[_si].t; }
            in.sensor_nivel = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t _i_valvula_manual = (fmu_bool_t)in.valvula_manual;
            FMU_CALL(m, set_boolean, &vr_valvula_manual, 1, (const fmu_bool_t *)&_i_valvula_manual);
            fmu_bool_t _more = 1, _term = 0;
            while (_more && !_term)
                FMU_CALL(m, new_discrete_states, &_more, &_term);
            FMU_CALL(m, enter_cont_mode);
            FMU_CALL(m, set_time, (fmu_real_t)t);
        }
        {
            fmu_real_t _i_sensor_nivel = (fmu_real_t)in.sensor_nivel;
            FMU_CALL(m, set_real, &vr_sensor_nivel, 1, (const fmu_real_t *)&_i_sensor_nivel);
        }

        FMU_CALL(m, set_cont_states, x, NIVELDEPOSITO_N_STATES);

        NivelDeposito_Outputs out = {0};
        {
            fmu_bool_t _o_alarma_maximo = 0;
            FMU_CALL(m, get_boolean, &vr_alarma_maximo, 1, &_o_alarma_maximo);
            out.alarma_maximo = (int)_o_alarma_maximo;
        }
        {
            fmu_bool_t _o_alarma_minimo = 0;
            FMU_CALL(m, get_boolean, &vr_alarma_minimo, 1, &_o_alarma_minimo);
            out.alarma_minimo = (int)_o_alarma_minimo;
        }
        {
            fmu_bool_t _o_bomba_activa = 0;
            FMU_CALL(m, get_boolean, &vr_bomba_activa, 1, &_o_bomba_activa);
            out.bomba_activa = (int)_o_bomba_activa;
        }
        {
            fmu_real_t _o_bomba = 0.0;
            FMU_CALL(m, get_real, &vr_bomba, 1, &_o_bomba);
            out.bomba = (double)_o_bomba;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.valvula_manual, in.sensor_nivel, (int)out.alarma_maximo, (int)out.alarma_minimo, (int)out.bomba_activa, out.bomba);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, NIVELDEPOSITO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, NIVELDEPOSITO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, NIVELDEPOSITO_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < NIVELDEPOSITO_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < NIVELDEPOSITO_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, NIVELDEPOSITO_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, NIVELDEPOSITO_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
