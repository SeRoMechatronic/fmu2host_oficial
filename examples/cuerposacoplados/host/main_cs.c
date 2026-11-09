/**
 * @file main_cs.c -- generated typed Co-Simulation loop for CuerposAcoplados.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cuerposacoplados_api.h"
#include "cuerposacoplados_adapter.h"

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
    double cli_fuerza_externa = 0.0; int has_fuerza_externa = 0;
    struct { double t; double val; } sched_fuerza_externa[MAX_SCHEDULE]; int ns_fuerza_externa = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "fuerza_externa") == 0 && ns_fuerza_externa < MAX_SCHEDULE) {
                sched_fuerza_externa[ns_fuerza_externa].t = at_t;
                sched_fuerza_externa[ns_fuerza_externa++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "fuerza_externa") == 0) { cli_fuerza_externa = (double)(atof(_eq + 1)); has_fuerza_externa = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = cuerposacoplados_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_fuerza_externa = CUERPOSACOPLADOS_VR_FUERZA_EXTERNA;
    const fmu_vref_t vr_en_fase = CUERPOSACOPLADOS_VR_EN_FASE;
    const fmu_vref_t vr_energia_total = CUERPOSACOPLADOS_VR_ENERGIA_TOTAL;
    const fmu_vref_t vr_pos1 = CUERPOSACOPLADOS_VR_POS1;
    const fmu_vref_t vr_pos2 = CUERPOSACOPLADOS_VR_POS2;
    const fmu_vref_t vr_vel1 = CUERPOSACOPLADOS_VR_VEL1;
    const fmu_vref_t vr_vel2 = CUERPOSACOPLADOS_VR_VEL2;

    SIM_PRINT("t,fuerza_externa,en_fase,energia_total,pos1,pos2,vel1,vel2\n");
    double t = 0.0;
    for (;;) {
        CuerposAcoplados_Inputs in = {0};
        get_inputs(t, &in);
        if (has_fuerza_externa) in.fuerza_externa = (double)cli_fuerza_externa;
        if (ns_fuerza_externa > 0) {
            double best = (double)in.fuerza_externa; double best_t = -1e300;
            for (int si = 0; si < ns_fuerza_externa; si++)
                if (t >= sched_fuerza_externa[si].t && sched_fuerza_externa[si].t >= best_t)
                    { best = sched_fuerza_externa[si].val; best_t = sched_fuerza_externa[si].t; }
            in.fuerza_externa = (double)best;
        }
        fmu_real_t set_fuerza_externa = (fmu_real_t)in.fuerza_externa;
        if (FMU_CALL(m, set_real, &vr_fuerza_externa, 1, (const fmu_real_t *)&set_fuerza_externa) > FMU_WARNING) {
            SIM_ERROR("Error: setting input fuerza_externa failed\n");
            m->terminate(m); return 1;
        }
        CuerposAcoplados_Outputs out = {0};
        fmu_bool_t got_en_fase = 0;
        if (FMU_CALL(m, get_boolean, &vr_en_fase, 1, &got_en_fase) > FMU_WARNING) {
            SIM_ERROR("Error: reading output en_fase failed\n");
            m->terminate(m); return 1;
        }
        out.en_fase = (int)got_en_fase;
        fmu_real_t got_energia_total = 0.0;
        if (FMU_CALL(m, get_real, &vr_energia_total, 1, &got_energia_total) > FMU_WARNING) {
            SIM_ERROR("Error: reading output energia_total failed\n");
            m->terminate(m); return 1;
        }
        out.energia_total = (double)got_energia_total;
        fmu_real_t got_pos1 = 0.0;
        if (FMU_CALL(m, get_real, &vr_pos1, 1, &got_pos1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output pos1 failed\n");
            m->terminate(m); return 1;
        }
        out.pos1 = (double)got_pos1;
        fmu_real_t got_pos2 = 0.0;
        if (FMU_CALL(m, get_real, &vr_pos2, 1, &got_pos2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output pos2 failed\n");
            m->terminate(m); return 1;
        }
        out.pos2 = (double)got_pos2;
        fmu_real_t got_vel1 = 0.0;
        if (FMU_CALL(m, get_real, &vr_vel1, 1, &got_vel1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output vel1 failed\n");
            m->terminate(m); return 1;
        }
        out.vel1 = (double)got_vel1;
        fmu_real_t got_vel2 = 0.0;
        if (FMU_CALL(m, get_real, &vr_vel2, 1, &got_vel2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output vel2 failed\n");
            m->terminate(m); return 1;
        }
        out.vel2 = (double)got_vel2;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, in.fuerza_externa, (int)out.en_fase, out.energia_total, out.pos1, out.pos2, out.vel1, out.vel2);
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
