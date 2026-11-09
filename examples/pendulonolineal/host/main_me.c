/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para PenduloNoLineal — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : PenduloNoLineal
 * GUID   : {7efc0b1a-c4e8-44f3-ad91-6fca093cece0}
 * Estados: 2  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "pendulonolineal_api.h"
#include "pendulonolineal_adapter.h"

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

    fmu_t *m = pendulonolineal_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_en_reposo = PENDULONOLINEAL_VR_EN_REPOSO;
    const fmu_vref_t vr_angulo = PENDULONOLINEAL_VR_ANGULO;
    const fmu_vref_t vr_energia_total = PENDULONOLINEAL_VR_ENERGIA_TOTAL;
    const fmu_vref_t vr_velocidad_angular = PENDULONOLINEAL_VR_VELOCIDAD_ANGULAR;

    fmu_real_t solver_buf[PENDULONOLINEAL_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? PENDULONOLINEAL_RK4_BUF_SIZE : PENDULONOLINEAL_EULER_BUF_SIZE);

    fmu_real_t x[PENDULONOLINEAL_N_STATES];
    FMU_CALL(m, get_cont_states, x, PENDULONOLINEAL_N_STATES);

    fmu_real_t ei_prev[PENDULONOLINEAL_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[PENDULONOLINEAL_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, PENDULONOLINEAL_N_EVENT_INDICATORS);

    SIM_PRINT("t,en_reposo,angulo,energia_total,velocidad_angular\n");

    double t = 0.0;
    for (;;) {

        FMU_CALL(m, set_time, (fmu_real_t)t);
        FMU_CALL(m, set_cont_states, x, PENDULONOLINEAL_N_STATES);

        PenduloNoLineal_Outputs out = {0};
        {
            fmu_bool_t _o_en_reposo = 0;
            FMU_CALL(m, get_boolean, &vr_en_reposo, 1, &_o_en_reposo);
            out.en_reposo = (int)_o_en_reposo;
        }
        {
            fmu_real_t _o_angulo = 0.0;
            FMU_CALL(m, get_real, &vr_angulo, 1, &_o_angulo);
            out.angulo = (double)_o_angulo;
        }
        {
            fmu_real_t _o_energia_total = 0.0;
            FMU_CALL(m, get_real, &vr_energia_total, 1, &_o_energia_total);
            out.energia_total = (double)_o_energia_total;
        }
        {
            fmu_real_t _o_velocidad_angular = 0.0;
            FMU_CALL(m, get_real, &vr_velocidad_angular, 1, &_o_velocidad_angular);
            out.velocidad_angular = (double)_o_velocidad_angular;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%.10g,%.10g\n", t, (int)out.en_reposo, out.angulo, out.energia_total, out.velocidad_angular);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, PENDULONOLINEAL_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, PENDULONOLINEAL_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, PENDULONOLINEAL_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < PENDULONOLINEAL_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < PENDULONOLINEAL_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, PENDULONOLINEAL_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, PENDULONOLINEAL_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
