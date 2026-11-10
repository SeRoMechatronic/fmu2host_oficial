/**
 * @file main_cs.c -- generated typed Co-Simulation loop for ArraysVectores.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arraysvectores_api.h"
#include "arraysvectores_adapter.h"

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

    fmu_t *m = arraysvectores_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_suma_real = ARRAYSVECTORES_VR_SUMA_REAL;
    const fmu_vref_t vr_suma_int = ARRAYSVECTORES_VR_SUMA_INT;
    const fmu_vref_t vr_v_doble_1 = ARRAYSVECTORES_VR_V_DOBLE_1;
    const fmu_vref_t vr_v_doble_2 = ARRAYSVECTORES_VR_V_DOBLE_2;
    const fmu_vref_t vr_v_doble_3 = ARRAYSVECTORES_VR_V_DOBLE_3;
    const fmu_vref_t vr_v_doble_4 = ARRAYSVECTORES_VR_V_DOBLE_4;
    const fmu_vref_t vr_alguno_true = ARRAYSVECTORES_VR_ALGUNO_TRUE;

    SIM_PRINT("t,suma_real,suma_int,v_doble[1],v_doble[2],v_doble[3],v_doble[4],alguno_true\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        ArraysVectores_Outputs out = {0};
        fmu_real_t got_suma_real = 0.0;
        if (FMU_CALL(m, get_real, &vr_suma_real, 1, &got_suma_real) > FMU_WARNING) {
            SIM_ERROR("Error: reading output suma_real failed\n");
            m->terminate(m); return 1;
        }
        out.suma_real = (double)got_suma_real;
        fmu_int_t got_suma_int = 0;
        if (FMU_CALL(m, get_integer, &vr_suma_int, 1, &got_suma_int) > FMU_WARNING) {
            SIM_ERROR("Error: reading output suma_int failed\n");
            m->terminate(m); return 1;
        }
        out.suma_int = (int)got_suma_int;
        fmu_real_t got_v_doble_1 = 0.0;
        if (FMU_CALL(m, get_real, &vr_v_doble_1, 1, &got_v_doble_1) > FMU_WARNING) {
            SIM_ERROR("Error: reading output v_doble[1] failed\n");
            m->terminate(m); return 1;
        }
        out.v_doble_1 = (double)got_v_doble_1;
        fmu_real_t got_v_doble_2 = 0.0;
        if (FMU_CALL(m, get_real, &vr_v_doble_2, 1, &got_v_doble_2) > FMU_WARNING) {
            SIM_ERROR("Error: reading output v_doble[2] failed\n");
            m->terminate(m); return 1;
        }
        out.v_doble_2 = (double)got_v_doble_2;
        fmu_real_t got_v_doble_3 = 0.0;
        if (FMU_CALL(m, get_real, &vr_v_doble_3, 1, &got_v_doble_3) > FMU_WARNING) {
            SIM_ERROR("Error: reading output v_doble[3] failed\n");
            m->terminate(m); return 1;
        }
        out.v_doble_3 = (double)got_v_doble_3;
        fmu_real_t got_v_doble_4 = 0.0;
        if (FMU_CALL(m, get_real, &vr_v_doble_4, 1, &got_v_doble_4) > FMU_WARNING) {
            SIM_ERROR("Error: reading output v_doble[4] failed\n");
            m->terminate(m); return 1;
        }
        out.v_doble_4 = (double)got_v_doble_4;
        fmu_bool_t got_alguno_true = 0;
        if (FMU_CALL(m, get_boolean, &vr_alguno_true, 1, &got_alguno_true) > FMU_WARNING) {
            SIM_ERROR("Error: reading output alguno_true failed\n");
            m->terminate(m); return 1;
        }
        out.alguno_true = (int)got_alguno_true;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%d\n", t, out.suma_real, (int)out.suma_int, out.v_doble_1, out.v_doble_2, out.v_doble_3, out.v_doble_4, (int)out.alguno_true);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
