/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para MatrizEstado — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : MatrizEstado
 * GUID   : {3a0ae851-e11b-4c5c-82ce-70d83b41ce13}
 * Estados: 3  |  Indicadores: 0
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "matrizestado_api.h"
#include "matrizestado_adapter.h"

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
    if (argc >= 4 && !strchr(argv[3], '=')) cfg.use_rk4 = (strcmp(argv[3], "rk4") == 0);

    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    (void)argc; (void)argv;

    fmu_t *m = matrizestado_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_traza = MATRIZESTADO_VR_TRAZA;
    const fmu_vref_t vr_x_1 = MATRIZESTADO_VR_X_1;
    const fmu_vref_t vr_x_2 = MATRIZESTADO_VR_X_2;
    const fmu_vref_t vr_x_3 = MATRIZESTADO_VR_X_3;
    const fmu_vref_t vr_y_norma = MATRIZESTADO_VR_Y_NORMA;

    fmu_real_t solver_buf[MATRIZESTADO_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? MATRIZESTADO_RK4_BUF_SIZE : MATRIZESTADO_EULER_BUF_SIZE);

    fmu_real_t x[MATRIZESTADO_N_STATES];
    FMU_CALL(m, get_cont_states, x, MATRIZESTADO_N_STATES);

    SIM_PRINT("t,traza,x[1],x[2],x[3],y_norma\n");

    double t = 0.0;
    for (;;) {

        FMU_CALL(m, set_time, (fmu_real_t)t);
        FMU_CALL(m, set_cont_states, x, MATRIZESTADO_N_STATES);

        MatrizEstado_Outputs out = {0};
        {
            fmu_real_t _o_traza = 0.0;
            FMU_CALL(m, get_real, &vr_traza, 1, &_o_traza);
            out.traza = (double)_o_traza;
        }
        {
            fmu_real_t _o_x_1 = 0.0;
            FMU_CALL(m, get_real, &vr_x_1, 1, &_o_x_1);
            out.x_1 = (double)_o_x_1;
        }
        {
            fmu_real_t _o_x_2 = 0.0;
            FMU_CALL(m, get_real, &vr_x_2, 1, &_o_x_2);
            out.x_2 = (double)_o_x_2;
        }
        {
            fmu_real_t _o_x_3 = 0.0;
            FMU_CALL(m, get_real, &vr_x_3, 1, &_o_x_3);
            out.x_3 = (double)_o_x_3;
        }
        {
            fmu_real_t _o_y_norma = 0.0;
            FMU_CALL(m, get_real, &vr_y_norma, 1, &_o_y_norma);
            out.y_norma = (double)_o_y_norma;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%.10g,%.10g,%.10g\n", t, out.traza, out.x_1, out.x_2, out.x_3, out.y_norma);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, MATRIZESTADO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, MATRIZESTADO_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, MATRIZESTADO_N_STATES);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
