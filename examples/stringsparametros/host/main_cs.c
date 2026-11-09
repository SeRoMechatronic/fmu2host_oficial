/**
 * @file main_cs.c -- generated typed Co-Simulation loop for StringsParametros.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stringsparametros_api.h"
#include "stringsparametros_adapter.h"

#define SIM_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define SIM_ERROR(msg) fprintf(stderr, "%s", msg)
#define SIM_DELAY(h) ((void)(h))

int main(int argc, char *argv[])
{
    SimConfig cfg = get_config();
    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);
    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h = atof(argv[2]);
    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    #define MAX_SCHEDULE 512
    double cli_u = 0.0; int has_u = 0;
    struct { double t; double val; } sched_u[MAX_SCHEDULE]; int ns_u = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "u") == 0 && ns_u < MAX_SCHEDULE) {
                sched_u[ns_u].t = at_t;
                sched_u[ns_u++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "u") == 0) { cli_u = (double)(atof(_eq + 1)); has_u = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = stringsparametros_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_u = STRINGSPARAMETROS_VR_U;
    const fmu_vref_t vr_y = STRINGSPARAMETROS_VR_Y;

    SIM_PRINT("t,u,y\n");
    double t = 0.0;
    for (;;) {
        StringsParametros_Inputs in = {0};
        get_inputs(t, &in);
        if (has_u) in.u = (double)cli_u;
        if (ns_u > 0) {
            double best = (double)in.u; double best_t = -1e300;
            for (int si = 0; si < ns_u; si++)
                if (t >= sched_u[si].t && sched_u[si].t >= best_t)
                    { best = sched_u[si].val; best_t = sched_u[si].t; }
            in.u = (double)best;
        }
        fmu_real_t set_u = (fmu_real_t)in.u;
        if (FMU_CALL(m, set_real, &vr_u, 1, (const fmu_real_t *)&set_u) > FMU_WARNING) {
            SIM_ERROR("Error: setting input u failed\n");
            m->terminate(m); return 1;
        }
        StringsParametros_Outputs out = {0};
        fmu_real_t got_y = 0.0;
        if (FMU_CALL(m, get_real, &vr_y, 1, &got_y) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y failed\n");
            m->terminate(m); return 1;
        }
        out.y = (double)got_y;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g\n", t, in.u, out.y);
        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
