/**
 * @file main_cs.c -- generated typed Co-Simulation loop for testUPM.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "testupm_api.h"
#include "testupm_adapter.h"

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
    double cli_pot = 0.0; int has_pot = 0;
    struct { double t; double val; } sched_pot[MAX_SCHEDULE]; int ns_pot = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "pot") == 0 && ns_pot < MAX_SCHEDULE) {
                sched_pot[ns_pot].t = at_t;
                sched_pot[ns_pot++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "pot") == 0) { cli_pot = (double)(atof(_eq + 1)); has_pot = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = testupm_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_pot = TESTUPM_VR_POT;
    const fmu_vref_t vr_led1 = TESTUPM_VR_LED1;
    const fmu_vref_t vr_led2 = TESTUPM_VR_LED2;
    const fmu_vref_t vr_led3 = TESTUPM_VR_LED3;
    const fmu_vref_t vr_led4 = TESTUPM_VR_LED4;
    const fmu_vref_t vr_led5 = TESTUPM_VR_LED5;

    SIM_PRINT("t,pot,led1,led2,led3,led4,led5\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        testUPM_Inputs in = {0};
        get_inputs(t, &in);
        if (has_pot) in.pot = (double)cli_pot;
        if (ns_pot > 0) {
            double best = (double)in.pot; double best_t = -1e300;
            for (int si = 0; si < ns_pot; si++)
                if (t >= sched_pot[si].t && sched_pot[si].t >= best_t)
                    { best = sched_pot[si].val; best_t = sched_pot[si].t; }
            in.pot = (double)best;
        }
        fmu_real_t set_pot = (fmu_real_t)in.pot;
        if (FMU_CALL(m, set_real, &vr_pot, 1, (const fmu_real_t *)&set_pot) > FMU_WARNING) {
            SIM_ERROR("Error: setting input pot failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        testUPM_Outputs out = {0};
        fmu_bool_t got_led1 = 0;
        if (FMU_CALL(m, get_boolean, &vr_led1, 1, &got_led1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output led1 failed\n");
            m->terminate(m); return 1;
        }
        out.led1 = (int)got_led1;
        fmu_bool_t got_led2 = 0;
        if (FMU_CALL(m, get_boolean, &vr_led2, 1, &got_led2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output led2 failed\n");
            m->terminate(m); return 1;
        }
        out.led2 = (int)got_led2;
        fmu_bool_t got_led3 = 0;
        if (FMU_CALL(m, get_boolean, &vr_led3, 1, &got_led3) > FMU_WARNING) {
            SIM_ERROR("Error: reading output led3 failed\n");
            m->terminate(m); return 1;
        }
        out.led3 = (int)got_led3;
        fmu_bool_t got_led4 = 0;
        if (FMU_CALL(m, get_boolean, &vr_led4, 1, &got_led4) > FMU_WARNING) {
            SIM_ERROR("Error: reading output led4 failed\n");
            m->terminate(m); return 1;
        }
        out.led4 = (int)got_led4;
        fmu_bool_t got_led5 = 0;
        if (FMU_CALL(m, get_boolean, &vr_led5, 1, &got_led5) > FMU_WARNING) {
            SIM_ERROR("Error: reading output led5 failed\n");
            m->terminate(m); return 1;
        }
        out.led5 = (int)got_led5;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%d,%d\n", t, in.pot, (int)out.led1, (int)out.led2, (int)out.led3, (int)out.led4, (int)out.led5);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
