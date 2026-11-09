/**
 * @file main_cs.c -- generated typed Co-Simulation loop for TiposMixtos.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiposmixtos_api.h"
#include "tiposmixtos_adapter.h"

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
    double cli_i_in = 0.0; int has_i_in = 0;
    struct { double t; double val; } sched_i_in[MAX_SCHEDULE]; int ns_i_in = 0;
    double cli_b_in = 0.0; int has_b_in = 0;
    struct { double t; double val; } sched_b_in[MAX_SCHEDULE]; int ns_b_in = 0;
    double cli_r_in = 0.0; int has_r_in = 0;
    struct { double t; double val; } sched_r_in[MAX_SCHEDULE]; int ns_r_in = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "i_in") == 0 && ns_i_in < MAX_SCHEDULE) {
                sched_i_in[ns_i_in].t = at_t;
                sched_i_in[ns_i_in++].val = (double)(atoi(_eq + 1));
            }
            if (strcmp(argv[oi], "b_in") == 0 && ns_b_in < MAX_SCHEDULE) {
                sched_b_in[ns_b_in].t = at_t;
                sched_b_in[ns_b_in++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "r_in") == 0 && ns_r_in < MAX_SCHEDULE) {
                sched_r_in[ns_r_in].t = at_t;
                sched_r_in[ns_r_in++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "i_in") == 0) { cli_i_in = (double)(atoi(_eq + 1)); has_i_in = 1; }
            if (strcmp(argv[oi], "b_in") == 0) { cli_b_in = (double)((atoi(_eq + 1) != 0)); has_b_in = 1; }
            if (strcmp(argv[oi], "r_in") == 0) { cli_r_in = (double)(atof(_eq + 1)); has_r_in = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = tiposmixtos_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
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
        if (has_i_in) in.i_in = (int)cli_i_in;
        if (ns_i_in > 0) {
            double best = (double)in.i_in; double best_t = -1e300;
            for (int si = 0; si < ns_i_in; si++)
                if (t >= sched_i_in[si].t && sched_i_in[si].t >= best_t)
                    { best = sched_i_in[si].val; best_t = sched_i_in[si].t; }
            in.i_in = (int)best;
        }
        if (has_b_in) in.b_in = (int)cli_b_in;
        if (ns_b_in > 0) {
            double best = (double)in.b_in; double best_t = -1e300;
            for (int si = 0; si < ns_b_in; si++)
                if (t >= sched_b_in[si].t && sched_b_in[si].t >= best_t)
                    { best = sched_b_in[si].val; best_t = sched_b_in[si].t; }
            in.b_in = (int)best;
        }
        if (has_r_in) in.r_in = (double)cli_r_in;
        if (ns_r_in > 0) {
            double best = (double)in.r_in; double best_t = -1e300;
            for (int si = 0; si < ns_r_in; si++)
                if (t >= sched_r_in[si].t && sched_r_in[si].t >= best_t)
                    { best = sched_r_in[si].val; best_t = sched_r_in[si].t; }
            in.r_in = (double)best;
        }
        fmu_int_t set_i_in = (fmu_int_t)in.i_in;
        if (FMU_CALL(m, set_integer, &vr_i_in, 1, (const fmu_int_t *)&set_i_in) > FMU_WARNING) {
            SIM_ERROR("Error: setting input i_in failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_b_in = (fmu_bool_t)in.b_in;
        if (FMU_CALL(m, set_boolean, &vr_b_in, 1, (const fmu_bool_t *)&set_b_in) > FMU_WARNING) {
            SIM_ERROR("Error: setting input b_in failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_r_in = (fmu_real_t)in.r_in;
        if (FMU_CALL(m, set_real, &vr_r_in, 1, (const fmu_real_t *)&set_r_in) > FMU_WARNING) {
            SIM_ERROR("Error: setting input r_in failed\n");
            m->terminate(m); return 1;
        }
        TiposMixtos_Outputs out = {0};
        fmu_real_t got_r_abs = 0.0;
        if (FMU_CALL(m, get_real, &vr_r_abs, 1, &got_r_abs) > FMU_WARNING) {
            SIM_ERROR("Error: reading output r_abs failed\n");
            m->terminate(m); return 1;
        }
        out.r_abs = (double)got_r_abs;
        fmu_int_t got_i_out = 0;
        if (FMU_CALL(m, get_integer, &vr_i_out, 1, &got_i_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output i_out failed\n");
            m->terminate(m); return 1;
        }
        out.i_out = (int)got_i_out;
        fmu_bool_t got_b_out = 0;
        if (FMU_CALL(m, get_boolean, &vr_b_out, 1, &got_b_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output b_out failed\n");
            m->terminate(m); return 1;
        }
        out.b_out = (int)got_b_out;
        fmu_real_t got_r_out = 0.0;
        if (FMU_CALL(m, get_real, &vr_r_out, 1, &got_r_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output r_out failed\n");
            m->terminate(m); return 1;
        }
        out.r_out = (double)got_r_out;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%d,%.10g,%.10g,%d,%d,%.10g\n", t, (int)in.i_in, (int)in.b_in, in.r_in, out.r_abs, (int)out.i_out, (int)out.b_out, out.r_out);
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
