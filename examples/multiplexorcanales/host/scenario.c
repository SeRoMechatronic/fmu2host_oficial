/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para MultiplexorCanales.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "multiplexorcanales_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, MultiplexorCanales_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->canal_0 = ...; */
    /* in->canal_1 = ...; */
    /* in->canal_seleccion = ...; */
    /* in->canal_2 = ...; */
    /* in->canal_3 = ...; */
}

void on_outputs(double t, const MultiplexorCanales_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->canal_activo) { ... } */
    /* if (out->canal_valido) { ... } */
    /* if (out->salida) { ... } */
}
