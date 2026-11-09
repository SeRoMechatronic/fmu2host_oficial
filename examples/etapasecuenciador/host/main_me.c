/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para EtapaSecuenciador — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : EtapaSecuenciador
 * GUID   : {8dd659c4-cec8-4fc5-ba83-5de4a39c0d1f}
 * Estados: 0  |  Indicadores: 0
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "etapasecuenciador_api.h"
#include "etapasecuenciador_adapter.h"

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
    double _cli_sensor_confirmacion = 0.0; int _has_sensor_confirmacion = 0;
    struct { double t; double val; } _sched_sensor_confirmacion[_MAX_SCHED]; int _ns_sensor_confirmacion = 0;
    double _cli_arrancar = 0.0; int _has_arrancar = 0;
    struct { double t; double val; } _sched_arrancar[_MAX_SCHED]; int _ns_arrancar = 0;
    double _cli_parar = 0.0; int _has_parar = 0;
    struct { double t; double val; } _sched_parar[_MAX_SCHED]; int _ns_parar = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "sensor_confirmacion") == 0 && _ns_sensor_confirmacion < _MAX_SCHED) {
                _sched_sensor_confirmacion[_ns_sensor_confirmacion].t   = _at_t;
                _sched_sensor_confirmacion[_ns_sensor_confirmacion++].val = (double)(atof(_eq+1));
            }
            if (strcmp(argv[_oi], "arrancar") == 0 && _ns_arrancar < _MAX_SCHED) {
                _sched_arrancar[_ns_arrancar].t   = _at_t;
                _sched_arrancar[_ns_arrancar++].val = (double)((atoi(_eq+1) != 0));
            }
            if (strcmp(argv[_oi], "parar") == 0 && _ns_parar < _MAX_SCHED) {
                _sched_parar[_ns_parar].t   = _at_t;
                _sched_parar[_ns_parar++].val = (double)((atoi(_eq+1) != 0));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "sensor_confirmacion") == 0) { _cli_sensor_confirmacion = (double)(atof(_eq+1)); _has_sensor_confirmacion = 1; }
            if (strcmp(argv[_oi], "arrancar") == 0) { _cli_arrancar = (double)((atoi(_eq+1) != 0)); _has_arrancar = 1; }
            if (strcmp(argv[_oi], "parar") == 0) { _cli_parar = (double)((atoi(_eq+1) != 0)); _has_parar = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = etapasecuenciador_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
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

        if (_has_sensor_confirmacion) in.sensor_confirmacion = (double)_cli_sensor_confirmacion;
        if (_ns_sensor_confirmacion > 0) {
            double _bv = (double)in.sensor_confirmacion; double _bt = -1e300;
            for (int _si = 0; _si < _ns_sensor_confirmacion; _si++)
                if (t >= _sched_sensor_confirmacion[_si].t && _sched_sensor_confirmacion[_si].t >= _bt)
                    { _bv = _sched_sensor_confirmacion[_si].val; _bt = _sched_sensor_confirmacion[_si].t; }
            in.sensor_confirmacion = (double)_bv;
        }
        if (_has_arrancar) in.arrancar = (int)_cli_arrancar;
        if (_ns_arrancar > 0) {
            double _bv = (double)in.arrancar; double _bt = -1e300;
            for (int _si = 0; _si < _ns_arrancar; _si++)
                if (t >= _sched_arrancar[_si].t && _sched_arrancar[_si].t >= _bt)
                    { _bv = _sched_arrancar[_si].val; _bt = _sched_arrancar[_si].t; }
            in.arrancar = (int)_bv;
        }
        if (_has_parar) in.parar = (int)_cli_parar;
        if (_ns_parar > 0) {
            double _bv = (double)in.parar; double _bt = -1e300;
            for (int _si = 0; _si < _ns_parar; _si++)
                if (t >= _sched_parar[_si].t && _sched_parar[_si].t >= _bt)
                    { _bv = _sched_parar[_si].val; _bt = _sched_parar[_si].t; }
            in.parar = (int)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_sensor_confirmacion = (fmu_real_t)in.sensor_confirmacion;
            FMU_CALL(m, set_real, &vr_sensor_confirmacion, 1, (const fmu_real_t *)&_i_sensor_confirmacion);
            fmu_bool_t _i_arrancar = (fmu_bool_t)in.arrancar;
            FMU_CALL(m, set_boolean, &vr_arrancar, 1, (const fmu_bool_t *)&_i_arrancar);
            fmu_bool_t _i_parar = (fmu_bool_t)in.parar;
            FMU_CALL(m, set_boolean, &vr_parar, 1, (const fmu_bool_t *)&_i_parar);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        EtapaSecuenciador_Outputs out = {0};
        {
            fmu_real_t _o_progreso_etapa = 0.0;
            FMU_CALL(m, get_real, &vr_progreso_etapa, 1, &_o_progreso_etapa);
            out.progreso_etapa = (double)_o_progreso_etapa;
        }
        {
            fmu_int_t _o_etapa_actual = 0;
            FMU_CALL(m, get_integer, &vr_etapa_actual, 1, &_o_etapa_actual);
            out.etapa_actual = (int)_o_etapa_actual;
        }
        {
            fmu_int_t _o_etapa_previa = 0;
            FMU_CALL(m, get_integer, &vr_etapa_previa, 1, &_o_etapa_previa);
            out.etapa_previa = (int)_o_etapa_previa;
        }
        {
            fmu_bool_t _o_secuencia_completa = 0;
            FMU_CALL(m, get_boolean, &vr_secuencia_completa, 1, &_o_secuencia_completa);
            out.secuencia_completa = (int)_o_secuencia_completa;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%d,%.10g,%d,%d,%d\n", t, in.sensor_confirmacion, (int)in.arrancar, (int)in.parar, out.progreso_etapa, (int)out.etapa_actual, (int)out.etapa_previa, (int)out.secuencia_completa);

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
