/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para MultiplexorCanales — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : MultiplexorCanales
 * GUID   : {dcf0a32f-6203-4553-8a23-9c7afeb44655}
 * Estados: 0  |  Indicadores: 7
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "multiplexorcanales_api.h"
#include "multiplexorcanales_adapter.h"

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
    double _cli_canal_0 = 0.0; int _has_canal_0 = 0;
    struct { double t; double val; } _sched_canal_0[_MAX_SCHED]; int _ns_canal_0 = 0;
    double _cli_canal_1 = 0.0; int _has_canal_1 = 0;
    struct { double t; double val; } _sched_canal_1[_MAX_SCHED]; int _ns_canal_1 = 0;
    double _cli_canal_seleccion = 0.0; int _has_canal_seleccion = 0;
    struct { double t; double val; } _sched_canal_seleccion[_MAX_SCHED]; int _ns_canal_seleccion = 0;
    double _cli_canal_2 = 0.0; int _has_canal_2 = 0;
    struct { double t; double val; } _sched_canal_2[_MAX_SCHED]; int _ns_canal_2 = 0;
    double _cli_canal_3 = 0.0; int _has_canal_3 = 0;
    struct { double t; double val; } _sched_canal_3[_MAX_SCHED]; int _ns_canal_3 = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "canal_0") == 0 && _ns_canal_0 < _MAX_SCHED) {
                _sched_canal_0[_ns_canal_0].t   = _at_t;
                _sched_canal_0[_ns_canal_0++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "canal_1") == 0 && _ns_canal_1 < _MAX_SCHED) {
                _sched_canal_1[_ns_canal_1].t   = _at_t;
                _sched_canal_1[_ns_canal_1++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "canal_seleccion") == 0 && _ns_canal_seleccion < _MAX_SCHED) {
                _sched_canal_seleccion[_ns_canal_seleccion].t   = _at_t;
                _sched_canal_seleccion[_ns_canal_seleccion++].val = (double)(atoi(_eq+1));
            }
            if (strcmp(argv[_oi], "canal_2") == 0 && _ns_canal_2 < _MAX_SCHED) {
                _sched_canal_2[_ns_canal_2].t   = _at_t;
                _sched_canal_2[_ns_canal_2++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "canal_3") == 0 && _ns_canal_3 < _MAX_SCHED) {
                _sched_canal_3[_ns_canal_3].t   = _at_t;
                _sched_canal_3[_ns_canal_3++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "canal_0") == 0) { _cli_canal_0 = (double)(atof(_eq+1)); _has_canal_0 = 1; }
            if (strcmp(argv[_oi], "canal_1") == 0) { _cli_canal_1 = (double)(atof(_eq+1)); _has_canal_1 = 1; }
            if (strcmp(argv[_oi], "canal_seleccion") == 0) { _cli_canal_seleccion = (double)(atoi(_eq+1)); _has_canal_seleccion = 1; }
            if (strcmp(argv[_oi], "canal_2") == 0) { _cli_canal_2 = (double)(atof(_eq+1)); _has_canal_2 = 1; }
            if (strcmp(argv[_oi], "canal_3") == 0) { _cli_canal_3 = (double)(atof(_eq+1)); _has_canal_3 = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = multiplexorcanales_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_canal_0 = MULTIPLEXORCANALES_VR_CANAL_0;
    const fmu_vref_t vr_canal_1 = MULTIPLEXORCANALES_VR_CANAL_1;
    const fmu_vref_t vr_canal_seleccion = MULTIPLEXORCANALES_VR_CANAL_SELECCION;
    const fmu_vref_t vr_canal_2 = MULTIPLEXORCANALES_VR_CANAL_2;
    const fmu_vref_t vr_canal_3 = MULTIPLEXORCANALES_VR_CANAL_3;
    const fmu_vref_t vr_canal_activo = MULTIPLEXORCANALES_VR_CANAL_ACTIVO;
    const fmu_vref_t vr_canal_valido = MULTIPLEXORCANALES_VR_CANAL_VALIDO;
    const fmu_vref_t vr_salida = MULTIPLEXORCANALES_VR_SALIDA;

    SIM_PRINT("t,canal_0,canal_1,canal_seleccion,canal_2,canal_3,canal_activo,canal_valido,salida\n");

    double t = 0.0;
    for (;;) {

        MultiplexorCanales_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_canal_0) in.canal_0 = (double)_cli_canal_0;
        if (_ns_canal_0 > 0) {
            double _bv = (double)in.canal_0; double _bt = -1e300;
            for (int _si = 0; _si < _ns_canal_0; _si++)
                if (t >= _sched_canal_0[_si].t && _sched_canal_0[_si].t >= _bt)
                    { _bv = _sched_canal_0[_si].val; _bt = _sched_canal_0[_si].t; }
            in.canal_0 = (double)_bv;
        }
        if (_has_canal_1) in.canal_1 = (double)_cli_canal_1;
        if (_ns_canal_1 > 0) {
            double _bv = (double)in.canal_1; double _bt = -1e300;
            for (int _si = 0; _si < _ns_canal_1; _si++)
                if (t >= _sched_canal_1[_si].t && _sched_canal_1[_si].t >= _bt)
                    { _bv = _sched_canal_1[_si].val; _bt = _sched_canal_1[_si].t; }
            in.canal_1 = (double)_bv;
        }
        if (_has_canal_seleccion) in.canal_seleccion = (int)_cli_canal_seleccion;
        if (_ns_canal_seleccion > 0) {
            double _bv = (double)in.canal_seleccion; double _bt = -1e300;
            for (int _si = 0; _si < _ns_canal_seleccion; _si++)
                if (t >= _sched_canal_seleccion[_si].t && _sched_canal_seleccion[_si].t >= _bt)
                    { _bv = _sched_canal_seleccion[_si].val; _bt = _sched_canal_seleccion[_si].t; }
            in.canal_seleccion = (int)_bv;
        }
        if (_has_canal_2) in.canal_2 = (double)_cli_canal_2;
        if (_ns_canal_2 > 0) {
            double _bv = (double)in.canal_2; double _bt = -1e300;
            for (int _si = 0; _si < _ns_canal_2; _si++)
                if (t >= _sched_canal_2[_si].t && _sched_canal_2[_si].t >= _bt)
                    { _bv = _sched_canal_2[_si].val; _bt = _sched_canal_2[_si].t; }
            in.canal_2 = (double)_bv;
        }
        if (_has_canal_3) in.canal_3 = (double)_cli_canal_3;
        if (_ns_canal_3 > 0) {
            double _bv = (double)in.canal_3; double _bt = -1e300;
            for (int _si = 0; _si < _ns_canal_3; _si++)
                if (t >= _sched_canal_3[_si].t && _sched_canal_3[_si].t >= _bt)
                    { _bv = _sched_canal_3[_si].val; _bt = _sched_canal_3[_si].t; }
            in.canal_3 = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_canal_0 = (fmu_real_t)in.canal_0;
            FMU_CALL(m, set_real, &vr_canal_0, 1, (const fmu_real_t *)&_i_canal_0);
            fmu_real_t _i_canal_1 = (fmu_real_t)in.canal_1;
            FMU_CALL(m, set_real, &vr_canal_1, 1, (const fmu_real_t *)&_i_canal_1);
            fmu_int_t _i_canal_seleccion = (fmu_int_t)in.canal_seleccion;
            FMU_CALL(m, set_integer, &vr_canal_seleccion, 1, (const fmu_int_t *)&_i_canal_seleccion);
            fmu_real_t _i_canal_2 = (fmu_real_t)in.canal_2;
            FMU_CALL(m, set_real, &vr_canal_2, 1, (const fmu_real_t *)&_i_canal_2);
            fmu_real_t _i_canal_3 = (fmu_real_t)in.canal_3;
            FMU_CALL(m, set_real, &vr_canal_3, 1, (const fmu_real_t *)&_i_canal_3);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        MultiplexorCanales_Outputs out = {0};
        {
            fmu_int_t _o_canal_activo = 0;
            FMU_CALL(m, get_integer, &vr_canal_activo, 1, &_o_canal_activo);
            out.canal_activo = (int)_o_canal_activo;
        }
        {
            fmu_bool_t _o_canal_valido = 0;
            FMU_CALL(m, get_boolean, &vr_canal_valido, 1, &_o_canal_valido);
            out.canal_valido = (int)_o_canal_valido;
        }
        {
            fmu_real_t _o_salida = 0.0;
            FMU_CALL(m, get_real, &vr_salida, 1, &_o_salida);
            out.salida = (double)_o_salida;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%d,%.10g,%.10g,%d,%d,%.10g\n", t, in.canal_0, in.canal_1, (int)in.canal_seleccion, in.canal_2, in.canal_3, (int)out.canal_activo, (int)out.canal_valido, out.salida);

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
