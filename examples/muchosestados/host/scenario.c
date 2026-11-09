/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para MuchosEstados.
 *  UNICO archivo que debes editar.
 */

#include "muchosestados_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 30,
        .h       = 0.01,
        .use_rk4 = 1,
    };
}

void get_inputs(double t, MuchosEstados_Inputs *in)
{
    (void)t;
    /* in->u = ...; */
}

void on_outputs(double t, const MuchosEstados_Outputs *out)
{
    (void)t;
    /* if (out->todos_activos) { ... } */
    /* if (out->y1) { ... } */
    /* if (out->y2) { ... } */
    /* if (out->y3) { ... } */
    /* if (out->y4) { ... } */
    /* if (out->y5) { ... } */
    /* if (out->y6) { ... } */
    /* if (out->y7) { ... } */
    /* if (out->y8) { ... } */
}
