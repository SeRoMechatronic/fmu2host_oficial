/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para ArraysVectores — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : ArraysVectores
 * GUID   : {00d6ddbc-ef60-461b-ad3e-2fcdca1616a5}
 * Estados: 0  |  Indicadores: 0
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arraysvectores_api.h"
#include "arraysvectores_adapter.h"

#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#define SIM_ERROR(msg)       fprintf(stderr, "%s", msg)
#define SIM_DELAY(h)         ((void)(h))

static int process_events(fmu_t *m)
{
    if (FMU_CALL(m, enter_event_mode) > FMU_WARNING) return -1;
    fmu_bool_t more = 1, terminate = 0;
    while (more && !terminate) {
        if (FMU_CALL(m, new_discrete_states, &more, &terminate) > FMU_WARNING)
            return -1;
    }
    if (terminate) return -1;
    return (FMU_CALL(m, enter_cont_mode) <= FMU_WARNING) ? 0 : -1;
}

int main(int argc, char *argv[])
{
    SimConfig cfg = get_config();

    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);
    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h     = atof(argv[2]);

    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    (void)argc; (void)argv;

    fmu_t *m = arraysvectores_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
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
    for (;;) {

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        ArraysVectores_Outputs out = {0};
        {
            fmu_real_t _o_suma_real = 0.0;
            FMU_CALL(m, get_real, &vr_suma_real, 1, &_o_suma_real);
            out.suma_real = (double)_o_suma_real;
        }
        {
            fmu_int_t _o_suma_int = 0;
            FMU_CALL(m, get_integer, &vr_suma_int, 1, &_o_suma_int);
            out.suma_int = (int)_o_suma_int;
        }
        {
            fmu_real_t _o_v_doble_1 = 0.0;
            FMU_CALL(m, get_real, &vr_v_doble_1, 1, &_o_v_doble_1);
            out.v_doble_1 = (double)_o_v_doble_1;
        }
        {
            fmu_real_t _o_v_doble_2 = 0.0;
            FMU_CALL(m, get_real, &vr_v_doble_2, 1, &_o_v_doble_2);
            out.v_doble_2 = (double)_o_v_doble_2;
        }
        {
            fmu_real_t _o_v_doble_3 = 0.0;
            FMU_CALL(m, get_real, &vr_v_doble_3, 1, &_o_v_doble_3);
            out.v_doble_3 = (double)_o_v_doble_3;
        }
        {
            fmu_real_t _o_v_doble_4 = 0.0;
            FMU_CALL(m, get_real, &vr_v_doble_4, 1, &_o_v_doble_4);
            out.v_doble_4 = (double)_o_v_doble_4;
        }
        {
            fmu_bool_t _o_alguno_true = 0;
            FMU_CALL(m, get_boolean, &vr_alguno_true, 1, &_o_alguno_true);
            out.alguno_true = (int)_o_alguno_true;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g,%.10g,%d\n", t, out.suma_real, (int)out.suma_int, out.v_doble_1, out.v_doble_2, out.v_doble_3, out.v_doble_4, (int)out.alguno_true);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
