/**
 * @file main_cs.c -- generated typed Co-Simulation loop for ReguladorBateria.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "reguladorbateria_api.h"
#include "reguladorbateria_adapter.h"

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
    double cli_carga_conectada = 0.0; int has_carga_conectada = 0;
    struct { double t; double val; } sched_carga_conectada[MAX_SCHEDULE]; int ns_carga_conectada = 0;
    double cli_tension_bateria = 0.0; int has_tension_bateria = 0;
    struct { double t; double val; } sched_tension_bateria[MAX_SCHEDULE]; int ns_tension_bateria = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "carga_conectada") == 0 && ns_carga_conectada < MAX_SCHEDULE) {
                sched_carga_conectada[ns_carga_conectada].t = at_t;
                sched_carga_conectada[ns_carga_conectada++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "tension_bateria") == 0 && ns_tension_bateria < MAX_SCHEDULE) {
                sched_tension_bateria[ns_tension_bateria].t = at_t;
                sched_tension_bateria[ns_tension_bateria++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "carga_conectada") == 0) { cli_carga_conectada = (double)((atoi(_eq + 1) != 0)); has_carga_conectada = 1; }
            if (strcmp(argv[oi], "tension_bateria") == 0) { cli_tension_bateria = (double)(atof(_eq + 1)); has_tension_bateria = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = reguladorbateria_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_carga_conectada = REGULADORBATERIA_VR_CARGA_CONECTADA;
    const fmu_vref_t vr_tension_bateria = REGULADORBATERIA_VR_TENSION_BATERIA;
    const fmu_vref_t vr_carga_completa = REGULADORBATERIA_VR_CARGA_COMPLETA;
    const fmu_vref_t vr_cargando = REGULADORBATERIA_VR_CARGANDO;
    const fmu_vref_t vr_fallo_sobretension = REGULADORBATERIA_VR_FALLO_SOBRETENSION;
    const fmu_vref_t vr_corriente_carga = REGULADORBATERIA_VR_CORRIENTE_CARGA;

    SIM_PRINT("t,carga_conectada,tension_bateria,carga_completa,cargando,fallo_sobretension,corriente_carga\n");
    double t = 0.0;
    for (;;) {
        ReguladorBateria_Inputs in = {0};
        get_inputs(t, &in);
        if (has_carga_conectada) in.carga_conectada = (int)cli_carga_conectada;
        if (ns_carga_conectada > 0) {
            double best = (double)in.carga_conectada; double best_t = -1e300;
            for (int si = 0; si < ns_carga_conectada; si++)
                if (t >= sched_carga_conectada[si].t && sched_carga_conectada[si].t >= best_t)
                    { best = sched_carga_conectada[si].val; best_t = sched_carga_conectada[si].t; }
            in.carga_conectada = (int)best;
        }
        if (has_tension_bateria) in.tension_bateria = (double)cli_tension_bateria;
        if (ns_tension_bateria > 0) {
            double best = (double)in.tension_bateria; double best_t = -1e300;
            for (int si = 0; si < ns_tension_bateria; si++)
                if (t >= sched_tension_bateria[si].t && sched_tension_bateria[si].t >= best_t)
                    { best = sched_tension_bateria[si].val; best_t = sched_tension_bateria[si].t; }
            in.tension_bateria = (double)best;
        }
        fmu_bool_t set_carga_conectada = (fmu_bool_t)in.carga_conectada;
        if (FMU_CALL(m, set_boolean, &vr_carga_conectada, 1, (const fmu_bool_t *)&set_carga_conectada) > FMU_WARNING) {
            SIM_ERROR("Error: setting input carga_conectada failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_tension_bateria = (fmu_real_t)in.tension_bateria;
        if (FMU_CALL(m, set_real, &vr_tension_bateria, 1, (const fmu_real_t *)&set_tension_bateria) > FMU_WARNING) {
            SIM_ERROR("Error: setting input tension_bateria failed\n");
            m->terminate(m); return 1;
        }
        ReguladorBateria_Outputs out = {0};
        fmu_bool_t got_carga_completa = 0;
        if (FMU_CALL(m, get_boolean, &vr_carga_completa, 1, &got_carga_completa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output carga_completa failed\n");
            m->terminate(m); return 1;
        }
        out.carga_completa = (int)got_carga_completa;
        fmu_bool_t got_cargando = 0;
        if (FMU_CALL(m, get_boolean, &vr_cargando, 1, &got_cargando) > FMU_WARNING) {
            SIM_ERROR("Error: reading output cargando failed\n");
            m->terminate(m); return 1;
        }
        out.cargando = (int)got_cargando;
        fmu_bool_t got_fallo_sobretension = 0;
        if (FMU_CALL(m, get_boolean, &vr_fallo_sobretension, 1, &got_fallo_sobretension) > FMU_WARNING) {
            SIM_ERROR("Error: reading output fallo_sobretension failed\n");
            m->terminate(m); return 1;
        }
        out.fallo_sobretension = (int)got_fallo_sobretension;
        fmu_real_t got_corriente_carga = 0.0;
        if (FMU_CALL(m, get_real, &vr_corriente_carga, 1, &got_corriente_carga) > FMU_WARNING) {
            SIM_ERROR("Error: reading output corriente_carga failed\n");
            m->terminate(m); return 1;
        }
        out.corriente_carga = (double)got_corriente_carga;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%d,%d,%d,%.10g\n", t, (int)in.carga_conectada, in.tension_bateria, (int)out.carga_completa, (int)out.cargando, (int)out.fallo_sobretension, out.corriente_carga);
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
