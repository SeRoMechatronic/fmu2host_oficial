/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para ValoresExtremos.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "valoresextremos_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, ValoresExtremos_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->u = ...; */
}

void on_outputs(double t, const ValoresExtremos_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->es_finito) { ... } */
    /* if (out->y_inv) { ... } */
    /* if (out->y_log) { ... } */
    /* if (out->y_sat) { ... } */
    /* if (out->y_sqrt) { ... } */
}
