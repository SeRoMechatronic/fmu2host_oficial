/**
 * @file main_cs.c -- generated typed Co-Simulation loop for CrecimientoPoblacional.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "crecimientopoblacional_api.h"
#include "crecimientopoblacional_adapter.h"

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
    double cli_tasa_entrada = 0.0; int has_tasa_entrada = 0;
    struct { double t; double val; } sched_tasa_entrada[MAX_SCHEDULE]; int ns_tasa_entrada = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "tasa_entrada") == 0 && ns_tasa_entrada < MAX_SCHEDULE) {
                sched_tasa_entrada[ns_tasa_entrada].t = at_t;
                sched_tasa_entrada[ns_tasa_entrada++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "tasa_entrada") == 0) { cli_tasa_entrada = (double)(atof(_eq + 1)); has_tasa_entrada = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = crecimientopoblacional_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_tasa_entrada = CRECIMIENTOPOBLACIONAL_VR_TASA_ENTRADA;
    const fmu_vref_t vr_superpoblacion = CRECIMIENTOPOBLACIONAL_VR_SUPERPOBLACION;
    const fmu_vref_t vr_poblacion = CRECIMIENTOPOBLACIONAL_VR_POBLACION;
    const fmu_vref_t vr_saturacion = CRECIMIENTOPOBLACIONAL_VR_SATURACION;
    const fmu_vref_t vr_tasa_crecimiento = CRECIMIENTOPOBLACIONAL_VR_TASA_CRECIMIENTO;

    SIM_PRINT("t,tasa_entrada,superpoblacion,poblacion,saturacion,tasa_crecimiento\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        CrecimientoPoblacional_Inputs in = {0};
        get_inputs(t, &in);
        if (has_tasa_entrada) in.tasa_entrada = (double)cli_tasa_entrada;
        if (ns_tasa_entrada > 0) {
            double best = (double)in.tasa_entrada; double best_t = -1e300;
            for (int si = 0; si < ns_tasa_entrada; si++)
                if (t >= sched_tasa_entrada[si].t && sched_tasa_entrada[si].t >= best_t)
                    { best = sched_tasa_entrada[si].val; best_t = sched_tasa_entrada[si].t; }
            in.tasa_entrada = (double)best;
        }
        fmu_real_t set_tasa_entrada = (fmu_real_t)in.tasa_entrada;
        if (FMU_CALL(m, set_real, &vr_tasa_entrada, 1, (const fmu_real_t *)&set_tasa_entrada) > FMU_WARNING) {
            SIM_ERROR("Error: setting input tasa_entrada failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        CrecimientoPoblacional_Outputs out = {0};
        fmu_bool_t got_superpoblacion = 0;
        if (FMU_CALL(m, get_boolean, &vr_superpoblacion, 1, &got_superpoblacion) > FMU_WARNING) {
            SIM_ERROR("Error: reading output superpoblacion failed\n");
            m->terminate(m); return 1;
        }
        out.superpoblacion = (int)got_superpoblacion;
        fmu_real_t got_poblacion = 0.0;
        if (FMU_CALL(m, get_real, &vr_poblacion, 1, &got_poblacion) > FMU_WARNING) {
            SIM_ERROR("Error: reading output poblacion failed\n");
            m->terminate(m); return 1;
        }
        out.poblacion = (double)got_poblacion;
        fmu_real_t got_saturacion = 0.0;
        if (FMU_CALL(m, get_real, &vr_saturacion, 1, &got_saturacion) > FMU_WARNING) {
            SIM_ERROR("Error: reading output saturacion failed\n");
            m->terminate(m); return 1;
        }
        out.saturacion = (double)got_saturacion;
        fmu_real_t got_tasa_crecimiento = 0.0;
        if (FMU_CALL(m, get_real, &vr_tasa_crecimiento, 1, &got_tasa_crecimiento) > FMU_WARNING) {
            SIM_ERROR("Error: reading output tasa_crecimiento failed\n");
            m->terminate(m); return 1;
        }
        out.tasa_crecimiento = (double)got_tasa_crecimiento;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%.10g,%.10g,%.10g\n", t, in.tasa_entrada, (int)out.superpoblacion, out.poblacion, out.saturacion, out.tasa_crecimiento);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
