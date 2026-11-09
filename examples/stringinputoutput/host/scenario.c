/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para StringInputOutput.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "stringinputoutput_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, StringInputOutput_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->value = ...; */
    /* in->mode_operation = ...; */
    /* in->tag_sensor = ...; */
}

void on_outputs(double t, const StringInputOutput_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->scaled_value) { ... } */
    /* if (out->alarm) { ... } */
    /* if (out->alert_msg) { ... } */
    /* if (out->status) { ... } */
}
