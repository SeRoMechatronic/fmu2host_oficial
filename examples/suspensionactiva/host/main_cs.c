/**
 * @file main_cs.c -- generated typed Co-Simulation loop for SuspensionActiva.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "suspensionactiva_api.h"
#include "suspensionactiva_adapter.h"

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
    double cli_perfil_bache = 0.0; int has_perfil_bache = 0;
    struct { double t; double val; } sched_perfil_bache[MAX_SCHEDULE]; int ns_perfil_bache = 0;
    double cli_velocidad_vehiculo = 0.0; int has_velocidad_vehiculo = 0;
    struct { double t; double val; } sched_velocidad_vehiculo[MAX_SCHEDULE]; int ns_velocidad_vehiculo = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "perfil_bache") == 0 && ns_perfil_bache < MAX_SCHEDULE) {
                sched_perfil_bache[ns_perfil_bache].t = at_t;
                sched_perfil_bache[ns_perfil_bache++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "velocidad_vehiculo") == 0 && ns_velocidad_vehiculo < MAX_SCHEDULE) {
                sched_velocidad_vehiculo[ns_velocidad_vehiculo].t = at_t;
                sched_velocidad_vehiculo[ns_velocidad_vehiculo++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "perfil_bache") == 0) { cli_perfil_bache = (double)(atof(_eq + 1)); has_perfil_bache = 1; }
            if (strcmp(argv[oi], "velocidad_vehiculo") == 0) { cli_velocidad_vehiculo = (double)(atof(_eq + 1)); has_velocidad_vehiculo = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = suspensionactiva_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_perfil_bache = SUSPENSIONACTIVA_VR_PERFIL_BACHE;
    const fmu_vref_t vr_velocidad_vehiculo = SUSPENSIONACTIVA_VR_VELOCIDAD_VEHICULO;
    const fmu_vref_t vr_actuador_saturado = SUSPENSIONACTIVA_VR_ACTUADOR_SATURADO;
    const fmu_vref_t vr_bache_detectado = SUSPENSIONACTIVA_VR_BACHE_DETECTADO;
    const fmu_vref_t vr_modo_confort = SUSPENSIONACTIVA_VR_MODO_CONFORT;
    const fmu_vref_t vr_fuerza_actuador = SUSPENSIONACTIVA_VR_FUERZA_ACTUADOR;

    SIM_PRINT("t,perfil_bache,velocidad_vehiculo,actuador_saturado,bache_detectado,modo_confort,fuerza_actuador\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        SuspensionActiva_Inputs in = {0};
        get_inputs(t, &in);
        if (has_perfil_bache) in.perfil_bache = (double)cli_perfil_bache;
        if (ns_perfil_bache > 0) {
            double best = (double)in.perfil_bache; double best_t = -1e300;
            for (int si = 0; si < ns_perfil_bache; si++)
                if (t >= sched_perfil_bache[si].t && sched_perfil_bache[si].t >= best_t)
                    { best = sched_perfil_bache[si].val; best_t = sched_perfil_bache[si].t; }
            in.perfil_bache = (double)best;
        }
        if (has_velocidad_vehiculo) in.velocidad_vehiculo = (double)cli_velocidad_vehiculo;
        if (ns_velocidad_vehiculo > 0) {
            double best = (double)in.velocidad_vehiculo; double best_t = -1e300;
            for (int si = 0; si < ns_velocidad_vehiculo; si++)
                if (t >= sched_velocidad_vehiculo[si].t && sched_velocidad_vehiculo[si].t >= best_t)
                    { best = sched_velocidad_vehiculo[si].val; best_t = sched_velocidad_vehiculo[si].t; }
            in.velocidad_vehiculo = (double)best;
        }
        fmu_real_t set_perfil_bache = (fmu_real_t)in.perfil_bache;
        if (FMU_CALL(m, set_real, &vr_perfil_bache, 1, (const fmu_real_t *)&set_perfil_bache) > FMU_WARNING) {
            SIM_ERROR("Error: setting input perfil_bache failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_velocidad_vehiculo = (fmu_real_t)in.velocidad_vehiculo;
        if (FMU_CALL(m, set_real, &vr_velocidad_vehiculo, 1, (const fmu_real_t *)&set_velocidad_vehiculo) > FMU_WARNING) {
            SIM_ERROR("Error: setting input velocidad_vehiculo failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        SuspensionActiva_Outputs out = {0};
        fmu_bool_t got_actuador_saturado = 0;
        if (FMU_CALL(m, get_boolean, &vr_actuador_saturado, 1, &got_actuador_saturado) > FMU_WARNING) {
            SIM_ERROR("Error: reading output actuador_saturado failed\n");
            m->terminate(m); return 1;
        }
        out.actuador_saturado = (int)got_actuador_saturado;
        fmu_bool_t got_bache_detectado = 0;
        if (FMU_CALL(m, get_boolean, &vr_bache_detectado, 1, &got_bache_detectado) > FMU_WARNING) {
            SIM_ERROR("Error: reading output bache_detectado failed\n");
            m->terminate(m); return 1;
        }
        out.bache_detectado = (int)got_bache_detectado;
        fmu_bool_t got_modo_confort = 0;
        if (FMU_CALL(m, get_boolean, &vr_modo_confort, 1, &got_modo_confort) > FMU_WARNING) {
            SIM_ERROR("Error: reading output modo_confort failed\n");
            m->terminate(m); return 1;
        }
        out.modo_confort = (int)got_modo_confort;
        fmu_real_t got_fuerza_actuador = 0.0;
        if (FMU_CALL(m, get_real, &vr_fuerza_actuador, 1, &got_fuerza_actuador) > FMU_WARNING) {
            SIM_ERROR("Error: reading output fuerza_actuador failed\n");
            m->terminate(m); return 1;
        }
        out.fuerza_actuador = (double)got_fuerza_actuador;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.perfil_bache, in.velocidad_vehiculo, (int)out.actuador_saturado, (int)out.bache_detectado, (int)out.modo_confort, out.fuerza_actuador);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
