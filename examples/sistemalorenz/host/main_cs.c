/**
 * @file main_cs.c -- generated typed Co-Simulation loop for SistemaLorenz.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sistemalorenz_api.h"
#include "sistemalorenz_adapter.h"

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

    fmu_t *m = sistemalorenz_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_on_attractor = SISTEMALORENZ_VR_ON_ATTRACTOR;
    const fmu_vref_t vr_x_out = SISTEMALORENZ_VR_X_OUT;
    const fmu_vref_t vr_y_out = SISTEMALORENZ_VR_Y_OUT;
    const fmu_vref_t vr_z_out = SISTEMALORENZ_VR_Z_OUT;

    SIM_PRINT("t,on_attractor,x_out,y_out,z_out\n");
    double t = 0.0;
    for (;;) {
        SistemaLorenz_Outputs out = {0};
        fmu_bool_t got_on_attractor = 0;
        if (FMU_CALL(m, get_boolean, &vr_on_attractor, 1, &got_on_attractor) > FMU_WARNING) {
            SIM_ERROR("Error: reading output on_attractor failed\n");
            m->terminate(m); return 1;
        }
        out.on_attractor = (int)got_on_attractor;
        fmu_real_t got_x_out = 0.0;
        if (FMU_CALL(m, get_real, &vr_x_out, 1, &got_x_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output x_out failed\n");
            m->terminate(m); return 1;
        }
        out.x_out = (double)got_x_out;
        fmu_real_t got_y_out = 0.0;
        if (FMU_CALL(m, get_real, &vr_y_out, 1, &got_y_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output y_out failed\n");
            m->terminate(m); return 1;
        }
        out.y_out = (double)got_y_out;
        fmu_real_t got_z_out = 0.0;
        if (FMU_CALL(m, get_real, &vr_z_out, 1, &got_z_out) > FMU_WARNING) {
            SIM_ERROR("Error: reading output z_out failed\n");
            m->terminate(m); return 1;
        }
        out.z_out = (double)got_z_out;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%.10g,%.10g\n", t, (int)out.on_attractor, out.x_out, out.y_out, out.z_out);
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
