/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para OsciladorArmonico.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 */

#include "osciladorarmonico_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 20,
        .h       = 0.01,
        .use_rk4 = 1,
    };
}

void on_outputs(double t, const OsciladorArmonico_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->energia) { ... } */
    /* if (out->posicion) { ... } */
    /* if (out->velocidad) { ... } */
}

