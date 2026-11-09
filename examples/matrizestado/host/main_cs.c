/**
 * @file main_cs.c -- generated typed Co-Simulation loop for MatrizEstado.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrizestado_api.h"
#include "matrizestado_adapter.h"

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

    fmu_t *m = matrizestado_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_traza = MATRIZESTADO_VR_TRAZA;
    const fmu_vref_t vr_x_1 = MATRIZESTADO_VR_X_1;
    const fmu_vref_t vr_x_2 = MATRIZESTADO_VR_X_2;
    const fmu_vref_t vr_x_3 = MATRIZESTADO_VR_X_3;
    const fmu_vref_t vr_y_norma = MATRIZESTADO_VR_Y_NORMA;

    SIM_PRINT("t,traza,x[1],x[2],x[3],y_norma\n");
    double t = 0.0;
    for (;;) {
        MatrizEstado_Outputs out = {0};
        fmu_real_t got_traza = 0.0;
        if (FMU_CALL(m, get_real, &vr_traza, 1, &got_traza) > FMU_WARNING) {
            SIM_ERROR("Error: reading output traza failed\n");
            m->terminate(m); return 1;
        }
        out.traza = (double)got_traza;
        fmu_real_t got_x_1 = 0.0;
        if (FMU_CALL(m, get_real, &vr_x_1, 1, &got_x_1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output x[1] failed\n");
            m->terminate(m); return 1;
        }
        out.x_1 = (double)got_x_1;
        fmu_real_t got_x_2 = 0.0;
        if (FMU_CALL(m, get_real, &vr_x_2, 1, &got_x_2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output x[2] failed\n");
            m->terminate(m); return 1;
        }
        out.x_2 = (double)got_x_2;
        fmu_real_t got_x_3 = 0.0;
        if (FMU_CALL(m, get_real, &vr_x_3, 1, &got_x_3) > FMU_WARNING) {
            SIM_ERROR("Error: reading output x[3] failed\n");
            m->terminate(m); return 1;
        }
        out.x_3 = (double)got_x_3;
        fmu_real_t got_y_norma = 0.0;
        if (FMU_CALL(m, get_real, &vr_y_norma, 1, &got_y_norma) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_norma failed\n");
            m->terminate(m); return 1;
        }
        out.y_norma = (double)got_y_norma;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, out.traza, out.x_1, out.x_2, out.x_3, out.y_norma);
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
