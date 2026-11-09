/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para SinInputs.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 */

#include "sininputs_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void on_outputs(double t, const SinInputs_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->energia) { ... } */
    /* if (out->posicion) { ... } */
    /* if (out->velocidad) { ... } */
}
