/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para CodigoErrorDiagnostico.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "codigoerrordiagnostico_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, CodigoErrorDiagnostico_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->temperatura = ...; */
    /* in->tension = ...; */
    /* in->vibracion = ...; */
}

void on_outputs(double t, const CodigoErrorDiagnostico_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->factor_reduccion) { ... } */
    /* if (out->codigo_error) { ... } */
    /* if (out->parada_emergencia) { ... } */
    /* if (out->nivel_prioridad) { ... } */
}
