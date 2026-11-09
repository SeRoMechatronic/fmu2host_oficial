/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para CrecimientoPoblacional.
 *  UNICO archivo que debes editar.
 */

#include "crecimientopoblacional_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 5.1,
        .h       = 0.1,
        .use_rk4 = 1,
    };
}

void get_inputs(double t, CrecimientoPoblacional_Inputs *in)
{
    (void)t;
    /* in->tasa_entrada = ...; */
}

void on_outputs(double t, const CrecimientoPoblacional_Outputs *out)
{
    (void)t;
    /* if (out->superpoblacion) { ... } */
    /* if (out->poblacion) { ... } */
    /* if (out->saturacion) { ... } */
    /* if (out->tasa_crecimiento) { ... } */
}
