/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para testUPM.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "testupm_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, testUPM_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->pot = ...; */
}

void on_outputs(double t, const testUPM_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->led1) { ... } */
    /* if (out->led2) { ... } */
    /* if (out->led3) { ... } */
    /* if (out->led4) { ... } */
    /* if (out->led5) { ... } */
}
