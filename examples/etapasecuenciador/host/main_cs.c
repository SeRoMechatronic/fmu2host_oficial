/**
 * @file main_cs.c -- generated typed Co-Simulation loop for EtapaSecuenciador.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "etapasecuenciador_api.h"
#include "etapasecuenciador_adapter.h"

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
    double cli_sensor_confirmacion = 0.0; int has_sensor_confirmacion = 0;
    struct { double t; double val; } sched_sensor_confirmacion[MAX_SCHEDULE]; int ns_sensor_confirmacion = 0;
    double cli_arrancar = 0.0; int has_arrancar = 0;
    struct { double t; double val; } sched_arrancar[MAX_SCHEDULE]; int ns_arrancar = 0;
    double cli_parar = 0.0; int has_parar = 0;
    struct { double t; double val; } sched_parar[MAX_SCHEDULE]; int ns_parar = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "sensor_confirmacion") == 0 && ns_sensor_confirmacion < MAX_SCHEDULE) {
                sched_sensor_confirmacion[ns_sensor_confirmacion].t = at_t;
                sched_sensor_confirmacion[ns_sensor_confirmacion++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "arrancar") == 0 && ns_arrancar < MAX_SCHEDULE) {
                sched_arrancar[ns_arrancar].t = at_t;
                sched_arrancar[ns_arrancar++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "parar") == 0 && ns_parar < MAX_SCHEDULE) {
                sched_parar[ns_parar].t = at_t;
                sched_parar[ns_parar++].val = (double)((atoi(_eq + 1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "sensor_confirmacion") == 0) { cli_sensor_confirmacion = (double)(atof(_eq + 1)); has_sensor_confirmacion = 1; }
            if (strcmp(argv[oi], "arrancar") == 0) { cli_arrancar = (double)((atoi(_eq + 1) != 0)); has_arrancar = 1; }
            if (strcmp(argv[oi], "parar") == 0) { cli_parar = (double)((atoi(_eq + 1) != 0)); has_parar = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = etapasecuenciador_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_sensor_confirmacion = ETAPASECUENCIADOR_VR_SENSOR_CONFIRMACION;
    const fmu_vref_t vr_arrancar = ETAPASECUENCIADOR_VR_ARRANCAR;
    const fmu_vref_t vr_parar = ETAPASECUENCIADOR_VR_PARAR;
    const fmu_vref_t vr_progreso_etapa = ETAPASECUENCIADOR_VR_PROGRESO_ETAPA;
    const fmu_vref_t vr_etapa_actual = ETAPASECUENCIADOR_VR_ETAPA_ACTUAL;
    const fmu_vref_t vr_etapa_previa = ETAPASECUENCIADOR_VR_ETAPA_PREVIA;
    const fmu_vref_t vr_secuencia_completa = ETAPASECUENCIADOR_VR_SECUENCIA_COMPLETA;

    SIM_PRINT("t,sensor_confirmacion,arrancar,parar,progreso_etapa,etapa_actual,etapa_previa,secuencia_completa\n");
    double t = 0.0;
    for (;;) {
        EtapaSecuenciador_Inputs in = {0};
        get_inputs(t, &in);
        if (has_sensor_confirmacion) in.sensor_confirmacion = (double)cli_sensor_confirmacion;
        if (ns_sensor_confirmacion > 0) {
            double best = (double)in.sensor_confirmacion; double best_t = -1e300;
            for (int si = 0; si < ns_sensor_confirmacion; si++)
                if (t >= sched_sensor_confirmacion[si].t && sched_sensor_confirmacion[si].t >= best_t)
                    { best = sched_sensor_confirmacion[si].val; best_t = sched_sensor_confirmacion[si].t; }
            in.sensor_confirmacion = (double)best;
        }
        if (has_arrancar) in.arrancar = (int)cli_arrancar;
        if (ns_arrancar > 0) {
            double best = (double)in.arrancar; double best_t = -1e300;
            for (int si = 0; si < ns_arrancar; si++)
                if (t >= sched_arrancar[si].t && sched_arrancar[si].t >= best_t)
                    { best = sched_arrancar[si].val; best_t = sched_arrancar[si].t; }
            in.arrancar = (int)best;
        }
        if (has_parar) in.parar = (int)cli_parar;
        if (ns_parar > 0) {
            double best = (double)in.parar; double best_t = -1e300;
            for (int si = 0; si < ns_parar; si++)
                if (t >= sched_parar[si].t && sched_parar[si].t >= best_t)
                    { best = sched_parar[si].val; best_t = sched_parar[si].t; }
            in.parar = (int)best;
        }
        fmu_real_t set_sensor_confirmacion = (fmu_real_t)in.sensor_confirmacion;
        if (FMU_CALL(m, set_real, &vr_sensor_confirmacion, 1, (const fmu_real_t *)&set_sensor_confirmacion) > FMU_WARNING) {
            SIM_ERROR("Error: setting input sensor_confirmacion failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_arrancar = (fmu_bool_t)in.arrancar;
        if (FMU_CALL(m, set_boolean, &vr_arrancar, 1, (const fmu_bool_t *)&set_arrancar) > FMU_WARNING) {
            SIM_ERROR("Error: setting input arrancar failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_parar = (fmu_bool_t)in.parar;
        if (FMU_CALL(m, set_boolean, &vr_parar, 1, (const fmu_bool_t *)&set_parar) > FMU_WARNING) {
            SIM_ERROR("Error: setting input parar failed\n");
            m->terminate(m); return 1;
        }
        EtapaSecuenciador_Outputs out = {0};
        fmu_real_t got_progreso_etapa = 0.0;
        if (FMU_CALL(m, get_real, &vr_progreso_etapa, 1, &got_progreso_etapa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output progreso_etapa failed\n");
            m->terminate(m); return 1;
        }
        out.progreso_etapa = (double)got_progreso_etapa;
        fmu_int_t got_etapa_actual = 0;
        if (FMU_CALL(m, get_integer, &vr_etapa_actual, 1, &got_etapa_actual) > FMU_WARNING) {
            SIM_ERROR("Error: reading output etapa_actual failed\n");
            m->terminate(m); return 1;
        }
        out.etapa_actual = (int)got_etapa_actual;
        fmu_int_t got_etapa_previa = 0;
        if (FMU_CALL(m, get_integer, &vr_etapa_previa, 1, &got_etapa_previa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output etapa_previa failed\n");
            m->terminate(m); return 1;
        }
        out.etapa_previa = (int)got_etapa_previa;
        fmu_bool_t got_secuencia_completa = 0;
        if (FMU_CALL(m, get_boolean, &vr_secuencia_completa, 1, &got_secuencia_completa) > FMU_WARNING) {
            SIM_ERROR("Error: reading output secuencia_completa failed\n");
            m->terminate(m); return 1;
        }
        out.secuencia_completa = (int)got_secuencia_completa;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%d,%.10g,%d,%d,%d\n", t, in.sensor_confirmacion, (int)in.arrancar, (int)in.parar, out.progreso_etapa, (int)out.etapa_actual, (int)out.etapa_previa, (int)out.secuencia_completa);
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
