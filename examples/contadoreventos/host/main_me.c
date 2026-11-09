/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para ContadorEventos — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : ContadorEventos
 * GUID   : {74a5f633-cf1b-4cc7-a4bb-0e6d63cf1bac}
 * Estados: 0  |  Indicadores: 2
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "contadoreventos_api.h"
#include "contadoreventos_adapter.h"

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
    double _cli_evento = 0.0; int _has_evento = 0;
    struct { double t; double val; } _sched_evento[_MAX_SCHED]; int _ns_evento = 0;
    double _cli_reset = 0.0; int _has_reset = 0;
    struct { double t; double val; } _sched_reset[_MAX_SCHED]; int _ns_reset = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "evento") == 0 && _ns_evento < _MAX_SCHED) {
                _sched_evento[_ns_evento].t   = _at_t;
                _sched_evento[_ns_evento++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "reset") == 0 && _ns_reset < _MAX_SCHED) {
                _sched_reset[_ns_reset].t   = _at_t;
                _sched_reset[_ns_reset++].val = (double)((atoi(_eq+1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "evento") == 0) { _cli_evento = (double)((atoi(_eq+1) != 0)); _has_evento = 1; }
            if (strcmp(argv[_oi], "reset") == 0) { _cli_reset = (double)((atoi(_eq+1) != 0)); _has_reset = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = contadoreventos_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
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

        if (_has_evento) in.evento = (int)_cli_evento;
        if (_ns_evento > 0) {
            double _bv = (double)in.evento; double _bt = -1e300;
            for (int _si = 0; _si < _ns_evento; _si++)
                if (t >= _sched_evento[_si].t && _sched_evento[_si].t >= _bt)
                    { _bv = _sched_evento[_si].val; _bt = _sched_evento[_si].t; }
            in.evento = (int)_bv;
        }
        if (_has_reset) in.reset = (int)_cli_reset;
        if (_ns_reset > 0) {
            double _bv = (double)in.reset; double _bt = -1e300;
            for (int _si = 0; _si < _ns_reset; _si++)
                if (t >= _sched_reset[_si].t && _sched_reset[_si].t >= _bt)
                    { _bv = _sched_reset[_si].val; _bt = _sched_reset[_si].t; }
            in.reset = (int)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_bool_t _i_evento = (fmu_bool_t)in.evento;
            FMU_CALL(m, set_boolean, &vr_evento, 1, (const fmu_bool_t *)&_i_evento);
            fmu_bool_t _i_reset = (fmu_bool_t)in.reset;
            FMU_CALL(m, set_boolean, &vr_reset, 1, (const fmu_bool_t *)&_i_reset);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        ContadorEventos_Outputs out = {0};
        {
            fmu_int_t _o_cuenta = 0;
            FMU_CALL(m, get_integer, &vr_cuenta, 1, &_o_cuenta);
            out.cuenta = (int)_o_cuenta;
        }
        {
            fmu_int_t _o_decenas = 0;
            FMU_CALL(m, get_integer, &vr_decenas, 1, &_o_decenas);
            out.decenas = (int)_o_decenas;
        }
        {
            fmu_bool_t _o_desbordamiento = 0;
            FMU_CALL(m, get_boolean, &vr_desbordamiento, 1, &_o_desbordamiento);
            out.desbordamiento = (int)_o_desbordamiento;
        }
        {
            fmu_int_t _o_unidades = 0;
            FMU_CALL(m, get_integer, &vr_unidades, 1, &_o_unidades);
            out.unidades = (int)_o_unidades;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%d,%d,%d,%d,%d,%d\n", t, (int)in.evento, (int)in.reset, (int)out.cuenta, (int)out.decenas, (int)out.desbordamiento, (int)out.unidades);

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
