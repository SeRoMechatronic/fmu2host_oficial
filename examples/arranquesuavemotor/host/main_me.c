/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para ArranqueSuaveMotor — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : ArranqueSuaveMotor
 * GUID   : {9b76140e-9465-4bfc-ae96-7c5a06fa5352}
 * Estados: 3  |  Indicadores: 4
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "arranquesuavemotor_api.h"
#include "arranquesuavemotor_adapter.h"

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
    double _cli_orden_arranque = 0.0; int _has_orden_arranque = 0;
    struct { double t; double val; } _sched_orden_arranque[_MAX_SCHED]; int _ns_orden_arranque = 0;
    double _cli_carga_motor = 0.0; int _has_carga_motor = 0;
    struct { double t; double val; } _sched_carga_motor[_MAX_SCHED]; int _ns_carga_motor = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "orden_arranque") == 0 && _ns_orden_arranque < _MAX_SCHED) {
                _sched_orden_arranque[_ns_orden_arranque].t   = _at_t;
                _sched_orden_arranque[_ns_orden_arranque++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "carga_motor") == 0 && _ns_carga_motor < _MAX_SCHED) {
                _sched_carga_motor[_ns_carga_motor].t   = _at_t;
                _sched_carga_motor[_ns_carga_motor++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "orden_arranque") == 0) { _cli_orden_arranque = (double)((atoi(_eq+1) != 0)); _has_orden_arranque = 1; }
            if (strcmp(argv[_oi], "carga_motor") == 0) { _cli_carga_motor = (double)(atof(_eq+1)); _has_carga_motor = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = arranquesuavemotor_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_orden_arranque = ARRANQUESUAVEMOTOR_VR_ORDEN_ARRANQUE;
    const fmu_vref_t vr_carga_motor = ARRANQUESUAVEMOTOR_VR_CARGA_MOTOR;
    const fmu_vref_t vr_en_rampa = ARRANQUESUAVEMOTOR_VR_EN_RAMPA;
    const fmu_vref_t vr_fallo_sobrecarga = ARRANQUESUAVEMOTOR_VR_FALLO_SOBRECARGA;
    const fmu_vref_t vr_motor_en_marcha = ARRANQUESUAVEMOTOR_VR_MOTOR_EN_MARCHA;
    const fmu_vref_t vr_tension_aplicada = ARRANQUESUAVEMOTOR_VR_TENSION_APLICADA;

    fmu_real_t solver_buf[ARRANQUESUAVEMOTOR_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? ARRANQUESUAVEMOTOR_RK4_BUF_SIZE : ARRANQUESUAVEMOTOR_EULER_BUF_SIZE);

    fmu_real_t x[ARRANQUESUAVEMOTOR_N_STATES];
    FMU_CALL(m, get_cont_states, x, ARRANQUESUAVEMOTOR_N_STATES);

    fmu_real_t ei_prev[ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS);

    SIM_PRINT("t,orden_arranque,carga_motor,en_rampa,fallo_sobrecarga,motor_en_marcha,tension_aplicada\n");

    double t = 0.0;
    for (;;) {

        ArranqueSuaveMotor_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_orden_arranque) in.orden_arranque = (int)_cli_orden_arranque;
        if (_ns_orden_arranque > 0) {
            double _bv = (double)in.orden_arranque; double _bt = -1e300;
            for (int _si = 0; _si < _ns_orden_arranque; _si++)
                if (t >= _sched_orden_arranque[_si].t && _sched_orden_arranque[_si].t >= _bt)
                    { _bv = _sched_orden_arranque[_si].val; _bt = _sched_orden_arranque[_si].t; }
            in.orden_arranque = (int)_bv;
        }
        if (_has_carga_motor) in.carga_motor = (double)_cli_carga_motor;
        if (_ns_carga_motor > 0) {
            double _bv = (double)in.carga_motor; double _bt = -1e300;
            for (int _si = 0; _si < _ns_carga_motor; _si++)
                if (t >= _sched_carga_motor[_si].t && _sched_carga_motor[_si].t >= _bt)
                    { _bv = _sched_carga_motor[_si].val; _bt = _sched_carga_motor[_si].t; }
            in.carga_motor = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t _i_orden_arranque = (fmu_bool_t)in.orden_arranque;
            FMU_CALL(m, set_boolean, &vr_orden_arranque, 1, (const fmu_bool_t *)&_i_orden_arranque);
            fmu_bool_t _more = 1, _term = 0;
            while (_more && !_term)
                FMU_CALL(m, new_discrete_states, &_more, &_term);
            FMU_CALL(m, enter_cont_mode);
            FMU_CALL(m, set_time, (fmu_real_t)t);
        }
        {
            fmu_real_t _i_carga_motor = (fmu_real_t)in.carga_motor;
            FMU_CALL(m, set_real, &vr_carga_motor, 1, (const fmu_real_t *)&_i_carga_motor);
        }

        FMU_CALL(m, set_cont_states, x, ARRANQUESUAVEMOTOR_N_STATES);

        ArranqueSuaveMotor_Outputs out = {0};
        {
            fmu_bool_t _o_en_rampa = 0;
            FMU_CALL(m, get_boolean, &vr_en_rampa, 1, &_o_en_rampa);
            out.en_rampa = (int)_o_en_rampa;
        }
        {
            fmu_bool_t _o_fallo_sobrecarga = 0;
            FMU_CALL(m, get_boolean, &vr_fallo_sobrecarga, 1, &_o_fallo_sobrecarga);
            out.fallo_sobrecarga = (int)_o_fallo_sobrecarga;
        }
        {
            fmu_bool_t _o_motor_en_marcha = 0;
            FMU_CALL(m, get_boolean, &vr_motor_en_marcha, 1, &_o_motor_en_marcha);
            out.motor_en_marcha = (int)_o_motor_en_marcha;
        }
        {
            fmu_real_t _o_tension_aplicada = 0.0;
            FMU_CALL(m, get_real, &vr_tension_aplicada, 1, &_o_tension_aplicada);
            out.tension_aplicada = (double)_o_tension_aplicada;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.orden_arranque, in.carga_motor, (int)out.en_rampa, (int)out.fallo_sobrecarga, (int)out.motor_en_marcha, out.tension_aplicada);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, ARRANQUESUAVEMOTOR_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, ARRANQUESUAVEMOTOR_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, ARRANQUESUAVEMOTOR_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, ARRANQUESUAVEMOTOR_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
