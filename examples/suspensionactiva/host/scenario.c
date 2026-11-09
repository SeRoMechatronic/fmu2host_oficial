/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para SuspensionActiva.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "suspensionactiva_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, SuspensionActiva_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->perfil_bache = ...; */
    /* in->velocidad_vehiculo = ...; */
}

void on_outputs(double t, const SuspensionActiva_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->actuador_saturado) { ... } */
    /* if (out->bache_detectado) { ... } */
    /* if (out->modo_confort) { ... } */
    /* if (out->fuerza_actuador) { ... } */
}
