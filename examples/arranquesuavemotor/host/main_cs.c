/**
 * @file main_cs.c -- generated typed Co-Simulation loop for ArranqueSuaveMotor.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arranquesuavemotor_api.h"
#include "arranquesuavemotor_adapter.h"

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
    double cli_orden_arranque = 0.0; int has_orden_arranque = 0;
    struct { double t; double val; } sched_orden_arranque[MAX_SCHEDULE]; int ns_orden_arranque = 0;
    double cli_carga_motor = 0.0; int has_carga_motor = 0;
    struct { double t; double val; } sched_carga_motor[MAX_SCHEDULE]; int ns_carga_motor = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "orden_arranque") == 0 && ns_orden_arranque < MAX_SCHEDULE) {
                sched_orden_arranque[ns_orden_arranque].t = at_t;
                sched_orden_arranque[ns_orden_arranque++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "carga_motor") == 0 && ns_carga_motor < MAX_SCHEDULE) {
                sched_carga_motor[ns_carga_motor].t = at_t;
                sched_carga_motor[ns_carga_motor++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "orden_arranque") == 0) { cli_orden_arranque = (double)((atoi(_eq + 1) != 0)); has_orden_arranque = 1; }
            if (strcmp(argv[oi], "carga_motor") == 0) { cli_carga_motor = (double)(atof(_eq + 1)); has_carga_motor = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = arranquesuavemotor_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_orden_arranque = ARRANQUESUAVEMOTOR_VR_ORDEN_ARRANQUE;
    const fmu_vref_t vr_carga_motor = ARRANQUESUAVEMOTOR_VR_CARGA_MOTOR;
    const fmu_vref_t vr_en_rampa = ARRANQUESUAVEMOTOR_VR_EN_RAMPA;
    const fmu_vref_t vr_fallo_sobrecarga = ARRANQUESUAVEMOTOR_VR_FALLO_SOBRECARGA;
    const fmu_vref_t vr_motor_en_marcha = ARRANQUESUAVEMOTOR_VR_MOTOR_EN_MARCHA;
    const fmu_vref_t vr_tension_aplicada = ARRANQUESUAVEMOTOR_VR_TENSION_APLICADA;

    SIM_PRINT("t,orden_arranque,carga_motor,en_rampa,fallo_sobrecarga,motor_en_marcha,tension_aplicada\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        ArranqueSuaveMotor_Inputs in = {0};
        get_inputs(t, &in);
        if (has_orden_arranque) in.orden_arranque = (int)cli_orden_arranque;
        if (ns_orden_arranque > 0) {
            double best = (double)in.orden_arranque; double best_t = -1e300;
            for (int si = 0; si < ns_orden_arranque; si++)
                if (t >= sched_orden_arranque[si].t && sched_orden_arranque[si].t >= best_t)
                    { best = sched_orden_arranque[si].val; best_t = sched_orden_arranque[si].t; }
            in.orden_arranque = (int)best;
        }
        if (has_carga_motor) in.carga_motor = (double)cli_carga_motor;
        if (ns_carga_motor > 0) {
            double best = (double)in.carga_motor; double best_t = -1e300;
            for (int si = 0; si < ns_carga_motor; si++)
                if (t >= sched_carga_motor[si].t && sched_carga_motor[si].t >= best_t)
                    { best = sched_carga_motor[si].val; best_t = sched_carga_motor[si].t; }
            in.carga_motor = (double)best;
        }
        fmu_bool_t set_orden_arranque = (fmu_bool_t)in.orden_arranque;
        if (FMU_CALL(m, set_boolean, &vr_orden_arranque, 1, (const fmu_bool_t *)&set_orden_arranque) > FMU_WARNING) {
            SIM_ERROR("Error: setting input orden_arranque failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_carga_motor = (fmu_real_t)in.carga_motor;
        if (FMU_CALL(m, set_real, &vr_carga_motor, 1, (const fmu_real_t *)&set_carga_motor) > FMU_WARNING) {
            SIM_ERROR("Error: setting input carga_motor failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        ArranqueSuaveMotor_Outputs out = {0};
        fmu_bool_t got_en_rampa = 0;
        if (FMU_CALL(m, get_boolean, &vr_en_rampa, 1, &got_en_rampa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output en_rampa failed\n");
            m->terminate(m); return 1;
        }
        out.en_rampa = (int)got_en_rampa;
        fmu_bool_t got_fallo_sobrecarga = 0;
        if (FMU_CALL(m, get_boolean, &vr_fallo_sobrecarga, 1, &got_fallo_sobrecarga) > FMU_WARNING) {
            SIM_ERROR("Error: reading output fallo_sobrecarga failed\n");
            m->terminate(m); return 1;
        }
        out.fallo_sobrecarga = (int)got_fallo_sobrecarga;
        fmu_bool_t got_motor_en_marcha = 0;
        if (FMU_CALL(m, get_boolean, &vr_motor_en_marcha, 1, &got_motor_en_marcha) > FMU_WARNING) {
            SIM_ERROR("Error: reading output motor_en_marcha failed\n");
            m->terminate(m); return 1;
        }
        out.motor_en_marcha = (int)got_motor_en_marcha;
        fmu_real_t got_tension_aplicada = 0.0;
        if (FMU_CALL(m, get_real, &vr_tension_aplicada, 1, &got_tension_aplicada) > FMU_WARNING) {
            SIM_ERROR("Error: reading output tension_aplicada failed\n");
            m->terminate(m); return 1;
        }
        out.tension_aplicada = (double)got_tension_aplicada;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.orden_arranque, in.carga_motor, (int)out.en_rampa, (int)out.fallo_sobrecarga, (int)out.motor_en_marcha, out.tension_aplicada);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
