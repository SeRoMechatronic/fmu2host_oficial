/**
 * @file main_cs.c -- generated typed Co-Simulation loop for Mi_Modelo_Nuevo.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mi_modelo_nuevo_api.h"
#include "mi_modelo_nuevo_adapter.h"

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
    double cli_flag_activo = 0.0; int has_flag_activo = 0;
    struct { double t; double val; } sched_flag_activo[MAX_SCHEDULE]; int ns_flag_activo = 0;
    double cli_entrada_principal = 0.0; int has_entrada_principal = 0;
    struct { double t; double val; } sched_entrada_principal[MAX_SCHEDULE]; int ns_entrada_principal = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "flag_activo") == 0 && ns_flag_activo < MAX_SCHEDULE) {
                sched_flag_activo[ns_flag_activo].t = at_t;
                sched_flag_activo[ns_flag_activo++].val = (double)((atoi(_eq + 1) != 0));
            }
            if (strcmp(argv[oi], "entrada_principal") == 0 && ns_entrada_principal < MAX_SCHEDULE) {
                sched_entrada_principal[ns_entrada_principal].t = at_t;
                sched_entrada_principal[ns_entrada_principal++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "flag_activo") == 0) { cli_flag_activo = (double)((atoi(_eq + 1) != 0)); has_flag_activo = 1; }
            if (strcmp(argv[oi], "entrada_principal") == 0) { cli_entrada_principal = (double)(atof(_eq + 1)); has_entrada_principal = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = mi_modelo_nuevo_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_flag_activo = MI_MODELO_NUEVO_VR_FLAG_ACTIVO;
    const fmu_vref_t vr_entrada_principal = MI_MODELO_NUEVO_VR_ENTRADA_PRINCIPAL;
    const fmu_vref_t vr_flag_salida = MI_MODELO_NUEVO_VR_FLAG_SALIDA;
    const fmu_vref_t vr_salida_filtrada = MI_MODELO_NUEVO_VR_SALIDA_FILTRADA;

    SIM_PRINT("t,flag_activo,entrada_principal,flag_salida,salida_filtrada\n");
    double t = 0.0;
    for (;;) {
        Mi_Modelo_Nuevo_Inputs in = {0};
        get_inputs(t, &in);
        if (has_flag_activo) in.flag_activo = (int)cli_flag_activo;
        if (ns_flag_activo > 0) {
            double best = (double)in.flag_activo; double best_t = -1e300;
            for (int si = 0; si < ns_flag_activo; si++)
                if (t >= sched_flag_activo[si].t && sched_flag_activo[si].t >= best_t)
                    { best = sched_flag_activo[si].val; best_t = sched_flag_activo[si].t; }
            in.flag_activo = (int)best;
        }
        if (has_entrada_principal) in.entrada_principal = (double)cli_entrada_principal;
        if (ns_entrada_principal > 0) {
            double best = (double)in.entrada_principal; double best_t = -1e300;
            for (int si = 0; si < ns_entrada_principal; si++)
                if (t >= sched_entrada_principal[si].t && sched_entrada_principal[si].t >= best_t)
                    { best = sched_entrada_principal[si].val; best_t = sched_entrada_principal[si].t; }
            in.entrada_principal = (double)best;
        }
        fmu_bool_t set_flag_activo = (fmu_bool_t)in.flag_activo;
        if (FMU_CALL(m, set_boolean, &vr_flag_activo, 1, (const fmu_bool_t *)&set_flag_activo) > FMU_WARNING) {
            SIM_ERROR("Error: setting input flag_activo failed\n");
            m->terminate(m); return 1;
        }
        fmu_real_t set_entrada_principal = (fmu_real_t)in.entrada_principal;
        if (FMU_CALL(m, set_real, &vr_entrada_principal, 1, (const fmu_real_t *)&set_entrada_principal) > FMU_WARNING) {
            SIM_ERROR("Error: setting input entrada_principal failed\n");
            m->terminate(m); return 1;
        }
        Mi_Modelo_Nuevo_Outputs out = {0};
        fmu_bool_t got_flag_salida = 0;
        if (FMU_CALL(m, get_boolean, &vr_flag_salida, 1, &got_flag_salida) > FMU_WARNING) {
            SIM_ERROR("Error: reading output flag_salida failed\n");
            m->terminate(m); return 1;
        }
        out.flag_salida = (int)got_flag_salida;
        fmu_real_t got_salida_filtrada = 0.0;
        if (FMU_CALL(m, get_real, &vr_salida_filtrada, 1, &got_salida_filtrada) > FMU_WARNING) {
            SIM_ERROR("Error: reading output salida_filtrada failed\n");
            m->terminate(m); return 1;
        }
        out.salida_filtrada = (double)got_salida_filtrada;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%d,%.10g,%d,%.10g\n", t, (int)in.flag_activo, in.entrada_principal, (int)out.flag_salida, out.salida_filtrada);
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
