/**
 * @file   scenario.c
 * @brief  Escenario de simulacion para EtapaSecuenciador.
 *
 *  UNICO archivo que debes editar.
 *  Ajusta get_config() para cambiar tiempo y paso de simulacion.
 *  Ajusta get_inputs() para proporcionar entradas en cada instante t.
 */

#include "etapasecuenciador_api.h"

SimConfig get_config(void)
{
    return (SimConfig){
        .t_end   = 1.0,
        .h       = 0.01,
        .use_rk4 = 0,
    };
}

void get_inputs(double t, EtapaSecuenciador_Inputs *in)
{
    (void)t;
    /* Ajusta las entradas segun tu escenario: */
    /* in->sensor_confirmacion = ...; */
    /* in->arrancar = ...; */
    /* in->parar = ...; */
}

void on_outputs(double t, const EtapaSecuenciador_Outputs *out)
{
    (void)t;
    /* Reacciona a las salidas del modelo: */
    /* if (out->progreso_etapa) { ... } */
    /* if (out->etapa_actual) { ... } */
    /* if (out->etapa_previa) { ... } */
    /* if (out->secuencia_completa) { ... } */
}
