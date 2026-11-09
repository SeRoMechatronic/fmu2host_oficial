/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para SistemaLorenz.
 *  UNICO archivo que debes editar.
 */

#include "sistemalorenz_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 30,
        .h       = 0.01,
        .use_rk4 = 1,
    };
}

void on_outputs(double t, const SistemaLorenz_Outputs *out)
{
    (void)t;
    /* if (out->on_attractor) { ... } */
    /* if (out->x_out) { ... } */
    /* if (out->y_out) { ... } */
    /* if (out->z_out) { ... } */
}

