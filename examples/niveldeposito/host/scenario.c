/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para NivelDeposito.
 *  UNICO archivo que debes editar.
 */

#include "niveldeposito_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 10.01,
        .h       = 0.01,
        .use_rk4 = 1,
    };
}

void get_inputs(double t, NivelDeposito_Inputs *in)
{
    (void)t;
    /* in->valvula_manual = ...; */
    /* in->sensor_nivel = ...; */
}

void on_outputs(double t, const NivelDeposito_Outputs *out)
{
    (void)t;
    /* if (out->alarma_maximo) { ... } */
    /* if (out->alarma_minimo) { ... } */
    /* if (out->bomba_activa) { ... } */
    /* if (out->bomba) { ... } */
}
