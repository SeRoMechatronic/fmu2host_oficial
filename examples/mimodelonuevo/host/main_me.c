/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para Mi_Modelo_Nuevo — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : Mi_Modelo_Nuevo
 * GUID   : {849bd289-0db4-442e-8921-9fad06a5254d}
 * Estados: 1  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "mi_modelo_nuevo_api.h"
#include "mi_modelo_nuevo_adapter.h"

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
    double _cli_flag_activo = 0.0; int _has_flag_activo = 0;
    struct { double t; double val; } _sched_flag_activo[_MAX_SCHED]; int _ns_flag_activo = 0;
    double _cli_entrada_principal = 0.0; int _has_entrada_principal = 0;
    struct { double t; double val; } _sched_entrada_principal[_MAX_SCHED]; int _ns_entrada_principal = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "flag_activo") == 0 && _ns_flag_activo < _MAX_SCHED) {
                _sched_flag_activo[_ns_flag_activo].t   = _at_t;
                _sched_flag_activo[_ns_flag_activo++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "entrada_principal") == 0 && _ns_entrada_principal < _MAX_SCHED) {
                _sched_entrada_principal[_ns_entrada_principal].t   = _at_t;
                _sched_entrada_principal[_ns_entrada_principal++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "flag_activo") == 0) { _cli_flag_activo = (double)((atoi(_eq+1) != 0)); _has_flag_activo = 1; }
            if (strcmp(argv[_oi], "entrada_principal") == 0) { _cli_entrada_principal = (double)(atof(_eq+1)); _has_entrada_principal = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = mi_modelo_nuevo_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_flag_activo = MI_MODELO_NUEVO_VR_FLAG_ACTIVO;
    const fmu_vref_t vr_entrada_principal = MI_MODELO_NUEVO_VR_ENTRADA_PRINCIPAL;
    const fmu_vref_t vr_flag_salida = MI_MODELO_NUEVO_VR_FLAG_SALIDA;
    const fmu_vref_t vr_salida_filtrada = MI_MODELO_NUEVO_VR_SALIDA_FILTRADA;

    fmu_real_t solver_buf[MI_MODELO_NUEVO_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? MI_MODELO_NUEVO_RK4_BUF_SIZE : MI_MODELO_NUEVO_EULER_BUF_SIZE);

    fmu_real_t x[MI_MODELO_NUEVO_N_STATES];
    FMU_CALL(m, get_cont_states, x, MI_MODELO_NUEVO_N_STATES);

    fmu_real_t ei_prev[MI_MODELO_NUEVO_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[MI_MODELO_NUEVO_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, MI_MODELO_NUEVO_N_EVENT_INDICATORS);

    SIM_PRINT("t,flag_activo,entrada_principal,flag_salida,salida_filtrada\n");

    double t = 0.0;
    for (;;) {

        Mi_Modelo_Nuevo_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_flag_activo) in.flag_activo = (int)_cli_flag_activo;
        if (_ns_flag_activo > 0) {
            double _bv = (double)in.flag_activo; double _bt = -1e300;
            for (int _si = 0; _si < _ns_flag_activo; _si++)
                if (t >= _sched_flag_activo[_si].t && _sched_flag_activo[_si].t >= _bt)
                    { _bv = _sched_flag_activo[_si].val; _bt = _sched_flag_activo[_si].t; }
            in.flag_activo = (int)_bv;
        }
        if (_has_entrada_principal) in.entrada_principal = (double)_cli_entrada_principal;
        if (_ns_entrada_principal > 0) {
            double _bv = (double)in.entrada_principal; double _bt = -1e300;
            for (int _si = 0; _si < _ns_entrada_principal; _si++)
                if (t >= _sched_entrada_principal[_si].t && _sched_entrada_principal[_si].t >= _bt)
                    { _bv = _sched_entrada_principal[_si].val; _bt = _sched_entrada_principal[_si].t; }
            in.entrada_principal = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t _i_flag_activo = (fmu_bool_t)in.flag_activo;
            FMU_CALL(m, set_boolean, &vr_flag_activo, 1, (const fmu_bool_t *)&_i_flag_activo);
            fmu_bool_t _more = 1, _term = 0;
            while (_more && !_term)
                FMU_CALL(m, new_discrete_states, &_more, &_term);
            FMU_CALL(m, enter_cont_mode);
            FMU_CALL(m, set_time, (fmu_real_t)t);
        }
        {
            fmu_real_t _i_entrada_principal = (fmu_real_t)in.entrada_principal;
            FMU_CALL(m, set_real, &vr_entrada_principal, 1, (const fmu_real_t *)&_i_entrada_principal);
        }

        FMU_CALL(m, set_cont_states, x, MI_MODELO_NUEVO_N_STATES);

        Mi_Modelo_Nuevo_Outputs out = {0};
        {
            fmu_bool_t _o_flag_salida = 0;
            FMU_CALL(m, get_boolean, &vr_flag_salida, 1, &_o_flag_salida);
            out.flag_salida = (int)_o_flag_salida;
        }
        {
            fmu_real_t _o_salida_filtrada = 0.0;
            FMU_CALL(m, get_real, &vr_salida_filtrada, 1, &_o_salida_filtrada);
            out.salida_filtrada = (double)_o_salida_filtrada;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%d,%.10g\n", t, (int)in.flag_activo, in.entrada_principal, (int)out.flag_salida, out.salida_filtrada);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, MI_MODELO_NUEVO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, MI_MODELO_NUEVO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, MI_MODELO_NUEVO_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < MI_MODELO_NUEVO_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < MI_MODELO_NUEVO_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, MI_MODELO_NUEVO_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, MI_MODELO_NUEVO_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
