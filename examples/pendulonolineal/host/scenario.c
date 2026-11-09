/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para PenduloNoLineal.
 *  UNICO archivo que debes editar.
 */

#include "pendulonolineal_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 10,
        .h       = 0.05,
        .use_rk4 = 1,
    };
}

void on_outputs(double t, const PenduloNoLineal_Outputs *out)
{
    (void)t;
    /* if (out->en_reposo) { ... } */
    /* if (out->angulo) { ... } */
    /* if (out->energia_total) { ... } */
    /* if (out->velocidad_angular) { ... } */
}

