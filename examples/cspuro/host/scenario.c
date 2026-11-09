/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para CSPuro_SinME.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "cspuro_sinme_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, CSPuro_SinME_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->u1 = ...; */
    /* in->u2 = ...; */
}

void on_outputs(double t, const CSPuro_SinME_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->active) { ... } */
    /* if (out->y_prod) { ... } */
    /* if (out->y_sum) { ... } */
}
