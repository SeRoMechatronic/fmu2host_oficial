/**
 * @file main_cs.c -- generated typed Co-Simulation loop for NivelDeposito.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "niveldeposito_api.h"
#include "niveldeposito_adapter.h"

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
    double cli_valvula_manual = 0.0; int has_valvula_manual = 0;
    struct { double t; double val; } sched_valvula_manual[MAX_SCHEDULE]; int ns_valvula_manual = 0;
    double cli_sensor_nivel = 0.0; int has_sensor_nivel = 0;
    struct { double t; double val; } sched_sensor_nivel[MAX_SCHEDULE]; int ns_sensor_nivel = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "valvula_manual") == 0 && ns_valvula_manual < MAX_SCHEDULE) {
                sched_valvula_manual[ns_valvula_manual].t = at_t;
                sched_valvula_manual[ns_valvula_manual++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "sensor_nivel") == 0 && ns_sensor_nivel < MAX_SCHEDULE) {
                sched_sensor_nivel[ns_sensor_nivel].t = at_t;
                sched_sensor_nivel[ns_sensor_nivel++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "valvula_manual") == 0) { cli_valvula_manual = (double)((atoi(_eq + 1) != 0)); has_valvula_manual = 1; }
            if (strcmp(argv[oi], "sensor_nivel") == 0) { cli_sensor_nivel = (double)(atof(_eq + 1)); has_sensor_nivel = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = niveldeposito_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_valvula_manual = NIVELDEPOSITO_VR_VALVULA_MANUAL;
    const fmu_vref_t vr_sensor_nivel = NIVELDEPOSITO_VR_SENSOR_NIVEL;
    const fmu_vref_t vr_alarma_maximo = NIVELDEPOSITO_VR_ALARMA_MAXIMO;
    const fmu_vref_t vr_alarma_minimo = NIVELDEPOSITO_VR_ALARMA_MINIMO;
    const fmu_vref_t vr_bomba_activa = NIVELDEPOSITO_VR_BOMBA_ACTIVA;
    const fmu_vref_t vr_bomba = NIVELDEPOSITO_VR_BOMBA;

    SIM_PRINT("t,valvula_manual,sensor_nivel,alarma_maximo,alarma_minimo,bomba_activa,bomba\n");
    double t = 0.0;
    for (;;) {
        NivelDeposito_Inputs in = {0};
        get_inputs(t, &in);
        if (has_valvula_manual) in.valvula_manual = (int)cli_valvula_manual;
        if (ns_valvula_manual > 0) {
            double best = (double)in.valvula_manual; double best_t = -1e300;
            for (int si = 0; si < ns_valvula_manual; si++)
                if (t >= sched_valvula_manual[si].t && sched_valvula_manual[si].t >= best_t)
                    { best = sched_valvula_manual[si].val; best_t = sched_valvula_manual[si].t; }
            in.valvula_manual = (int)best;
        }
        if (has_sensor_nivel) in.sensor_nivel = (double)cli_sensor_nivel;
        if (ns_sensor_nivel > 0) {
            double best = (double)in.sensor_nivel; double best_t = -1e300;
            for (int si = 0; si < ns_sensor_nivel; si++)
                if (t >= sched_sensor_nivel[si].t && sched_sensor_nivel[si].t >= best_t)
                    { best = sched_sensor_nivel[si].val; best_t = sched_sensor_nivel[si].t; }
            in.sensor_nivel = (double)best;
        }
        fmu_bool_t set_valvula_manual = (fmu_bool_t)in.valvula_manual;
        if (FMU_CALL(m, set_boolean, &vr_valvula_manual, 1, (const fmu_bool_t *)&set_valvula_manual) > FMU_WARNING) {
            SIM_ERROR("Error: setting input valvula_manual failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_sensor_nivel = (fmu_real_t)in.sensor_nivel;
        if (FMU_CALL(m, set_real, &vr_sensor_nivel, 1, (const fmu_real_t *)&set_sensor_nivel) > FMU_WARNING) {
            SIM_ERROR("Error: setting input sensor_nivel failed\n");
            m->terminate(m); return 1;
        }
        NivelDeposito_Outputs out = {0};
        fmu_bool_t got_alarma_maximo = 0;
        if (FMU_CALL(m, get_boolean, &vr_alarma_maximo, 1, &got_alarma_maximo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output alarma_maximo failed\n");
            m->terminate(m); return 1;
        }
        out.alarma_maximo = (int)got_alarma_maximo;
        fmu_bool_t got_alarma_minimo = 0;
        if (FMU_CALL(m, get_boolean, &vr_alarma_minimo, 1, &got_alarma_minimo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output alarma_minimo failed\n");
            m->terminate(m); return 1;
        }
        out.alarma_minimo = (int)got_alarma_minimo;
        fmu_bool_t got_bomba_activa = 0;
        if (FMU_CALL(m, get_boolean, &vr_bomba_activa, 1, &got_bomba_activa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output bomba_activa failed\n");
            m->terminate(m); return 1;
        }
        out.bomba_activa = (int)got_bomba_activa;
        fmu_real_t got_bomba = 0.0;
        if (FMU_CALL(m, get_real, &vr_bomba, 1, &got_bomba) > FMU_WARNING) {
            SIM_ERROR("Error: reading output bomba failed\n");
            m->terminate(m); return 1;
        }
        out.bomba = (double)got_bomba;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.valvula_manual, in.sensor_nivel, (int)out.alarma_maximo, (int)out.alarma_minimo, (int)out.bomba_activa, out.bomba);
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
