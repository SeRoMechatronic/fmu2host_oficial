/**
 * @file main_cs.c -- generated typed Co-Simulation loop for StringInputOutput.
 * scenario.c is shared by the ME and CS executables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stringinputoutput_api.h"
#include "stringinputoutput_adapter.h"

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
    double cli_value = 0.0; int has_value = 0;
    struct { double t; double val; } sched_value[MAX_SCHEDULE]; int ns_value = 0;
    for (int oi = 1; oi < argc; oi++) {
        char *_at = strchr(argv[oi], '@');
        char *_eq = strchr(argv[oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double at_t = atof(_at + 1);
            if (strcmp(argv[oi], "value") == 0 && ns_value < MAX_SCHEDULE) {
                sched_value[ns_value].t = at_t;
                sched_value[ns_value++].val = (double)(atof(_eq + 1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[oi], "value") == 0) { cli_value = (double)(atof(_eq + 1)); has_value = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = stringinputoutput_create_cs();
    if (m->initialize(m) > FMU_WARNING) {
        SIM_ERROR("Error: initialize() failed\n");
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
        if (has_value) in.value = (double)cli_value;
        if (ns_value > 0) {
            double best = (double)in.value; double best_t = -1e300;
            for (int si = 0; si < ns_value; si++)
                if (t >= sched_value[si].t && sched_value[si].t >= best_t)
                    { best = sched_value[si].val; best_t = sched_value[si].t; }
            in.value = (double)best;
        }
        fmu_real_t set_value = (fmu_real_t)in.value;
        if (FMU_CALL(m, set_real, &vr_value, 1, (const fmu_real_t *)&set_value) > FMU_WARNING) {
            SIM_ERROR("Error: setting input value failed\n");
            m->terminate(m); return 1;
        }
        fmu_string_t set_mode_operation = in.mode_operation ? (fmu_string_t)in.mode_operation : (fmu_string_t)"";
        if (FMU_CALL(m, set_string, &vr_mode_operation, 1, (const fmu_string_t *)&set_mode_operation) > FMU_WARNING) {
            SIM_ERROR("Error: setting input mode_operation failed\n");
            m->terminate(m); return 1;
        }
        fmu_string_t set_tag_sensor = in.tag_sensor ? (fmu_string_t)in.tag_sensor : (fmu_string_t)"";
        if (FMU_CALL(m, set_string, &vr_tag_sensor, 1, (const fmu_string_t *)&set_tag_sensor) > FMU_WARNING) {
            SIM_ERROR("Error: setting input tag_sensor failed\n");
            m->terminate(m); return 1;
        }
        StringInputOutput_Outputs out = {0};
        fmu_real_t got_scaled_value = 0.0;
        if (FMU_CALL(m, get_real, &vr_scaled_value, 1, &got_scaled_value) > FMU_WARNING) {
            SIM_ERROR("Error: reading output scaled_value failed\n");
            m->terminate(m); return 1;
        }
        out.scaled_value = (double)got_scaled_value;
        fmu_bool_t got_alarm = 0;
        if (FMU_CALL(m, get_boolean, &vr_alarm, 1, &got_alarm) > FMU_WARNING) {
            SIM_ERROR("Error: reading output alarm failed\n");
            m->terminate(m); return 1;
        }
        out.alarm = (int)got_alarm;
        fmu_string_t got_alert_msg = NULL;
        if (FMU_CALL(m, get_string, &vr_alert_msg, 1, &got_alert_msg) > FMU_WARNING) {
            SIM_ERROR("Error: reading output alert_msg failed\n");
            m->terminate(m); return 1;
        }
        out.alert_msg = (const char *)got_alert_msg;
        fmu_string_t got_status = NULL;
        if (FMU_CALL(m, get_string, &vr_status, 1, &got_status) > FMU_WARNING) {
            SIM_ERROR("Error: reading output status failed\n");
            m->terminate(m); return 1;
        }
        out.status = (const char *)got_status;
        on_outputs(t, &out);
        SIM_PRINT("%.10g,%.10g,%s,%s,%.10g,%d,%s,%s\n", t, in.value, (in.mode_operation ? in.mode_operation : ""), (in.tag_sensor ? in.tag_sensor : ""), out.scaled_value, (int)out.alarm, (out.alert_msg ? out.alert_msg : ""), (out.status ? out.status : ""));
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
