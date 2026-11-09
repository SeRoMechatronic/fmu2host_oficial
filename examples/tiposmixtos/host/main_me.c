/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para TiposMixtos — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : TiposMixtos
 * GUID   : {d5c6119d-6663-45d8-a27b-93c10193be62}
 * Estados: 0  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiposmixtos_api.h"
#include "tiposmixtos_adapter.h"

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

    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    #define _MAX_SCHED 512
    double _cli_i_in = 0.0; int _has_i_in = 0;
    struct { double t; double val; } _sched_i_in[_MAX_SCHED]; int _ns_i_in = 0;
    double _cli_b_in = 0.0; int _has_b_in = 0;
    struct { double t; double val; } _sched_b_in[_MAX_SCHED]; int _ns_b_in = 0;
    double _cli_r_in = 0.0; int _has_r_in = 0;
    struct { double t; double val; } _sched_r_in[_MAX_SCHED]; int _ns_r_in = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "i_in") == 0 && _ns_i_in < _MAX_SCHED) {
                _sched_i_in[_ns_i_in].t   = _at_t;
                _sched_i_in[_ns_i_in++].val = (double)(atoi(_eq+1));
            }
            if (strcmp(argv[_oi], "b_in") == 0 && _ns_b_in < _MAX_SCHED) {
                _sched_b_in[_ns_b_in].t   = _at_t;
                _sched_b_in[_ns_b_in++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "r_in") == 0 && _ns_r_in < _MAX_SCHED) {
                _sched_r_in[_ns_r_in].t   = _at_t;
                _sched_r_in[_ns_r_in++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "i_in") == 0) { _cli_i_in = (double)(atoi(_eq+1)); _has_i_in = 1; }
            if (strcmp(argv[_oi], "b_in") == 0) { _cli_b_in = (double)((atoi(_eq+1) != 0)); _has_b_in = 1; }
            if (strcmp(argv[_oi], "r_in") == 0) { _cli_r_in = (double)(atof(_eq+1)); _has_r_in = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = tiposmixtos_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_i_in = TIPOSMIXTOS_VR_I_IN;
    const fmu_vref_t vr_b_in = TIPOSMIXTOS_VR_B_IN;
    const fmu_vref_t vr_r_in = TIPOSMIXTOS_VR_R_IN;
    const fmu_vref_t vr_r_abs = TIPOSMIXTOS_VR_R_ABS;
    const fmu_vref_t vr_i_out = TIPOSMIXTOS_VR_I_OUT;
    const fmu_vref_t vr_b_out = TIPOSMIXTOS_VR_B_OUT;
    const fmu_vref_t vr_r_out = TIPOSMIXTOS_VR_R_OUT;

    SIM_PRINT("t,i_in,b_in,r_in,r_abs,i_out,b_out,r_out\n");

    double t = 0.0;
    for (;;) {

        TiposMixtos_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_i_in) in.i_in = (int)_cli_i_in;
        if (_ns_i_in > 0) {
            double _bv = (double)in.i_in; double _bt = -1e300;
            for (int _si = 0; _si < _ns_i_in; _si++)
                if (t >= _sched_i_in[_si].t && _sched_i_in[_si].t >= _bt)
                    { _bv = _sched_i_in[_si].val; _bt = _sched_i_in[_si].t; }
            in.i_in = (int)_bv;
        }
        if (_has_b_in) in.b_in = (int)_cli_b_in;
        if (_ns_b_in > 0) {
            double _bv = (double)in.b_in; double _bt = -1e300;
            for (int _si = 0; _si < _ns_b_in; _si++)
                if (t >= _sched_b_in[_si].t && _sched_b_in[_si].t >= _bt)
                    { _bv = _sched_b_in[_si].val; _bt = _sched_b_in[_si].t; }
            in.b_in = (int)_bv;
        }
        if (_has_r_in) in.r_in = (double)_cli_r_in;
        if (_ns_r_in > 0) {
            double _bv = (double)in.r_in; double _bt = -1e300;
            for (int _si = 0; _si < _ns_r_in; _si++)
                if (t >= _sched_r_in[_si].t && _sched_r_in[_si].t >= _bt)
                    { _bv = _sched_r_in[_si].val; _bt = _sched_r_in[_si].t; }
            in.r_in = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_int_t _i_i_in = (fmu_int_t)in.i_in;
            FMU_CALL(m, set_integer, &vr_i_in, 1, (const fmu_int_t *)&_i_i_in);
            fmu_bool_t _i_b_in = (fmu_bool_t)in.b_in;
            FMU_CALL(m, set_boolean, &vr_b_in, 1, (const fmu_bool_t *)&_i_b_in);
            fmu_real_t _i_r_in = (fmu_real_t)in.r_in;
            FMU_CALL(m, set_real, &vr_r_in, 1, (const fmu_real_t *)&_i_r_in);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        TiposMixtos_Outputs out = {0};
        {
            fmu_real_t _o_r_abs = 0.0;
            FMU_CALL(m, get_real, &vr_r_abs, 1, &_o_r_abs);
            out.r_abs = (double)_o_r_abs;
        }
        {
            fmu_int_t _o_i_out = 0;
            FMU_CALL(m, get_integer, &vr_i_out, 1, &_o_i_out);
            out.i_out = (int)_o_i_out;
        }
        {
            fmu_bool_t _o_b_out = 0;
            FMU_CALL(m, get_boolean, &vr_b_out, 1, &_o_b_out);
            out.b_out = (int)_o_b_out;
        }
        {
            fmu_real_t _o_r_out = 0.0;
            FMU_CALL(m, get_real, &vr_r_out, 1, &_o_r_out);
            out.r_out = (double)_o_r_out;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%d,%.10g,%.10g,%d,%d,%.10g\n", t, (int)in.i_in, (int)in.b_in, in.r_in, out.r_abs, (int)out.i_out, (int)out.b_out, out.r_out);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
