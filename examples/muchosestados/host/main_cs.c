/**
 * @file main_cs.c -- generated typed Co-Simulation loop for MuchosEstados.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "muchosestados_api.h"
#include "muchosestados_adapter.h"

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

    fmu_t *m = muchosestados_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_u = MUCHOSESTADOS_VR_U;
    const fmu_vref_t vr_todos_activos = MUCHOSESTADOS_VR_TODOS_ACTIVOS;
    const fmu_vref_t vr_y1 = MUCHOSESTADOS_VR_Y1;
    const fmu_vref_t vr_y2 = MUCHOSESTADOS_VR_Y2;
    const fmu_vref_t vr_y3 = MUCHOSESTADOS_VR_Y3;
    const fmu_vref_t vr_y4 = MUCHOSESTADOS_VR_Y4;
    const fmu_vref_t vr_y5 = MUCHOSESTADOS_VR_Y5;
    const fmu_vref_t vr_y6 = MUCHOSESTADOS_VR_Y6;
    const fmu_vref_t vr_y7 = MUCHOSESTADOS_VR_Y7;
    const fmu_vref_t vr_y8 = MUCHOSESTADOS_VR_Y8;

    SIM_PRINT("t,u,todos_activos,y1,y2,y3,y4,y5,y6,y7,y8\n");
    double t = 0.0;
    for (;;) {
        MuchosEstados_Inputs in = {0};
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
        MuchosEstados_Outputs out = {0};
        fmu_bool_t got_todos_activos = 0;
        if (FMU_CALL(m, get_boolean, &vr_todos_activos, 1, &got_todos_activos) > FMU_WARNING) {
            SIM_ERROR("Error: reading output todos_activos failed\n");
            m->terminate(m); return 1;
        }
        out.todos_activos = (int)got_todos_activos;
        fmu_real_t got_y1 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y1, 1, &got_y1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y1 failed\n");
            m->terminate(m); return 1;
        }
        out.y1 = (double)got_y1;
        fmu_real_t got_y2 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y2, 1, &got_y2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y2 failed\n");
            m->terminate(m); return 1;
        }
        out.y2 = (double)got_y2;
        fmu_real_t got_y3 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y3, 1, &got_y3) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y3 failed\n");
            m->terminate(m); return 1;
        }
        out.y3 = (double)got_y3;
        fmu_real_t got_y4 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y4, 1, &got_y4) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y4 failed\n");
            m->terminate(m); return 1;
        }
        out.y4 = (double)got_y4;
        fmu_real_t got_y5 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y5, 1, &got_y5) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y5 failed\n");
            m->terminate(m); return 1;
        }
        out.y5 = (double)got_y5;
        fmu_real_t got_y6 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y6, 1, &got_y6) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y6 failed\n");
            m->terminate(m); return 1;
        }
        out.y6 = (double)got_y6;
        fmu_real_t got_y7 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y7, 1, &got_y7) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y7 failed\n");
            m->terminate(m); return 1;
        }
        out.y7 = (double)got_y7;
        fmu_real_t got_y8 = 0.0;
        if (FMU_CALL(m, get_real, &vr_y8, 1, &got_y8) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y8 failed\n");
            m->terminate(m); return 1;
        }
        out.y8 = (double)got_y8;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, in.u, (int)out.todos_activos, out.y1, out.y2, out.y3, out.y4, out.y5, out.y6, out.y7, out.y8);
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
