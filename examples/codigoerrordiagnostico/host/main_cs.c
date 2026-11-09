/**
 * @file main_cs.c -- generated typed Co-Simulation loop for CodigoErrorDiagnostico.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "codigoerrordiagnostico_api.h"
#include "codigoerrordiagnostico_adapter.h"

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
    double cli_temperatura = 0.0; int has_temperatura = 0;
    struct { double t; double val; } sched_temperatura[MAX_SCHEDULE]; int ns_temperatura = 0;
    double cli_tension = 0.0; int has_tension = 0;
    struct { double t; double val; } sched_tension[MAX_SCHEDULE]; int ns_tension = 0;
    double cli_vibracion = 0.0; int has_vibracion = 0;
    struct { double t; double val; } sched_vibracion[MAX_SCHEDULE]; int ns_vibracion = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "temperatura") == 0 && ns_temperatura < MAX_SCHEDULE) {
                sched_temperatura[ns_temperatura].t = at_t;
                sched_temperatura[ns_temperatura++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "tension") == 0 && ns_tension < MAX_SCHEDULE) {
                sched_tension[ns_tension].t = at_t;
                sched_tension[ns_tension++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "vibracion") == 0 && ns_vibracion < MAX_SCHEDULE) {
                sched_vibracion[ns_vibracion].t = at_t;
                sched_vibracion[ns_vibracion++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "temperatura") == 0) { cli_temperatura = (double)(atof(_eq + 1)); has_temperatura = 1; }
            if (strcmp(argv[oi], "tension") == 0) { cli_tension = (double)(atof(_eq + 1)); has_tension = 1; }
            if (strcmp(argv[oi], "vibracion") == 0) { cli_vibracion = (double)(atof(_eq + 1)); has_vibracion = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = codigoerrordiagnostico_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_temperatura = CODIGOERRORDIAGNOSTICO_VR_TEMPERATURA;
    const fmu_vref_t vr_tension = CODIGOERRORDIAGNOSTICO_VR_TENSION;
    const fmu_vref_t vr_vibracion = CODIGOERRORDIAGNOSTICO_VR_VIBRACION;
    const fmu_vref_t vr_factor_reduccion = CODIGOERRORDIAGNOSTICO_VR_FACTOR_REDUCCION;
    const fmu_vref_t vr_codigo_error = CODIGOERRORDIAGNOSTICO_VR_CODIGO_ERROR;
    const fmu_vref_t vr_parada_emergencia = CODIGOERRORDIAGNOSTICO_VR_PARADA_EMERGENCIA;
    const fmu_vref_t vr_nivel_prioridad = CODIGOERRORDIAGNOSTICO_VR_NIVEL_PRIORIDAD;

    SIM_PRINT("t,temperatura,tension,vibracion,factor_reduccion,codigo_error,parada_emergencia,nivel_prioridad\n");
    double t = 0.0;
    for (;;) {
        CodigoErrorDiagnostico_Inputs in = {0};
        get_inputs(t, &in);
        if (has_temperatura) in.temperatura = (double)cli_temperatura;
        if (ns_temperatura > 0) {
            double best = (double)in.temperatura; double best_t = -1e300;
            for (int si = 0; si < ns_temperatura; si++)
                if (t >= sched_temperatura[si].t && sched_temperatura[si].t >= best_t)
                    { best = sched_temperatura[si].val; best_t = sched_temperatura[si].t; }
            in.temperatura = (double)best;
        }
        if (has_tension) in.tension = (double)cli_tension;
        if (ns_tension > 0) {
            double best = (double)in.tension; double best_t = -1e300;
            for (int si = 0; si < ns_tension; si++)
                if (t >= sched_tension[si].t && sched_tension[si].t >= best_t)
                    { best = sched_tension[si].val; best_t = sched_tension[si].t; }
            in.tension = (double)best;
        }
        if (has_vibracion) in.vibracion = (double)cli_vibracion;
        if (ns_vibracion > 0) {
            double best = (double)in.vibracion; double best_t = -1e300;
            for (int si = 0; si < ns_vibracion; si++)
                if (t >= sched_vibracion[si].t && sched_vibracion[si].t >= best_t)
                    { best = sched_vibracion[si].val; best_t = sched_vibracion[si].t; }
            in.vibracion = (double)best;
        }
        fmu_real_t set_temperatura = (fmu_real_t)in.temperatura;
        if (FMU_CALL(m, set_real, &vr_temperatura, 1, (const fmu_real_t *)&set_temperatura) > FMU_WARNING) {
            SIM_ERROR("Error: setting input temperatura failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_tension = (fmu_real_t)in.tension;
        if (FMU_CALL(m, set_real, &vr_tension, 1, (const fmu_real_t *)&set_tension) > FMU_WARNING) {
            SIM_ERROR("Error: setting input tension failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_vibracion = (fmu_real_t)in.vibracion;
        if (FMU_CALL(m, set_real, &vr_vibracion, 1, (const fmu_real_t *)&set_vibracion) > FMU_WARNING) {
            SIM_ERROR("Error: setting input vibracion failed\n");
            m->terminate(m); return 1;
        }
        CodigoErrorDiagnostico_Outputs out = {0};
        fmu_real_t got_factor_reduccion = 0.0;
        if (FMU_CALL(m, get_real, &vr_factor_reduccion, 1, &got_factor_reduccion) > FMU_WARNING) {
            SIM_ERROR("Error: reading output factor_reduccion failed\n");
            m->terminate(m); return 1;
        }
        out.factor_reduccion = (double)got_factor_reduccion;
        fmu_int_t got_codigo_error = 0;
        if (FMU_CALL(m, get_integer, &vr_codigo_error, 1, &got_codigo_error) > FMU_WARNING) {
            SIM_ERROR("Error: reading output codigo_error failed\n");
            m->terminate(m); return 1;
        }
        out.codigo_error = (int)got_codigo_error;
        fmu_bool_t got_parada_emergencia = 0;
        if (FMU_CALL(m, get_boolean, &vr_parada_emergencia, 1, &got_parada_emergencia) > FMU_WARNING) {
            SIM_ERROR("Error: reading output parada_emergencia failed\n");
            m->terminate(m); return 1;
        }
        out.parada_emergencia = (int)got_parada_emergencia;
        fmu_int_t got_nivel_prioridad = 0;
        if (FMU_CALL(m, get_integer, &vr_nivel_prioridad, 1, &got_nivel_prioridad) > FMU_WARNING) {
            SIM_ERROR("Error: reading output nivel_prioridad failed\n");
            m->terminate(m); return 1;
        }
        out.nivel_prioridad = (int)got_nivel_prioridad;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%.10g,%.10g,%d,%d,%d\n", t, in.temperatura, in.tension, in.vibracion, out.factor_reduccion, (int)out.codigo_error, (int)out.parada_emergencia, (int)out.nivel_prioridad);
        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
