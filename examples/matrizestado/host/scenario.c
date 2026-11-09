/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para MatrizEstado.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 */

#include "matrizestado_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void on_outputs(double t, const MatrizEstado_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->traza) { ... } */
    /* if (out->x_1) { ... } */
    /* if (out->x_2) { ... } */
    /* if (out->x_3) { ... } */
    /* if (out->y_norma) { ... } */
}
