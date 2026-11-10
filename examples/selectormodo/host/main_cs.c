/**
 * @file main_cs.c -- generated typed Co-Simulation loop for SelectorModo.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "selectormodo_api.h"
#include "selectormodo_adapter.h"

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
    double cli_consigna_manual = 0.0; int has_consigna_manual = 0;
    struct { double t; double val; } sched_consigna_manual[MAX_SCHEDULE]; int ns_consigna_manual = 0;
    double cli_modo_operacion = 0.0; int has_modo_operacion = 0;
    struct { double t; double val; } sched_modo_operacion[MAX_SCHEDULE]; int ns_modo_operacion = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "consigna_manual") == 0 && ns_consigna_manual < MAX_SCHEDULE) {
                sched_consigna_manual[ns_consigna_manual].t = at_t;
                sched_consigna_manual[ns_consigna_manual++].val = (double)(atof(_eq + 1));
            }
            if (strcmp(argv[oi], "modo_operacion") == 0 && ns_modo_operacion < MAX_SCHEDULE) {
                sched_modo_operacion[ns_modo_operacion].t = at_t;
                sched_modo_operacion[ns_modo_operacion++].val = (double)(atoi(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "consigna_manual") == 0) { cli_consigna_manual = (double)(atof(_eq + 1)); has_consigna_manual = 1; }
            if (strcmp(argv[oi], "modo_operacion") == 0) { cli_modo_operacion = (double)(atoi(_eq + 1)); has_modo_operacion = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = selectormodo_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
        return 1;
    }
    const fmu_vref_t vr_consigna_manual = SELECTORMODO_VR_CONSIGNA_MANUAL;
    const fmu_vref_t vr_modo_operacion = SELECTORMODO_VR_MODO_OPERACION;
    const fmu_vref_t vr_codigo_estado = SELECTORMODO_VR_CODIGO_ESTADO;
    const fmu_vref_t vr_fallo_modo = SELECTORMODO_VR_FALLO_MODO;
    const fmu_vref_t vr_salida_actuador = SELECTORMODO_VR_SALIDA_ACTUADOR;

    SIM_PRINT("t,consigna_manual,modo_operacion,codigo_estado,fallo_modo,salida_actuador\n");
    double t = 0.0;
    while (t < cfg.t_end) {
        SelectorModo_Inputs in = {0};
        get_inputs(t, &in);
        if (has_consigna_manual) in.consigna_manual = (double)cli_consigna_manual;
        if (ns_consigna_manual > 0) {
            double best = (double)in.consigna_manual; double best_t = -1e300;
            for (int si = 0; si < ns_consigna_manual; si++)
                if (t >= sched_consigna_manual[si].t && sched_consigna_manual[si].t >= best_t)
                    { best = sched_consigna_manual[si].val; best_t = sched_consigna_manual[si].t; }
            in.consigna_manual = (double)best;
        }
        if (has_modo_operacion) in.modo_operacion = (int)cli_modo_operacion;
        if (ns_modo_operacion > 0) {
            double best = (double)in.modo_operacion; double best_t = -1e300;
            for (int si = 0; si < ns_modo_operacion; si++)
                if (t >= sched_modo_operacion[si].t && sched_modo_operacion[si].t >= best_t)
                    { best = sched_modo_operacion[si].val; best_t = sched_modo_operacion[si].t; }
            in.modo_operacion = (int)best;
        }
        fmu_real_t set_consigna_manual = (fmu_real_t)in.consigna_manual;
        if (FMU_CALL(m, set_real, &vr_consigna_manual, 1, (const fmu_real_t *)&set_consigna_manual) > FMU_WARNING) {
            SIM_ERROR("Error: setting input consigna_manual failed\n");
            m->terminate(m); return 1;
        }
        fmu_int_t set_modo_operacion = (fmu_int_t)in.modo_operacion;
        if (FMU_CALL(m, set_integer, &vr_modo_operacion, 1, (const fmu_int_t *)&set_modo_operacion) > FMU_WARNING) {
            SIM_ERROR("Error: setting input modo_operacion failed\n");
            m->terminate(m); return 1;
        }
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (FMU_CALL(m, do_step, (fmu_real_t)t, (fmu_real_t)step) > FMU_WARNING) {
            SIM_ERROR("Error: fmi2DoStep failed\n");
            m->terminate(m); return 1;
        }
        t += step;
        SelectorModo_Outputs out = {0};
        fmu_int_t got_codigo_estado = 0;
        if (FMU_CALL(m, get_integer, &vr_codigo_estado, 1, &got_codigo_estado) > FMU_WARNING) {
            SIM_ERROR("Error: reading output codigo_estado failed\n");
            m->terminate(m); return 1;
        }
        out.codigo_estado = (int)got_codigo_estado;
        fmu_bool_t got_fallo_modo = 0;
        if (FMU_CALL(m, get_boolean, &vr_fallo_modo, 1, &got_fallo_modo) > FMU_WARNING) {
            SIM_ERROR("Error: reading output fallo_modo failed\n");
            m->terminate(m); return 1;
        }
        out.fallo_modo = (int)got_fallo_modo;
        fmu_real_t got_salida_actuador = 0.0;
        if (FMU_CALL(m, get_real, &vr_salida_actuador, 1, &got_salida_actuador) > FMU_WARNING) {
            SIM_ERROR("Error: reading output salida_actuador failed\n");
            m->terminate(m); return 1;
        }
        out.salida_actuador = (double)got_salida_actuador;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.consigna_manual, (int)in.modo_operacion, (int)out.codigo_estado, (int)out.fallo_modo, out.salida_actuador);
        SIM_DELAY(step);
    }
    m->terminate(m);
    return 0;
}
