/**
 * @file   tiposmixtos_api.h
 * @brief  API de simulacion para TiposMixtos.
 *
 *  Define los structs de entrada/salida y la configuracion de simulacion.
 *  Implementa get_config() y get_inputs() en scenario.c.
 *
 * @note  AUTO-GENERADO por fmu_codegen_host.py. No editar manualmente.
 */

#ifndef TIPOSMIXTOS_API_H
#define TIPOSMIXTOS_API_H

/** Configuracion de la simulacion. Devuelta por get_config(). */
typedef struct {
    double t_end;    /**< Tiempo final de simulacion (s) */
    double h;        /**< Paso de integracion (s) */
    int    use_rk4;  /**< 0 = Euler, 1 = RK4 (solo modelos con estados continuos) */
} SimConfig;

/** Entradas del modelo en cada instante t. Devuelta por get_inputs(). */
typedef struct {
    int              i_in;   /**< Integer input 'i_in' */
    int              b_in;   /**< Boolean input 'b_in' */
    double           r_in;   /**< Real input 'r_in' */
} TiposMixtos_Inputs;

/** Salidas del modelo en cada instante t. */
typedef struct {
    double           r_abs;   /**< Real output 'r_abs' */
    int              i_out;   /**< Integer output 'i_out' */
    int              b_out;   /**< Boolean output 'b_out' */
    double           r_out;   /**< Real output 'r_out' */
} TiposMixtos_Outputs;

/** Devuelve la configuracion de la simulacion. Definir en scenario.c. */
SimConfig get_config(void);

/** Rellena las entradas en el instante t. Definir en scenario.c. */
void get_inputs(double t, TiposMixtos_Inputs *in);

/** Llamada tras leer las salidas en cada paso. Definir en scenario.c. */
void on_outputs(double t, const TiposMixtos_Outputs *out);

#endif /* TIPOSMIXTOS_API_H */
