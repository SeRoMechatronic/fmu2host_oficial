/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para ArraysVectores.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 */

#include "arraysvectores_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void on_outputs(double t, const ArraysVectores_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->suma_real) { ... } */
    /* if (out->suma_int) { ... } */
    /* if (out->v_doble_1) { ... } */
    /* if (out->v_doble_2) { ... } */
    /* if (out->v_doble_3) { ... } */
    /* if (out->v_doble_4) { ... } */
    /* if (out->alguno_true) { ... } */
}
