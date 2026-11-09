/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para TiposMixtos.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "tiposmixtos_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, TiposMixtos_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->i_in = ...; */
    /* in->b_in = ...; */
    /* in->r_in = ...; */
}

void on_outputs(double t, const TiposMixtos_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->r_abs) { ... } */
    /* if (out->i_out) { ... } */
    /* if (out->b_out) { ... } */
    /* if (out->r_out) { ... } */
}
