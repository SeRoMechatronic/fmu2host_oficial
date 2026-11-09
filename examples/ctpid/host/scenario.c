/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para CTPID.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "ctpid_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, CTPID_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->consigna = ...; */
    /* in->temperatura = ...; */
}

void on_outputs(double t, const CTPID_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->ledalcanzado) { ... } */
    /* if (out->ledpordebajo) { ... } */
    /* if (out->ledporencima) { ... } */
    /* if (out->ventilador) { ... } */
}
