/**
 * @file main_cs.c -- generated typed Co-Simulation loop for CTPID.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ctpid_api.h"
#include "ctpid_adapter.h"

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
    double cli_consigna = 0.0; int has_consigna = 0;
    struct { double t; double val; } sched_consigna[MAX_SCHEDULE]; int ns_consigna = 0;
    double cli_temperatura = 0.0; int has_temperatura = 0;
    struct { double t; double val; } sched_temperatura[MAX_SCHEDULE]; int ns_temperatura = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "consigna") == 0 && ns_consigna < MAX_SCHEDULE) {
                sched_consigna[ns_consigna].t = at_t;
                sched_consigna[ns_consigna++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "temperatura") == 0 && ns_temperatura < MAX_SCHEDULE) {
                sched_temperatura[ns_temperatura].t = at_t;
                sched_temperatura[ns_temperatura++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "consigna") == 0) { cli_consigna = (double)(atof(_eq + 1)); has_consigna = 1; }
            if (strcmp(argv[oi], "temperatura") == 0) { cli_temperatura = (double)(atof(_eq + 1)); has_temperatura = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = ctpid_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_consigna = CTPID_VR_CONSIGNA;
    const fmu_vref_t vr_temperatura = CTPID_VR_TEMPERATURA;
    const fmu_vref_t vr_ledalcanzado = CTPID_VR_LEDALCANZADO;
    const fmu_vref_t vr_ledpordebajo = CTPID_VR_LEDPORDEBAJO;
    const fmu_vref_t vr_ledporencima = CTPID_VR_LEDPORENCIMA;
    const fmu_vref_t vr_ventilador = CTPID_VR_VENTILADOR;

    SIM_PRINT("t,consigna,temperatura,ledAlcanzado,ledPorDebajo,ledPorEncima,ventilador\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        CTPID_Inputs in = {0};
        get_inputs(t, &in);
        if (has_consigna) in.consigna = (double)cli_consigna;
        if (ns_consigna > 0) {
            double best = (double)in.consigna; double best_t = -1e300;
            for (int si = 0; si < ns_consigna; si++)
                if (t >= sched_consigna[si].t && sched_consigna[si].t >= best_t)
                    { best = sched_consigna[si].val; best_t = sched_consigna[si].t; }
            in.consigna = (double)best;
        }
        if (has_temperatura) in.temperatura = (double)cli_temperatura;
        if (ns_temperatura > 0) {
            double best = (double)in.temperatura; double best_t = -1e300;
            for (int si = 0; si < ns_temperatura; si++)
                if (t >= sched_temperatura[si].t && sched_temperatura[si].t >= best_t)
                    { best = sched_temperatura[si].val; best_t = sched_temperatura[si].t; }
            in.temperatura = (double)best;
        }
        fmu_real_t set_consigna = (fmu_real_t)in.consigna;
        if (FMU_CALL(m, set_real, &vr_consigna, 1, (const fmu_real_t *)&set_consigna) > FMU_WARNING) {
            SIM_ERROR("Error: setting input consigna failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_temperatura = (fmu_real_t)in.temperatura;
        if (FMU_CALL(m, set_real, &vr_temperatura, 1, (const fmu_real_t *)&set_temperatura) > FMU_WARNING) {
            SIM_ERROR("Error: setting input temperatura failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        CTPID_Outputs out = {0};
        fmu_bool_t got_ledalcanzado = 0;
        if (FMU_CALL(m, get_boolean, &vr_ledalcanzado, 1, &got_ledalcanzado) > FMU_WARNING) {
            SIM_ERROR("Error: reading output ledAlcanzado failed\n");
            m->terminate(m); return 1;
        }
        out.ledalcanzado = (int)got_ledalcanzado;
        fmu_bool_t got_ledpordebajo = 0;
        if (FMU_CALL(m, get_boolean, &vr_ledpordebajo, 1, &got_ledpordebajo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output ledPorDebajo failed\n");
            m->terminate(m); return 1;
        }
        out.ledpordebajo = (int)got_ledpordebajo;
        fmu_bool_t got_ledporencima = 0;
        if (FMU_CALL(m, get_boolean, &vr_ledporencima, 1, &got_ledporencima) > FMU_WARNING) {
            SIM_ERROR("Error: reading output ledPorEncima failed\n");
            m->terminate(m); return 1;
        }
        out.ledporencima = (int)got_ledporencima;
        fmu_real_t got_ventilador = 0.0;
        if (FMU_CALL(m, get_real, &vr_ventilador, 1, &got_ventilador) > FMU_WARNING) {
            SIM_ERROR("Error: reading output ventilador failed\n");
            m->terminate(m); return 1;
        }
        out.ventilador = (double)got_ventilador;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.consigna, in.temperatura, (int)out.ledalcanzado, (int)out.ledpordebajo, (int)out.ledporencima, out.ventilador);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
