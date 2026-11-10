/**
 * @file main_cs.c -- generated typed Co-Simulation loop for OsciladorArmonico.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "osciladorarmonico_api.h"
#include "osciladorarmonico_adapter.h"

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

    fmu_t *m = osciladorarmonico_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_energia = OSCILADORARMONICO_VR_ENERGIA;
    const fmu_vref_t vr_posicion = OSCILADORARMONICO_VR_POSICION;
    const fmu_vref_t vr_velocidad = OSCILADORARMONICO_VR_VELOCIDAD;

    SIM_PRINT("t,energia,posicion,velocidad\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        OsciladorArmonico_Outputs out = {0};
        fmu_real_t got_energia = 0.0;
        if (FMU_CALL(m, get_real, &vr_energia, 1, &got_energia) > FMU_WARNING) {
            SIM_ERROR("Error: reading output energia failed\n");
            m->terminate(m); return 1;
        }
        out.energia = (double)got_energia;
        fmu_real_t got_posicion = 0.0;
        if (FMU_CALL(m, get_real, &vr_posicion, 1, &got_posicion) > FMU_WARNING) {
            SIM_ERROR("Error: reading output posicion failed\n");
            m->terminate(m); return 1;
        }
        out.posicion = (double)got_posicion;
        fmu_real_t got_velocidad = 0.0;
        if (FMU_CALL(m, get_real, &vr_velocidad, 1, &got_velocidad) > FMU_WARNING) {
            SIM_ERROR("Error: reading output velocidad failed\n");
            m->terminate(m); return 1;
        }
        out.velocidad = (double)got_velocidad;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%.10g\n", t, out.energia, out.posicion, out.velocidad);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
