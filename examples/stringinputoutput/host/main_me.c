/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para StringInputOutput — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : StringInputOutput
 * GUID   : {f65d9ebe-f41f-4336-bd36-24062740e954}
 * Estados: 0  |  Indicadores: 2
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stringinputoutput_api.h"
#include "stringinputoutput_adapter.h"

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
    double _cli_value = 0.0; int _has_value = 0;
    struct { double t; double val; } _sched_value[_MAX_SCHED]; int _ns_value = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "value") == 0 && _ns_value < _MAX_SCHED) {
                _sched_value[_ns_value].t   = _at_t;
                _sched_value[_ns_value++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "value") == 0) { _cli_value = (double)(atof(_eq+1)); _has_value = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = stringinputoutput_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_value = STRINGINPUTOUTPUT_VR_VALUE;
    const fmu_vref_t vr_mode_operation = STRINGINPUTOUTPUT_VR_MODE_OPERATION;
    const fmu_vref_t vr_tag_sensor = STRINGINPUTOUTPUT_VR_TAG_SENSOR;
    const fmu_vref_t vr_scaled_value = STRINGINPUTOUTPUT_VR_SCALED_VALUE;
    const fmu_vref_t vr_alarm = STRINGINPUTOUTPUT_VR_ALARM;
    const fmu_vref_t vr_alert_msg = STRINGINPUTOUTPUT_VR_ALERT_MSG;
    const fmu_vref_t vr_status = STRINGINPUTOUTPUT_VR_STATUS;

    SIM_PRINT("t,value,mode_operation,tag_sensor,scaled_value,alarm,alert_msg,status\n");

    double t = 0.0;
    for (;;) {

        StringInputOutput_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_value) in.value = (double)_cli_value;
        if (_ns_value > 0) {
            double _bv = (double)in.value; double _bt = -1e300;
            for (int _si = 0; _si < _ns_value; _si++)
                if (t >= _sched_value[_si].t && _sched_value[_si].t >= _bt)
                    { _bv = _sched_value[_si].val; _bt = _sched_value[_si].t; }
            in.value = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_value = (fmu_real_t)in.value;
            FMU_CALL(m, set_real, &vr_value, 1, (const fmu_real_t *)&_i_value);
            fmu_string_t _i_mode_operation = (in.mode_operation ? (fmu_string_t)in.mode_operation : (fmu_string_t)"");
            FMU_CALL(m, set_string, &vr_mode_operation, 1, (const fmu_string_t *)&_i_mode_operation);
            fmu_string_t _i_tag_sensor = (in.tag_sensor ? (fmu_string_t)in.tag_sensor : (fmu_string_t)"");
            FMU_CALL(m, set_string, &vr_tag_sensor, 1, (const fmu_string_t *)&_i_tag_sensor);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        StringInputOutput_Outputs out = {0};
        {
            fmu_real_t _o_scaled_value = 0.0;
            FMU_CALL(m, get_real, &vr_scaled_value, 1, &_o_scaled_value);
            out.scaled_value = (double)_o_scaled_value;
        }
        {
            fmu_bool_t _o_alarm = 0;
            FMU_CALL(m, get_boolean, &vr_alarm, 1, &_o_alarm);
            out.alarm = (int)_o_alarm;
        }
        {
            fmu_string_t _o_alert_msg = NULL;
            FMU_CALL(m, get_string, &vr_alert_msg, 1, &_o_alert_msg);
            out.alert_msg = (const char *)_o_alert_msg;
        }
        {
            fmu_string_t _o_status = NULL;
            FMU_CALL(m, get_string, &vr_status, 1, &_o_status);
            out.status = (const char *)_o_status;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%s,%s,%.10g,%d,%s,%s\n", t, in.value, (in.mode_operation ? in.mode_operation : ""), (in.tag_sensor ? in.tag_sensor : ""), out.scaled_value, (int)out.alarm, (out.alert_msg ? out.alert_msg : ""), (out.status ? out.status : ""));

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
