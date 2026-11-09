/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para CodigoErrorDiagnostico — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : CodigoErrorDiagnostico
 * GUID   : {5d9a5441-4697-4945-99cb-289a15bd1126}
 * Estados: 0  |  Indicadores: 3
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "codigoerrordiagnostico_api.h"
#include "codigoerrordiagnostico_adapter.h"

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
    double _cli_temperatura = 0.0; int _has_temperatura = 0;
    struct { double t; double val; } _sched_temperatura[_MAX_SCHED]; int _ns_temperatura = 0;
    double _cli_tension = 0.0; int _has_tension = 0;
    struct { double t; double val; } _sched_tension[_MAX_SCHED]; int _ns_tension = 0;
    double _cli_vibracion = 0.0; int _has_vibracion = 0;
    struct { double t; double val; } _sched_vibracion[_MAX_SCHED]; int _ns_vibracion = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "temperatura") == 0 && _ns_temperatura < _MAX_SCHED) {
                _sched_temperatura[_ns_temperatura].t   = _at_t;
                _sched_temperatura[_ns_temperatura++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "tension") == 0 && _ns_tension < _MAX_SCHED) {
                _sched_tension[_ns_tension].t   = _at_t;
                _sched_tension[_ns_tension++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "vibracion") == 0 && _ns_vibracion < _MAX_SCHED) {
                _sched_vibracion[_ns_vibracion].t   = _at_t;
                _sched_vibracion[_ns_vibracion++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "temperatura") == 0) { _cli_temperatura = (double)(atof(_eq+1)); _has_temperatura = 1; }
            if (strcmp(argv[_oi], "tension") == 0) { _cli_tension = (double)(atof(_eq+1)); _has_tension = 1; }
            if (strcmp(argv[_oi], "vibracion") == 0) { _cli_vibracion = (double)(atof(_eq+1)); _has_vibracion = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = codigoerrordiagnostico_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_temperatura = CODIGOERRORDIAGNOSTICO_VR_TEMPERATURA;
    const fmu_vref_t vr_tension = CODIGOERRORDIAGNOSTICO_VR_TENSION;
    const fmu_vref_t vr_vibracion = CODIGOERRORDIAGNOSTICO_VR_VIBRACION;
    const fmu_vref_t vr_factor_reduccion = CODIGOERRORDIAGNOSTICO_VR_FACTOR_REDUCCION;
    const fmu_vref_t vr_codigo_error = CODIGOERRORDIAGNOSTICO_VR_CODIGO_ERROR;
    const fmu_vref_t vr_parada_emergencia = CODIGOERRORDIAGNOSTICO_VR_PARADA_EMERGENCIA;
    const fmu_vref_t vr_nivel_prioridad = CODIGOERRORDIAGNOSTICO_VR_NIVEL_PRIORIDAD;

    SIM_PRINT("t,temperatura,tension,vibracion,factor_reduccion,codigo_error,parada_emergencia,nivel_prioridad\n");

    double t = 0.0;
    for (;;) {

        CodigoErrorDiagnostico_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_temperatura) in.temperatura = (double)_cli_temperatura;
        if (_ns_temperatura > 0) {
            double _bv = (double)in.temperatura; double _bt = -1e300;
            for (int _si = 0; _si < _ns_temperatura; _si++)
                if (t >= _sched_temperatura[_si].t && _sched_temperatura[_si].t >= _bt)
                    { _bv = _sched_temperatura[_si].val; _bt = _sched_temperatura[_si].t; }
            in.temperatura = (double)_bv;
        }
        if (_has_tension) in.tension = (double)_cli_tension;
        if (_ns_tension > 0) {
            double _bv = (double)in.tension; double _bt = -1e300;
            for (int _si = 0; _si < _ns_tension; _si++)
                if (t >= _sched_tension[_si].t && _sched_tension[_si].t >= _bt)
                    { _bv = _sched_tension[_si].val; _bt = _sched_tension[_si].t; }
            in.tension = (double)_bv;
        }
        if (_has_vibracion) in.vibracion = (double)_cli_vibracion;
        if (_ns_vibracion > 0) {
            double _bv = (double)in.vibracion; double _bt = -1e300;
            for (int _si = 0; _si < _ns_vibracion; _si++)
                if (t >= _sched_vibracion[_si].t && _sched_vibracion[_si].t >= _bt)
                    { _bv = _sched_vibracion[_si].val; _bt = _sched_vibracion[_si].t; }
            in.vibracion = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_temperatura = (fmu_real_t)in.temperatura;
            FMU_CALL(m, set_real, &vr_temperatura, 1, (const fmu_real_t *)&_i_temperatura);
            fmu_real_t _i_tension = (fmu_real_t)in.tension;
            FMU_CALL(m, set_real, &vr_tension, 1, (const fmu_real_t *)&_i_tension);
            fmu_real_t _i_vibracion = (fmu_real_t)in.vibracion;
            FMU_CALL(m, set_real, &vr_vibracion, 1, (const fmu_real_t *)&_i_vibracion);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        CodigoErrorDiagnostico_Outputs out = {0};
        {
            fmu_real_t _o_factor_reduccion = 0.0;
            FMU_CALL(m, get_real, &vr_factor_reduccion, 1, &_o_factor_reduccion);
            out.factor_reduccion = (double)_o_factor_reduccion;
        }
        {
            fmu_int_t _o_codigo_error = 0;
            FMU_CALL(m, get_integer, &vr_codigo_error, 1, &_o_codigo_error);
            out.codigo_error = (int)_o_codigo_error;
        }
        {
            fmu_bool_t _o_parada_emergencia = 0;
            FMU_CALL(m, get_boolean, &vr_parada_emergencia, 1, &_o_parada_emergencia);
            out.parada_emergencia = (int)_o_parada_emergencia;
        }
        {
            fmu_int_t _o_nivel_prioridad = 0;
            FMU_CALL(m, get_integer, &vr_nivel_prioridad, 1, &_o_nivel_prioridad);
            out.nivel_prioridad = (int)_o_nivel_prioridad;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%.10g,%.10g,%.10g,%d,%d,%d\n", t, in.temperatura, in.tension, in.vibracion, out.factor_reduccion, (int)out.codigo_error, (int)out.parada_emergencia, (int)out.nivel_prioridad);

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
