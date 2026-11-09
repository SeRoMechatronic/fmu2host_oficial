/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para SelectorModo — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : SelectorModo
 * GUID   : {1a2b3f1f-16f4-4130-bc9c-3c8938410178}
 * Estados: 0  |  Indicadores: 4
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "selectormodo_api.h"
#include "selectormodo_adapter.h"

#define SIM_PRINT(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#define SIM_ERROR(msg)       fprintf(stderr, "%s", msg)
#define SIM_DELAY(h)         ((void)(h))

static int process_events(fmu_t *m)
{
    if (FMU_CALL(m, enter_event_mode) > FMU_WARNING) return -1;
    fmu_bool_t more = 1, terminate = 0;
    while (more && !terminate) {
        if (FMU_CALL(m, new_discrete_states, &more, &terminate) > FMU_WARNING)
            return -1;
    }
    if (terminate) return -1;
    return (FMU_CALL(m, enter_cont_mode) <= FMU_WARNING) ? 0 : -1;
}

int main(int argc, char *argv[])
{
    SimConfig cfg = get_config();

    if (argc >= 2 && !strchr(argv[1], '=')) cfg.t_end = atof(argv[1]);
    if (argc >= 3 && !strchr(argv[2], '=')) cfg.h     = atof(argv[2]);

    if (!isfinite(cfg.t_end) || !isfinite(cfg.h) || cfg.t_end < 0.0 || cfg.h <= 0.0) {
        SIM_ERROR("Error: expected finite t_end >= 0 and h > 0\n");
        return 2;
    }

    #define _MAX_SCHED 512
    double _cli_consigna_manual = 0.0; int _has_consigna_manual = 0;
    struct { double t; double val; } _sched_consigna_manual[_MAX_SCHED]; int _ns_consigna_manual = 0;
    double _cli_modo_operacion = 0.0; int _has_modo_operacion = 0;
    struct { double t; double val; } _sched_modo_operacion[_MAX_SCHED]; int _ns_modo_operacion = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "consigna_manual") == 0 && _ns_consigna_manual < _MAX_SCHED) {
                _sched_consigna_manual[_ns_consigna_manual].t   = _at_t;
                _sched_consigna_manual[_ns_consigna_manual++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "modo_operacion") == 0 && _ns_modo_operacion < _MAX_SCHED) {
                _sched_modo_operacion[_ns_modo_operacion].t   = _at_t;
                _sched_modo_operacion[_ns_modo_operacion++].val = (double)(atoi(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "consigna_manual") == 0) { _cli_consigna_manual = (double)(atof(_eq+1)); _has_consigna_manual = 1; }
            if (strcmp(argv[_oi], "modo_operacion") == 0) { _cli_modo_operacion = (double)(atoi(_eq+1)); _has_modo_operacion = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = selectormodo_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_consigna_manual = SELECTORMODO_VR_CONSIGNA_MANUAL;
    const fmu_vref_t vr_modo_operacion = SELECTORMODO_VR_MODO_OPERACION;
    const fmu_vref_t vr_codigo_estado = SELECTORMODO_VR_CODIGO_ESTADO;
    const fmu_vref_t vr_fallo_modo = SELECTORMODO_VR_FALLO_MODO;
    const fmu_vref_t vr_salida_actuador = SELECTORMODO_VR_SALIDA_ACTUADOR;

    SIM_PRINT("t,consigna_manual,modo_operacion,codigo_estado,fallo_modo,salida_actuador\n");

    double t = 0.0;
    for (;;) {

        SelectorModo_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_consigna_manual) in.consigna_manual = (double)_cli_consigna_manual;
        if (_ns_consigna_manual > 0) {
            double _bv = (double)in.consigna_manual; double _bt = -1e300;
            for (int _si = 0; _si < _ns_consigna_manual; _si++)
                if (t >= _sched_consigna_manual[_si].t && _sched_consigna_manual[_si].t >= _bt)
                    { _bv = _sched_consigna_manual[_si].val; _bt = _sched_consigna_manual[_si].t; }
            in.consigna_manual = (double)_bv;
        }
        if (_has_modo_operacion) in.modo_operacion = (int)_cli_modo_operacion;
        if (_ns_modo_operacion > 0) {
            double _bv = (double)in.modo_operacion; double _bt = -1e300;
            for (int _si = 0; _si < _ns_modo_operacion; _si++)
                if (t >= _sched_modo_operacion[_si].t && _sched_modo_operacion[_si].t >= _bt)
                    { _bv = _sched_modo_operacion[_si].val; _bt = _sched_modo_operacion[_si].t; }
            in.modo_operacion = (int)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_consigna_manual = (fmu_real_t)in.consigna_manual;
            FMU_CALL(m, set_real, &vr_consigna_manual, 1, (const fmu_real_t *)&_i_consigna_manual);
            fmu_int_t _i_modo_operacion = (fmu_int_t)in.modo_operacion;
            FMU_CALL(m, set_integer, &vr_modo_operacion, 1, (const fmu_int_t *)&_i_modo_operacion);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        SelectorModo_Outputs out = {0};
        {
            fmu_int_t _o_codigo_estado = 0;
            FMU_CALL(m, get_integer, &vr_codigo_estado, 1, &_o_codigo_estado);
            out.codigo_estado = (int)_o_codigo_estado;
        }
        {
            fmu_bool_t _o_fallo_modo = 0;
            FMU_CALL(m, get_boolean, &vr_fallo_modo, 1, &_o_fallo_modo);
            out.fallo_modo = (int)_o_fallo_modo;
        }
        {
            fmu_real_t _o_salida_actuador = 0.0;
            FMU_CALL(m, get_real, &vr_salida_actuador, 1, &_o_salida_actuador);
            out.salida_actuador = (double)_o_salida_actuador;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%.10g\n", t, in.consigna_manual, (int)in.modo_operacion, (int)out.codigo_estado, (int)out.fallo_modo, out.salida_actuador);

        if (t >= cfg.t_end) break;
        double step = cfg.h;
        if (t + step > cfg.t_end) step = cfg.t_end - t;
        if (m->next_event_time_defined && m->next_event_time > t &&
            m->next_event_time < t + step)
            step = m->next_event_time - t;

        t += step;
        SIM_DELAY(step);
    }

    m->terminate(m);
    return 0;
}
