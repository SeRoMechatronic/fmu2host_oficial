/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para CTPID — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : CTPID
 * GUID   : {1e4ce642-3cf9-4c84-8816-d34ec05d4156}
 * Estados: 1  |  Indicadores: 3
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "ctpid_api.h"
#include "ctpid_adapter.h"

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
    double _cli_consigna = 0.0; int _has_consigna = 0;
    struct { double t; double val; } _sched_consigna[_MAX_SCHED]; int _ns_consigna = 0;
    double _cli_temperatura = 0.0; int _has_temperatura = 0;
    struct { double t; double val; } _sched_temperatura[_MAX_SCHED]; int _ns_temperatura = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "consigna") == 0 && _ns_consigna < _MAX_SCHED) {
                _sched_consigna[_ns_consigna].t   = _at_t;
                _sched_consigna[_ns_consigna++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "temperatura") == 0 && _ns_temperatura < _MAX_SCHED) {
                _sched_temperatura[_ns_temperatura].t   = _at_t;
                _sched_temperatura[_ns_temperatura++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "consigna") == 0) { _cli_consigna = (double)(atof(_eq+1)); _has_consigna = 1; }
            if (strcmp(argv[_oi], "temperatura") == 0) { _cli_temperatura = (double)(atof(_eq+1)); _has_temperatura = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = ctpid_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_consigna = CTPID_VR_CONSIGNA;
    const fmu_vref_t vr_temperatura = CTPID_VR_TEMPERATURA;
    const fmu_vref_t vr_ledalcanzado = CTPID_VR_LEDALCANZADO;
    const fmu_vref_t vr_ledpordebajo = CTPID_VR_LEDPORDEBAJO;
    const fmu_vref_t vr_ledporencima = CTPID_VR_LEDPORENCIMA;
    const fmu_vref_t vr_ventilador = CTPID_VR_VENTILADOR;

    fmu_real_t solver_buf[CTPID_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? CTPID_RK4_BUF_SIZE : CTPID_EULER_BUF_SIZE);

    fmu_real_t x[CTPID_N_STATES];
    FMU_CALL(m, get_cont_states, x, CTPID_N_STATES);

    fmu_real_t ei_prev[CTPID_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[CTPID_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, CTPID_N_EVENT_INDICATORS);

    SIM_PRINT("t,consigna,temperatura,ledAlcanzado,ledPorDebajo,ledPorEncima,ventilador\n");

    double t = 0.0;
    for (;;) {

        CTPID_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_consigna) in.consigna = (double)_cli_consigna;
        if (_ns_consigna > 0) {
            double _bv = (double)in.consigna; double _bt = -1e300;
            for (int _si = 0; _si < _ns_consigna; _si++)
                if (t >= _sched_consigna[_si].t && _sched_consigna[_si].t >= _bt)
                    { _bv = _sched_consigna[_si].val; _bt = _sched_consigna[_si].t; }
            in.consigna = (double)_bv;
        }
        if (_has_temperatura) in.temperatura = (double)_cli_temperatura;
        if (_ns_temperatura > 0) {
            double _bv = (double)in.temperatura; double _bt = -1e300;
            for (int _si = 0; _si < _ns_temperatura; _si++)
                if (t >= _sched_temperatura[_si].t && _sched_temperatura[_si].t >= _bt)
                    { _bv = _sched_temperatura[_si].val; _bt = _sched_temperatura[_si].t; }
            in.temperatura = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        {
            fmu_real_t _i_consigna = (fmu_real_t)in.consigna;
            FMU_CALL(m, set_real, &vr_consigna, 1, (const fmu_real_t *)&_i_consigna);
        }
        {
            fmu_real_t _i_temperatura = (fmu_real_t)in.temperatura;
            FMU_CALL(m, set_real, &vr_temperatura, 1, (const fmu_real_t *)&_i_temperatura);
        }

        FMU_CALL(m, set_cont_states, x, CTPID_N_STATES);

        CTPID_Outputs out = {0};
        {
            fmu_bool_t _o_ledalcanzado = 0;
            FMU_CALL(m, get_boolean, &vr_ledalcanzado, 1, &_o_ledalcanzado);
            out.ledalcanzado = (int)_o_ledalcanzado;
        }
        {
            fmu_bool_t _o_ledpordebajo = 0;
            FMU_CALL(m, get_boolean, &vr_ledpordebajo, 1, &_o_ledpordebajo);
            out.ledpordebajo = (int)_o_ledpordebajo;
        }
        {
            fmu_bool_t _o_ledporencima = 0;
            FMU_CALL(m, get_boolean, &vr_ledporencima, 1, &_o_ledporencima);
            out.ledporencima = (int)_o_ledporencima;
        }
        {
            fmu_real_t _o_ventilador = 0.0;
            FMU_CALL(m, get_real, &vr_ventilador, 1, &_o_ventilador);
            out.ventilador = (double)_o_ventilador;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.consigna, in.temperatura, (int)out.ledalcanzado, (int)out.ledpordebajo, (int)out.ledporencima, out.ventilador);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, CTPID_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, CTPID_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, CTPID_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < CTPID_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < CTPID_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, CTPID_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, CTPID_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
