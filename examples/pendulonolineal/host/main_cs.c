/**
 * @file main_cs.c -- generated typed Co-Simulation loop for PenduloNoLineal.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pendulonolineal_api.h"
#include "pendulonolineal_adapter.h"

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

    (void)argc; (void)argv;

    fmu_t *m = pendulonolineal_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_en_reposo = PENDULONOLINEAL_VR_EN_REPOSO;
    const fmu_vref_t vr_angulo = PENDULONOLINEAL_VR_ANGULO;
    const fmu_vref_t vr_energia_total = PENDULONOLINEAL_VR_ENERGIA_TOTAL;
    const fmu_vref_t vr_velocidad_angular = PENDULONOLINEAL_VR_VELOCIDAD_ANGULAR;

    SIM_PRINT("t,en_reposo,angulo,energia_total,velocidad_angular\n");
    double t = 0.0;
    for (;;) {
        PenduloNoLineal_Outputs out = {0};
        fmu_bool_t got_en_reposo = 0;
        if (FMU_CALL(m, get_boolean, &vr_en_reposo, 1, &got_en_reposo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output en_reposo failed\n");
            m->terminate(m); return 1;
        }
        out.en_reposo = (int)got_en_reposo;
        fmu_real_t got_angulo = 0.0;
        if (FMU_CALL(m, get_real, &vr_angulo, 1, &got_angulo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output angulo failed\n");
            m->terminate(m); return 1;
        }
        out.angulo = (double)got_angulo;
        fmu_real_t got_energia_total = 0.0;
        if (FMU_CALL(m, get_real, &vr_energia_total, 1, &got_energia_total) > FMU_WARNING) {
            SIM_ERROR("Error: reading output energia_total failed\n");
            m->terminate(m); return 1;
        }
        out.energia_total = (double)got_energia_total;
        fmu_real_t got_velocidad_angular = 0.0;
        if (FMU_CALL(m, get_real, &vr_velocidad_angular, 1, &got_velocidad_angular) > FMU_WARNING) {
            SIM_ERROR("Error: reading output velocidad_angular failed\n");
            m->terminate(m); return 1;
        }
        out.velocidad_angular = (double)got_velocidad_angular;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%.10g,%.10g\n", t, (int)out.en_reposo, out.angulo, out.energia_total, out.velocidad_angular);
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
