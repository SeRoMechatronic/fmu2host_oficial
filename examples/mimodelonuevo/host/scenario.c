/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para Mi_Modelo_Nuevo.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "mi_modelo_nuevo_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, Mi_Modelo_Nuevo_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->flag_activo = ...; */
    /* in->entrada_principal = ...; */
}

void on_outputs(double t, const Mi_Modelo_Nuevo_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->flag_salida) { ... } */
    /* if (out->salida_filtrada) { ... } */
}
