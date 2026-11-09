/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para BooleanLogica.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "booleanlogica_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, BooleanLogica_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->umbral = ...; */
    /* in->a = ...; */
    /* in->b = ...; */
    /* in->clk = ...; */
}

void on_outputs(double t, const BooleanLogica_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->cuenta_flancos) { ... } */
    /* if (out->above_threshold) { ... } */
    /* if (out->y_and) { ... } */
    /* if (out->y_latch) { ... } */
    /* if (out->y_or) { ... } */
    /* if (out->y_xor) { ... } */
}
