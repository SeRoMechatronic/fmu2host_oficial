/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para StringsParametros — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : StringsParametros
 * GUID   : {77af6522-3e13-4790-bfe6-bb3bab410d3e}
 * Estados: 0  |  Indicadores: 0
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stringsparametros_api.h"
#include "stringsparametros_adapter.h"

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
    double _cli_u = 0.0; int _has_u = 0;
    struct { double t; double val; } _sched_u[_MAX_SCHED]; int _ns_u = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "u") == 0 && _ns_u < _MAX_SCHED) {
                _sched_u[_ns_u].t   = _at_t;
                _sched_u[_ns_u++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "u") == 0) { _cli_u = (double)(atof(_eq+1)); _has_u = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = stringsparametros_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_u = STRINGSPARAMETROS_VR_U;
    const fmu_vref_t vr_y = STRINGSPARAMETROS_VR_Y;

    SIM_PRINT("t,u,y\n");

    double t = 0.0;
    for (;;) {

        StringsParametros_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_u) in.u = (double)_cli_u;
        if (_ns_u > 0) {
            double _bv = (double)in.u; double _bt = -1e300;
            for (int _si = 0; _si < _ns_u; _si++)
                if (t >= _sched_u[_si].t && _sched_u[_si].t >= _bt)
                    { _bv = _sched_u[_si].val; _bt = _sched_u[_si].t; }
            in.u = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_u = (fmu_real_t)in.u;
            FMU_CALL(m, set_real, &vr_u, 1, (const fmu_real_t *)&_i_u);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        StringsParametros_Outputs out = {0};
        {
            fmu_real_t _o_y = 0.0;
            FMU_CALL(m, get_real, &vr_y, 1, &_o_y);
            out.y = (double)_o_y;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g\n", t, in.u, out.y);

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
