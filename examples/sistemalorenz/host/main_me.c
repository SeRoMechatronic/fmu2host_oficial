/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para SistemaLorenz — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : SistemaLorenz
 * GUID   : {e184239f-b020-43fc-8477-5b9da822fb88}
 * Estados: 3  |  Indicadores: 1
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fmu_solver.h"
#include "sistemalorenz_api.h"
#include "sistemalorenz_adapter.h"

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

    fmu_t *m = sistemalorenz_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_on_attractor = SISTEMALORENZ_VR_ON_ATTRACTOR;
    const fmu_vref_t vr_x_out = SISTEMALORENZ_VR_X_OUT;
    const fmu_vref_t vr_y_out = SISTEMALORENZ_VR_Y_OUT;
    const fmu_vref_t vr_z_out = SISTEMALORENZ_VR_Z_OUT;

    fmu_real_t solver_buf[SISTEMALORENZ_RK4_BUF_SIZE];
    fmu_solver_t solver;
    fmu_solver_init(&solver, solver_buf,
                   cfg.use_rk4 ? SISTEMALORENZ_RK4_BUF_SIZE : SISTEMALORENZ_EULER_BUF_SIZE);

    fmu_real_t x[SISTEMALORENZ_N_STATES];
    FMU_CALL(m, get_cont_states, x, SISTEMALORENZ_N_STATES);

    fmu_real_t ei_prev[SISTEMALORENZ_N_EVENT_INDICATORS];
    fmu_real_t ei_curr[SISTEMALORENZ_N_EVENT_INDICATORS];
    FMU_CALL(m, get_event_indicators, ei_prev, SISTEMALORENZ_N_EVENT_INDICATORS);

    SIM_PRINT("t,on_attractor,x_out,y_out,z_out\n");

    double t = 0.0;
    for (;;) {

        FMU_CALL(m, set_time, (fmu_real_t)t);
        FMU_CALL(m, set_cont_states, x, SISTEMALORENZ_N_STATES);

        SistemaLorenz_Outputs out = {0};
        {
            fmu_bool_t _o_on_attractor = 0;
            FMU_CALL(m, get_boolean, &vr_on_attractor, 1, &_o_on_attractor);
            out.on_attractor = (int)_o_on_attractor;
        }
        {
            fmu_real_t _o_x_out = 0.0;
            FMU_CALL(m, get_real, &vr_x_out, 1, &_o_x_out);
            out.x_out = (double)_o_x_out;
        }
        {
            fmu_real_t _o_y_out = 0.0;
            FMU_CALL(m, get_real, &vr_y_out, 1, &_o_y_out);
            out.y_out = (double)_o_y_out;
        }
        {
            fmu_real_t _o_z_out = 0.0;
            FMU_CALL(m, get_real, &vr_z_out, 1, &_o_z_out);
            out.z_out = (double)_o_z_out;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%.10g,%.10g,%.10g\n", t, (int)out.on_attractor, out.x_out, out.y_out, out.z_out);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        if (cfg.use_rk4)
            fmu_rk4_step(m, &solver, x, SISTEMALORENZ_N_STATES, (fmu_real_t)t, (fmu_real_t)step);
        else
            fmu_euler_step(m, &solver, x, SISTEMALORENZ_N_STATES, (fmu_real_t)t, (fmu_real_t)step);

        FMU_CALL(m, get_event_indicators, ei_curr, SISTEMALORENZ_N_EVENT_INDICATORS);
        fmu_bool_t zero_cross = 0;
        for (int i = 0; i < SISTEMALORENZ_N_EVENT_INDICATORS; i++) {
            if ((ei_prev[i] > 0.0) != (ei_curr[i] > 0.0)) { zero_cross = 1; break; }
        }
        for (int i = 0; i < SISTEMALORENZ_N_EVENT_INDICATORS; i++)
            ei_prev[i] = ei_curr[i];

        fmu_bool_t enter_event = 0;
        if (FMU_CALL(m, completed_step, &enter_event) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2CompletedIntegratorStep failed\n");
            break;
        }
        if (m->termination_requested) break;
        if (enter_event || zero_cross) {
            if (process_events(m) != 0) break;
            FMU_CALL(m, get_cont_states, x, SISTEMALORENZ_N_STATES);
            FMU_CALL(m, get_event_indicators, ei_prev, SISTEMALORENZ_N_EVENT_INDICATORS);
        }

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
