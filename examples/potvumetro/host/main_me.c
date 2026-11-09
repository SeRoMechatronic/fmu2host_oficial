/**
 * @file   main_me.c
 * @brief  Loop ME auto-generado para PotVumetro — no editar.
 *
 *  Personaliza get_config() y get_inputs() en scenario.c.
 *
 * Modelo : PotVumetro
 * GUID   : {ab7bb8fe-cb29-4aff-b8cc-95d1c27f2d3b}
 * Estados: 0  |  Indicadores: 5
 *
 * GENERADO por fmu_codegen_host.py — no editar manualmente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "potvumetro_api.h"
#include "potvumetro_adapter.h"

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
    double _cli_pot = 0.0; int _has_pot = 0;
    struct { double t; double val; } _sched_pot[_MAX_SCHED]; int _ns_pot = 0;

    for (int _oi = 1; _oi < argc; _oi++) {
        char *_at = strchr(argv[_oi], '@');
        char *_eq = strchr(argv[_oi], '=');
        if (!_eq) continue;
        if (_at && _at < _eq) {
            *_at = '\0'; *_eq = '\0';
            double _at_t = atof(_at + 1);
            if (strcmp(argv[_oi], "pot") == 0 && _ns_pot < _MAX_SCHED) {
                _sched_pot[_ns_pot].t   = _at_t;
                _sched_pot[_ns_pot++].val = (double)(atof(_eq+1));
            }
            *_at = '@'; *_eq = '=';
        } else {
            *_eq = '\0';
            if (strcmp(argv[_oi], "pot") == 0) { _cli_pot = (double)(atof(_eq+1)); _has_pot = 1; }
            *_eq = '=';
        }
    }

    fmu_t *m = potvumetro_create_me();
    if (m->initialize(m) != FMU_OK) {
        SIM_ERROR("Error: initialize() fallo\n");
        return 1;
    }

    if (process_events(m) != 0) {
        SIM_ERROR("Error: eventos iniciales\n");
        m->terminate(m);
        return 1;
    }

    const fmu_vref_t vr_pot = POTVUMETRO_VR_POT;
    const fmu_vref_t vr_led1 = POTVUMETRO_VR_LED1;
    const fmu_vref_t vr_led2 = POTVUMETRO_VR_LED2;
    const fmu_vref_t vr_led3 = POTVUMETRO_VR_LED3;
    const fmu_vref_t vr_led4 = POTVUMETRO_VR_LED4;
    const fmu_vref_t vr_led5 = POTVUMETRO_VR_LED5;

    SIM_PRINT("t,pot,led1,led2,led3,led4,led5\n");

    double t = 0.0;
    for (;;) {

        PotVumetro_Inputs in = {0};
        get_inputs(t, &in);

        if (_has_pot) in.pot = (double)_cli_pot;
        if (_ns_pot > 0) {
            double _bv = (double)in.pot; double _bt = -1e300;
            for (int _si = 0; _si < _ns_pot; _si++)
                if (t >= _sched_pot[_si].t && _sched_pot[_si].t >= _bt)
                    { _bv = _sched_pot[_si].val; _bt = _sched_pot[_si].t; }
            in.pot = (double)_bv;
        }

        FMU_CALL(m, set_time, (fmu_real_t)t);
        if (FMU_CALL(m, enter_event_mode) == FMU_OK) {
            fmu_real_t _i_pot = (fmu_real_t)in.pot;
            FMU_CALL(m, set_real, &vr_pot, 1, (const fmu_real_t *)&_i_pot);
            fmu_bool_t more = 1, terminate = 0;
            while (more && !terminate)
                FMU_CALL(m, new_discrete_states, &more, &terminate);
            FMU_CALL(m, enter_cont_mode);
        }

        PotVumetro_Outputs out = {0};
        {
            fmu_bool_t _o_led1 = 0;
            FMU_CALL(m, get_boolean, &vr_led1, 1, &_o_led1);
            out.led1 = (int)_o_led1;
        }
        {
            fmu_bool_t _o_led2 = 0;
            FMU_CALL(m, get_boolean, &vr_led2, 1, &_o_led2);
            out.led2 = (int)_o_led2;
        }
        {
            fmu_bool_t _o_led3 = 0;
            FMU_CALL(m, get_boolean, &vr_led3, 1, &_o_led3);
            out.led3 = (int)_o_led3;
        }
        {
            fmu_bool_t _o_led4 = 0;
            FMU_CALL(m, get_boolean, &vr_led4, 1, &_o_led4);
            out.led4 = (int)_o_led4;
        }
        {
            fmu_bool_t _o_led5 = 0;
            FMU_CALL(m, get_boolean, &vr_led5, 1, &_o_led5);
            out.led5 = (int)_o_led5;
        }
        on_outputs(t, &out);

        SIM_PRINT("%.10g,%.10g,%d,%d,%d,%d,%d\n", t, in.pot, (int)out.led1, (int)out.led2, (int)out.led3, (int)out.led4, (int)out.led5);

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
