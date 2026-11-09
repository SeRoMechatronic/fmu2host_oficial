/**
 * @file main_cs.c -- generated typed Co-Simulation loop for CSPuro_SinME.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cspuro_sinme_api.h"
#include "cspuro_sinme_adapter.h"

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
    double cli_u1 = 0.0; int has_u1 = 0;
    struct { double t; double val; } sched_u1[MAX_SCHEDULE]; int ns_u1 = 0;
    double cli_u2 = 0.0; int has_u2 = 0;
    struct { double t; double val; } sched_u2[MAX_SCHEDULE]; int ns_u2 = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "u1") == 0 && ns_u1 < MAX_SCHEDULE) {
                sched_u1[ns_u1].t = at_t;
                sched_u1[ns_u1++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "u2") == 0 && ns_u2 < MAX_SCHEDULE) {
                sched_u2[ns_u2].t = at_t;
                sched_u2[ns_u2++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "u1") == 0) { cli_u1 = (double)(atof(_eq + 1)); has_u1 = 1; }
            if (strcmp(argv[oi], "u2") == 0) { cli_u2 = (double)(atof(_eq + 1)); has_u2 = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = cspuro_sinme_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_u1 = CSPURO_SINME_VR_U1;
    const fmu_vref_t vr_u2 = CSPURO_SINME_VR_U2;
    const fmu_vref_t vr_active = CSPURO_SINME_VR_ACTIVE;
    const fmu_vref_t vr_y_prod = CSPURO_SINME_VR_Y_PROD;
    const fmu_vref_t vr_y_sum = CSPURO_SINME_VR_Y_SUM;

    SIM_PRINT("t,u1,u2,active,y_prod,y_sum\n");
    double t = 0.0;
    for (;;) {
        CSPuro_SinME_Inputs in = {0};
        get_inputs(t, &in);
        if (has_u1) in.u1 = (double)cli_u1;
        if (ns_u1 > 0) {
            double best = (double)in.u1; double best_t = -1e300;
            for (int si = 0; si < ns_u1; si++)
                if (t >= sched_u1[si].t && sched_u1[si].t >= best_t)
                    { best = sched_u1[si].val; best_t = sched_u1[si].t; }
            in.u1 = (double)best;
        }
        if (has_u2) in.u2 = (double)cli_u2;
        if (ns_u2 > 0) {
            double best = (double)in.u2; double best_t = -1e300;
            for (int si = 0; si < ns_u2; si++)
                if (t >= sched_u2[si].t && sched_u2[si].t >= best_t)
                    { best = sched_u2[si].val; best_t = sched_u2[si].t; }
            in.u2 = (double)best;
        }
        fmu_real_t set_u1 = (fmu_real_t)in.u1;
        if (FMU_CALL(m, set_real, &vr_u1, 1, (const fmu_real_t *)&set_u1) > FMU_WARNING) {
            SIM_ERROR("Error: setting input u1 failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_u2 = (fmu_real_t)in.u2;
        if (FMU_CALL(m, set_real, &vr_u2, 1, (const fmu_real_t *)&set_u2) > FMU_WARNING) {
            SIM_ERROR("Error: setting input u2 failed\n");
            m->terminate(m); return 1;
        }
        CSPuro_SinME_Outputs out = {0};
        fmu_bool_t got_active = 0;
        if (FMU_CALL(m, get_boolean, &vr_active, 1, &got_active) > FMU_WARNING) {
            SIM_ERROR("Error: reading output active failed\n");
            m->terminate(m); return 1;
        }
        out.active = (int)got_active;
        fmu_real_t got_y_prod = 0.0;
        if (FMU_CALL(m, get_real, &vr_y_prod, 1, &got_y_prod) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_prod failed\n");
            m->terminate(m); return 1;
        }
        out.y_prod = (double)got_y_prod;
        fmu_real_t got_y_sum = 0.0;
        if (FMU_CALL(m, get_real, &vr_y_sum, 1, &got_y_sum) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_sum failed\n");
            m->terminate(m); return 1;
        }
        out.y_sum = (double)got_y_sum;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%d,%.10g,%.10g\n", t, in.u1, in.u2, (int)out.active, out.y_prod, out.y_sum);
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
