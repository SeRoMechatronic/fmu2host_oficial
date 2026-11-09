/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para FrenadoABS.
 *  UNICO archivo que debes editar.
 */

#include "frenadoabs_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 20,
        .h       = 0.01,
        .use_rk4 = 1,
    };
}

void get_inputs(double t, FrenadoABS_Inputs *in)
{
    (void)t;
    in->presion_pedal   = 0.9;
    in->velocidad_rueda = 0.9;
}

void on_outputs(double t, const FrenadoABS_Outputs *out)
{
    (void)t;
    /* if (out->abs_activo) { ... } */
    /* if (out->frenado_normal) { ... } */
    /* if (out->rueda_bloqueada) { ... } */
    /* if (out->presion_modulada) { ... } */
}

