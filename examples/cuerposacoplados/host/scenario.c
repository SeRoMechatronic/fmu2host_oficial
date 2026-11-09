/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para CuerposAcoplados.
 *  UNICO archivo que debes editar.
 */

#include "cuerposacoplados_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 20,
        .h       = 0.05,
        .use_rk4 = 1,
    };
}

void get_inputs(double t, CuerposAcoplados_Inputs *in)
{
    (void)t;
    /* in->fuerza_externa = ...; */
}

void on_outputs(double t, const CuerposAcoplados_Outputs *out)
{
    (void)t;
    /* if (out->en_fase) { ... } */
    /* if (out->energia_total) { ... } */
    /* if (out->pos1) { ... } */
    /* if (out->pos2) { ... } */
    /* if (out->vel1) { ... } */
    /* if (out->vel2) { ... } */
}

