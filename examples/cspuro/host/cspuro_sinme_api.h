/**
 * @file   cspuro_sinme_api.h
 * @brief  API de simulacion para CSPuro_SinME.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef CSPURO_SINME_API_H
#define CSPURO_SINME_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    double           u1;   /**< Real input 'u1' */
    double           u2;   /**< Real input 'u2' */
} CSPuro_SinME_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    int              active;   /**< Boolean output 'active' */
    double           y_prod;   /**< Real output 'y_prod' */
    double           y_sum;   /**< Real output 'y_sum' */
} CSPuro_SinME_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, CSPuro_SinME_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const CSPuro_SinME_Outputs *out);

#endif /* CSPURO_SINME_API_H */
