/**
 * @file main_cs.c -- generated typed Co-Simulation loop for FrenadoABS.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "frenadoabs_api.h"
#include "frenadoabs_adapter.h"

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
    double cli_presion_pedal = 0.0; int has_presion_pedal = 0;
    struct { double t; double val; } sched_presion_pedal[MAX_SCHEDULE]; int ns_presion_pedal = 0;
    double cli_velocidad_rueda = 0.0; int has_velocidad_rueda = 0;
    struct { double t; double val; } sched_velocidad_rueda[MAX_SCHEDULE]; int ns_velocidad_rueda = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "presion_pedal") == 0 && ns_presion_pedal < MAX_SCHEDULE) {
                sched_presion_pedal[ns_presion_pedal].t = at_t;
                sched_presion_pedal[ns_presion_pedal++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "velocidad_rueda") == 0 && ns_velocidad_rueda < MAX_SCHEDULE) {
                sched_velocidad_rueda[ns_velocidad_rueda].t = at_t;
                sched_velocidad_rueda[ns_velocidad_rueda++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "presion_pedal") == 0) { cli_presion_pedal = (double)(atof(_eq + 1)); has_presion_pedal = 1; }
            if (strcmp(argv[oi], "velocidad_rueda") == 0) { cli_velocidad_rueda = (double)(atof(_eq + 1)); has_velocidad_rueda = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = frenadoabs_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_presion_pedal = FRENADOABS_VR_PRESION_PEDAL;
    const fmu_vref_t vr_velocidad_rueda = FRENADOABS_VR_VELOCIDAD_RUEDA;
    const fmu_vref_t vr_abs_activo = FRENADOABS_VR_ABS_ACTIVO;
    const fmu_vref_t vr_frenado_normal = FRENADOABS_VR_FRENADO_NORMAL;
    const fmu_vref_t vr_rueda_bloqueada = FRENADOABS_VR_RUEDA_BLOQUEADA;
    const fmu_vref_t vr_presion_modulada = FRENADOABS_VR_PRESION_MODULADA;

    SIM_PRINT("t,presion_pedal,velocidad_rueda,abs_activo,frenado_normal,rueda_bloqueada,presion_modulada\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        FrenadoABS_Inputs in = {0};
        get_inputs(t, &in);
        if (has_presion_pedal) in.presion_pedal = (double)cli_presion_pedal;
        if (ns_presion_pedal > 0) {
            double best = (double)in.presion_pedal; double best_t = -1e300;
            for (int si = 0; si < ns_presion_pedal; si++)
                if (t >= sched_presion_pedal[si].t && sched_presion_pedal[si].t >= best_t)
                    { best = sched_presion_pedal[si].val; best_t = sched_presion_pedal[si].t; }
            in.presion_pedal = (double)best;
        }
        if (has_velocidad_rueda) in.velocidad_rueda = (double)cli_velocidad_rueda;
        if (ns_velocidad_rueda > 0) {
            double best = (double)in.velocidad_rueda; double best_t = -1e300;
            for (int si = 0; si < ns_velocidad_rueda; si++)
                if (t >= sched_velocidad_rueda[si].t && sched_velocidad_rueda[si].t >= best_t)
                    { best = sched_velocidad_rueda[si].val; best_t = sched_velocidad_rueda[si].t; }
            in.velocidad_rueda = (double)best;
        }
        fmu_real_t set_presion_pedal = (fmu_real_t)in.presion_pedal;
        if (FMU_CALL(m, set_real, &vr_presion_pedal, 1, (const fmu_real_t *)&set_presion_pedal) > FMU_WARNING) {
            SIM_ERROR("Error: setting input presion_pedal failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_velocidad_rueda = (fmu_real_t)in.velocidad_rueda;
        if (FMU_CALL(m, set_real, &vr_velocidad_rueda, 1, (const fmu_real_t *)&set_velocidad_rueda) > FMU_WARNING) {
            SIM_ERROR("Error: setting input velocidad_rueda failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        FrenadoABS_Outputs out = {0};
        fmu_bool_t got_abs_activo = 0;
        if (FMU_CALL(m, get_boolean, &vr_abs_activo, 1, &got_abs_activo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output abs_activo failed\n");
            m->terminate(m); return 1;
        }
        out.abs_activo = (int)got_abs_activo;
        fmu_bool_t got_frenado_normal = 0;
        if (FMU_CALL(m, get_boolean, &vr_frenado_normal, 1, &got_frenado_normal) > FMU_WARNING) {
            SIM_ERROR("Error: reading output frenado_normal failed\n");
            m->terminate(m); return 1;
        }
        out.frenado_normal = (int)got_frenado_normal;
        fmu_bool_t got_rueda_bloqueada = 0;
        if (FMU_CALL(m, get_boolean, &vr_rueda_bloqueada, 1, &got_rueda_bloqueada) > FMU_WARNING) {
            SIM_ERROR("Error: reading output rueda_bloqueada failed\n");
            m->terminate(m); return 1;
        }
        out.rueda_bloqueada = (int)got_rueda_bloqueada;
        fmu_real_t got_presion_modulada = 0.0;
        if (FMU_CALL(m, get_real, &vr_presion_modulada, 1, &got_presion_modulada) > FMU_WARNING) {
            SIM_ERROR("Error: reading output presion_modulada failed\n");
            m->terminate(m); return 1;
        }
        out.presion_modulada = (double)got_presion_modulada;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.presion_pedal, in.velocidad_rueda, (int)out.abs_activo, (int)out.frenado_normal, (int)out.rueda_bloqueada, out.presion_modulada);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
