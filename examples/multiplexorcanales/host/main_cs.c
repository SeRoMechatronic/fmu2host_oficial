/**
 * @file main_cs.c -- generated typed Co-Simulation loop for MultiplexorCanales.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "multiplexorcanales_api.h"
#include "multiplexorcanales_adapter.h"

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
    double cli_canal_0 = 0.0; int has_canal_0 = 0;
    struct { double t; double val; } sched_canal_0[MAX_SCHEDULE]; int ns_canal_0 = 0;
    double cli_canal_1 = 0.0; int has_canal_1 = 0;
    struct { double t; double val; } sched_canal_1[MAX_SCHEDULE]; int ns_canal_1 = 0;
    double cli_canal_seleccion = 0.0; int has_canal_seleccion = 0;
    struct { double t; double val; } sched_canal_seleccion[MAX_SCHEDULE]; int ns_canal_seleccion = 0;
    double cli_canal_2 = 0.0; int has_canal_2 = 0;
    struct { double t; double val; } sched_canal_2[MAX_SCHEDULE]; int ns_canal_2 = 0;
    double cli_canal_3 = 0.0; int has_canal_3 = 0;
    struct { double t; double val; } sched_canal_3[MAX_SCHEDULE]; int ns_canal_3 = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "canal_0") == 0 && ns_canal_0 < MAX_SCHEDULE) {
                sched_canal_0[ns_canal_0].t = at_t;
                sched_canal_0[ns_canal_0++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "canal_1") == 0 && ns_canal_1 < MAX_SCHEDULE) {
                sched_canal_1[ns_canal_1].t = at_t;
                sched_canal_1[ns_canal_1++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "canal_seleccion") == 0 && ns_canal_seleccion < MAX_SCHEDULE) {
                sched_canal_seleccion[ns_canal_seleccion].t = at_t;
                sched_canal_seleccion[ns_canal_seleccion++].val = (double)(atoi(_eq + 1));
            }
            if (strcmp(argv[oi], "canal_2") == 0 && ns_canal_2 < MAX_SCHEDULE) {
                sched_canal_2[ns_canal_2].t = at_t;
                sched_canal_2[ns_canal_2++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "canal_3") == 0 && ns_canal_3 < MAX_SCHEDULE) {
                sched_canal_3[ns_canal_3].t = at_t;
                sched_canal_3[ns_canal_3++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "canal_0") == 0) { cli_canal_0 = (double)(atof(_eq + 1)); has_canal_0 = 1; }
            if (strcmp(argv[oi], "canal_1") == 0) { cli_canal_1 = (double)(atof(_eq + 1)); has_canal_1 = 1; }
            if (strcmp(argv[oi], "canal_seleccion") == 0) { cli_canal_seleccion = (double)(atoi(_eq + 1)); has_canal_seleccion = 1; }
            if (strcmp(argv[oi], "canal_2") == 0) { cli_canal_2 = (double)(atof(_eq + 1)); has_canal_2 = 1; }
            if (strcmp(argv[oi], "canal_3") == 0) { cli_canal_3 = (double)(atof(_eq + 1)); has_canal_3 = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = multiplexorcanales_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_canal_0 = MULTIPLEXORCANALES_VR_CANAL_0;
    const fmu_vref_t vr_canal_1 = MULTIPLEXORCANALES_VR_CANAL_1;
    const fmu_vref_t vr_canal_seleccion = MULTIPLEXORCANALES_VR_CANAL_SELECCION;
    const fmu_vref_t vr_canal_2 = MULTIPLEXORCANALES_VR_CANAL_2;
    const fmu_vref_t vr_canal_3 = MULTIPLEXORCANALES_VR_CANAL_3;
    const fmu_vref_t vr_canal_activo = MULTIPLEXORCANALES_VR_CANAL_ACTIVO;
    const fmu_vref_t vr_canal_valido = MULTIPLEXORCANALES_VR_CANAL_VALIDO;
    const fmu_vref_t vr_salida = MULTIPLEXORCANALES_VR_SALIDA;

    SIM_PRINT("t,canal_0,canal_1,canal_seleccion,canal_2,canal_3,canal_activo,canal_valido,salida\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        MultiplexorCanales_Inputs in = {0};
        get_inputs(t, &in);
        if (has_canal_0) in.canal_0 = (double)cli_canal_0;
        if (ns_canal_0 > 0) {
            double best = (double)in.canal_0; double best_t = -1e300;
            for (int si = 0; si < ns_canal_0; si++)
                if (t >= sched_canal_0[si].t && sched_canal_0[si].t >= best_t)
                    { best = sched_canal_0[si].val; best_t = sched_canal_0[si].t; }
            in.canal_0 = (double)best;
        }
        if (has_canal_1) in.canal_1 = (double)cli_canal_1;
        if (ns_canal_1 > 0) {
            double best = (double)in.canal_1; double best_t = -1e300;
            for (int si = 0; si < ns_canal_1; si++)
                if (t >= sched_canal_1[si].t && sched_canal_1[si].t >= best_t)
                    { best = sched_canal_1[si].val; best_t = sched_canal_1[si].t; }
            in.canal_1 = (double)best;
        }
        if (has_canal_seleccion) in.canal_seleccion = (int)cli_canal_seleccion;
        if (ns_canal_seleccion > 0) {
            double best = (double)in.canal_seleccion; double best_t = -1e300;
            for (int si = 0; si < ns_canal_seleccion; si++)
                if (t >= sched_canal_seleccion[si].t && sched_canal_seleccion[si].t >= best_t)
                    { best = sched_canal_seleccion[si].val; best_t = sched_canal_seleccion[si].t; }
            in.canal_seleccion = (int)best;
        }
        if (has_canal_2) in.canal_2 = (double)cli_canal_2;
        if (ns_canal_2 > 0) {
            double best = (double)in.canal_2; double best_t = -1e300;
            for (int si = 0; si < ns_canal_2; si++)
                if (t >= sched_canal_2[si].t && sched_canal_2[si].t >= best_t)
                    { best = sched_canal_2[si].val; best_t = sched_canal_2[si].t; }
            in.canal_2 = (double)best;
        }
        if (has_canal_3) in.canal_3 = (double)cli_canal_3;
        if (ns_canal_3 > 0) {
            double best = (double)in.canal_3; double best_t = -1e300;
            for (int si = 0; si < ns_canal_3; si++)
                if (t >= sched_canal_3[si].t && sched_canal_3[si].t >= best_t)
                    { best = sched_canal_3[si].val; best_t = sched_canal_3[si].t; }
            in.canal_3 = (double)best;
        }
        fmu_real_t set_canal_0 = (fmu_real_t)in.canal_0;
        if (FMU_CALL(m, set_real, &vr_canal_0, 1, (const fmu_real_t *)&set_canal_0) > FMU_WARNING) {
            SIM_ERROR("Error: setting input canal_0 failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_canal_1 = (fmu_real_t)in.canal_1;
        if (FMU_CALL(m, set_real, &vr_canal_1, 1, (const fmu_real_t *)&set_canal_1) > FMU_WARNING) {
            SIM_ERROR("Error: setting input canal_1 failed\n");
            m->terminate(m); return 1;
        }
        fmu_int_t set_canal_seleccion = (fmu_int_t)in.canal_seleccion;
        if (FMU_CALL(m, set_integer, &vr_canal_seleccion, 1, (const fmu_int_t *)&set_canal_seleccion) > FMU_WARNING) {
            SIM_ERROR("Error: setting input canal_seleccion failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_canal_2 = (fmu_real_t)in.canal_2;
        if (FMU_CALL(m, set_real, &vr_canal_2, 1, (const fmu_real_t *)&set_canal_2) > FMU_WARNING) {
            SIM_ERROR("Error: setting input canal_2 failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_canal_3 = (fmu_real_t)in.canal_3;
        if (FMU_CALL(m, set_real, &vr_canal_3, 1, (const fmu_real_t *)&set_canal_3) > FMU_WARNING) {
            SIM_ERROR("Error: setting input canal_3 failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        MultiplexorCanales_Outputs out = {0};
        fmu_int_t got_canal_activo = 0;
        if (FMU_CALL(m, get_integer, &vr_canal_activo, 1, &got_canal_activo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output canal_activo failed\n");
            m->terminate(m); return 1;
        }
        out.canal_activo = (int)got_canal_activo;
        fmu_bool_t got_canal_valido = 0;
        if (FMU_CALL(m, get_boolean, &vr_canal_valido, 1, &got_canal_valido) > FMU_WARNING) {
            SIM_ERROR("Error: reading output canal_valido failed\n");
            m->terminate(m); return 1;
        }
        out.canal_valido = (int)got_canal_valido;
        fmu_real_t got_salida = 0.0;
        if (FMU_CALL(m, get_real, &vr_salida, 1, &got_salida) > FMU_WARNING) {
            SIM_ERROR("Error: reading output salida failed\n");
            m->terminate(m); return 1;
        }
        out.salida = (double)got_salida;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%d,%.10g,%.10g,%d,%d,%.10g\n", t, in.canal_0, in.canal_1, (int)in.canal_seleccion, in.canal_2, in.canal_3, (int)out.canal_activo, (int)out.canal_valido, out.salida);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
