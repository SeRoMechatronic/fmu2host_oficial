/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para ReguladorBateria.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "reguladorbateria_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, ReguladorBateria_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->carga_conectada = ...; */
    /* in->tension_bateria = ...; */
}

void on_outputs(double t, const ReguladorBateria_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->carga_completa) { ... } */
    /* if (out->cargando) { ... } */
    /* if (out->fallo_sobretension) { ... } */
    /* if (out->corriente_carga) { ... } */
}
