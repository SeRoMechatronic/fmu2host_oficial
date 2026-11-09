/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para ContadorEventos.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "contadoreventos_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, ContadorEventos_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->evento = ...; */
    /* in->reset = ...; */
}

void on_outputs(double t, const ContadorEventos_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->cuenta) { ... } */
    /* if (out->decenas) { ... } */
    /* if (out->desbordamiento) { ... } */
    /* if (out->unidades) { ... } */
}
