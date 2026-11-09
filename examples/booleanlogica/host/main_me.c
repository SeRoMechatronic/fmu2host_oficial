/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para BooleanLogica — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : BooleanLogica
 * GUID   : {c2452a7d-230b-4fd7-9fca-37ef7e949ad6}
 * Estados: 0  |  Indicadores: 2
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "booleanlogica_api.h"
#include "booleanlogica_adapter.h"

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
    double _cli_umbral = 0.0; int _has_umbral = 0;
    struct { double t; double val; } _sched_umbral[_MAX_SCHED]; int _ns_umbral = 0;
    double _cli_a = 0.0; int _has_a = 0;
    struct { double t; double val; } _sched_a[_MAX_SCHED]; int _ns_a = 0;
    double _cli_b = 0.0; int _has_b = 0;
    struct { double t; double val; } _sched_b[_MAX_SCHED]; int _ns_b = 0;
    double _cli_clk = 0.0; int _has_clk = 0;
    struct { double t; double val; } _sched_clk[_MAX_SCHED]; int _ns_clk = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "umbral") == 0 && _ns_umbral < _MAX_SCHED) {
                _sched_umbral[_ns_umbral].t   = _at_t;
                _sched_umbral[_ns_umbral++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "a") == 0 && _ns_a < _MAX_SCHED) {
                _sched_a[_ns_a].t   = _at_t;
                _sched_a[_ns_a++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "b") == 0 && _ns_b < _MAX_SCHED) {
                _sched_b[_ns_b].t   = _at_t;
                _sched_b[_ns_b++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "clk") == 0 && _ns_clk < _MAX_SCHED) {
                _sched_clk[_ns_clk].t   = _at_t;
                _sched_clk[_ns_clk++].val = (double)((atoi(_eq+1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "umbral") == 0) { _cli_umbral = (double)(atof(_eq+1)); _has_umbral = 1; }
            if (strcmp(argv[_oi], "a") == 0) { _cli_a = (double)((atoi(_eq+1) != 0)); _has_a = 1; }
            if (strcmp(argv[_oi], "b") == 0) { _cli_b = (double)((atoi(_eq+1) != 0)); _has_b = 1; }
            if (strcmp(argv[_oi], "clk") == 0) { _cli_clk = (double)((atoi(_eq+1) != 0)); _has_clk = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = booleanlogica_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_umbral = BOOLEANLOGICA_VR_UMBRAL;
    const fmu_vref_t vr_a = BOOLEANLOGICA_VR_A;
    const fmu_vref_t vr_b = BOOLEANLOGICA_VR_B;
    const fmu_vref_t vr_clk = BOOLEANLOGICA_VR_CLK;
    const fmu_vref_t vr_cuenta_flancos = BOOLEANLOGICA_VR_CUENTA_FLANCOS;
    const fmu_vref_t vr_above_threshold = BOOLEANLOGICA_VR_ABOVE_THRESHOLD;
    const fmu_vref_t vr_y_and = BOOLEANLOGICA_VR_Y_AND;
    const fmu_vref_t vr_y_latch = BOOLEANLOGICA_VR_Y_LATCH;
    const fmu_vref_t vr_y_or = BOOLEANLOGICA_VR_Y_OR;
    const fmu_vref_t vr_y_xor = BOOLEANLOGICA_VR_Y_XOR;

    SIM_PRINT("t,umbral,a,b,clk,cuenta_flancos,above_threshold,y_and,y_latch,y_or,y_xor\n");

    double t = 0.0;
    for (;;) {

        BooleanLogica_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_umbral) in.umbral = (double)_cli_umbral;
        if (_ns_umbral > 0) {
            double _bv = (double)in.umbral; double _bt = -1e300;
            for (int _si = 0; _si < _ns_umbral; _si++)
                if (t >= _sched_umbral[_si].t && _sched_umbral[_si].t >= _bt)
                    { _bv = _sched_umbral[_si].val; _bt = _sched_umbral[_si].t; }
            in.umbral = (double)_bv;
        }
        if (_has_a) in.a = (int)_cli_a;
        if (_ns_a > 0) {
            double _bv = (double)in.a; double _bt = -1e300;
            for (int _si = 0; _si < _ns_a; _si++)
                if (t >= _sched_a[_si].t && _sched_a[_si].t >= _bt)
                    { _bv = _sched_a[_si].val; _bt = _sched_a[_si].t; }
            in.a = (int)_bv;
        }
        if (_has_b) in.b = (int)_cli_b;
        if (_ns_b > 0) {
            double _bv = (double)in.b; double _bt = -1e300;
            for (int _si = 0; _si < _ns_b; _si++)
                if (t >= _sched_b[_si].t && _sched_b[_si].t >= _bt)
                    { _bv = _sched_b[_si].val; _bt = _sched_b[_si].t; }
            in.b = (int)_bv;
        }
        if (_has_clk) in.clk = (int)_cli_clk;
        if (_ns_clk > 0) {
            double _bv = (double)in.clk; double _bt = -1e300;
            for (int _si = 0; _si < _ns_clk; _si++)
                if (t >= _sched_clk[_si].t && _sched_clk[_si].t >= _bt)
                    { _bv = _sched_clk[_si].val; _bt = _sched_clk[_si].t; }
            in.clk = (int)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_umbral = (fmu_real_t)in.umbral;
            FMU_CALL(m, set_real, &vr_umbral, 1, (const fmu_real_t *)&_i_umbral);
            fmu_bool_t _i_a = (fmu_bool_t)in.a;
            FMU_CALL(m, set_boolean, &vr_a, 1, (const fmu_bool_t *)&_i_a);
            fmu_bool_t _i_b = (fmu_bool_t)in.b;
            FMU_CALL(m, set_boolean, &vr_b, 1, (const fmu_bool_t *)&_i_b);
            fmu_bool_t _i_clk = (fmu_bool_t)in.clk;
            FMU_CALL(m, set_boolean, &vr_clk, 1, (const fmu_bool_t *)&_i_clk);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        BooleanLogica_Outputs out = {0};
        {
            fmu_int_t _o_cuenta_flancos = 0;
            FMU_CALL(m, get_integer, &vr_cuenta_flancos, 1, &_o_cuenta_flancos);
            out.cuenta_flancos = (int)_o_cuenta_flancos;
        }
        {
            fmu_bool_t _o_above_threshold = 0;
            FMU_CALL(m, get_boolean, &vr_above_threshold, 1, &_o_above_threshold);
            out.above_threshold = (int)_o_above_threshold;
        }
        {
            fmu_bool_t _o_y_and = 0;
            FMU_CALL(m, get_boolean, &vr_y_and, 1, &_o_y_and);
            out.y_and = (int)_o_y_and;
        }
        {
            fmu_bool_t _o_y_latch = 0;
            FMU_CALL(m, get_boolean, &vr_y_latch, 1, &_o_y_latch);
            out.y_latch = (int)_o_y_latch;
        }
        {
            fmu_bool_t _o_y_or = 0;
            FMU_CALL(m, get_boolean, &vr_y_or, 1, &_o_y_or);
            out.y_or = (int)_o_y_or;
        }
        {
            fmu_bool_t _o_y_xor = 0;
            FMU_CALL(m, get_boolean, &vr_y_xor, 1, &_o_y_xor);
            out.y_xor = (int)_o_y_xor;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", t, in.umbral, (int)in.a, (int)in.b, (int)in.clk, (int)out.cuenta_flancos, (int)out.above_threshold, (int)out.y_and, (int)out.y_latch, (int)out.y_or, (int)out.y_xor);

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
