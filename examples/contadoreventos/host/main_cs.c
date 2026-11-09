/**
 * @file main_cs.c -- generated typed Co-Simulation loop for ContadorEventos.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "contadoreventos_api.h"
#include "contadoreventos_adapter.h"

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
    double cli_evento = 0.0; int has_evento = 0;
    struct { double t; double val; } sched_evento[MAX_SCHEDULE]; int ns_evento = 0;
    double cli_reset = 0.0; int has_reset = 0;
    struct { double t; double val; } sched_reset[MAX_SCHEDULE]; int ns_reset = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "evento") == 0 && ns_evento < MAX_SCHEDULE) {
                sched_evento[ns_evento].t = at_t;
                sched_evento[ns_evento++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "reset") == 0 && ns_reset < MAX_SCHEDULE) {
                sched_reset[ns_reset].t = at_t;
                sched_reset[ns_reset++].val = (double)((atoi(_eq + 1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "evento") == 0) { cli_evento = (double)((atoi(_eq + 1) != 0)); has_evento = 1; }
            if (strcmp(argv[oi], "reset") == 0) { cli_reset = (double)((atoi(_eq + 1) != 0)); has_reset = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = contadoreventos_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_evento = CONTADOREVENTOS_VR_EVENTO;
    const fmu_vref_t vr_reset = CONTADOREVENTOS_VR_RESET;
    const fmu_vref_t vr_cuenta = CONTADOREVENTOS_VR_CUENTA;
    const fmu_vref_t vr_decenas = CONTADOREVENTOS_VR_DECENAS;
    const fmu_vref_t vr_desbordamiento = CONTADOREVENTOS_VR_DESBORDAMIENTO;
    const fmu_vref_t vr_unidades = CONTADOREVENTOS_VR_UNIDADES;

    SIM_PRINT("t,evento,reset,cuenta,decenas,desbordamiento,unidades\n");
    double t = 0.0;
    for (;;) {
        ContadorEventos_Inputs in = {0};
        get_inputs(t, &in);
        if (has_evento) in.evento = (int)cli_evento;
        if (ns_evento > 0) {
            double best = (double)in.evento; double best_t = -1e300;
            for (int si = 0; si < ns_evento; si++)
                if (t >= sched_evento[si].t && sched_evento[si].t >= best_t)
                    { best = sched_evento[si].val; best_t = sched_evento[si].t; }
            in.evento = (int)best;
        }
        if (has_reset) in.reset = (int)cli_reset;
        if (ns_reset > 0) {
            double best = (double)in.reset; double best_t = -1e300;
            for (int si = 0; si < ns_reset; si++)
                if (t >= sched_reset[si].t && sched_reset[si].t >= best_t)
                    { best = sched_reset[si].val; best_t = sched_reset[si].t; }
            in.reset = (int)best;
        }
        fmu_bool_t set_evento = (fmu_bool_t)in.evento;
        if (FMU_CALL(m, set_boolean, &vr_evento, 1, (const fmu_bool_t *)&set_evento) > FMU_WARNING) {
            SIM_ERROR("Error: setting input evento failed\n");
            m->terminate(m); return 1;
        }
        fmu_bool_t set_reset = (fmu_bool_t)in.reset;
        if (FMU_CALL(m, set_boolean, &vr_reset, 1, (const fmu_bool_t *)&set_reset) > FMU_WARNING) {
            SIM_ERROR("Error: setting input reset failed\n");
            m->terminate(m); return 1;
        }
        ContadorEventos_Outputs out = {0};
        fmu_int_t got_cuenta = 0;
        if (FMU_CALL(m, get_integer, &vr_cuenta, 1, &got_cuenta) > FMU_WARNING) {
            SIM_ERROR("Error: reading output cuenta failed\n");
            m->terminate(m); return 1;
        }
        out.cuenta = (int)got_cuenta;
        fmu_int_t got_decenas = 0;
        if (FMU_CALL(m, get_integer, &vr_decenas, 1, &got_decenas) > FMU_WARNING) {
            SIM_ERROR("Error: reading output decenas failed\n");
            m->terminate(m); return 1;
        }
        out.decenas = (int)got_decenas;
        fmu_bool_t got_desbordamiento = 0;
        if (FMU_CALL(m, get_boolean, &vr_desbordamiento, 1, &got_desbordamiento) > FMU_WARNING) {
            SIM_ERROR("Error: reading output desbordamiento failed\n");
            m->terminate(m); return 1;
        }
        out.desbordamiento = (int)got_desbordamiento;
        fmu_int_t got_unidades = 0;
        if (FMU_CALL(m, get_integer, &vr_unidades, 1, &got_unidades) > FMU_WARNING) {
            SIM_ERROR("Error: reading output unidades failed\n");
            m->terminate(m); return 1;
        }
        out.unidades = (int)got_unidades;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%d,%d,%d,%d,%d\n", t, (int)in.evento, (int)in.reset, (int)out.cuenta, (int)out.decenas, (int)out.desbordamiento, (int)out.unidades);
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
