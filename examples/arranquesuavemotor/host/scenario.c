/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para ArranqueSuaveMotor.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "arranquesuavemotor_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, ArranqueSuaveMotor_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->orden_arranque = ...; */
    /* in->carga_motor = ...; */
}

void on_outputs(double t, const ArranqueSuaveMotor_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->en_rampa) { ... } */
    /* if (out->fallo_sobrecarga) { ... } */
    /* if (out->motor_en_marcha) { ... } */
    /* if (out->tension_aplicada) { ... } */
}
