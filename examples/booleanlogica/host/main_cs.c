/**
 * @file main_cs.c -- generated typed Co-Simulation loop for BooleanLogica.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "booleanlogica_api.h"
#include "booleanlogica_adapter.h"

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
    double cli_umbral = 0.0; int has_umbral = 0;
    struct { double t; double val; } sched_umbral[MAX_SCHEDULE]; int ns_umbral = 0;
    double cli_a = 0.0; int has_a = 0;
    struct { double t; double val; } sched_a[MAX_SCHEDULE]; int ns_a = 0;
    double cli_b = 0.0; int has_b = 0;
    struct { double t; double val; } sched_b[MAX_SCHEDULE]; int ns_b = 0;
    double cli_clk = 0.0; int has_clk = 0;
    struct { double t; double val; } sched_clk[MAX_SCHEDULE]; int ns_clk = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "umbral") == 0 && ns_umbral < MAX_SCHEDULE) {
                sched_umbral[ns_umbral].t = at_t;
                sched_umbral[ns_umbral++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "a") == 0 && ns_a < MAX_SCHEDULE) {
                sched_a[ns_a].t = at_t;
                sched_a[ns_a++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "b") == 0 && ns_b < MAX_SCHEDULE) {
                sched_b[ns_b].t = at_t;
                sched_b[ns_b++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "clk") == 0 && ns_clk < MAX_SCHEDULE) {
                sched_clk[ns_clk].t = at_t;
                sched_clk[ns_clk++].val = (double)((atoi(_eq + 1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "umbral") == 0) { cli_umbral = (double)(atof(_eq + 1)); has_umbral = 1; }
            if (strcmp(argv[oi], "a") == 0) { cli_a = (double)((atoi(_eq + 1) != 0)); has_a = 1; }
            if (strcmp(argv[oi], "b") == 0) { cli_b = (double)((atoi(_eq + 1) != 0)); has_b = 1; }
            if (strcmp(argv[oi], "clk") == 0) { cli_clk = (double)((atoi(_eq + 1) != 0)); has_clk = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = booleanlogica_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
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
        if (has_umbral) in.umbral = (double)cli_umbral;
        if (ns_umbral > 0) {
            double best = (double)in.umbral; double best_t = -1e300;
            for (int si = 0; si < ns_umbral; si++)
                if (t >= sched_umbral[si].t && sched_umbral[si].t >= best_t)
                    { best = sched_umbral[si].val; best_t = sched_umbral[si].t; }
            in.umbral = (double)best;
        }
        if (has_a) in.a = (int)cli_a;
        if (ns_a > 0) {
            double best = (double)in.a; double best_t = -1e300;
            for (int si = 0; si < ns_a; si++)
                if (t >= sched_a[si].t && sched_a[si].t >= best_t)
                    { best = sched_a[si].val; best_t = sched_a[si].t; }
            in.a = (int)best;
        }
        if (has_b) in.b = (int)cli_b;
        if (ns_b > 0) {
            double best = (double)in.b; double best_t = -1e300;
            for (int si = 0; si < ns_b; si++)
                if (t >= sched_b[si].t && sched_b[si].t >= best_t)
                    { best = sched_b[si].val; best_t = sched_b[si].t; }
            in.b = (int)best;
        }
        if (has_clk) in.clk = (int)cli_clk;
        if (ns_clk > 0) {
            double best = (double)in.clk; double best_t = -1e300;
            for (int si = 0; si < ns_clk; si++)
                if (t >= sched_clk[si].t && sched_clk[si].t >= best_t)
                    { best = sched_clk[si].val; best_t = sched_clk[si].t; }
            in.clk = (int)best;
        }
        fmu_real_t set_umbral = (fmu_real_t)in.umbral;
        if (FMU_CALL(m, set_real, &vr_umbral, 1, (const fmu_real_t *)&set_umbral) > FMU_WARNING) {
            SIM_ERROR("Error: setting input umbral failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_a = (fmu_bool_t)in.a;
        if (FMU_CALL(m, set_boolean, &vr_a, 1, (const fmu_bool_t *)&set_a) > FMU_WARNING) {
            SIM_ERROR("Error: setting input a failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_b = (fmu_bool_t)in.b;
        if (FMU_CALL(m, set_boolean, &vr_b, 1, (const fmu_bool_t *)&set_b) > FMU_WARNING) {
            SIM_ERROR("Error: setting input b failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_clk = (fmu_bool_t)in.clk;
        if (FMU_CALL(m, set_boolean, &vr_clk, 1, (const fmu_bool_t *)&set_clk) > FMU_WARNING) {
            SIM_ERROR("Error: setting input clk failed\n");
            m->terminate(m); return 1;
        }
        BooleanLogica_Outputs out = {0};
        fmu_int_t got_cuenta_flancos = 0;
        if (FMU_CALL(m, get_integer, &vr_cuenta_flancos, 1, &got_cuenta_flancos) > FMU_WARNING) {
            SIM_ERROR("Error: reading output cuenta_flancos failed\n");
            m->terminate(m); return 1;
        }
        out.cuenta_flancos = (int)got_cuenta_flancos;
        fmu_bool_t got_above_threshold = 0;
        if (FMU_CALL(m, get_boolean, &vr_above_threshold, 1, &got_above_threshold) > FMU_WARNING) {
            SIM_ERROR("Error: reading output above_threshold failed\n");
            m->terminate(m); return 1;
        }
        out.above_threshold = (int)got_above_threshold;
        fmu_bool_t got_y_and = 0;
        if (FMU_CALL(m, get_boolean, &vr_y_and, 1, &got_y_and) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_and failed\n");
            m->terminate(m); return 1;
        }
        out.y_and = (int)got_y_and;
        fmu_bool_t got_y_latch = 0;
        if (FMU_CALL(m, get_boolean, &vr_y_latch, 1, &got_y_latch) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_latch failed\n");
            m->terminate(m); return 1;
        }
        out.y_latch = (int)got_y_latch;
        fmu_bool_t got_y_or = 0;
        if (FMU_CALL(m, get_boolean, &vr_y_or, 1, &got_y_or) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_or failed\n");
            m->terminate(m); return 1;
        }
        out.y_or = (int)got_y_or;
        fmu_bool_t got_y_xor = 0;
        if (FMU_CALL(m, get_boolean, &vr_y_xor, 1, &got_y_xor) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_xor failed\n");
            m->terminate(m); return 1;
        }
        out.y_xor = (int)got_y_xor;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", t, in.umbral, (int)in.a, (int)in.b, (int)in.clk, (int)out.cuenta_flancos, (int)out.above_threshold, (int)out.y_and, (int)out.y_latch, (int)out.y_or, (int)out.y_xor);
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
